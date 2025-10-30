
from compiler.codegen import CodeGenDriver
from compiler.graph_builder import GraphDriver
from diagnostics.diagnostics import Diagnostics
def main():
    try:
        xml_program = ParseXML(filepath)
        graph = GraphDriver(xml_program)
        code = CodeGenDriver(graph)
    except Exception as ex:
        assert Diagnostics.is_error(ex), Diagnostics.is_error(ex)

    return code
