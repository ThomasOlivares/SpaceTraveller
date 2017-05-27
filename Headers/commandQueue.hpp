#ifndef COMMAND_QUEUE
#define COMMAND_QUEUE

#include "../Headers/command.hpp"
#include "../Headers/sceneNode.hpp"

#include <queue>

class CommandQueue{
	public:
		void push(const Command& command);
		Command pop();
		Command front();
		bool isEmpty() const;

	private:
		std::queue<Command> mQueue;
};

#endif //COMMAND_QUEUE