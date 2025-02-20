# DSA Train Simulator

A command-line tool for simulating train operations in C. This project implements a dynamic train data structure and a command queue to mimic various train manipulations such as moving, writing, inserting, and clearing wagons.

## Features

- **Dynamic Train Operations:**
  - Move the train left and right (`MOVE_LEFT`, `MOVE_RIGHT`)
  - Write a value in the current wagon (`WRITE`)
  - Clear a wagon or all wagons (`CLEAR_CELL`, `CLEAR_ALL`)
- **Wagon Insertion:**
  - Insert new wagons to the left or right of the current position (`INSERT_LEFT`, `INSERT_RIGHT`)
- **Command Queue:**
  - Queue commands for later execution with the support of switching the command order (`SWITCH`, `EXECUTE`)
- **Search Operations:**
  - Search for patterns in the train from the current wagon (`SEARCH`, `SEARCH_LEFT`, `SEARCH_RIGHT`)
- **Display:**
  - Show the entire train or the current wagon, with the current wagon highlighted (`SHOW`, `SHOW_CURRENT`)

## Project Structure

- **`tema1.c`**
  Main file that sets up input/output, initializes the train and command queue, processes commands, and cleans up. See [tema1.c](tema1.c).

- **Train Module (`train.c` / `train.h`)**
  Implements the train and wagon operations. The train is built as a circular doubly linked list with a locomotive and a current position indicator. See [train.c](train.c) and [train.h](train.h).

- **Command Queue Module (`queue.c` / `queue.h`)**
  Maintains a queue of commands that are executed sequentially on the train. See [queue.c](queue.c) and [queue.h](queue.h).

- **`Makefile`**
  Contains build targets to compile, run, and clean up the project. See [Makefile](Makefile).

- **Testing Files (`Teste/`)**
  Contains a set of inputs and expected outputs for testing the project. See [Teste](Teste).

- **`checker.sh`**
  A script to run the tests and perform memory leak checks via Valgrind. See [checker.sh](checker.sh).

- **`assignment.pdf`**
  The assignment description and requirements.

## Building the Project

```bash
make       # Builds the project
make run   # Runs the compiled executable
make clean # Cleans build artifacts
```

## Running the Simulator

The simulator reads commands from the file `tema1.in` and writes outputs to `tema1.out`. Typical commands include:

- `MOVE_LEFT` / `MOVE_RIGHT`
- `WRITE <char>`
- `INSERT_LEFT <char>` / `INSERT_RIGHT <char>`
- `CLEAR_CELL` / `CLEAR_ALL`
- `SWITCH` and `EXECUTE`
- Display commands: `SHOW`, `SHOW_CURRENT`
- Search commands: `SEARCH <pattern>`, `SEARCH_LEFT <pattern>`, `SEARCH_RIGHT <pattern>`

For example, an input file might contain:

```in
3
MOVE_RIGHT
EXECUTE
SHOW
```

## Implementation Details

- **Train Data Structure:**
  The train is represented as a circular doubly linked list. The locomotive serves as a marker, and the current wagon indicates the position where operations are performed.

- **Command Queue:**
  Implemented via a doubly linked list to allow insertion and reversal of command order.

- **Memory Management:**
  The project dynamically allocates memory for wagons and queue nodes. Resources are freed appropriately after execution.

## Example Usage

A typical workflow using a test case might be:

```bash
./tema1 < tema1.in > tema1.out
```

Then, compare the output with the expected file in the [Teste/Output](Teste/Output ).