#ifndef _2048GAME_H
#define _2048GAME_H

#include <Arduino.h>

uint16_t board[16] = 
{   0,0,0,0,
    0,0,0,0,
    0,0,0,0,
    2,2,0,4
};
uint16_t board_before[16];
uint8_t num_zeros = 0;
uint16_t score = 0;

void init_board() {
    static bool randomseed_initialized = false; // 静态变量，初始值为 false
    if (!randomseed_initialized) {
        randomSeed(analogRead(0)); // 初始化随机数生成器
        randomseed_initialized = true; // 设置为 true，表示已经初始化过
    }
    for (int i = 0; i < 16; i++) {
        board[i] = 0;
    }
    // 随机生成两个不同的位置
    int pos1 = random(0, 16);
    int pos2;
    do {
        pos2 = random(0, 16);
    } while (pos1 == pos2);
    // 在随机位置放置一个4和一个2
    board[pos1] = 4;
    board[pos2] = 2;
}

uint16_t* move_line(uint16_t* input) {
    static uint16_t out[4]; // 使用 static 关键字定义固定大小的数组
    memcpy(out, input, 4 * sizeof(uint16_t));

    // 移动所有非零元素到前面
    int index = 0;
    for (int i = 0; i < 4; i++) {
        if (out[i] != 0) {
            out[index++] = out[i];
        }
    }
    // 填充剩余位置为零
    while (index < 4) {
        out[index++] = 0;
    }

    // 合并相同的元素，且不超过2048
    for (int i = 0; i < 3; i++) {
        if (out[i] == out[i + 1] && out[i] != 0 && out[i] < 2048) {
            out[i] *= 2;
            out[i + 1] = 0;
        }
    }

    // 再次移动所有非零元素到前面
    index = 0;
    for (int i = 0; i < 4; i++) {
        if (out[i] != 0) {
            out[index++] = out[i];
        }
    }
    // 填充剩余位置为零
    while (index < 4) {
        out[index++] = 0;
    }

    return out;
}

// 对比 board和board_before，如果相同则返回true，否则返回false
bool mat_compare() {
    for (int i = 0; i < 16; i++) {
        if (board[i] != board_before[i]) {
            return false;
        }
    }
    return true;
}

// 随机在一个非零区块生成一个2或者4
bool random_insert() {
    uint8_t empty_positions[16];
    uint8_t empty_count = 0;

    // 找到所有为零的区块
    for (int i = 0; i < 16; i++) {
        if (board[i] == 0) {
            empty_positions[empty_count++] = i;
        }
    }

    // 如果没有空位，返回 false
    if (empty_count == 0) {
        return false;
    }

    // 随机选择一个空位
    int random_index = random(0, empty_count);
    int pos = empty_positions[random_index];

    // 1/4几率生成4，否则生成2
    board[pos] = (random(0, 4) == 0) ? 4 : 2;

    return true;
}

uint16_t get_score() {
    uint16_t score = 0;
    for (int i = 0; i < 16; i++) {
        score += board[i];
    }
    return score;
}

void move_up() {
    memcpy(board_before, board, 16 * sizeof(uint16_t));
    static uint16_t line_buffer[4];
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            line_buffer[j] = board[j * 4 + i];
        }
        memcpy(line_buffer, move_line(line_buffer), 4 * sizeof(uint16_t));
        for(int j = 0; j < 4; j++) {
            board[j * 4 + i] = line_buffer[j];
        }
    }
    if (!mat_compare()) {
        random_insert();
    }
}
void move_down() {
    memcpy(board_before, board, 16 * sizeof(uint16_t));
    static uint16_t line_buffer[4];
    for(int i = 3; i >= 0; i--) {
        for(int j = 3; j >= 0; j--) {
            line_buffer[3-j] = board[j * 4 + i];
        }
        memcpy(line_buffer, move_line(line_buffer), 4 * sizeof(uint16_t));
        for(int j = 3; j >= 0; j--) {
            board[j * 4 + i] = line_buffer[3-j];
        }
    }
    if (!mat_compare()) {
        random_insert();
    }
}

void move_left() {
    memcpy(board_before, board, 16 * sizeof(uint16_t));
    static uint16_t line_buffer[4];
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            line_buffer[j] = board[i * 4 + j];
        }
        memcpy(line_buffer, move_line(line_buffer), 4 * sizeof(uint16_t));
        for(int j = 0; j < 4; j++) {
            board[i * 4 + j] = line_buffer[j];
        }
    }
    if (!mat_compare()) {
        random_insert();
    }
}
void move_right() {
    memcpy(board_before, board, 16 * sizeof(uint16_t));
    static uint16_t line_buffer[4];
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            line_buffer[3-j] = board[i * 4 + j];
        }
        memcpy(line_buffer, move_line(line_buffer), 4 * sizeof(uint16_t));
        for(int j = 0; j < 4; j++) {
            board[i * 4 + j] = line_buffer[3-j];
        }
    }
    if (!mat_compare()) {
        random_insert();
    }
}

#endif
