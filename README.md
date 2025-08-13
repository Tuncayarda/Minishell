# Minishell

A tiny, Bash-like shell written in C. The goal is to understand how shells work end-to-end: lexing/parsing, environment expansion, pipelines & redirections, process management, and signals. This project follows the common expectations of the 42 **minishell** assignment (prompt, built-ins, heredoc, pipes, signals, exit codes, etc.).

---

## Features

- **Prompt & command line editing** via GNU Readline (history included).
- **Built-ins:** `echo` (with `-n`), `cd`, `pwd`, `export`, `unset`, `env`, `exit`. (Bash-like behavior and exit codes.)
- **External commands:** PATH search, absolute/relative paths.
- **Redirections & pipes:** `<`, `>`, `>>`, and **heredoc** `<<`.
- **Quoting & expansion:** single/double quotes; `$VAR` and `$?` expansion.
- **Signals:** `Ctrl-C`, `Ctrl-D`, `Ctrl-\` handled in a Bash-like manner.

---

## Repository structure

This is the layout actually used by the build system:

```
include/                      # Public headers
lib/libft/                    # 42 libft (cloned via make update_libs)
src/
  _GC/                        # (Optional) simple GC / allocation helpers
  debug/                      # Logging / helpers for debugging
  env/                        # Environment & $? handling
  exec/                       # Executor (fork/execve, pipes, dup2)
    built_in/                 # Built-in command implementations
  init/                       # Program initialization
  lexer/                      # Lexing (input -> tokens)
  parser/                      # Parsing (tokens -> command/AST)
    check_syntax/
    cmd_utils/
    complete_pipe/
    redir_utils/
  signal/                      # SIGINT/SIGQUIT integration with Readline
  token/                       # Token utilities
  utils/                       # Shared helpers
ascii_anim/                   # Tiny ASCII animation shown during build
Makefile
valgrind.supp
```

---

## Requirements

- **C compiler** (clang or gcc), **make**
- **GNU Readline** development files
  - **Ubuntu/Debian:**
    ```bash
    sudo apt install libreadline-dev
    ```
  - **macOS (Homebrew):**
    ```bash
    brew install readline
    ```

---

## Build & Run

> This project doesn’t use git submodules. **Before the first build**, fetch the libraries once:

```bash
make update_libs     # clones libft into lib/libft
```

Then build:

```bash
make                  # fancy ASCII animation + build log
./minishell
```

- On success the build prints **“✅  Build succeeded”** and removes `build.log`.
- On failure you’ll see **“❌  Build failed. Last 100 lines of log:”** followed by the tail of `build.log`.
- Silent, colorless compilation is used under the hood; the animation runs from `ascii_anim/`.

### Useful targets

```text
make              # Build with ASCII animation & status
make minishell    # Link the binary without the animation wrapper
make clean        # Remove object files and build.log
make fclean       # Clean objects + binary
make re           # Full rebuild
make update_libs  # Clone/refresh libft from GitHub
make setup_env    # Add two push URLs (convenience)
make run_valgrind # Run with Valgrind + supplied suppressions
make test_parse   # Build & run parser tests in tests/
make help         # Pretty list of available targets
```

---

## How it’s built (Makefile highlights)

- **Portability**: detects `Darwin` vs `Linux` and sets include/lib paths for Readline accordingly (`brew --prefix readline` on macOS; `/usr/include/readline` on Linux).
- **Source discovery**: compiles every `*.c` under the directories listed in `SUBDIRS`, mirroring the tree under `obj/`.
- **Linking**: links against **libft** and Readline (`-lreadline -lhistory -lncurses`).
- **Incremental builds**: object files are split into per-subdir folders inside `obj/`.

GNU Readline provides line editing, history, and Emacs/vi modes—ideal for a shell’s interactive prompt.

---

## Testing & Debugging

- **Valgrind** (Linux):
  ```bash
  make run_valgrind
  ```
  Uses `valgrind.supp` to filter known noise and prints leaks/errors clearly.
- **Parser tests**:
  ```bash
  make test_parse
  ```
  Compiles `tests/test_parser/*.c` and runs a lightweight parser suite.

---

## Usage examples

```console
$ ./minishell
minishell$ echo hello
hello
minishell$ export NAME=Tuncay
minishell$ echo "Hi $NAME"
Hi Tuncay
minishell$ ls | grep '\.c$' > sources.txt
minishell$ cat <<EOF
> multi-line
> heredoc
> EOF
minishell$ echo $?
0
minishell$ exit
```

---

## Roadmap / Notes

- Mandatory scope is complete (prompt, built-ins, pipes/redirs, heredoc, env expansion, signals, exit codes).
- Possible extras (if added later): logical operators `&&`/`||`, subshell grouping, wildcard expansion.

---

## License

Personal/educational use. All rights reserved unless stated otherwise.

---

## Authors

- [**Tuncayarda**](https://github.com/Tuncayarda)  
- [**kdrturan**](https://github.com/kdrturan)

---

### TL;DR (setup)

```bash
# 1) Install deps
# Ubuntu/Debian
sudo apt install libreadline-dev
# macOS
brew install readline

# 2) Fetch libs (no submodules are used)
make update_libs

# 3) Build & run
make
./minishell
```
