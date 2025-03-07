#include <Arduino.h>
#include "2048.h"

uint16_t inputl[4] = {2, 2, 0, 4};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void print_line(uint16_t *line) {
  for (int i = 0; i < 4; i++) {
    Serial.print(line[i]);
    Serial.print(" ");
  }
  Serial.println();
}

void print_board(uint16_t *board) {
  for (int i = 0; i < 4; i++) {
    print_line(board + i * 4);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Move Line Test");
  print_line(inputl);
  uint16_t* moved_line = move_line(inputl);
  print_line(moved_line);
  delay(1000);
  Serial.println("Init Board Test");
  // init_board();
  print_board(board);
  delay(1000);
  Serial.println("Move up Board Test");
  move_up();
  print_board(board);
  delay(1000);
  Serial.println("Move down Board Test");
  move_down();
  print_board(board);
  delay(1000);
  Serial.println("Move left Board Test");
  move_left();
  print_board(board);
  delay(1000);
  Serial.println("Move right Board Test");
  move_right();
  print_board(board);
  delay(1000);
  
  // 输出本局得分
  Serial.print("Current Score: ");
  Serial.println(get_score());
  delay(1000);
}
