#ifndef CLI_IO_H
#define CLI_IO_H
#include<iostream>
#include<string>
namespace mocores
{
    //!Print a string on the console
    void cliPrint(const char * str);
    //!Read a string from console
    void cliGetline(char *str, unsigned int len);
}

#endif // CLI_IO_H
