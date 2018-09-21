#ifndef MOCORES_COMMON_MESSAGE_H
#define MOCORES_COMMON_MESSAGE_H

#include <string>
#include <list>
#include <vector>

namespace mocores
{
	class CallMessage
	{
	public:
		std::string actor_name;
		std::string actor_identity;
		std::string actor_method;
		std::list<> parameters;
	};

	class ReturnMessage
	{
	public:
		std::string actor_name;
		std::string actor_identity;
		std::string actor_method;
		std::list<> parameters;
	};
}

#endif // !MOCORES_COMMON_MESSAGE_H
