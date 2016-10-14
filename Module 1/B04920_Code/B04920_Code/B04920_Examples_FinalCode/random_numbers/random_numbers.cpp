// Random number generation
// This program will generate a random number each time we press enter.

#include <iostream>

using namespace std;

int main()
{
	while (true)
	{
		cout << "Press enter to generate a random number:";
		cin.get();

		// Generate a random integer.
		int randomInteger = rand();

		cout << randomInteger << endl << endl;
	}

	return 0;
}