# turing-box
A platform-agnostic, header-only collection of simple 2D cellular automata and games, written in C++.

## Cellular Automata
| File  | Description |
| :--- | :--- |
| [`conway.h`](https://github.com/Matthewacon/turing-box/blob/master/include/conway.h)  | Standard ruleset of [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life#Rules).  |
| [`anti_conway.h`](https://github.com/Matthewacon/turing-box/blob/master/include/anti_conway.h)  | Conway's Game of Life ruleset modified to bias toward living cells and recurrently modify the board.  |
| [`ulam.h`](https://github.com/Matthewacon/turing-box/blob/master/include/ulam.h) | Standard ruleset of [Ulam-Warburton's Automaton](https://en.wikipedia.org/wiki/Ulam%E2%80%93Warburton_automaton). |
| [`anti_ulam.h`](https://github.com/Matthewacon/turing-box/blob/master/include/anti_ulam.h) | Ulam-Warburton's Automaton modified to also kill cells without exactly one neighbour. |
| [`langton.h`]() | Standard ruleset of [Langton's Ant](https://en.wikipedia.org/wiki/Langton's_ant#Rules). |
| [`pong.h`](https://github.com/Matthewacon/turing-box/blob/master/include/pong.h) | Simple implementation of [Atari's 1972, Pong](https://en.wikipedia.org/wiki/Pong). |
| [`text.h`](https://github.com/Matthewacon/turing-box/blob/master/include/text.h) | A simple horizontal and vertical text scalable character scrolling algorithm. |

## API
#### Utility types:
| Type  | Name | Description |
| :-- | :-- | :-- |
| `struct` | `<T> Point` | Simple bivariate storage struct of type `T`. |
| `class` | `<T> Board` | 2D grid of type `T` with utility functions. |

#### `<T> Board`:
There are a few inherited members and functions available for use from `<T> Board`:

| Member | Type | Description |
| :--- | :--- | :--- |
| `len` | `unsigned int` | The vertical length of the board. |
| `width` | `unsigned int` | The horizontal length of the board. |
| `total_len` | `unsigned int` | The area of the board. |

| Function | Return Type | Description |
| :--- | :--- | :--- |
| `get(unsigned int x, unsigned int y)` | `T` | Returns the element associated with the index `(x, y)` when indexing the board as a 2D array with the homogeneous bounds `(len, width)`. |
| `get(unsigned int x)` | `T` | Returns the element in the board at the index `x` when indexing the board as a 1D array. |
| `set(unsigned int x, unsigned int y, T flag)` | `void` | Sets the element associated with the index `(x, y)` to `flag`. |
| `set(unsigned int x, T flag)` | `void` | Sets the element associated with the index `x` to `flag`. |
| `calculate_index(unsigned int x, unsigned int y)` | `unsigned int` | Returns the equivalent 1D index of the element at the 2D index `(x, y)`. |
| `calculate_index(unsigned int index)` | `Point<unsigned int>` | Returns the equivalent 2D index of the element at the 1D index `index`. |
| `wrap_around(int x, int bound)` | `unsinged int` | Wraps the value of `x` to withing the range of `0 <= x <= bound` |

## Example
Defining a cellular automaton is as simple as `#include`ing `board.h` and implementing `void update`:
```cpp
#include "board.h"

class Invert final : public Board<bool> {
public:
 //Explicitly inherit constructor for backwards compatability (pre C++11)
 using Board<bool>::Board();
 
 void update() {
  bool *copy = new bool[];
  memcpy(board, copy, sizeof(bool) * total_len);
  for (unsigned int i = 0; i < total_len; i++) {
   //Make changes to copy based on values of board
   copy[i] = !board[i];
  }
  delete[] board;
  board = copy;
 }
};
```

## License
This project is licensed under the [M.I.T. License](https://github.com/Matthewacon/turing-box/blob/master/LICENSE)
