#include "core/gb.h"

int main(void) {
    auto console = new GB();
    console->Run();
    delete console;
}