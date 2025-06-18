# Minishell - 42 Project

[![English](https://img.shields.io/badge/English-blue.svg)](./READMEen.md)
[![Français](https://img.shields.io/badge/Français-gray.svg)](./README.md)

## 📋 Table of Contents

- [Overview](#-overview)
- [Features](#-features)
- [Architecture](#-architecture)
- [Installation](#-installation)
- [Usage](#-usage)
- [Supported Commands](#-supported-commands)
- [Signal Handling](#-signal-handling)
- [Examples](#-examples)
- [Dependencies](#-dependencies)
- [Development](#-development)
- [Tests](#-tests)
- [Documentation](#-documentation)
- [Contributors](#-contributors)
- [License](#-license)

## 🚀 Overview

Minishell is a simplified implementation of a Unix shell, developed as part of the 42 school curriculum. This project applies advanced system programming concepts in C, including process management, signals, redirections, and pipes.

This shell allows you to execute commands, manage the system environment, and use essential features like redirections and pipes, while providing a user experience similar to standard Unix shells.

## ✨ Features

- **Interactive prompt** with custom display
- **Command history** (navigation with up/down arrows)
- **Command execution** with PATH search
- **Built-in commands**: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- **Redirections**: `<` (input), `>` (output), `>>` (append), `<<` (heredoc)
- **Pipes** (`|`) to chain multiple commands
- **Environment variables** (expansion with `$VAR`)
- **Signal handling**: SIGINT (Ctrl+C), SIGQUIT (Ctrl+\\)
- **Quote handling** (single and double) with proper parsing rules
- **Return code** (`$?`) to check the status of the last command

## 🏗 Architecture

The project is organized using a modular architecture to facilitate maintenance and code evolution:

```
minishell/
├── src/                # Source code
│   ├── builtins/       # Built-in commands (cd, echo, etc.)
│   ├── execution/      # Command and process execution
│   ├── lexer/          # Lexical analysis of user input
│   ├── parsing/        # Syntax analysis and AST construction
│   ├── signals/        # Signal handling
│   ├── utils/          # Utility functions
│   └── main.c          # Program entry point
├── includes/           # Header files
├── libft/              # Standard function library
├── doc/                # Technical documentation
└── Makefile            # Project compilation
```

### Execution Flow

1. **Reading**: Capture user input via readline
2. **Lexer**: Break input into tokens (words, operators, etc.)
3. **Parser**: Syntax analysis and command tree construction
4. **Expansion**: Processing environment variables and quotes
5. **Execution**: Command execution with redirection and pipe handling
6. **Waiting**: Waiting for child processes to complete
7. **Return**: Displaying the prompt for a new command

## 📥 Installation

### Prerequisites

- GCC or Clang
- Make
- Readline library

### Compilation

```bash
# Clone the repository
git clone https://github.com/MatthieuGillieron/minishell.git
cd minishell

# Compile the project
make

# Check for memory leaks (optional)
make leaks
```

The Makefile automatically detects your operating system and configures the paths for the Readline library.

## 🖥 Usage

```bash
# Launch the shell
./minishell
```

Once launched, the shell displays a prompt and waits for your commands.

## 📝 Supported Commands

### Built-in Commands

| Command | Description | Options |
|---------|-------------|---------|
| `echo` | Displays text | `-n` (without newline) |
| `cd` | Changes directory | Relative or absolute path |
| `pwd` | Displays current directory | None |
| `export` | Sets environment variables | `VAR=value` |
| `unset` | Removes environment variables | Variable name |
| `env` | Displays environment | None |
| `exit` | Exits the shell | Exit code (optional) |

### Operators and Redirections

| Operator | Description | Example |
|----------|-------------|---------|
| `|` | Pipe (output to input redirection) | `ls \| grep .c` |
| `<` | Input redirection | `cat < file.txt` |
| `>` | Output redirection (overwrite) | `ls > output.txt` |
| `>>` | Output redirection (append) | `echo "text" >> log.txt` |
| `<<` | Heredoc (multi-line input) | `cat << EOF` |

## 🚦 Signal Handling

| Signal | Combination | Behavior |
|--------|-------------|----------|
| SIGINT | Ctrl+C | Interrupts the current command, displays a new prompt |
| SIGQUIT | Ctrl+\\ | Ignored in interactive shell, terminates child processes |
| EOF | Ctrl+D | Exits the shell properly if the line is empty |

## 📋 Examples

```bash
# Simple commands
echo "Hello, World!"
pwd
cd Documents

# Environment variables
export NAME=value
echo $NAME
echo "Current path: $PATH"

# Redirections
echo "content" > file.txt
cat < file.txt
ls -la >> log.txt

# Pipes
ls -la | grep .c | wc -l

# Heredoc
cat << EOF
This is a multi-line
text input
$USER
EOF

# Complex combinations
cat < input.txt | grep "pattern" > output.txt
```

## 📚 Dependencies

- **Readline**: User interface and history management
- **Libft**: Custom library of standard functions

## 🛠 Development

### Code Structure

- **Lexer**: Lexical analysis of user input
  - Input tokenization
  - Quote and special character handling
  
- **Parser**: Syntax tree construction
  - Syntax checking
  - Command and operator organization
  
- **Executor**: Command execution
  - Process creation
  - Redirection and pipe handling
  - Builtin execution

### Coding Standards

The code follows the 42 school norm:
- Maximum 25 lines per function
- Maximum 5 functions per file
- Maximum 4 parameters per function
- Variable declarations at the beginning of functions
- Use of prefixes for file names

## 🧪 Tests

The project includes tests to verify the proper functioning of various features:

```bash
# Check for memory leaks
make leaks

# Recommended manual tests
./minishell
> echo $PATH
> ls -la | grep .c | wc -l
> cat << EOF > file.txt
```

## 📖 Documentation

A brief detailed documentation is available in the `doc/` directory:

- `doc/doc.md`: Project overview
- `doc/builtins/`: Built-in command documentation
- `doc/lexer.md`: Lexical analysis functioning
- `doc/parser.md`: Syntax analysis functioning
- `doc/pipes.md`: Pipe implementation
- `doc/redirections.md`: Redirection handling
- `doc/environnement.md`: Environment variable management

## 👥 Contributors

- [Matthieu Gillieron](https://github.com/MatthieuGillieron) - Developer
- [Mathieu taramarcaz](https://github.com/PalmaSkry) - Developer

## 📄 License

This project is distributed under the MIT license. See the `LICENSE` file for more information.

---

© 2025 Minishell - 42 School Project