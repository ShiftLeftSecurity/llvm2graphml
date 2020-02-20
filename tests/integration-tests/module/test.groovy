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

dump(g.V().hasLabel('module').valueMap('moduleIdentifier'))
// CHECK: moduleIdentifier=[main.ll]

dump(g.V().hasLabel('module').out('function').valueMap('name'))
// CHECK-NEXT: name=[helloWorld]

dump(g.V().hasLabel('function').valueMap('name'))
// CHECK-NEXT: name=[helloWorld]

dump(g.V().hasLabel('function').out('module').valueMap('moduleIdentifier'))
// CHECK-NEXT: moduleIdentifier=[main.ll]

dump(g.V().hasLabel('module', 'function').count())
// CHECK-NEXT: 2

:exit
// CHECK-EMPTY: