# arduino-2048-game-core
A basic 2048-game engine based on arduino that easy to apply

# 2048 Game for Arduino

This project implements the 2048 game on an Arduino platform.

## Functions

### `void init_board()`

**Description:**
Initializes the game board by setting all positions to 0 and randomly placing a 4 and a 2 at different positions.

**描述：**
初始化游戏棋盘，将所有位置设置为0，并随机在不同位置放置一个4和一个2。

### `uint16_t* move_line(uint16_t* input)`

**Description:**
Moves and merges the elements of a line according to the 2048 game rules. Returns the modified line.

**描述：**
根据2048游戏规则移动并合并一行的元素。返回修改后的行。

### `bool mat_compare()`

**Description:**
Compares the current board with the previous board. Returns `true` if they are the same, otherwise returns `false`.

**描述：**
比较当前棋盘和之前的棋盘。如果相同则返回`true`，否则返回`false`。

### `bool random_insert()`

**Description:**
Inserts a 2 or 4 at a random empty position on the board. Returns `true` if successful, otherwise returns `false`.

**描述：**
在棋盘的随机空位置插入一个2或4。如果成功则返回`true`，否则返回`false`。

### `uint16_t get_score()`

**Description:**
Calculates and returns the current score of the game by summing all the values on the board.

**描述：**
通过将棋盘上的所有值相加来计算并返回当前游戏的得分。

### `void move_up()`

**Description:**
Moves all tiles up according to the 2048 game rules and inserts a new tile if the board has changed.

**描述：**
根据2048游戏规则将所有方块向上移动，如果棋盘发生变化则插入一个新方块。

### `void move_down()`

**Description:**
Moves all tiles down according to the 2048 game rules and inserts a new tile if the board has changed.

**描述：**
根据2048游戏规则将所有方块向下移动，如果棋盘发生变化则插入一个新方块。

### `void move_left()`

**Description:**
Moves all tiles left according to the 2048 game rules and inserts a new tile if the board has changed.

**描述：**
根据2048游戏规则将所有方块向左移动，如果棋盘发生变化则插入一个新方块。

### `void move_right()`

**Description:**
Moves all tiles right according to the 2048 game rules and inserts a new tile if the board has changed.

**描述：**
根据2048游戏规则将所有方块向右移动，如果棋盘发生变化则插入一个新方块。

## Example Usage

```cpp
#include <Arduino.h>
#include "2048.h"

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0)); // Initialize random number generator
  init_board(); // Initialize the board
}

void loop() {
  // Example of moving the tiles up
  move_up();
  delay(1000);
}
