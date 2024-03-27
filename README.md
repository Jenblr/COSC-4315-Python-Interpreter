# A Basic Interpreter of Python Programs
# Authors: Jennifer Nguyen, Elinnoel Nunez
---
**INTRODUCTION:**
...

---
# Table of Contents
- Lexer
---
## Lexer Files:
- Lexer.h
- Lexer.cpp

**Lexer.h**
Purpose: This file defines the interface for the Lexer class, which is responsible for tokenizing Python code. This header file contains class declarations, enumerations, and function prototypes necessary for tokenization.

Contents: 
- TokenType: Enumerates token types like identifiers, keywords, and literals.
- Token: Represents a token with type and value.
- Lexer: Class for tokenizing Python code.

**Lexer.cpp**
Purpose: This file prepares the Python input code for processing by tokenizing the Python input. The program breaks down each item into individual tokens by running the following tokenization process:
1. The tokenize function iterates through the input Python code character by character.
2. It skips whitespace and comments to identify meaningful tokens.
3. For each character, it determines whether it's part of an identifier/keyword, a number, a string literal, or an operator.
4. It then reads the corresponding token using helper functions like readIdentifierOrKeyword, readNumber, readStringLiteral, or readOperator.
5. Each token is classified using the classifyToken function, which determines its type (e.g., identifier, keyword, operator, etc.).
6. The token (string value) is then pushed into the tokens vector.
7. Once the entire input code is processed, the tokens vector containing the tokenized representation of the Python code is returned.