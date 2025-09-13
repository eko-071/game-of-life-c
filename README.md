# Conway's Game of Life
The Game of Life is a cellular automaton devised by British mathematician John Horton Conway in 1970. It is a zero-player game, meaning that its evolution is determined by its initial state and the Game of Life [rules](#Rules), requiring no further input.
Built using C, this is a simple implementation of the Game of Life that runs it using a 2D grid in either a Linux or Windows terminal. It supports configurable grid size, generations, and random density of live cells.

## Rules
The universe of the Game of Life is a two-dimensional orthogonal grid of square cells, each of which is in one of two possible states, live or dead (or populated and unpopulated, respectively). Every cell interacts with its eight neighbours, which are the cells that are horizontally, vertically, or diagonally adjacent. At each step in time, the following transitions occur:

1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
2. Any live cell with two or three live neighbours lives on to the next generation.
3. Any live cell with more than three live neighbours dies, as if by overpopulation.
4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

## Features
- Randomized initial grid with adjustable density
- Wrap-around grid edges
- ANSI-colored output for live (`#`) and dead (`.`) cells
- Cross-platform support for sleep and screen clearing

## How to Run
Clone this repository and go to the project directory.

### Linux / macOS
Make sure 'gcc' is installed.

```shell
gcc game.c
./a.out
```

### Windows
Install [MinGW](https://www.mingw-w64.org/) or some other GCC-based toolchain.

```shell
gcc game.c
./a.exe
```

## Usage
Once the program has been compiled and run, it will prompt the user for the number of rows, number of columns, number of generations, and the random density of the live cells (i.e, x such that approximately 1 in x cells should be live).
