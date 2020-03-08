#include "..\Include\List.hpp"
#include "..\Include\Point.hpp"

int main()
{
	List<int> list = List<int>();
	list.Insert(13, 0);
	list.Insert(12, 0);
	list.Insert(14, 1);
	list.Insert(15, 2);
	//12 14 15 13
	list.Remove(3);
	//12 14 15
	int a = list.Get(0);
	int b = list.Get(1);
	int c = list.Get(2);

	list.Set(47, 1);

	a = list.Get(0);
	b = list.Get(1);
	c = list.Get(2);
	//list.CreateEmpty();
}