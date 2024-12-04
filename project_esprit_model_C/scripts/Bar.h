//
// Created by Badi on 9/6/2024.
//

#ifndef PROJECT_ESPRIT_MODEL_C_BAR_H
#define PROJECT_ESPRIT_MODEL_C_BAR_H

#include <iostream>
#include <utility>
#include <string>

class Bar {
private:
    int value{};
    int bar_count{};
    int max_bar_count = 20;
    char bar_symbol = '|';
    std::string brackets = "{}";
public:
    Bar() = default;
    explicit Bar(int);
    Bar(int, int, char, std::string);
    void modifyBars(int, const std::string&);
    int getBarCount() const;
    std::string displayBar();
};


#endif //PROJECT_ESPRIT_MODEL_C_BAR_H
