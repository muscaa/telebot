#pragma once

#include "../utils.h"
#include "../pharmacy/pharmacy.h"

#define HELP -1
#define SUCCESS 0
#define FAIL 1

namespace cmds {

class Command {
protected:
    string name;
    vector<string> alias;
    string usage;
    string description;

public:
    Command(string name, vector<string> alias, string usage, string description)
        : name(name), alias(alias), usage(usage), description(description) {}

    virtual int execute(utils::Args args) = 0;

    string getName() const { return name; }

    vector<string> getAlias() const { return alias; }

    string getUsage() const { return usage; }

    string getDescription() const { return description; }
};

class Task : public Command {
public:
    vector<unique_ptr<Command>> commands;
    vector<unique_ptr<Task>> tasks;

    Task(string name, vector<string> alias, string description) : Command(name, alias, "<command>", description) {}

    int execute(utils::Args args) override;

    void add(Command* command);

    void add(Task* task);
};

void init();

int execute(utils::Args args);

void show_help(utils::Args args);

template<typename T>
void print_left(int width, const T& obj) {
    cout << left << setw(width) << obj;
}

template<typename T>
void print_middle(int width, const T& obj) {
    ostringstream oss;
    oss << obj;
    string str = oss.str();
    int padding_left = (width - str.size()) / 2;
    int padding_right = width - str.size() - padding_left;

    cout << setw(padding_left) << "" << obj << setw(padding_right) << "";
}

template<typename T>
void print_right(int width, const T& obj) {
    cout << right << setw(width) << obj;
}

}
