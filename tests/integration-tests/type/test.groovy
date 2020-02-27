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

dump(g.V().hasLabel('type').order().by('typeID', asc).valueMap('typeID').dedup())
// CHECK-NEXT: typeID=[float]
// CHECK-NEXT: typeID=[function]
// CHECK-NEXT: typeID=[integer]
// CHECK-NEXT: typeID=[label]
// CHECK-NEXT: typeID=[pointer]
// CHECK-NEXT: typeID=[struct]
// CHECK-NEXT: typeID=[void]

dump(g.V().has('type', 'typeID', 'integer').order().by('bitwidth', asc).valueMap('bitwidth').dedup())
// CHECK-NEXT: bitwidth=[1]
// CHECK-NEXT: bitwidth=[32]

dump(g.V().has('type', 'typeID', 'pointer').outE('pointeeType').inV().order().by('typeID', asc).valueMap('typeID').dedup())
// CHECK-NEXT: typeID=[function]
// CHECK-NEXT: typeID=[integer]
// CHECK-NEXT: typeID=[struct]

dump(g.V().has('type', 'typeID', 'function').outE('returnType').inV().order().by('typeID', asc).valueMap('typeID').dedup())
// CHECK-NEXT: typeID=[integer]
// CHECK-NEXT: typeID=[void]

dump(g.V().has('type', 'typeID', 'function').outE('parameterType').has('order', 0).inV().order().by('typeID', asc).valueMap('typeID').dedup())
// CHECK-NEXT: typeID=[integer]
// CHECK-NEXT: typeID=[pointer]

dump(g.V().has('type', 'typeID', 'struct').valueMap('name'))
// CHECK-NEXT: name=[struct.Foo]

dump(g.V().has('type', 'typeID', 'struct').outE('elementType').has('order', 0).inV().valueMap('typeID'))
// CHECK-NEXT: typeID=[integer]

dump(g.V().has('type', 'typeID', 'struct').outE('elementType').has('order', 1).inV().valueMap('typeID'))
// CHECK-NEXT: typeID=[float]

dump(g.V().has('function', 'name', 'abs').outE('argument').inV().outE('type').inV().order().by('typeID', asc).valueMap('typeID').dedup())
// CHECK-NEXT: typeID=[integer]

:exit
// CHECK-EMPTY: