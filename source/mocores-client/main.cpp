#include <iostream>

#include <boost/log/trivial.hpp>


int main()
{
    BOOST_LOG_TRIVIAL(info) << "Mocores client is starting.";
    std::cout<<"hello world"<<std::endl;
	BOOST_LOG_TRIVIAL(info) << "Mocores client is existing.";
    return 0;
}