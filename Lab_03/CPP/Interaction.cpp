#include "../Include/Interaction.hpp"



int SIZE = 1;
Point3D* MOTHER_ARRAY = new Point3D[SIZE];


void PrintArray(Point3D arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << "(" << arr[i].X << " " << arr[i].Y << " " << arr[i].Z << ")" << std::endl;
	}
	std::cout << std::endl;
}

int ReadPositiveInteger()
{
	int x;
	std::cin >> x;
	while (std::cin.fail()) {
		std::cout << "Invalid input! Enter positive integer! Not a character, INTEGER!!! It may look like this: 47" << std::endl;
		std::cout << "If it looks like Ɉɛɱɢɫɥɢɬɢ or -1, please, call exorcist." << std::endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> x;
	}
	return x;
}

void LaunchBenchmark()
{
	auto begin = std::chrono::steady_clock::now();
	auto end = std::chrono::steady_clock::now();
	auto time = 0.0;
	auto maxTime = 0.0;

	int elements = 10000;

	do 
	{
		std::cout << std::endl;
		elements *= 10;
		std::cout << "Creating array of " << elements << " elements" << std::endl;

		SilentShuffle(elements);
		Point3D* arr = new Point3D[SIZE];


		for (int i = 0; i < SIZE; i++) arr[i] = MOTHER_ARRAY[i];
		
		begin = std::chrono::steady_clock::now();
		InsertionSort(arr, 0, SIZE - 1);
		end = std::chrono::steady_clock::now();
		time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000.0;
		std::cout << "Insertion sort time: "<< time<< " miliseconds" << std::endl;
		if (time > maxTime)
			maxTime = time;

		for (int i = 0; i < SIZE; i++) arr[i] = MOTHER_ARRAY[i];

		begin = std::chrono::steady_clock::now();
		QuickSort(arr, 0, SIZE - 1);
		end = std::chrono::steady_clock::now();
		time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000.0;
		std::cout << "Quick sort time: " << time << " miliseconds" << std::endl;
		if (time > maxTime) maxTime = time;

		for (int i = 0; i < SIZE; i++) arr[i] = MOTHER_ARRAY[i];

		begin = std::chrono::steady_clock::now();
		MergeSort(arr, 0, SIZE - 1);
		end = std::chrono::steady_clock::now();
		time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000.0;
		std::cout << "Merge sort time: " << time << " miliseconds" << std::endl;
		if (time > maxTime) maxTime = time;

		delete[] arr;
	} while (maxTime < 10000);


}


void Shuffle()
{
	std::cout << std::endl;
	std::cout << "Enter array size : ";
	SIZE = ReadPositiveInteger();
	delete[] MOTHER_ARRAY;
	MOTHER_ARRAY = new Point3D[SIZE];

	double max = (INT16_MAX / 8.0);
	double min = (INT16_MIN / 8.0);

	double x, y, z, f;

	srand(time(NULL));
	for (int i = 0; i < SIZE; i++)
	{
		f = (double)rand() / RAND_MAX;
		x = min + f * (max - min);
		f = (double)rand() / RAND_MAX;
		y = min + f * (max - min);
		f = (double)rand() / RAND_MAX;
		z = min + f * (max - min);

		Point3D point = Point3D(x, y, z);
		MOTHER_ARRAY[i] = point;
	}
	if (SIZE < 1024)
		PrintArray(MOTHER_ARRAY, SIZE);
	else
		std::cout << "Your monitor is to small to fit " << SIZE << " elements. Please purchase compatible monitor." << std::endl;

	//mama mia system pause oh no shit what i have to do
	std::cout << "Pres eni ki to kontinue.,." << std::endl;
	_getch();
}

void SilentShuffle(int size)
{
	SIZE = size;
	delete[] MOTHER_ARRAY;
	MOTHER_ARRAY = new Point3D[SIZE];

	double max = (INT16_MAX / 8.0);
	double min = (INT16_MIN / 8.0);

	double x, y, z, f;

	srand(time(NULL));
	for (int i = 0; i < SIZE; i++)
	{
		f = (double)rand() / RAND_MAX;
		x = min + f * (max - min);
		f = (double)rand() / RAND_MAX;
		y = min + f * (max - min);
		f = (double)rand() / RAND_MAX;
		z = min + f * (max - min);

		Point3D point = Point3D(x, y, z);
		MOTHER_ARRAY[i] = point;
	}
}


void InsertionSortLaunch()
{
	std::cout << std::endl;
	auto begin = std::chrono::steady_clock::now();
	auto end = std::chrono::steady_clock::now();
	auto time = 0.0;

	Point3D* arr = new Point3D[SIZE];
	for (int i = 0; i < SIZE; i++) arr[i] = MOTHER_ARRAY[i];

	begin = std::chrono::steady_clock::now();
	InsertionSort(arr, 0, SIZE - 1);
	end = std::chrono::steady_clock::now();

	time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000.0;
	std::cout
		<< "Insertion sort time: "
		<< time
		<< " miliseconds (trust me, it sorted)" << std::endl;

	delete[] arr;
	std::cout << "system(\"pause\");" << std::endl;
	_getch();

	//PrintArray(arr, SIZE);
	//_getch();
}

void QuickSortLaunch()
{
	std::cout << std::endl;
	auto begin = std::chrono::steady_clock::now();
	auto end = std::chrono::steady_clock::now();
	auto time = 0.0;

	Point3D* arr = new Point3D[SIZE];
	for (int i = 0; i < SIZE; i++) arr[i] = MOTHER_ARRAY[i];

	begin = std::chrono::steady_clock::now();
	QuickSort(arr, 0, SIZE - 1);
	end = std::chrono::steady_clock::now();

	time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000.0;
	std::cout
		<< "Nesquick sort time: "
		<< time
		<< " miliseconds (trust me, it sorted)" << std::endl;

	delete[] arr;
	std::cout << "console, please wait" << std::endl;
	_getch();

	//PrintArray(arr, SIZE);
	//_getch();
}

void MergeSortLaunch()
{
	std::cout << std::endl;
	auto begin = std::chrono::steady_clock::now();
	auto end = std::chrono::steady_clock::now();
	auto time = 0.0;

	Point3D* arr = new Point3D[SIZE];
	for (int i = 0; i < SIZE; i++) arr[i] = MOTHER_ARRAY[i];

	begin = std::chrono::steady_clock::now();
	MergeSort(arr, 0, SIZE - 1);
	end = std::chrono::steady_clock::now();

	time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000.0;
	std::cout
		<< "Merge sort time: "
		<< time
		<< " miliseconds (trust me, it sorted)" << std::endl;

	delete[] arr;
	std::cout << "ZA WARUDO" << std::endl;
	_getch();

	//PrintArray(arr, SIZE);
	//_getch();
}
