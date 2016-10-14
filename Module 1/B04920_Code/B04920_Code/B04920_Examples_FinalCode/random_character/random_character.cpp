#include <iostream>

using namespace std;

// Entry method of the application.
int main()
{
	// Loop forever.
	while (true)
	{
		// Output instructions.
		cout << "Press enter to generate a random character from the ASCII standard:" << endl;

		// Pause for user input.
		cin.get();

		// The ASCII characters range from 0 - 127 in decimal.
		int randInt = rand() % 128;

		// To turn that into a char, we can just assign the int.
		char randChar = randInt;

		// Output the random char.
		cout << "Random Char: " << randChar << "\n" << endl;
	}

	// Exit function.
	return 0;
}