#include <iostream>
#include"../../src/masternode/mvariant.h"
using namespace std;

int main(int argc, char *argv[])
{
    mocores::MVariant<int,double,bool> var;
    var=1;
    cout << mocores::get<int>(var) << endl;
    return 0;
}
