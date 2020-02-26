# llvm2graphml

llvm2graphml is a tool that helps you explore [LLVM Bitcode](https://llvm.org/docs/BitCodeFormat.html) interactively using a graph database. 

## Installation

Get the latest binary from [here](https://github.com/ShiftLeftSecurity/llvm2graphml/releases) or build llvm2graphml yourself:

```
git clone https://github.com/ShiftLeftSecurity/llvm2graphml.git --recursive
mkdir build.dir; cd build.dir
cmake ../llvm2graphml
make
make install
```

## Usage

Take this file:

```llvm
; main.ll
define i32 @increment(i32 %x) {
  %result = add i32 %x, 1
  ret i32 %result
}
```

Convert it into [GraphML](http://graphml.graphdrawing.org):

```bash
> llvm2graphml --output-dir=/tmp main.ll
[llvm2graphml] [info] More details: /var/folders/pp/lt3pgm5971n1qw7pp2g_bmfr0000gn/T/llvm2graphml-77ed40.log
[llvm2graphml] [info] Loading main.ll
[llvm2graphml] [info] Saved result into /tmp/llvm.graphml.xml
[llvm2graphml] [info] Shutting down
```

The `/tmp/llvm.graphml.xml` now contains the graph version of the bitcode.

## Run queries

To follow the example you need to install [Gremlin Console](https://www.apache.org/dyn/closer.lua/tinkerpop/3.4.6/apache-tinkerpop-gremlin-console-3.4.6-bin.zip) from the [Apache TinkerPop](http://tinkerpop.apache.org) project.

Run the `gremlin.sh` to start the interactive session and load `/tmp/llvm.graphml.xml` into it.

```groovy
> gremlin-console/bin/gremlin.sh

         \,,,/
         (o o)
-----oOOo-(3)-oOOo-----
plugin activated: tinkerpop.server
plugin activated: tinkerpop.utilities
plugin activated: tinkerpop.tinkergraph
gremlin> 
gremlin> graph = TinkerGraph.open()
gremlin> g = graph.traversal()
gremlin> g.io("/tmp/llvm.graphml.xml").read()
```

List all modules:

```groovy
gremlin> g.V().hasLabel('module').valueMap().unfold()
==>moduleIdentifier=[main.ll]
```

List all functions:

```groovy
gremlin> g.V().hasLabel('function').valueMap().unfold()
==>argSize=[1]
==>basicBlockCount=[1]
==>name=[increment]
==>isDeclaration=[false]
==>isVarArg=[false]
==>isIntrinsic=[false]
==>numOperands=[0]
==>instructionCount=[2]
```

Count all the instructions:

```groovy
gremlin> g.V().hasLabel('instruction').groupCount().by('opcode').unfold()
==>ret=1
==>add=1
```

Explore the types:

```groovy
gremlin> g.V().hasLabel('type').valueMap().unfold()
==>type_id=[void_type]
==>type_id=[label_type]
==>type_id=[pointer_type]
==>type_id=[function_type]
==>type_id=[integer_type]
==>bitwidth=[32]
```

See more of those in the [Queries.md](Queries.md).

## Feature completeness

llvm2graphml is not feature complete and is in a very early stage. Properties of instructions and values are not there yet,
global variables and constants are also missing.

But we welcome contributions!

## Contributing

Please, look at the [CONTRIBUTING.md](CONTRIBUTING.md)

## License

[Apache 2](https://www.apache.org/licenses/LICENSE-2.0). See the [LICENSE](LICENSE) for more details.