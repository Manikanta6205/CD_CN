import ply.lex as lex
import ply.yacc as yacc
from graphviz import Digraph

# ---------- Lexer ----------
tokens = ('NUMBER',)
literals = ['+', '-', '*', '/', '(', ')']
t_ignore = ' \t\n'

def t_NUMBER(t):
    r'\d+'
    t.value = int(t.value)
    return t

def t_error(t):
    print(f"Illegal character '{t.value[0]}'")
    t.lexer.skip(1)

lexer = lex.lex()

# ---------- AST Classes ----------
class ASTNode:
    pass

class BinOp(ASTNode):
    def __init__(self, left, op, right):
        self.left = left
        self.op = op
        self.right = right
    def __repr__(self):
        return f"({self.left} {self.op} {self.right})"

class Num(ASTNode):
    def __init__(self, value):
        self.value = value
    def __repr__(self):
        return str(self.value)

# ---------- Convert BNF to YACC (optional helper) ----------
def bnf_to_yacc(bnf_grammar):
    rules = {}
    for line in bnf_grammar.splitlines():
        if '::=' not in line:
            continue
        left, right = line.split('::=')
        rules[left.strip()] = right.strip()
    return rules

# ---------- Parser ----------
def generate_parser(yacc_rules):
    def p_expr(p):
        '''expr : expr '+' term
                | expr '-' term
                | term'''
        if len(p) == 4:
            p[0] = BinOp(p[1], p[2], p[3])
        else:
            p[0] = p[1]

    def p_term(p):
        '''term : term '*' factor
                | term '/' factor
                | factor'''
        if len(p) == 4:
            p[0] = BinOp(p[1], p[2], p[3])
        else:
            p[0] = p[1]

    def p_factor(p):
        '''factor : '(' expr ')'
                  | NUMBER'''
        if p[1] == '(':
            p[0] = p[2]
        else:
            p[0] = Num(p[1])

    def p_error(p):
        print("Syntax error!")

    return yacc.yacc()

# ---------- AST → GraphViz ----------
def ast_to_graph(node, graph=None, counter=[0]):
    if graph is None:
        graph = Digraph()
        graph.attr('node', shape='circle')

    counter[0] += 1
    node_id = str(counter[0])

    if isinstance(node, BinOp):
        graph.node(node_id, node.op)
        left_id = ast_to_graph(node.left, graph, counter)
        right_id = ast_to_graph(node.right, graph, counter)
        graph.edge(node_id, left_id)
        graph.edge(node_id, right_id)
    elif isinstance(node, Num):
        graph.node(node_id, str(node.value))
    else:
        graph.node(node_id, "?")

    return node_id

# ---------- Main ----------
def main():
    print("Enter your BNF grammar (end with an empty line):")
    lines = []
    while True:
        line = input()
        if line.strip() == '':
            break
        lines.append(line)
    bnf_grammar = '\n'.join(lines)

    yacc_rules = bnf_to_yacc(bnf_grammar)
    print("Converted YACC rules:")
    print(yacc_rules)

    parser = generate_parser(yacc_rules)

    print("\nEnter arithmetic expressions (type 'exit' to quit):")
    while True:
        try:
            expr_input = input('>>> ')
            if expr_input.lower() == 'exit':
                break
            result = parser.parse(expr_input)
            print("AST:", result)
            # Generate AST diagram
            dot = Digraph()
            ast_to_graph(result, dot)
            dot.render('ast_tree', format='png', cleanup=True)
            print("AST diagram saved as ast_tree.png")
        except Exception as e:
            print("Error:", e)

if __name__ == '__main__':
    main()
