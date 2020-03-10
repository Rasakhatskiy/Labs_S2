#ifndef TASK_SCHEDULER_HPP
#define TASK_SCHEDULER_HPP

class TaskScheduler
{
private:
	struct Node
	{
		long Time;
		int Priority;
		Node* Next;

		Node() = default;
		Node(long time, int priority, Node* next)
		{
			Time = time;
			Priority = priority;
			Next = next;
		}
	};

	Node* Root;
	Node* Current;
	bool Error;
public:
	TaskScheduler();
	void Push(long time, int priority);
	void Interrupt();
	void Work(long time);
	bool IsError();
};

TaskScheduler::TaskScheduler()
{
	Root = nullptr;
}

void TaskScheduler::Push(long time, int priority)
{
	try
	{
		if (Root == nullptr)
		{
			Root = new Node(time, priority, nullptr);
			return;
		}

		if (priority < Root->Priority)
		{
			auto node = new Node(time, priority, Root);
			Root = node;
			return;
		}

		if (priority == Root->Priority)
		{
			if (time < Root->Time)
			{
				auto node = new Node(time, priority, Root);
				Root = node;
			}
			else
			{
				auto next = Root->Next;
				Root->Next = new Node(time, priority, next);
			}
			return;
		}

		auto current = Root;

		while (current->Next != nullptr && priority > current->Next->Priority)
			current = current->Next;

		while (current->Next != nullptr && time >= current->Next->Time)
			current = current->Next;


		auto next = current->Next;
		current->Next = new Node(time, priority, next);
	}
	catch (...)
	{
		Error = true;
	}

	return;
}

#endif // !TASK_SCHEDULER_HPP
