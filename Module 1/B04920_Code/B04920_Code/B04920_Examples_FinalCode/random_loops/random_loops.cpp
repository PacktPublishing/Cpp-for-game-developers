#include <iostream>
#include <ctime>

using namespace std;

void HelloWorld();

// Entry method of the application.
int main()
{
	// First we give the application a random seed.
	srand(static_cast<unsigned int>(time(nullptr)));

	// Loop forever.
	while (true)
	{
		// oOutput the welcome message.
		cout << "Press enter to iterate a random number of times:" << endl;

		// Pause for user input.
		cin.get();

		// Generate a random number between 1 and 10.
		int iterations = rand() % 10 + 1;

		// Now loop that number of times.
		for (int i = 0; i < iterations; i++)
		{
			cout << "Iteration " << i << ": ";
			HelloWorld();
		}

		// Output ending message.
		cout << endl << "We made " << iterations << " call(s) to HelloWorld() that time!" << endl << endl;
	}

	// Exit function.
	return 0;
}

// Outputs the text Hello World!
void HelloWorld()
{
	cout << "Hello World!" << endl;
}