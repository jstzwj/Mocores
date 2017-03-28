#include <iostream>
#include<string>
#include"../../src/masternode/mvariant.h"
using namespace std;

int main(int argc, char *argv[])
{
    mocores::MVariant<int,double,std::string> var=std::string("123");
    cout << mocores::get<std::string>(var) << endl;
    var=1;
    cout << mocores::get<int>(var) << endl;
    var=1.0;
    cout << mocores::get<double>(var) << endl;
    return 0;
}
