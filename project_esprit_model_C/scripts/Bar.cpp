//
// Created by Badi on 9/6/2024.
//

#include "Bar.h"

Bar::Bar(int value) {
    /*
     * Basic constructor for a Bar object
     * value determines the numerical value represented by the bar.
     */
    this->value = value;
    bar_count = max_bar_count;
}

Bar::Bar(int value, int max_bar_count, char bar_symbol, std::string brackets){
    /*
     * Constructor for a custom Bar object.
     * value determines the numerical value represented by the bar.
     * max_bar_count determines the maximum amount of bars to be held within the display.
     * bar_symbol determines the symbol used for the filled bars.
     * brackets determines the symbols that make for the visual limits of the bar.
     */
    this->value = value;
    this->max_bar_count = max_bar_count;
    bar_count = max_bar_count;
    this->bar_symbol = bar_symbol;
    this->brackets = std::move(brackets);

}

void Bar::modifyBars(int amount, const std::string& operation) {
    /*
     * Function adds or removes bars equal to the amount inserted.
     * Operation can be either "add" (addition) or "sub" (subtraction).
     * Any other string in the operation slot returns nothing.
     */
    if (operation == "add") {
        bar_count += amount;
    }
    else if (operation == "sub") {
        bar_count -= amount;
    }
    else {
        return;
    }
}

int Bar::getBarCount() const {
    return bar_count;
}

std::string Bar::displayBar() {

    // Repeat the bar_symbol `bar_count` times
    std::string filled_bars(bar_count, bar_symbol);
    std::string empty_bars((max_bar_count - bar_count), '-');

    // Construct the bar using brackets and repeated symbols
    std::string bar_model = brackets.substr(0, 1) + filled_bars + empty_bars + brackets.substr(1, 1);

    return bar_model;
}
