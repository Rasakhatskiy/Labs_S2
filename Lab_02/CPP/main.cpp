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
	//list.CreateEmpty();
}