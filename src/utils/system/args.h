#pragma once

#include "../utils_base.h"

namespace utils {

class Args {
private:
    vector<string> argsArray;
    int current;

public:
    Args(vector<string> argsArray);

    int size();

    string operator[](int index);

    bool hasNext();

    string String();

    int Int();
};

Args args(int argc, char* argv[]);
    
}
