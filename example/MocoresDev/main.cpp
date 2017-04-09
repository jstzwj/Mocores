#include <iostream>
#include<regex>
using namespace std;

int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;
    std::string result="%d123";
    std::smatch match;
    std::regex timeReg ("%d{(.*?)}");
    while (std::regex_search(result,match,timeReg)) {
        result=match.prefix().str()+match.suffix().str();
    }
    return 0;
}
