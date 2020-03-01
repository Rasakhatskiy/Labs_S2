#ifndef LIST_HPP
#define LIST_HPP

template <typename Type>
class List
{
public:
	//Does nothing, because i see no difference between constructor and create_empty
	List<Type>();

	//Deletes *array[]
	~List();
	
	//Creates an empty list or just clears current
	void CreateEmpty();

	//Returns current number of nodes in list
	int Length();

	//Inserts element BEFORE index
	void Insert(Type element, int index);

	//Removes element at position
	void Remove(int index);

	//Retuns element by id, returns NULL if there's no such id
	Type Get(int index);

	//Replaces element at index with given element
	void Set(Type element, int index);

private:
	struct Node
	{
		Type Value;
		Node* Next;
		Node* Previous;
	};

	//minimal real size of dynamic array
	const int MIN_REAL_SIZE = 16;

	//Real size of dynamic array
	int RealSize;

	//Shown size to user
	int Size;

	//Dynamic array of objects
	Type* Array[];

	//Increases array size by value
	void Upgrade(int size);

	//Decreases array size by value
	void Downgrade(int size);
};

#endif // !LIST_HPP

