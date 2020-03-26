#include "../Include/Menu.hpp"
#include "../Include/PriorityQueue.hpp"
#include "../Include/TaskScheduler.hpp"


int main()
{
	//sorry there is no menu for this lab, but you can try solve some linear algebra instead
	//linear algebra module have higher priority than console menu and also takes more time

	TaskScheduler task;
	task.Insert(10, 1);
	task.Insert(10, 2);
	task.Insert(5, 1);
	task.Insert(15, 2);
	task.Insert(45, 0);
	task.Insert(2, 1);

	//[NULL] 45, 2, 5, 10, 10, 15


	task.WorkLong(40);
	//[5] 2, 5, 10, 10, 15

	task.WorkLong(8);
	//[4] 10, 10, 15

	task.Insert(5, 1);
	//[4] 5, 10, 10, 15

	task.Insert(2, 1);
	//[2] 4, 5, 10, 10, 15

	return 0;
}