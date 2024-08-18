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
/// values of type 'i32' to the sum of two new variables in all 
/// places where the original variable is used.

struct VarToSumPass : public emitc::impl::VarToSumBase<VarToSumPass> {

  void runOnOperation() override {
    Operation *rootOp = getOperation();

    /// Collecting all 'emitc::Variable O p` operations into a vector for 
    /// subsequent processing. In the last intermediate version, this was 
    /// exactly the error. walk() bypassed all operations in the pass in 
    /// the form of a doubly linked list. Deleting a specific operation in 
    /// pace deleted pointers to the next operation, which caused an error 
    /// in the form of a signal 9.

    SmallVector<emitc::VariableOp> variablesVec;
    rootOp->walk([&](emitc::VariableOp variable) { variablesVec.push_back(variable); });

    for (auto &variable : variablesVec)
      if (variable.getType().isInteger(32))
        replaceVariableWithSum(variable);
  }

  void replaceVariableWithSum(emitc::VariableOp variable) {
    OpBuilder builder(variable);
    builder.setInsertionPoint(variable);

    int value = mlir::cast<IntegerAttr>(variable.getValue()).getInt();
    int val1 = value / 2;

    auto type = variable.getType();
    auto loc = variable.getLoc();

    auto part1 = builder.create<emitc::VariableOp>(loc, type, builder.getIntegerAttr(type, val1));
    auto part2 = builder.create<emitc::VariableOp>(loc, type, builder.getIntegerAttr(type, value - val1));

    builder.setInsertionPointAfter(variable);

    /// Bypassing all uses of the original variable. The variable can either 
    /// already be used by an operation that is in etc, or used by a return 
    /// operation, or used by an operation that is not wrapped in emitc

    for (auto &use : variable.getResult().getUses()) {
      Operation *userOp = use.getOwner();

      if (userOp->getParentOfType<emitc::ExpressionOp>()) {
        builder.setInsertionPoint(userOp);

        auto sum = builder.create<emitc::AddOp>(loc, type, part1, part2);
        userOp->setOperand(use.getOperandNumber(), sum.getResult());
      }

      else if (isa<emitc::ReturnOp>(userOp)) {
        builder.setInsertionPoint(userOp);

        auto sum = builder.create<emitc::AddOp>(loc, type, part1, part2);
        userOp->setOperand(0, sum.getResult());
      }

      else {
        builder.setInsertionPointAfter(userOp);
        auto expression = builder.create<emitc::ExpressionOp>(loc, type);
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

      if (variable.use_empty()) {
        variable.erase();
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
