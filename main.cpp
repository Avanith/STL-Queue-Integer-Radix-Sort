/* @purp  This program uses a queue to implement a radixSort for integers.
@file  main.cpp
@author Daniel Targonski
@date  12/4/2020
*/

#include<iostream>
#include<queue>
#include<fstream>
#include<array>
#include<string>
#include<sstream>
#include<math.h>
#include<ctime>

using namespace std;

/**  radixSort for an integer array
@param arr[] integer array.
n is the size of the array.
d is highest digit number.
@pre  array has integers in it. proper size and max digits are passed
@post  the passed integer array is sorted.
*/
void radixSort(int arr[], int n, int d);

int main()
{
	const int ARRAYSIZE = 45;
	int arr[ARRAYSIZE], i;

	ifstream nums("nums.txt");
	if (!nums.good()) {
		cerr << "File failed to open.\n";
		exit(-1);
	}

	cout << "The unsorted array: \n";
	for (i = 0; i < ARRAYSIZE; i++)
	{
		nums >> arr[i];
		cout << arr[i] << ' ';

		if (i % 10 == 5)
			cout << "\n";
	}
	cout << endl;

	radixSort(arr, ARRAYSIZE, 3);

	cout << "\n\nThe final sorted array: \n";
	for (i = 0; i < ARRAYSIZE; i++)
	{
		cout << arr[i] << ' ';

		if (i % 10 == 5)
			cout << "\n";
	}
	cout << "\n\n";

	srand(time(0));
	cout << "With 45 random numbers: \n";
	for (int i = 0; i < ARRAYSIZE; i++)
	{
		arr[i] = rand() % 1000 + 1;
		cout << arr[i] << " ";
		if (i % 10 == 5)
			cout << "\n";
	}
	cout << endl;
	radixSort(arr, ARRAYSIZE, 3);

	cout << "Final sorted array: \n";
	for (int i = 0; i < ARRAYSIZE; i++)
	{
		cout << arr[i] << " ";
		if (i % 10 == 5)
			cout << "\n";
	}
	cout << "\n\n";
}

/*
for example to isolate a digit at a time from right to left:

//k = jth digit of theArray[i]
int divisor = pow(10, d-j);
int num = theArray[i];
int k = static_cast ((num / divisor) % 10);

//Place theArray[i] at the end of group k
groups[k].push(num);
*/

// n decimal integers, d decimal integers each

void radixSort(int arr[], int n, int d)
{
	int j, k, i, divisor, num, counter{};
	for (j = d; j >= 1; j--)
	{
		queue<int> groups[10];
		int count[10] = { 0 };
		for (i = 0; i < n; i++)
		{
			divisor = pow(10, d - j);
			num = arr[i];
			k = static_cast<int>((num / divisor) % 10);
			groups[k].push(arr[i]);
			count[k]++;
		}
		counter = 0;
		for (i = 0; i < 10; i++)
		{
			while (count[i] != 0)
			{
				arr[counter] = groups[i].front();
				groups[i].pop();
				count[i]--;
				counter++;
			}
			// the following works too, to get the numbers out
			// of the queue and into the array
			//while (!groups[i].empty())
			//{
			//    arr[counter] = groups[i].front();
			//    groups[i].pop();
			//    counter++;
			//}
		}
		cout << "\nThe array after pass " << d - j + 1 << ": \n";
		for (i = 0; i < n; i++)
		{
			cout << arr[i] << ' ';
			if (i % 10 == 5)
				cout << endl;
		}
		cout << "\n\n";
	}
}

/*
// Sorts n d-digit integers in the array theArray.
radixSort(theArray: ItemArray, n: integer, d: integer): void
{
   for (j = d down to 1)
   {
	  Initialize 10 groups to empty
	  Initialize a counter for each group to 0
	  for (i = 0 through n − 1)
	  {
		 k = jth digit of theArray[i]
		 Place theArray[i] at the end of group k
		 Increase kth counter by 1
	  }
	  Replace the items in theArray with all the items in group 0,
		followed by all the items in group 1, and so on.
   }
}
*/