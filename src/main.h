#pragma once

typedef struct Recipe {
    char title[1][14];
    char name[1][20];
    char simple_table[9][3];
    char advanced_table[9][16];
    uint8_t type;
} Recipe;
