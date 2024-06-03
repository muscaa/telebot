#include "utils.hpp"
#include "cmds/command.hpp"
#include "pharmacy/pharmacy.hpp"

int main(int argc, char* argv[]) {
    utils::Args args = utils::args(argc, argv);

    cmds::init();
    pharmacy::init();

    return cmds::execute(args);
}