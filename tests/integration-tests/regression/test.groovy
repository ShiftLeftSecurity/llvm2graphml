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

dump(g.V().has('function', 'name', '-[Shape square]').valueMap('name'))
// CHECK: name=[-[Shape square]]

dump(g.V().has('type', 'type_id', 'struct_type').valueMap('name'))
// CHECK: name=[struct.std::_Rb_tree<std::__cxx11::basic_string<char>>::_Rb_tree_impl]

:exit
// CHECK-EMPTY: