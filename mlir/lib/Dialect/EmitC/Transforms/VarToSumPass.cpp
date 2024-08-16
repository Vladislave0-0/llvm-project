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
struct VarToSumPass : public emitc::impl::VarToSumBase<VarToSumPass> {

  void runOnOperation() override {
    Operation *rootOp = getOperation();

    // for (Region &region : rootOp->getRegions()) {
    //   for (Block &block : region.getBlocks()) {
    //     for (Operation &operation : block.getOperations()) {
    //       if (isa<emitc::VariableOp>(operation)) {
    //         llvm::outs() << "here";
    //         auto variable = dyn_cast<emitc::VariableOp>(operation);
    //         if (variable.getType().isInteger(32)) {
    //           replaceVariableWithSum(variable, rootOp);
    //           variable->erase();
    //         }
    //       } else {
    //         llvm::outs() << "no\n";
    //         llvm::outs() << operation.getName();
    //       }
    //     }
    //   }
    // }
    WalkResult result = rootOp->walk([&](emitc::VariableOp variable) {
      if (variable.getType().isInteger(32)) {
        replaceVariableWithSum(variable, rootOp);
        return WalkResult::interrupt();
      }
      return WalkResult::advance();
    });
  }

  void replaceVariableWithSum(emitc::VariableOp variable,
                              Operation *operationPtr) {
    OpBuilder builder(variable);
    builder.setInsertionPoint(variable);

    auto type = variable.getType();
    auto value = mlir::cast<IntegerAttr>(variable.getValue()).getInt();
    auto loc = variable.getLoc();

    auto part1 = builder.create<emitc::VariableOp>(
        loc, type, builder.getIntegerAttr(type, 0));

    builder.setInsertionPointAfter(variable);

    for (auto &use : variable.getResult().getUses()) {
      llvm::outs() << "Зашли в for()\n\n";
      Operation *userOp = use.getOwner();

      // Проверяем, находится ли использование в emitc.expression
      if (auto exprOp = userOp->getParentOfType<emitc::ExpressionOp>()) {
        llvm::outs() << "В emitc.expression\n\n";
        builder.setInsertionPoint(userOp);

        auto sum = builder.create<emitc::AddOp>(loc, type, part1,
                                                variable.getResult());
        userOp->setOperand(use.getOperandNumber(), sum.getResult());
      }

      // Если использование в emitc.return
      else if (isa<emitc::ReturnOp, emitc::YieldOp>(userOp)) {
        llvm::outs() << "В return\n\n";

        builder.setInsertionPoint(userOp);

        auto sum = builder.create<emitc::AddOp>(loc, type, part1,
                                                variable.getResult());
        userOp->setOperand(0, sum.getResult());
      }

      // Если не находится в emitc.expression, то оборачиваем в него
      else {
        llvm::outs() << "Не в emitc.expression\n\n";

        builder.setInsertionPointAfter(userOp);
        auto expression = builder.create<emitc::ExpressionOp>(loc, type);
        Region &region = expression.getRegion();
        Block &block = region.emplaceBlock();
        builder.setInsertionPointToStart(&block);

        auto sum = builder.create<emitc::AddOp>(loc, type, part1,
                                                variable.getResult());
        auto newOp = builder.clone(*userOp);

        newOp->setOperand(use.getOperandNumber(), sum.getResult());
        builder.create<emitc::YieldOp>(loc, newOp->getResult(0));
        userOp->replaceAllUsesWith(expression);

        userOp->erase();

        // vectorOps.push_back(userOp);
        // for (auto &use : userOp->getUses())
        //   use.getOwner()->replaceUsesOfWith(userOp->getResult(0),
        //   expression->getResult(0));

        // userOp->erase();
        // userOp->dropAllReferences();
      }

      if (variable.use_empty()) {
        llvm::outs() << "Variable empty\n\n";
      }
    }
  }

  void getDependentDialects(DialectRegistry &registry) const override {
    registry.insert<emitc::EmitCDialect>();
  }
};
} // namespace

std::unique_ptr<Pass> mlir::emitc::createVarToSumPass() {
  return std::make_unique<VarToSumPass>();
}

// #include "mlir/Dialect/EmitC/IR/EmitC.h"
// #include "mlir/Dialect/EmitC/Transforms/Passes.h"
// #include "mlir/Dialect/EmitC/Transforms/Transforms.h"
// #include "mlir/IR/IRMapping.h"
// #include "mlir/IR/PatternMatch.h"
// #include "mlir/Transforms/GreedyPatternRewriteDriver.h"
// #include "llvm/Support/Debug.h"

// namespace mlir {
// namespace emitc {
// #define GEN_PASS_DEF_VARTOSUM
// #include "mlir/Dialect/EmitC/Transforms/Passes.h.inc"
// } // namespace emitc
// } // namespace mlir

// using namespace mlir;
// using namespace emitc;

// namespace {
// struct VarToSumPass : public emitc::impl::VarToSumBase<VarToSumPass> {

//   void runOnOperation() override {
//     Operation *rootOp = getOperation();

//     rootOp->walk([&](emitc::VariableOp variable) {
//       if (variable.getType().isInteger(32)) {
//         replaceVariableWithSum(variable, rootOp);

//         // variable.getResult().replaceAllUsesWith({});
//         // variable->erase();
//       }
//     });
//   }

//   void replaceVariableWithSum(emitc::VariableOp variable,
//                               Operation *operationPtr) {
//     OpBuilder builder(variable);
//     builder.setInsertionPointAfter(variable);

//     auto type = variable.getType();
//     auto value = mlir::cast<IntegerAttr>(variable.getValue()).getInt();
//     auto loc = variable.getLoc();

//     auto part1 = builder.create<emitc::VariableOp>(
//         loc, type, builder.getIntegerAttr(type, 0));
//     auto part2 = builder.create<emitc::VariableOp>(
//         loc, type, builder.getIntegerAttr(type, value));

//     SmallVector<Operation *> vectorOps;

//     for (;iteratorUses != iteratopUsesEnd;) {

//       llvm::outs() << "Зашли в for()\n\n";
//       Operation *userOp = (*iteratorUses).getOwner();

//       // Проверяем, находится ли использование в emitc.expression
//       if (auto exprOp = userOp->getParentOfType<emitc::ExpressionOp>()) {
//         llvm::outs() << "В emitc.expression\n\n";
//         builder.setInsertionPoint(userOp);

//         auto sum = builder.create<emitc::AddOp>(loc, type, part1, part2);
//         userOp->setOperand((*iteratorUses).getOperandNumber(),
//         sum.getResult());
//       }

//       // Если использование в emitc.return
//       else if (isa<emitc::ReturnOp, emitc::YieldOp>(userOp)) {
//         llvm::outs() << "В return\n\n";

//         builder.setInsertionPoint(userOp);

//         auto sum = builder.create<emitc::AddOp>(loc, type, part1, part2);
//         userOp->setOperand(0, sum.getResult());
//       }

//       // Если не находится в emitc.expression, то оборачиваем в него
//       else {
//         llvm::outs() << "Не в emitc.expression\n\n";

//         builder.setInsertionPointAfter(userOp);
//         auto expression = builder.create<emitc::ExpressionOp>(loc, type);
//         Region &region = expression.getRegion();
//         Block &block = region.emplaceBlock();
//         builder.setInsertionPointToStart(&block);

//         auto sum = builder.create<emitc::AddOp>(loc, type, part1, part2);
//         auto newOp = builder.clone(*userOp);

//         newOp->setOperand((*iteratorUses).getOperandNumber(),
//         sum.getResult()); builder.create<emitc::YieldOp>(loc,
//         newOp->getResult(0)); userOp->replaceAllUsesWith(expression);

//         iteratorUses++;
//         userOp->erase();

//         // vectorOps.push_back(userOp);
//         // for (auto &use : userOp->getUses())
//         //   use.getOwner()->replaceUsesOfWith(userOp->getResult(0),
//         //   expression->getResult(0));

//         // userOp->erase();
//         // userOp->dropAllReferences();
//       }

//       if (variable.use_empty()) {
//         variable.erase();
//         llvm::outs() << "Variable empty\n\n";
//       }
//     }
//   }

//   void getDependentDialects(DialectRegistry &registry) const override {
//     registry.insert<emitc::EmitCDialect>();
//   }
// };
// } // namespace

// std::unique_ptr<Pass> mlir::emitc::createVarToSumPass() {
//   return std::make_unique<VarToSumPass>();
// }
