#include <iostream>

#include <mocores/cluster/node.h>


int main(int argc, char *argv[])
{
	
	mocores::Node node;
	node.run(argc, argv);
	node.exit();

	
    return 0;
}