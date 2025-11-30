# Mini Compiler – Frontend Module
Team Lead: Palak

This repository contains the frontend structure of our Mini Compiler project.
Each team member uploads work only in their assigned folders.  
The structure is modular and organized for easy integration and testing.

---

## 1. Project Structure

src/  
│  
├── 1-language-spec/  
│      Language specification files (Sonali)  
│  
├── 2-lexer/  
│      Lexer implementation in C++  
│      Generates tokens_output.txt  
│  
├── 3-parser/  
│      Parser implementation in C++  
│      Generates parse_output.txt  
│  
├── 4-lexer-testing/  
│      Lexer test cases and invalid program checks  
│  
├── 5-parser-testing/  
│      Parser test cases and syntax validation  
│  
└── README.md

---

## 2. Updated Team Responsibilities

### Language Designer (Completed)
**Sonali**  
- Defines keywords, operators, symbols  
- Provides sample programs  
- Uploads: language_spec.txt, specification PDF  
- Folder: `src/1-language-spec/`

---

## Lexer Team

### Lexer Developer (Main C++ Coding)  
**Palak**  
- Writes `lexer.cpp`  
- Implements token generation  
- Produces `tokens_output.txt`  
- Folder: `src/2-lexer/`

### Lexer Support + Token Testing  
**Ujjawal**  
- Tests lexer using valid & invalid programs  
- Maintains token test cases  
- Reports lexical errors  
- Folder: `src/4-lexer-testing/`

---

## Parser Team

### Parser Developer (Main C++ Coding)  
**Sooryanshi**  
- Writes `parser.cpp`  
- Implements recursive descent parsing  
- Generates `parse_output.txt`  
- Folder: `src/3-parser/`

### Parser Support + Syntax Testing  
**Vidushi**  
- Designs grammar along with parser developer  
- Tests parser with valid + invalid syntax cases  
- Reports grammar/syntax issues  
- Folder: `src/5-parser-testing/`

---

## 3. Contribution Rules

1. Upload files only inside your assigned folder.  
2. Do not change other team folders.  
3. Use clear and meaningful commit messages.  
4. Maintain clean and commented code.  
5. Main branch remains stable.

---

## 4. Build & Run (For Developers Only)

### Lexer
Compile:
