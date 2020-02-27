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

// Entry

dump(g.V().hasLabel('basicBlock').has('name', 'entry').count())
// CHECK-NEXT: 1

dump(g.V().hasLabel('basicBlock').has('name', 'entry').valueMap('instructionCount'))
// CHECK-NEXT: instructionCount=[3]

dump(g.V().hasLabel('basicBlock').has('name', 'entry').out('instruction').count())
// CHECK-NEXT: 3

dump(g.V().hasLabel('basicBlock').has('name', 'entry').out('instruction').order().by('opcode', asc).valueMap('opcode'))
// CHECK-NEXT: opcode=[alloca]
// CHECK-NEXT: opcode=[br]
// CHECK-NEXT: opcode=[icmp]

dump(g.V().hasLabel('basicBlock').has('name', 'then').out('instruction').count())
// CHECK-NEXT: 3

dump(g.V().hasLabel('basicBlock').has('name', 'then').out('instruction').order().by('opcode', asc).valueMap('opcode'))
// CHECK-NEXT: opcode=[br]
// CHECK-NEXT: opcode=[store]
// CHECK-NEXT: opcode=[sub]

dump(g.V().hasLabel('basicBlock').has('name', 'else').out('instruction').count())
// CHECK-NEXT: 2

dump(g.V().hasLabel('basicBlock').has('name', 'else').out('instruction').order().by('opcode', asc).valueMap('opcode'))
// CHECK-NEXT: opcode=[br]
// CHECK-NEXT: opcode=[store]

dump(g.V().hasLabel('basicBlock').has('name', 'end').out('instruction').count())
// CHECK-NEXT: 2

dump(g.V().hasLabel('basicBlock').has('name', 'end').out('instruction').order().by('opcode', asc).valueMap('opcode'))
// CHECK-NEXT: opcode=[load]
// CHECK-NEXT: opcode=[ret]

dump(g.V().hasLabel('instruction').has('name').order().by('name', asc).valueMap('name'))
// CHECK-NEXT: name=[cmp]
// CHECK-NEXT: name=[rval]
// CHECK-NEXT: name=[tmp]
// CHECK-NEXT: name=[tmpSub]

dump(g.V().has('basicBlock', 'name', 'entry')
          .out('instruction').has('opcode', 'br')
          .outE('operand').has('order', 0).inV().valueMap('name'))
// CHECK-NEXT: name=[cmp]

dump(g.V().has('basicBlock', 'name', 'entry')
          .out('instruction').has('opcode', 'br')
          .outE('operand').has('order', 1).inV().valueMap('name'))
// CHECK-NEXT: name=[else]

dump(g.V().has('basicBlock', 'name', 'entry')
          .out('instruction').has('opcode', 'br')
          .outE('operand').has('order', 2).inV().valueMap('name'))
// CHECK-NEXT: name=[then]

dump(g.V().has('basicBlock', 'name', 'entry')
          .out('instruction').has('opcode', 'alloca')
          .out('operand').hasLabel('value').valueMap('kind'))
// CHECK-NEXT: kind=[constantInt]

dump(g.V().has('basicBlock', 'name', 'entry')
          .out('instruction').has('opcode', 'icmp')
          .outE('operand').has('order', 0).inV()
          .valueMap('name', 'kind').order().by(values))
// CHECK-NEXT: kind=[argument]
// CHECK-NEXT: name=[x]

:exit
// CHECK-EMPTY: