#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <format>
#include <chrono>
#include "core/commands/UniCommands.h"
#include <cctype>
#include <unordered_map>
#include "scripts/Helper.h"
#include "core/Config/Config.h"
#include "scripts/TestUnit.h"

// --- Window and Console specifications (Config initialization) ---

Config consoleConfiguration;

// --- Console specifications ---
constexpr size_t MAX_CONSOLE_LINES = 30;
constexpr size_t MAX_INPUT_BUFFER = 100;

// System information

constexpr std::string version = "0.0.4";
int input_count = 0;
int frame_count = 0;

// Main loop
int main(){

    TestDoubleList();
    TestHashTable();
    TestXFastTrie();
    TestAVL();

    sf::RenderWindow window(sf::VideoMode(consoleConfiguration.WINDOW_X_SIZE, consoleConfiguration.WINDOW_Y_SIZE), "SFML window");
    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;

    std::unordered_map<std::string, std::string> local_variables;

        sf::Font consoleFont;

        if (!consoleFont.loadFromFile("resources/Minecraft.ttf")) {
            std::cerr << "Failed to load font!" << std::endl;
            return -1;
        }

        // Console text
        std::vector<std::string> consoleLines;
        sf::Text consoleText;
        consoleText.setFont(consoleFont);
        consoleText.setCharacterSize(consoleConfiguration.FONT_SIZE);
        consoleText.setFillColor(sf::Color::White);
        consoleText.setPosition(static_cast<float>(consoleConfiguration.RELATIVE_LEFT_X_EDGE), static_cast<float>(consoleConfiguration.RELATIVE_UPPER_Y_EDGE));

        // Input buffer
        std::string inputBuffer;
        sf::Text inputText;
        inputText.setFont(consoleFont);
        inputText.setCharacterSize(consoleConfiguration.FONT_SIZE);
        inputText.setFillColor(sf::Color::Green);
        inputText.setPosition(static_cast<float>(consoleConfiguration.RELATIVE_LEFT_X_EDGE), (static_cast<float>(consoleConfiguration.RELATIVE_LOWER_Y_EDGE))); // At the bottom of the screen

        // System text
        sf::Text console_system;
        console_system.setFont(consoleFont);
        console_system.setCharacterSize(consoleConfiguration.FONT_SIZE);
        console_system.setFillColor(sf::Color::Yellow);
        console_system.setPosition(static_cast<float>(consoleConfiguration.RELATIVE_RIGHT_X_EDGE), static_cast<float>(consoleConfiguration.RELATIVE_UPPER_Y_EDGE));

    // Create the commands
    ClearConsoleCommand clearCommand;
    HelpCommand helpCommand;
    RunCppFileCommand runCommand;
    SetStringVarCommand setCommand(local_variables);
    CloseWindowCommand closeCommand(window);

    // Add commands to the map
    std::unordered_map<std::string, Command*> commandMap;
    commandMap[clearCommand.getPrefix()] = &clearCommand;
    commandMap[helpCommand.getPrefix()] = &helpCommand;
    commandMap[runCommand.getPrefix()] = &runCommand;
    commandMap[setCommand.getPrefix()] = &setCommand;
    commandMap[closeCommand.getPrefix()] = &closeCommand;

    std::ostringstream systemStream;
    sf::Clock frameClock;

    // Add commands to the help command list
    helpCommand.addCommand(&clearCommand);
    helpCommand.addCommand(&helpCommand);
    helpCommand.addCommand(&runCommand);
    helpCommand.addCommand(&setCommand);
    helpCommand.addCommand(&closeCommand);

    consoleLines.emplace_back("Welcome to the SFML console!");

    while (window.isOpen()) {
            // Set run command file path
            runCommand.setFilePath(local_variables["target_run"]);
            frame_count++;
            sf::Event event{};
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                // Handle keyboard input
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == '\b') { // Backspace
                        if (!inputBuffer.empty()) {
                            inputBuffer.pop_back();
                        } else {
                            if (consoleLines.size() > MAX_CONSOLE_LINES) {
                                consoleLines.erase(consoleLines.begin());
                            }
                            consoleLines.emplace_back("No input to delete.");
                        }
                    } else if (event.text.unicode == '\r') { // Enter
                        if (inputBuffer.size() > MAX_INPUT_BUFFER) {
                            consoleLines.emplace_back("Line too long.");
                            inputBuffer = "";
                            continue;
                        }
                        if (consoleLines.size() > MAX_CONSOLE_LINES) {
                            consoleLines.erase(consoleLines.begin()); // Remove oldest line
                        }
                        consoleLines.push_back(inputBuffer); // Add input to console
                        input_count += 1;

                        if (!inputBuffer.empty() && inputBuffer[0] == '/') {
                            // Check if the command exists
                            std::vector<std::string> sliced_command = sliceStringByChar(inputBuffer, ' ');
                            auto commandIt = commandMap.find(sliced_command[0]);
                            if (commandIt != commandMap.end()) {
                                // Execute the command
                                commandIt->second->execute(consoleLines);
                            }
                            else {
                                consoleLines.push_back("Unknown command: " + inputBuffer);
                            }
                        }

                        inputBuffer = ""; // Clear the buffer

                    } else if (event.text.unicode < consoleConfiguration.ASCII_COUNT) { // Printable characters
                        inputBuffer += static_cast<char>(event.text.unicode);
                    }
                }
            }

        // FPS calculation
        float smoothedFps = 0.0;
        if (frameClock.getElapsedTime().asSeconds() >= 1.0f) {
            float currentFps = static_cast<float>(frame_count) / frameClock.restart().asSeconds();
            smoothedFps = currentFps;
            frame_count = 0;
        }

        // Update system stats
        std::string systemStatsText = std::format(
                "- - - [ <(_o_)> [-O-] <(_o_)> ] - - -\n"
                "Console Model: {}\n"
                "Status: {}\n"
                "User: {}\n"
                "Input Count: {}\n"
                "FPS: {}\n"
                "Date & Time: {}\n"
                "- - - - - - - - - - - - - - - - - - - - -\n\n",
                version,
                local_variables["status"],
                local_variables["user"],
                input_count,
                smoothedFps,
                getFormattedDateTime()
        );
        console_system.setString(systemStatsText);

        // Update the displayed text
            consoleText.setString(buildDisplayedText(consoleLines));
            inputText.setString("> " + inputBuffer);

            // Clear and draw
            window.clear(sf::Color::Black);
            window.draw(consoleText);
            window.draw(inputText);
            window.draw(console_system);
            window.display();
        }

        return 0;
}

