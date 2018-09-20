#include <iostream>

#include <boost/log/trivial.hpp>


int main()
{
    BOOST_LOG_TRIVIAL(info) << "Mocores client starts";
    std::cout<<"hello world"<<std::endl;
    return 0;
}