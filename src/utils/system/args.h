#pragma once

#include "../utils_base.h"

namespace utils {

class Args {
private:
    vector<string> argsArray;
    int currentIndex;

public:
    Args(vector<string> argsArray);

    string operator[](int index);

    int size();

    int remaining();

    int current();

    bool hasNext();

    string String();

    int Int();
};

Args args(int argc, char* argv[]);
    
}
