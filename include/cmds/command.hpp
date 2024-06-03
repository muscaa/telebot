#pragma once

#include "../utils.hpp"
#include "../pharmacy/pharmacy.hpp"

#define HELP -1
#define SUCCESS 0
#define FAIL 1

namespace cmds {

/**
 * @brief Base class for commands.
 *
 * This class provides a base interface for commands with basic attributes such as name, alias, usage, and description.
 */
class Command {
protected:
    string name;
    vector<string> alias;
    string usage;
    string description;

public:
    /**
     * @brief Constructs a Command object.
     *
     * This constructor initializes the Command object with the given parameters.
     *
     * @param name The name of the command.
     * @param alias The alias names for the command.
     * @param usage The usage information for the command.
     * @param description The description of the command.
     */
    Command(string name, vector<string> alias, string usage, string description)
        : name(name), alias(alias), usage(usage), description(description) {}

    /**
     * @brief Executes the command.
     *
     * This virtual function must be overridden by derived classes to define the command's behavior.
     *
     * @param args The arguments for the command.
     * @return The status code after execution (e.g., SUCCESS, FAIL).
     */
    virtual int execute(utils::Args args) = 0;

    /**
     * @brief Gets the name of the command.
     *
     * @return The name of the command.
     */
    string getName() const { return name; }

    /**
     * @brief Gets the alias names of the command.
     *
     * @return A vector of alias names.
     */
    vector<string> getAlias() const { return alias; }

    /**
     * @brief Gets the usage information of the command.
     *
     * @return The usage information of the command.
     */
    string getUsage() const { return usage; }

    /**
     * @brief Gets the description of the command.
     *
     * @return The description of the command.
     */
    string getDescription() const { return description; }
};

/**
 * @brief Class representing a task that can contain multiple commands or tasks.
 *
 * This class provides methods to manage and execute a collection of commands and tasks.
 */
class Task : public Command {
public:
    vector<unique_ptr<Command>> commands;
    vector<unique_ptr<Task>> tasks;

    /**
     * @brief Constructs a Task object.
     *
     * This constructor initializes the Task object with the given parameters.
     *
     * @param name The name of the task.
     * @param alias The alias names for the task.
     * @param description The description of the task.
     */
    Task(string name, vector<string> alias, string description)
        : Command(name, alias, "<command>", description) {}

    /**
     * @brief Executes the task.
     *
     * This function executes the task and its subcommands or subtasks based on the provided arguments.
     *
     * @param args The arguments for the task.
     * @return The status code after execution (e.g., SUCCESS, FAIL).
     */
    int execute(utils::Args args) override;

    /**
     * @brief Adds a command to the task.
     *
     * This function adds a new command to the task.
     *
     * @param command The command to add.
     */
    void add(Command* command);

    /**
     * @brief Adds a subtask to the task.
     *
     * This function adds a new subtask to the task.
     *
     * @param task The subtask to add.
     */
    void add(Task* task);
};

/**
 * @brief Initializes the command system.
 *
 * This function initializes the command system, setting up necessary commands and tasks.
 */
void init();

/**
 * @brief Executes a command based on the provided arguments.
 *
 * This function executes a command based on the provided arguments.
 *
 * @param args The arguments for the command.
 * @return The status code after execution (e.g., SUCCESS, FAIL).
 */
int execute(utils::Args args);

/**
 * @brief Shows the help information for commands.
 *
 * This function displays the help information for the available commands.
 *
 * @param args The arguments for the help command.
 */
void show_help(utils::Args args);

/**
 * @brief Prints an object left-aligned within a specified width.
 *
 * This template function prints an object left-aligned within a specified width.
 *
 * @tparam T The type of the object to print.
 * @param width The width to print the object within.
 * @param obj The object to print.
 */
template<typename T>
void print_left(int width, const T& obj) {
    cout << left << setw(width) << obj;
}

/**
 * @brief Prints an object centered within a specified width.
 *
 * This template function prints an object centered within a specified width.
 *
 * @tparam T The type of the object to print.
 * @param width The width to print the object within.
 * @param obj The object to print.
 */
template<typename T>
void print_middle(int width, const T& obj) {
    ostringstream oss;
    oss << obj;
    string str = oss.str();
    int padding_left = (width - str.size()) / 2;
    int padding_right = width - str.size() - padding_left;

    cout << setw(padding_left) << "" << obj << setw(padding_right) << "";
}

/**
 * @brief Prints an object right-aligned within a specified width.
 *
 * This template function prints an object right-aligned within a specified width.
 *
 * @tparam T The type of the object to print.
 * @param width The width to print the object within.
 * @param obj The object to print.
 */
template<typename T>
void print_right(int width, const T& obj) {
    cout << right << setw(width) << obj;
}

}
