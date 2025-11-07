# IRON Code Generation System

A flexible, graph-based code generation system for AMD's Ryzen AI NPU AIE programming using the IRON library.

## Overview

This system converts XML representations of IRON code into executable Python code through a two-stage process:

1. **GraphDriver**: Converts XML to semantic graph (GraphML)
2. **CodeGenerator**: Generates Python code from semantic graph

The system is designed to be **completely flexible** - no code patterns are hardcoded. All code generation is driven purely by graph structure traversal.

## Architecture

```
XML Input → GraphDriver → Semantic Graph → CodeGenerator → Python Code
```

### Key Components

- **main.py**: End-to-end orchestration (XML → Python)
- **GraphDriver.py**: XML parser and graph builder
- **CodeGenerator.py**: Graph traversal and code generation
- **passthrough.xml**: Example XML input
- **passthroughjit.py**: Reference implementation for validation

## Quick Start

### Basic Usage

```bash
# From the aiecad directory
cd aiecad_compiler
python main.py examples/passthrough/passthrough.xml

# Or from parent directory
python aiecad/main.py aiecad/examples/passthrough/passthrough.xml
```

This generates files in the same directory as the input XML:
- `<name>.graphml` - Semantic graph (for debugging/visualization)
- `generated_<name>.py` - Python code (ready to run)

### Examples

**Generate code only:**
```bash
python main.py examples/passthrough/passthrough.xml
```

**Generate and execute code:**
```bash
python main.py examples/passthrough/passthrough.xml --run
```

Output:
```
======================================================================
IRON Code Generation System
======================================================================

[1/2] Building semantic graph from XML...
      Input: passthrough.xml
      Output: passthrough.graphml
      Graph: 178 nodes, 206 edges
      Node types: 39 unique types

[2/2] Generating Python code from graph...
      Input: passthrough.graphml
      Output: generated_passthrough.py
      Generated: 85 lines of Python code

======================================================================
[SUCCESS] Code generation completed successfully!
======================================================================
```

## System Design

### GraphDriver Architecture

**11 Major Sections:**

1. **Node and Edge Management** - Core graph construction
2. **Symbol Table and Scope Management** - Variable/function scopes
3. **Main Build Process** - XML parsing orchestration
4. **Symbols Section Processing** - Imports, constants, types
5. **DataFlow Section Processing** - IRON runtime elements
6. **Method Chain and Call Processing** - Fluent API handling
7. **Function Processing** - Function definitions
8. **Statement Processing** - Assignments, assertions, comments
9. **Expression Processing** - Recursive expression trees
10. **Control Flow Processing** - If/else with branch separation
11. **CLI Entry Point** - Command-line interface

**Key Features:**
- Pure graph structure (no hardcoded logic)
- Complete information capture
- Flexible traversal
- Type-safe nodes and edges

### CodeGenerator Architecture

**11 Major Sections:**

1. **Graph Navigation and Code Emission** - Core utilities
2. **Main Code Generation Entry Point** - Process orchestration
3. **Symbols Section Processing** - Import generation
4. **Function Processing** - Function definitions
5. **Statement Processing** - Statement dispatch
6. **Expression Reconstruction** - Graph to Python syntax
7. **Call Reconstruction** - Method chains and function calls
8. **Statement-Specific Processors** - Assert, assign, etc.
9. **Type Definition Generation** - Numpy types
10. **DataFlow Generation** - IRON runtime code
11. **Control Flow Processing** - If/else and loops

**Key Features:**
- Pure graph traversal (no hardcoded patterns)
- Complete code generation
- Proper indentation management
- Expression reconstruction

## XML Schema

The XML format captures all code elements:

### Structure

```xml
<Module name="module_name">
  <Symbols>
    <Import name="numpy" alias="np"/>
    <Const name="N">4096</Const>
    <TypeAbstraction name="vector_ty">
      <!-- Type definition -->
    </TypeAbstraction>
  </Symbols>
  
  <DataFlow>
    <ObjectFifo name="of_in">
      <!-- ObjectFifo definition -->
    </ObjectFifo>
    <Runtime name="rt"/>
    <SequenceBlock>
      <!-- Operations -->
    </SequenceBlock>
  </DataFlow>
  
  <Function name="main" decorator="iron.device">
    <parameters>
      <param name="device_name"/>
    </parameters>
    <body>
      <!-- Function statements -->
    </body>
  </Function>
  
  <EntryPoint>
    <!-- if __name__ == "__main__" -->
  </EntryPoint>
</Module>
```

### Supported Elements

**Symbols:**
- Import (with optional alias)
- Const (constant values)
- TypeAbstraction (numpy types)

**DataFlow:**
- ObjectFifo (data buffers)
- Runtime (runtime operations)
- SequenceBlock (sequenced operations)
- Program (compiled program)
- Placer (placement strategy)

**Statements:**
- Assign (variable assignment)
- Assert (assertions with conditions)
- Call (function/method calls)
- If/Else (conditional branches)
- For (loops)
- Print (output)
- Comment (code comments)

**Expressions:**
- Variables (VarRef)
- Constants (ConstExpr)
- Binary operations (+, -, *, /, %)
- Comparisons (==, !=, <, >, <=, >=)
- Function calls
- Method calls
- Method chains (obj.method1().method2())
- Index expressions (arr[idx])

## Graph Structure

### Node Types

The semantic graph uses 39+ node types:

**Core:**
- Module, Section, Function, EntryPoint

**Symbols:**
- Import, Const, TypeAbstraction, TypeNode

**DataFlow:**
- ObjectFifo, Runtime, SequenceBlock, Program, Placer

**Statements:**
- Assign, Assert, Call, If, For, Print, Comment

**Expressions:**
- VarRef, ConstExpr, BinaryOp, ComparisonOp
- FunctionCall, MethodCall, IndexExpr

### Edge Types

Edges define relationships:

- `contains`: Structural containment
- `calls`: Function/method invocation
- `has_arg`: Function arguments
- `has_kwarg`: Keyword arguments
- `uses_type`: Type references
- `source`: Assignment source
- `condition`: Conditional expression
- `then`/`else`: Branch statements
- `nested_call`: Method chaining

## Code Generation Process

### Stage 1: XML → Graph

```python
from GraphDriver import GraphBuilder

builder = GraphBuilder("input.xml")
graph = builder.build()
```

**Process:**
1. Parse XML with lxml
2. Create Module node
3. Process Symbols section
4. Process DataFlow section
5. Process Functions
6. Process EntryPoint
7. Save to GraphML

### Stage 2: Graph → Python

```python
from CodeGenerator import CodeGenerator

generator = CodeGenerator("input.graphml")
code = generator.generate()
```

**Process:**
1. Load graph from GraphML
2. Find Module node
3. Generate imports
4. Generate type definitions
5. Generate DataFlow elements
6. Generate functions
7. Generate entry point
8. Return complete code

## Validation

The system achieves **100% functional accuracy** on the reference implementation:

- **Target**: passthroughjit.py (94 lines)
- **Generated**: generated_passthrough.py (85 lines)
- **Accuracy**: 100% (all logic, variables, method chains, arguments, branches, and comments correct)

### Validation Metrics

- Graph: 178 nodes, 206 edges, 39 node types
- All imports correct
- All type definitions correct
- All function signatures correct
- All method chains correct (including `of_in.cons().forward()`)
- All function arguments correct (including complex expressions)
- All control flow correct (if/else branches)
- All comments preserved

## Advanced Features

### Method Chaining

Handles complex method chains:

```python
of_out = of_in.cons().forward()
```

XML representation:
```xml
<source>
  <method_chain>
    <call>
      <method ref="of_in" name="cons"/>
    </call>
    <call>
      <method name="forward"/>
    </call>
  </method_chain>
</source>
```

### Complex Expressions

Handles nested expressions:

```python
assert N % line_size == 0, "N must be divisible by line_size"
```

XML representation:
```xml
<Assert>
  <condition>
    <comparison op="==">
      <left>
        <binary_op op="%">
          <left><var>N</var></left>
          <right><var>line_size</var></right>
        </binary_op>
      </left>
      <right><const>0</const></right>
    </comparison>
  </condition>
  <message>"N must be divisible by line_size"</message>
</Assert>
```

### Branch Separation

Uses distinct edge types for if/else branches:

- `then` edges: Statements in then branch
- `else` edges: Statements in else branch

This enables proper branch reconstruction without confusion.

## Extensibility

The system is designed to handle any IRON code pattern:

1. **Add new XML elements**: Create handler in GraphDriver
2. **Add new node types**: Define in graph structure
3. **Add new edge types**: Use in relationships
4. **Add new code patterns**: Implement in CodeGenerator

No hardcoded patterns means the system adapts to any structure.

## Debugging

### Visualize Graph

Use yEd or similar GraphML viewer:

```bash
# Generate graph
python main.py input.xml

# Open in yEd
yed input.graphml
```

### Inspect Graph

```python
import networkx as nx

graph = nx.read_graphml("input.graphml")
print(f"Nodes: {graph.number_of_nodes()}")
print(f"Edges: {graph.number_of_edges()}")

# Show node types
for node, data in graph.nodes(data=True):
    print(f"{node}: {data.get('kind')} - {data.get('label')}")
```

### Compare Output

```bash
# Generate code
python main.py passthrough.xml

# Compare with reference
diff generated_passthrough.py passthroughjit.py
```

## Requirements

- Python 3.7+
- lxml (XML parsing)
- networkx (graph structure)

Install dependencies:

```bash
pip install lxml networkx
```

## File Structure

```
AIECAD/
└── aiecad/                                    # Main package
    ├── __init__.py                            # Package initialization
    ├── main.py                                # Main entry point
    ├── README.md                              # This file
    │
    ├── generator/                             # Graph generation
    │   ├── __init__.py
    │   └── GraphDriver.py                     # XML → Graph converter
    │
    ├── codegen/                               # Code generation
    │   ├── __init__.py
    │   └── backends/                          # Generation backends
    │       ├── __init__.py
    │       └── CodeGenerator.py               # Graph → Python converter
    │
    └── examples/                              # Example programs
        ├── __init__.py
        └── passthrough/                       # Passthrough example
            ├── passthrough.xml                # XML input
            ├── passthroughjit.py             # Reference implementation
            ├── generated_passthrough.py       # Generated output
            └── passthrough.graphml            # Semantic graph
```

## Contributing

When extending the system:

1. Add XML elements to schema
2. Create graph nodes in GraphDriver
3. Add code generation in CodeGenerator
4. Test with reference implementation
5. Validate 100% accuracy

## License

Copyright © 2025 Brock Sorenson

## References

- IRON Library: https://github.com/Xilinx/mlir-aie
- AMD Ryzen AI NPU: https://www.amd.com/en/products/ryzen-ai
- NetworkX: https://networkx.org/
- GraphML: http://graphml.graphdrawing.org/

## Author

Brock Sorenson  
