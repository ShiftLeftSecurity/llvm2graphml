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

dump(g.V().hasLabel('type').order().by('type_id', asc).valueMap('type_id').dedup())
// CHECK-NEXT: type_id=[float_type]
// CHECK-NEXT: type_id=[function_type]
// CHECK-NEXT: type_id=[integer_type]
// CHECK-NEXT: type_id=[label_type]
// CHECK-NEXT: type_id=[pointer_type]
// CHECK-NEXT: type_id=[struct_type]
// CHECK-NEXT: type_id=[void_type]

dump(g.V().has('type', 'type_id', 'integer_type').order().by('bitwidth', asc).valueMap('bitwidth').dedup())
// CHECK-NEXT: bitwidth=[1]
// CHECK-NEXT: bitwidth=[32]

dump(g.V().has('type', 'type_id', 'pointer_type').outE('pointee_type').inV().order().by('type_id', asc).valueMap('type_id').dedup())
// CHECK-NEXT: type_id=[function_type]
// CHECK-NEXT: type_id=[integer_type]
// CHECK-NEXT: type_id=[struct_type]

dump(g.V().has('type', 'type_id', 'function_type').outE('return_type').inV().order().by('type_id', asc).valueMap('type_id').dedup())
// CHECK-NEXT: type_id=[integer_type]
// CHECK-NEXT: type_id=[void_type]

dump(g.V().has('type', 'type_id', 'function_type').outE('parameter_type').has('order', 0).inV().order().by('type_id', asc).valueMap('type_id').dedup())
// CHECK-NEXT: type_id=[integer_type]
// CHECK-NEXT: type_id=[pointer_type]

dump(g.V().has('type', 'type_id', 'struct_type').valueMap('name'))
// CHECK-NEXT: name=[struct.Foo]

dump(g.V().has('type', 'type_id', 'struct_type').outE('element_type').has('order', 0).inV().valueMap('type_id'))
// CHECK-NEXT: type_id=[integer_type]

dump(g.V().has('type', 'type_id', 'struct_type').outE('element_type').has('order', 1).inV().valueMap('type_id'))
// CHECK-NEXT: type_id=[float_type]

dump(g.V().has('function', 'name', 'abs').outE('argument').inV().outE('type').inV().order().by('type_id', asc).valueMap('type_id').dedup())
// CHECK-NEXT: type_id=[integer_type]

:exit
// CHECK-EMPTY: