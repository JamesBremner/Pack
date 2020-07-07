#include "cPackEngine.h"

cPackEngine thePackEngine;

int main( int argc, char* argv[] )
{
    thePackEngine.Build(
        "b1:in:-1:10x10:100",
        "i1:in:7:200:1x1:1" );        // spin disallowed
    thePackEngine.Pack();

    std::cout << "Bins used: " << thePackEngine.CountBinsUsed() << "\n";

    return 0;
}
