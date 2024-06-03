#include "utils/system/args.hpp"

utils::Args::Args(vector<string> argsArray) : argsArray(argsArray), currentIndex(0) {}

string utils::Args::operator[](int index) {
    return argsArray[index];
}

int utils::Args::size() {
    return argsArray.size();
}

int utils::Args::remaining() {
    return size() - currentIndex;
}

int utils::Args::current() {
    return currentIndex;
}

bool utils::Args::hasNext() {
    return currentIndex < size();
}

string utils::Args::String() {
    return argsArray[currentIndex++];
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
