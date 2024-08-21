#include "mlir/Dialect/EmitC/IR/EmitC.h"
#include "mlir/Dialect/EmitC/Transforms/Passes.h"
#include "mlir/Dialect/EmitC/Transforms/Transforms.h"
#include "mlir/IR/IRMapping.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"
#include "llvm/Support/Debug.h"

namespace mlir {
namespace emitc {
#define GEN_PASS_DEF_VARTOSUM
#include "mlir/Dialect/EmitC/Transforms/Passes.h.inc"
} // namespace emitc
} // namespace mlir

using namespace mlir;
using namespace emitc;

namespace {

/// 'VarToSumPass' converts `emitc.variable` operations containing
/// values of type `i32` to the sum of two new variables in all
/// places where the original variable is used.

struct VarToSumPass : public emitc::impl::VarToSumBase<VarToSumPass> {

  void runOnOperation() override {
    Operation *rootOp = getOperation();

    /// Collecting all `emitc::VariableOp` operations into a vector for
    /// subsequent processing. In the last intermediate version, this was
    /// exactly the error. `walk()` bypassed all operations in the pass in
    /// the form of a doubly linked list. Deleting a specific operation in
    /// pace deleted pointers to the next operation, which caused an error
    /// in the form of a signal 9.

    SmallVector<emitc::VariableOp> operationsVec, int32Vec;
    rootOp->walk([&](emitc::VariableOp operation) {
      operationsVec.push_back(operation);
    });

    for (auto &operation : operationsVec)
      if (operation.getType().isInteger(32)) {
        replaceVariableWithSum(operation);
        int32Vec.push_back(operation);
      }

    /// Deleting the original `emitc.variable` operations if they are no in use.
    for (auto &variable : int32Vec) {
      if (variable.use_empty()) {
        variable.erase();
      }
    }
  }

  /// The `replaceVariableWithSum` function does the main job of replacing
  /// a variable with the sum of two new variables. It creates two new variables
  /// corresponding to parts of the original value, and replaces all uses of the
  /// original variable with the sum of these two new variables.

  void replaceVariableWithSum(emitc::VariableOp variable) {
    OpBuilder builder(variable);
    builder.setInsertionPoint(variable);

    int value = mlir::cast<IntegerAttr>(variable.getValue()).getInt();
    int val1 = value / 2;

    auto type = variable.getType();
    auto loc = variable.getLoc();

    auto part1 = builder.create<emitc::VariableOp>(
        loc, type, builder.getIntegerAttr(type, val1));
    auto part2 = builder.create<emitc::VariableOp>(
        loc, type, builder.getIntegerAttr(type, value - val1));

    builder.setInsertionPointAfter(variable);

    for (auto &use :
         llvm::make_early_inc_range(variable.getResult().getUses())) {
      Operation *userOp = use.getOwner();

      Type UserType;
      if (userOp->getNumResults() > 0) {
        UserType = userOp->getResult(0).getType();
      } else {
        UserType = builder.getNoneType();
      }

      /// Processing operations that require the creation of an
      /// `emitc.expression`
      if (userOp->hasTrait<mlir::OpTrait::emitc::CExpression>() &&
          !userOp->getParentOfType<emitc::ExpressionOp>()) {
        builder.setInsertionPointAfter(userOp);

        auto expression = builder.create<emitc::ExpressionOp>(loc, UserType);

        Region &region = expression.getRegion();
        Block &block = region.emplaceBlock();
        builder.setInsertionPointToStart(&block);

        auto sum = builder.create<emitc::AddOp>(loc, type, part1, part2);
        auto newOp = builder.clone(*userOp);

        newOp->setOperand(use.getOperandNumber(), sum.getResult());
        builder.create<emitc::YieldOp>(loc, newOp->getResult(0));
        userOp->replaceAllUsesWith(expression);

        userOp->erase();
      }

      /// Handling other cases where the operation is part of an
      /// `emitc.expression`, or is `emitc.return`, `emitc.assign`, `emitc.call`
      /// or `emitc.call_opaque'.
      else if (userOp->getParentOfType<emitc::ExpressionOp>() ||
               isa<emitc::ReturnOp>(userOp) || isa<emitc::AssignOp>(userOp) ||
               isa<emitc::CallOp>(userOp) || isa<emitc::CallOpaqueOp>(userOp)) {
        builder.setInsertionPoint(userOp);
        auto sum = builder.create<emitc::AddOp>(loc, type, part1, part2);
        userOp->setOperand(use.getOperandNumber(), sum.getResult());
      }

      else {
        // llvm::outs() << "Unknown operation\n\n";
      }
    }
  }

  /// Registration of dependent dialects required for the operation of the pass.
  void getDependentDialects(DialectRegistry &registry) const override {
    registry.insert<emitc::EmitCDialect>();
  }
};
} // namespace

/// A function for creating an instance of the `VarToSumPass` pass.
std::unique_ptr<Pass> mlir::emitc::createVarToSumPass() {
  return std::make_unique<VarToSumPass>();
}

/// Operations that are currently counted in the pass:
/// emitc.yield               (emitc::YieldOp)
/// emitc.assign              (emitc::AssignOp)
/// emitc.cast                (emitc::CastOp)
/// emitc.return              (emitc::ReturnOp)
/// emitc.unary_plus          (emitc::UnaryPlusOp)
/// emitc.add                 (emitc::AddOp)
/// emitc.unary_minus         (emitc::UnaryMinusOp)
/// emitc.apply               (emitc::ApplyOp)
/// emitc.bitwise_and         (emitc::BitwiseAndOp)
/// emitc.bitwise_left_shift  (emitc::BitwiseLeftShiftOp)
/// emitc.bitwise_not         (emitc::BitwiseNotOp)
/// emitc.bitwise_or          (emitc::BitwiseOrOp)
/// emitc.bitwise_right_shift (emitc::BitwiseRightShiftOp)
/// emitc.bitwise_xor         (emitc::BitwiseXorOp)
/// emitc.sub                 (emitc::SubOp)
/// emitc.mul                 (emitc::MulOp)
/// emitc.div                 (emitc::DivOp)
/// emitc.logical_and         (emitc::LogicalAndOp)
/// emitc.logical_or          (emitc::LogicalOrOp)
/// emitc.logical_not         (emitc::LogicalNotOp)
/// emitc.rem                 (emitc::RemOp)
/// emitc.cmp                 (emitc::CmpOp)
/// emitc.conditional         (emitc::ConditionalOp)
/// emitc.for                 (emitc::ForOp)
/// emitc.if                  (emitc::IfOp)
/// emitc.switch              (emitc::SwitchOp)
/// emitc.call                (emitc::CallOp)
/// emitc.call_opaque         (emitc::CallOpaqueOp)
