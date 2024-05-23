#include "args.h"

utils::Args::Args(vector<string> argsArray) : argsArray(argsArray), current(0) {}

int utils::Args::size() {
    return argsArray.size();
}

string utils::Args::operator[](int index) {
    return argsArray[index];
}

bool utils::Args::hasNext() {
    return current < size();
}

string utils::Args::String() {
    return argsArray[current++];
}

int utils::Args::Int() {
    return stoi(String());
}

utils::Args utils::args(int argc, char* argv[]) {
    vector<string> argsArray;
    for (int i = 1; i < argc; i++) {
        argsArray.push_back(argv[i]);
    }
    return Args(argsArray);
}
