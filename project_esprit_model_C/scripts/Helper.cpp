//
// Created by Badi on 11/29/2024.
//
#include "Helper.h"

// Function definitions
std::string buildDisplayedText(const std::vector<std::string>& lines) {
    std::string displayedText;
    for (const auto& line : lines) {
        displayedText += line + "\n";
    }
    return displayedText;
}

std::string getFormattedDateTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    std::tm localTime = *std::localtime(&now_c);

    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m-%d\n    %H:%M:%S");
    return oss.str();
}

std::string trim(const std::string& str) {
    auto start = std::find_if_not(str.begin(), str.end(), ::isspace);
    auto end = std::find_if_not(str.rbegin(), str.rend(), ::isspace).base();
    return (start < end) ? std::string(start, end) : "";
}

std::vector<std::string> sliceStringByChar(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string segment;

    // Extract segments separated by the delimiter
    while (std::getline(ss, segment, delimiter)) {
        result.push_back(segment);
    }

    return result;
}

// Function to split a string by a delimiter
std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

// Function to parse .txt file and generate a list of Item objects

// Format: [name,price,market_value,tag1|tag2|tag3,vendor_name,code,status]
std::vector<Item> parseItemsFromFile(const std::string& filePath) {
    std::vector<Item> items;
    std::ifstream inputFile(filePath);

    if (!inputFile.is_open()) {
        throw std::runtime_error("Could not open file: " + filePath);
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        // Skip empty lines
        if (line.empty()) continue;

        // Split the line into fields
        std::vector<std::string> fields = split(line, ',');

        if (fields.size() < 7) {
            throw std::runtime_error("Invalid line format: " + line);
        }

        // Parse fields
        std::string name = fields[0];
        int price = std::stoi(fields[1]);
        int market_value = std::stoi(fields[2]);

        // Split tags by '|'
        std::vector<std::string> tags = split(fields[3], '|');

        std::string vendor_name = fields[4];
        int code = std::stoi(fields[5]);
        std::string status = fields[6];

        // Create an Item object
        items.emplace_back(name, price, market_value, tags, vendor_name, code, status);
    }

    inputFile.close();
    return items;
}
