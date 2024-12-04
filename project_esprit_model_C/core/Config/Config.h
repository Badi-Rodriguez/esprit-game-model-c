//
// Created by Badi on 11/30/2024.
//

#ifndef PROJECT_ESPRIT_MODEL_C_CONFIG_H
#define PROJECT_ESPRIT_MODEL_C_CONFIG_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <format>
#include <unordered_map>

struct Config {
// --- Window and Console specifications ---
    int FONT_SIZE = 15;
    int WINDOW_X_SIZE = 1000;
    int WINDOW_Y_SIZE = 600;
    double RELATIVE_UPPER_Y_EDGE = 10.0;
    double RELATIVE_LOWER_Y_EDGE = WINDOW_Y_SIZE - (FONT_SIZE + 20);
    double RELATIVE_LEFT_X_EDGE = 10.0;
    double RELATIVE_RIGHT_X_EDGE = WINDOW_X_SIZE - 250;
    int ASCII_COUNT = 128;
};


#endif //PROJECT_ESPRIT_MODEL_C_CONFIG_H
