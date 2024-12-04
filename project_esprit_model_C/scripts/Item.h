#ifndef PROJECT_ESPRIT_MODEL_C_ITEM_H
#define PROJECT_ESPRIT_MODEL_C_ITEM_H

#include <iostream>
#include <string>
#include <utility>
#include <vector>

class Item {
private:
    std::string name;
    int price;
    int market_value;
    std::vector<std::string> tags;
    std::string vendor_name;
    int code;
    std::string status; // Represents if it's "Available", "Unavailable", or "Reserved".

public:
    // Constructors
    Item() : name(""), price(0), market_value(0), vendor_name(""), code(0), status("Unavailable") {}
    ~Item() = default;
    Item(std::string  name,
         int price,
         int market_value,
         const std::vector<std::string>& tags,
         std::string vendor_name,
         int code,
         std::string status = "Unavailable")
            :
            name(std::move(name)),
            price(price),
            market_value(market_value),
            tags(tags),
            vendor_name(std::move(vendor_name)),
            code(code),
            status(std::move(status)) {}



    // Getters
    const std::string& getName() const { return name; }
    int getPrice() const { return price; }
    int getMarketValue() const { return market_value; }
    const std::vector<std::string>& getTags() const { return tags; }
    const std::string& getVendorName() const { return vendor_name; }
    int getCode() const { return code; }
    const std::string& getStatus() const { return status; }

    // Setters
    void setName(const std::string& newName) { name = newName; }
    void setPrice(int newPrice) { price = newPrice; }
    void setMarketValue(int newMarketValue) { market_value = newMarketValue; }
    void setTags(const std::vector<std::string>& newTags) { tags = newTags; }
    void setVendorName(const std::string& newVendorName) { vendor_name = newVendorName; }
    void setCode(int newCode) { code = newCode; }
    void setStatus(const std::string& newStatus) {
        if (newStatus == "Available" || newStatus == "Unavailable" || newStatus == "Reserved") {
            status = newStatus;
        } else {
            throw std::invalid_argument("Invalid status: must be 'Available', 'Unavailable', or 'Reserved'.");
        }
    }

    // Display as a string (for console output)
    void display() const {
        std::cout << "Item Name: " << name << "\n"
                  << "Price: " << price << "\n"
                  << "Market Value: " << market_value << "\n"
                  << "Tags: ";
        for (const auto& tag : tags) {
            std::cout << tag << " ";
        }
        std::cout << "\nVendor Name: " << vendor_name << "\n"
                  << "Code: " << code << "\n"
                  << "Status: " << status << "\n";
    }

    // Display in vector format (for SFML)
    std::vector<std::string> displayInVector() const {
        std::vector<std::string> itemVector;
        itemVector.push_back("Item Name: " + name);
        itemVector.push_back("Price: " + std::to_string(price));
        itemVector.push_back("Market Value: " + std::to_string(market_value));
        std::string tagsLine = "Tags: ";
        for (const auto& tag : tags) {
            tagsLine += tag + ", ";
        }
        if (!tags.empty()) {
            tagsLine.pop_back(); // Remove trailing space
            tagsLine.pop_back(); // Remove trailing comma
        }
        itemVector.push_back(tagsLine);
        itemVector.push_back("Vendor Name: " + vendor_name);
        itemVector.push_back("Code: " + std::to_string(code));
        itemVector.push_back("Status: " + status);
        return itemVector;
    }
};

/*
 *
 * Item exampleItem("Axe of Regock", 500, 700, {"weapon", "axe", "rare"}, "Vendor_123", 101, "Available");
 *
 * // Get vector for SFML rendering
 * std::vector<std::string> itemVector = exampleItem.displayInVector();
 * // Convert vector to displayable text for SFML
 * std::string displayedText = buildDisplayedText(itemVector);
 * std::cout << displayedText; // Output for testing
 *
 */

#endif //PROJECT_ESPRIT_MODEL_C_ITEM_H


