//===- FormExpressions.cpp - Form C-style expressions --------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements a pass that forms EmitC operations modeling C operators
// into C-style expressions using the emitc.expression op.
//
//===----------------------------------------------------------------------===//

#include "mlir/Dialect/EmitC/IR/EmitC.h"
#include "mlir/Dialect/EmitC/Transforms/Passes.h"
#include "mlir/Dialect/EmitC/Transforms/Transforms.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"

namespace mlir {
namespace emitc {
#define GEN_PASS_DEF_FORMEXPRESSIONS
#include "mlir/Dialect/EmitC/Transforms/Passes.h.inc"
} // namespace emitc
} // namespace mlir

using namespace mlir;
using namespace emitc;

namespace {
struct FormExpressionsPass
    : public emitc::impl::FormExpressionsBase<FormExpressionsPass> {
  void runOnOperation() override {
    Operation *rootOp = getOperation();
    MLIRContext *context = rootOp->getContext();

    // Wrap each C operator op with an expression op.
    OpBuilder builder(context);
    auto matchFun = [&](Operation *op) {
      // if (op->hasTrait<OpTrait::emitc::CExpression>() &&
      //     !op->getParentOfType<emitc::ExpressionOp>() &&
      //     op->getNumResults() == 1)
      //   createExpression(op, builder);
      createWhile(op, builder);
    };
    rootOp->walk(matchFun);

    // Fold expressions where possible.
    // RewritePatternSet patterns(context);
    // populateExpressionPatterns(patterns);

    // if (failed(applyPatternsGreedily(rootOp, std::move(patterns))))
    //   return signalPassFailure();
  }

  void createWhile(Operation *op, OpBuilder &builder) {
    // return;
    auto loc = op->getLoc();
    builder.setInsertionPointAfter(op);

    const int64_t value = 0;
    Type i1Type = builder.getI1Type();
    emitc::LValueType i1LvalueTy = emitc::LValueType::get(i1Type);
    auto variable = builder.create<emitc::VariableOp>(
        loc, i1LvalueTy, builder.getIntegerAttr(i1Type, value));

    auto whileOp = builder.create<emitc::WhileOp>(loc, variable);

    Block *body = new Block();
    whileOp.getRegion().push_back(body);

    builder.setInsertionPointToStart(body);

    Type i32Type = builder.getIntegerType(32);
    Value constValue = builder.create<emitc::ConstantOp>(
        loc, i32Type, builder.getI32IntegerAttr(42));

    builder.create<emitc::YieldOp>(loc);
  }

  void getDependentDialects(DialectRegistry &registry) const override {
    registry.insert<emitc::EmitCDialect>();
  }
};
} // namespace

std::unique_ptr<Pass> mlir::emitc::createFormExpressionsPass() {
  return std::make_unique<FormExpressionsPass>();
}
