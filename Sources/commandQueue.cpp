#include "../Headers/commandQueue.hpp"

void CommandQueue::push(const Command& command)
{
	mQueue.push(command);
}

Command CommandQueue::pop()
{
	Command command = mQueue.front();
	mQueue.pop();
	return command;
}

Command CommandQueue::front()
{
	Command command = mQueue.front();
	return command;
}

bool CommandQueue::isEmpty() const
{
	return mQueue.empty();
}

