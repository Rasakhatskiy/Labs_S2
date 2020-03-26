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

		Node() 
		{
			Time = NULL;
			Priority = NULL;
			Next = nullptr;
		}
		Node(long time, int priority, Node* next)
		{
			Time = time;
			Priority = priority;
			Next = next;
		}
	};

	Node* Root;
	Node Current;
	bool Error;

	Node Pop();
	void Push(long time, int priority);

	void Interrupt();

public:
	void Insert(long time, int priority);

	TaskScheduler();
	void WorkOnce();
	void WorkLong(long time);
	bool IsError();
};

TaskScheduler::TaskScheduler()
{
	Root = nullptr;
	Current = Node();
	Current.Time = NULL;
}

void TaskScheduler::Push(long time, int priority)
{
	try
	{
		//no time so it already completed
		if (time == NULL)
			return;

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

void TaskScheduler::Insert(long time, int priority)
{
	if (Current.Time != NULL && time < Current.Time)
	{
		Push(Current.Time, Current.Priority);
		Current.Time = time;
		Current.Priority = priority;
	}
	else
	{
		Push(time, priority);
	}
}

void TaskScheduler::WorkOnce()
{
	//if there is no work, just don't work
	if (Current.Time == NULL && Root == nullptr) return;

	//begin to work finally, if still no work
	if(Current.Time == NULL) Current = Pop();

	//if this task completed, take next one
	if (--Current.Time == 0) Current = Pop();
}

void TaskScheduler::WorkLong(long time)
{
	for (long i = 0; i < time; i++) WorkOnce();
}

TaskScheduler::Node TaskScheduler::Pop()
{
	try
	{
		if (Root == nullptr)
		{
			throw std::out_of_range("Queue is empty");
		}
		if (Root->Next == nullptr)
		{
			auto value = *Root;
			delete Root;
			return value;
		}
		{
			auto value = *Root;
			auto node = Root;
			Root = Root->Next;
			delete node;
			return value;
		}
	}
	catch (...)
	{
		Error = true;
	}
	return Node();
}

#endif // !TASK_SCHEDULER_HPP
