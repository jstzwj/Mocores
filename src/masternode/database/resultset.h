#ifndef RESULTSET_H
#define RESULTSET_H
#include<vector>
#include<string>
namespace mocores
{
    class ResultSet
    {
    public:
        ResultSet();
        std::vector<std::vector<std::string>> data;
    };
}


#endif // RESULTSET_H
