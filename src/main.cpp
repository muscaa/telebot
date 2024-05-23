#include "utils.h"
#include "cmds/command.h"
#include "pharmacy/pharmacy.h"

int main(int argc, char* argv[]) {
    utils::Args args = utils::args(argc, argv);

    cmds::init();
    pharmacy::init();

    return cmds::execute(args);
}