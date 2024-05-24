import re

# Классы токенов
TOKEN_TYPES = {
    'TYPE': r'\b(?:void|int|float|long|char|double)\b',  # Типы данных
    'ID': r'[a-zA-Z_][a-zA-Z0-9_]*',  # Идентификатор
    'NUMBER': r'\d+',  # Число
    'OP': r'[\+\-]',  # Операторы сложения и вычитания
    'STAR': r'\*+',  # Одна или несколько звездочек
    'LPAREN': r'\(',  # Левая скобка
    'RPAREN': r'\)',  # Правая скобка
    'LBRACKET': r'\[',  # Левая квадратная скобка
    'RBRACKET': r'\]',  # Правая квадратная скобка
    'COMMA': r',',  # Запятая
    'SEMICOLON': r';'  # Точка с запятой
}


class Token:
    def __init__(self, type, value):
        self.type = type
        self.value = value

    def __repr__(self):
        return f'Token({self.type}, {repr(self.value)})'


def lex(input_string):
    tokens = []
    position = 0
    while position < len(input_string):
        match = None
        if input_string[position].isspace():
            position += 1
            continue
        for token_type, token_regex in TOKEN_TYPES.items():
            pattern = re.compile(token_regex)
            match = pattern.match(input_string, position)
            if match:
                token = Token(token_type, match.group(0))
                tokens.append(token)
                position = match.end(0)
                break
        if not match:
            raise SyntaxError(f'Unexpected character: {input_string[position]}')
    return tokens


class Parser:
    def __init__(self, tokens):
        self.tokens = tokens
        self.position = 0

    def parse(self):
        return self.function_declaration()

    def function_declaration(self):
        self.data_type()
        self.identifier()
        self.eat('LPAREN')
        self.parameter_list()
        self.eat('RPAREN')
        self.eat('SEMICOLON')
        return "Function declaration parsed successfully"

    def data_type(self):
        if self.current_token().type == 'TYPE':
            self.eat('TYPE')
        else:
            raise SyntaxError(f'Expected data type, found {self.current_token()}')

    def identifier(self):
        if self.current_token().type == 'ID':
            self.eat('ID')
        else:
            raise SyntaxError(f'Expected identifier, found {self.current_token()}')

    def parameter_list(self):
        if self.current_token().type == 'TYPE':
            self.parameter()
            while self.current_token().type == 'COMMA':
                self.eat('COMMA')
                self.parameter()

    def parameter(self):
        self.data_type()
        while self.current_token().type == 'STAR':
            self.eat('STAR')
        self.identifier()
        while self.current_token().type == 'LBRACKET':
            self.eat('LBRACKET')
            self.eat('NUMBER')
            self.eat('RBRACKET')

    def current_token(self):
        return self.tokens[self.position]

    def eat(self, token_type):
        if self.current_token().type == token_type:
            self.position += 1
        else:
            raise SyntaxError(f'Unexpected token: {self.current_token()}')

    def pretty_print_declaration(self):
        function_name = ''
        return_type = ''
        parameters = []

        i = 0
        while i < len(self.tokens):
            if tokens[i].type == 'TYPE':
                return_type = tokens[i].value
            elif tokens[i].type == 'ID' and not function_name:
                function_name = tokens[i].value
            elif tokens[i].type == 'LPAREN':
                i += 1
                while tokens[i].type != 'RPAREN':
                    parameter_type = ''
                    pointers = ''
                    arrays = []

                    while tokens[i].type == 'TYPE':
                        parameter_type += tokens[i].value + ' '
                        i += 1

                    while tokens[i].type == 'STAR':
                        pointers += tokens[i].value
                        i += 1

                    parameter_name = tokens[i].value
                    i += 1

                    while tokens[i].type == 'LBRACKET':
                        arrays.append(tokens[i + 1].value)
                        i += 2

                    parameters.append({
                        'type': parameter_type,
                        'name': parameter_name,
                        'pointers': pointers,
                        'arrays': arrays
                    })

                    if tokens[i].type == 'COMMA':
                        i += 1

            i += 1

        print()
        print(f"{return_type} {function_name}")
        print("параметры:")
        for parameter in parameters:
            if parameter['name'] != ']':
                print()
                print(f"тип: {parameter['type']}")
                print(f"идентификатор: {parameter['name']}")
                print(f"казатели: {parameter['pointers']}")
                print(f"квадратные скобки: {', '.join(parameter['arrays'])}")
                print()


input_string = input("Введите выражение: ")
tokens = lex(input_string)
print("\nTokens:", tokens)

parser = Parser(tokens)
try:
    result = parser.parse()
    parser.pretty_print_declaration()

    print("OK")
except SyntaxError as e:
    print("ERROR")
    print(e)
