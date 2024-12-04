#ifndef PROJECT_ESPRIT_MODEL_C_HELPER_H
#define PROJECT_ESPRIT_MODEL_C_HELPER_H

#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <algorithm> // for std::find_if_not
#include <fstream>
#include "Item.h"

// Function declarations
std::string buildDisplayedText(const std::vector<std::string>& lines);
std::string getFormattedDateTime();
std::string trim(const std::string& str);
std::vector<std::string> sliceStringByChar(const std::string&, char);

#endif //PROJECT_ESPRIT_MODEL_C_HELPER_H

