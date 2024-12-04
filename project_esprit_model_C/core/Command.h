#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <utility>
#include <vector>
#include <string>

class Command {
private:
    std::string prefix;  // Command prefix (e.g., /clear)
public:
    // Default constructor for prefix (e.g. "/clear", "/help")
    Command(std::string  prefix = "/") : prefix(std::move(prefix)) {}

    virtual ~Command() = default;

    // Pure virtual execute function
    virtual void execute(std::vector<std::string>& consoleLines) = 0;

    // Get command prefix (e.g. "/clear")
    [[nodiscard]] std::string getPrefix() const { return prefix; }

    // Get the name of the command (used in Help)
    virtual std::string getName() const = 0;

    std::string getPrefix(){
        return prefix;
    }

};

#endif // COMMAND_H

