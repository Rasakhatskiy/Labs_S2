#include "..\Include\List.hpp"

template <typename Type> 
void List<Type>::CreateEmpty()
{
	Size = 0;
	RealSize = MIN_REAL_SIZE;
	delete[] Array;
	Array = new Type[MIN_REAL_SIZE];
}

template<typename Type>
int List<Type>::Length()
{
	return Size;
}

template<typename Type>
void List<Type>::Insert(Type element, int index)
{
	if (index < Size)
	{
		//throw
	}

	if (Size == RealSize)
	{
		//todo
	}

	return 0;
}

template<typename Type>
void List<Type>::Remove(int index)
{
	//todo
}

template<typename Type>
Type List<Type>::Get(int index)
{
	//todo
	return Type();
}

template<typename Type>
void List<Type>::Set(Type element, int index)
{
	//todo
}

template<typename Type>
void List<Type>::Upgrade(int size)
{
	Type* temp = new Type[RealSize + size];
	for (int i = 0; i < Size; i++) temp[i] = Array[i];
	Array = temp;
	delete[] temp;
}

template<typename Type>
void List<Type>::Downgrade(int size)
{
	Type* temp = new Type[RealSize - size];
	for (int i = 0; i < Size; i++) temp[i] = Array[i];
	Array = temp;
	delete[] temp;
}

template <typename Type> 
List<Type>::List()
{
	//Ahahaha you expected code here, but it's me - NULL
}

template<typename Type>
List<Type>::~List()
{
	delete[] Array;
}

