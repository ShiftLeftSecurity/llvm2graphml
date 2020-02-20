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

dump(g.V().hasLabel('function').valueMap('name'))
// CHECK: name=[abs]

dump(g.V().hasLabel('function').has('name', 'abs').valueMap('basicBlockCount'))
// CHECK-NEXT: basicBlockCount=[4]

dump(g.V().hasLabel('basicBlock').count())
// CHECK-NEXT: 4

dump(g.V().hasLabel('basicBlock').out('module').valueMap('moduleIdentifier').dedup())
// CHECK-NEXT: moduleIdentifier=[main.ll]

dump(g.V().hasLabel('basicBlock').out('function').valueMap('name').dedup())
// CHECK-NEXT: name=[abs]


// Entry

dump(g.V().hasLabel('basicBlock').has('name', '').count())
// CHECK-NEXT: 1

dump(g.V().hasLabel('basicBlock').has('name', '').valueMap('instructionCount'))
// CHECK-NEXT: instructionCount=[3]

dump(g.V().hasLabel('basicBlock').has('name', '').out('predecessor').count())
// CHECK-NEXT: 0

dump(g.V().hasLabel('basicBlock').has('name', '').out('predecessor').valueMap('name'))
// empty

dump(g.V().hasLabel('basicBlock').has('name', '').out('successor').count())
// CHECK-NEXT: 2

dump(g.V().hasLabel('basicBlock').has('name', '').out('successor').order().by('name', asc).valueMap('name'))
// CHECK-NEXT: name=[else]
// CHECK-NEXT: name=[then]


// Then

dump(g.V().hasLabel('basicBlock').has('name', 'then').count())
// CHECK-NEXT: 1

dump(g.V().hasLabel('basicBlock').has('name', 'then').valueMap('instructionCount'))
// CHECK-NEXT: instructionCount=[3]

dump(g.V().hasLabel('basicBlock').has('name', 'then').out('predecessor').count())
// CHECK-NEXT: 1

dump(g.V().hasLabel('basicBlock').has('name', 'then').out('predecessor').valueMap('name'))
// CHECK-NEXT: name=[]

dump(g.V().hasLabel('basicBlock').has('name', 'then').out('successor').count())
// CHECK-NEXT: 1

dump(g.V().hasLabel('basicBlock').has('name', 'then').out('successor').valueMap('name'))
// CHECK-NEXT: name=[end]


// Else

dump(g.V().hasLabel('basicBlock').has('name', 'else').count())
// CHECK-NEXT: 1

dump(g.V().hasLabel('basicBlock').has('name', 'else').valueMap('instructionCount'))
// CHECK-NEXT: instructionCount=[2]

dump(g.V().hasLabel('basicBlock').has('name', 'else').out('predecessor').count())
// CHECK-NEXT: 1

dump(g.V().hasLabel('basicBlock').has('name', 'else').out('predecessor').valueMap('name'))
// CHECK-NEXT: name=[]

dump(g.V().hasLabel('basicBlock').has('name', 'else').out('successor').count())
// CHECK-NEXT: 1

dump(g.V().hasLabel('basicBlock').has('name', 'else').out('successor').valueMap('name'))
// CHECK-NEXT: name=[end]


// End

dump(g.V().hasLabel('basicBlock').has('name', 'end').count())
// CHECK-NEXT: 1

dump(g.V().hasLabel('basicBlock').has('name', 'end').valueMap('instructionCount'))
// CHECK-NEXT: instructionCount=[2]

dump(g.V().hasLabel('basicBlock').has('name', 'end').out('predecessor').count())
// CHECK-NEXT: 2

dump(g.V().hasLabel('basicBlock').has('name', 'end').out('predecessor').order().by('name', asc).valueMap('name'))
// CHECK-NEXT: name=[else]
// CHECK-NEXT: name=[then]

dump(g.V().hasLabel('basicBlock').has('name', 'end').out('successor').count())
// CHECK-NEXT: 0

dump(g.V().hasLabel('basicBlock').has('name', 'end').out('successor').valueMap('name'))
// empty


:exit
// CHECK-EMPTY: