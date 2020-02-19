/**
; RUN: cd %p
; RUN: %LLVM2GRAPHML_EXEC --output=%t.xml main.ll
; RUN: %GREMLIN_CONSOLE_EXEC -e %s %t.xml | %FILECHECK_EXEC %s --match-full-lines
*/

/// Prepare

graph = TinkerGraph.open()
g = graph.traversal()
g.io(args[0]).read().iterate()

def dump(tr) {
  tr.unfold().sideEffect{println it}.iterate()
}

/// Assertions

dump(g.V().hasLabel('function').count())
// CHECK-NEXT: 3

dump(g.V().hasLabel('function').has('name', 'helloWorld').count())
// CHECK-NEXT: 1

dump(g.V().hasLabel('function').has('name', 'helloWorld').valueMap('isDeclaration'))
// CHECK-NEXT: isDeclaration=[false]

dump(g.V().hasLabel('function').has('name', 'helloWorld').valueMap('isVarArg'))
// CHECK-NEXT: isVarArg=[false]

dump(g.V().hasLabel('function').has('name', 'helloWorld').valueMap('argSize'))
// CHECK-NEXT: argSize=[4]

dump(g.V().hasLabel('function').has('name', 'helloWorld').valueMap('numOperands'))
// CHECK-NEXT: numOperands=[0]

dump(g.V().hasLabel('function').has('name', 'helloWorld').valueMap('instructionCount'))
// CHECK-NEXT: instructionCount=[1]

dump(g.V().hasLabel('function').has('name', 'helloWorld').valueMap('basicBlockCount'))
// CHECK-NEXT: basicBlockCount=[1]

dump(g.V().hasLabel('function').has('name', 'helloWorld').valueMap('isIntrinsic'))
// CHECK-NEXT: isIntrinsic=[false]

dump(g.V().hasLabel('function').has('name', 'helloWorldExt').count())
// CHECK-NEXT: 1

dump(g.V().hasLabel('function').has('name', 'helloWorldExt').valueMap('isDeclaration'))
// CHECK-NEXT: isDeclaration=[true]

dump(g.V().hasLabel('function').has('name', 'helloWorldExt').valueMap('isVarArg'))
// CHECK-NEXT: isVarArg=[true]

dump(g.V().hasLabel('function').has('name', 'helloWorldExt').valueMap('argSize'))
// CHECK-NEXT: argSize=[2]

dump(g.V().hasLabel('function').has('name', 'helloWorldExt').valueMap('numOperands'))
// CHECK-NEXT: numOperands=[0]

dump(g.V().hasLabel('function').has('name', 'helloWorldExt').valueMap('instructionCount'))
// CHECK-NEXT: instructionCount=[0]

dump(g.V().hasLabel('function').has('name', 'helloWorldExt').valueMap('basicBlockCount'))
// CHECK-NEXT: basicBlockCount=[0]

dump(g.V().hasLabel('function').has('name', 'helloWorldExt').valueMap('isIntrinsic'))
// CHECK-NEXT: isIntrinsic=[false]

dump(g.V().hasLabel('function').has('name', 'llvm.memcpy.i8').valueMap('isIntrinsic'))
// CHECK-NEXT: isIntrinsic=[true]

:exit
// CHECK-EMPTY: