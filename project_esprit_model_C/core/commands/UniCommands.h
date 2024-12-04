//
// Created by Badi on 11/29/2024.
//

#ifndef PROJECT_ESPRIT_MODEL_C_UNICOMMANDS_H
#define PROJECT_ESPRIT_MODEL_C_UNICOMMANDS_H

#include <iostream>
#include "../Command.h"
#include <utility>
#include <vector>
#include <format>
#include <chrono>
#include <thread>
#include <cstdlib>  // For system() function
#include <fstream>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "../../scripts/Helper.h"
#include <variant>
#include <string>


// --- ClearConsoleCommand ---
// Clears the console screen by removing all previously printed lines.
class ClearConsoleCommand : public Command {
public:
    // Constructor sets the prefix to "/clear"
    ClearConsoleCommand() : Command("/clear") {}

    // Execute command: Clears the console lines
    void execute(std::vector<std::string>& consoleLines) override {
        consoleLines.clear();  // Clears the console lines
        consoleLines.emplace_back("Console cleared.");
    }

    // Returns the name of the command
    std::string getName() const override {
        return "clear";
    }
};

// --- HelpCommand ---
// Displays a list of all available commands in the console.
class HelpCommand : public Command {
private:
    // Holds the list of available commands (name, command)
    std::vector<std::pair<std::string, Command*>> commandList;

public:
    // Constructor sets the prefix to "/help"
    HelpCommand() : Command("/help") {}

    // Execute command: Displays all available commands
    void execute(std::vector<std::string>& consoleLines) override {
        consoleLines.emplace_back("Available commands:");
        // Loop through commandList and print each command's name
        for (const auto& cmd : commandList) {
            consoleLines.push_back("- " + cmd.first);
        }
    }

    // Returns the name of the command
    std::string getName() const override {
        return "help";
    }

    // Add command to the help list
    void addCommand(Command* cmd) {
        commandList.emplace_back( cmd->getName(), cmd );
    }

};

// --- RunCppFileCommand ---
// Compiles and runs a given C++ file using the system shell.
class RunCppFileCommand : public Command {

private:
    // File path for the C++ source file to run
    std::string filePath;

public:
    // Constructor sets the prefix to "/run"
    RunCppFileCommand() : Command("/run") {}

    // Sets the file path for the C++ file to compile and run
    void setFilePath(const std::string &path) {
        filePath = path;
    }

    // Execute command: Compiles and runs the specified C++ file
    void execute(std::vector<std::string> &consoleLines) override {
        if (filePath.empty()) {
            consoleLines.emplace_back("Please specify a C++ file to run.");
            return;
        }

        // Compile and run the C++ file
        std::string compileCommand = "g++ " + filePath + " -o tempExecutable && ./tempExecutable";
        int result = system(compileCommand.c_str());  // Executes the compile and run command

        // Check if compilation and execution were successful
        if (result == 0) {
            consoleLines.emplace_back("C++ file executed successfully.");
        } else {
            consoleLines.emplace_back("Error: Failed to execute C++ file.");
        }
    }

    // Returns the name of the command
    std::string getName() const override {
        return "run";
    }

};

// --- CloseWindowCommand ---
// Closes the SFML window and exits the application.
class CloseWindowCommand : public Command {
private:
    // SFML window reference to close it
    sf::RenderWindow& window;

public:
    // Constructor sets the prefix to "/close" and accepts a window reference
    CloseWindowCommand(sf::RenderWindow& window) : Command("/close"), window(window) {}

    // Execute command: Closes the SFML window
    void execute(std::vector<std::string>& consoleLines) override {
        consoleLines.emplace_back("Closing the window...");
        window.close();  // Close the window
    }

    // Returns the name of the command
    std::string getName() const override {
        return "close";
    }
};

// --- SetStringVarCommand ---
class SetStringVarCommand : public Command {
private:
    std::unordered_map<std::string, std::string>& variables;  // Reference to the map of variables
public:
    // Constructor to initialize the target map
    explicit SetStringVarCommand(std::unordered_map<std::string, std::string>& target) : Command("/set"), variables(target) {}

    // Override the execute method from ParamCommand
    void execute(std::vector<std::string>& consoleLines) override {
        // Check if we have the correct number of parameters (2 parameters for varName and value)

        std::vector<std::string> sliced_command = sliceStringByChar(consoleLines[consoleLines.size() - 1], ' '); // Slice the instruction
        sliced_command.erase(sliced_command.begin()); // Remove the set

        if (sliced_command.size() != 2) {
            consoleLines.emplace_back("Error: Invalid number of parameters. Usage: /set <varName> <value>");
            return;
        }

        // Extract the variable name and value from parameters
        const std::string& varName = sliced_command[0];
        const std::string& newValue = sliced_command[1];

        // Update the variable map with the new value
        variables[varName] = newValue;

        // Confirm the update
        consoleLines.push_back("Variable '" + varName + "' set to: " + newValue);
    }

    [[nodiscard]] std::string getName() const override {
        return "set";
    }

};

#endif //PROJECT_ESPRIT_MODEL_C_UNICOMMANDS_H

