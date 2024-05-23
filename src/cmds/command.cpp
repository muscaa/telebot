#include "command.h"

#include "products/show.h"
#include "products/add.h"
#include "products/delete.h"
#include "products/reserve.h"

#include "reservations/show.h"
#include "reservations/cancel.h"

#define HELP_SPACES "  "

static cmds::Task mainTask = cmds::Task("Main", { }, "Main task");

int cmds::Task::execute(utils::Args args) {
    if (!args.hasNext()) return HELP;
    string name = args.String();

    for (unique_ptr<Command>& command : commands) {
        for (string alias : command->getAlias()) {
            if (alias == name) return command->execute(args);
        }
    }

    for (unique_ptr<Task>& task : tasks) {
        for (string alias : task->getAlias()) {
            if (alias == name) return task->execute(args);
        }
    }

    return HELP;
}

void cmds::Task::add(Command* command) {
    commands.push_back(unique_ptr<Command>(command));
}

void cmds::Task::add(Task* task) {
    tasks.push_back(unique_ptr<Task>(task));
}

void cmds::init() {
    auto products = new cmds::Task("Products", { "products" }, "Products task.");
    products->add(new cmds::products::Show());
    products->add(new cmds::products::Add());
    products->add(new cmds::products::Delete());
    products->add(new cmds::products::Reserve());
    mainTask.add(products);

    auto reservations = new cmds::Task("Reservations", { "reservations" }, "Reservations task.");
    reservations->add(new cmds::reservations::Show());
    reservations->add(new cmds::reservations::Cancel());
    mainTask.add(reservations);
}

int cmds::execute(utils::Args args) {
    int result = HELP;
    try {
        result = mainTask.execute(args);
    } catch (exception& e) {}

    if (result == HELP) show_help(args);
    
    return result;
}

static void command_help(cmds::Command* command, string spaces) {
    cout << spaces << command->getName() << ": " << endl;
    spaces += HELP_SPACES;

    cout << spaces << "Alias:";
    for (string alias : command->getAlias()) {
        cout << " " << alias;
    }
    cout << endl;
    cout << spaces << "Usage: " << command->getUsage() << endl;
    cout << spaces << "Description: " << command->getDescription() << endl;
}

static void task_help(cmds::Task* task, string spaces) {
    if (!task->commands.empty()) {
        cout << spaces << "Commands:" << endl;
        for (unique_ptr<cmds::Command>& subcommand : task->commands) {
            command_help(subcommand.get(), spaces + HELP_SPACES);
        }
    }

    if (!task->tasks.empty()) {
        cout << spaces << "Tasks:" << endl;
        spaces += HELP_SPACES;
        for (unique_ptr<cmds::Task>& subtask : task->tasks) {
            command_help(subtask.get(), spaces);
            task_help(subtask.get(), spaces + HELP_SPACES);
        }
    }
}

static bool show_some_help(utils::Args args, int index, cmds::Task* task) {
    if (index >= args.size()) return false;
    string name = args[index];

    for (unique_ptr<cmds::Command>& command : task->commands) {
        for (string alias : command->getAlias()) {
            if (alias == name) {
                command_help(command.get(), HELP_SPACES);
                return true;
            }
        }
    }

    for (unique_ptr<cmds::Task>& task : task->tasks) {
        for (string alias : task->getAlias()) {
            if (alias == name) {
                if (show_some_help(args, index + 1, task.get())) return true;

                command_help(task.get(), HELP_SPACES);
                task_help(task.get(), HELP_SPACES HELP_SPACES);
                return true;
            }
        }
    }

    return false;
}

void cmds::show_help(utils::Args args) {
    cout << "Help:" << endl;
    if (!show_some_help(args, 0, &mainTask)) {
        task_help(&mainTask, HELP_SPACES);
    }
}
