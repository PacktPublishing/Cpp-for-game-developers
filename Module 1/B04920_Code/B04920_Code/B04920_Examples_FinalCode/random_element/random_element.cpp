#include <iostream>
#include <vector>

using namespace std;

// Entry method of the application.
int main()
{
	// Create and populate an array of animals.
	vector<string> animals = { "Dog", "Cat", "Bird", "Fox", "Lizard" };

	// Output the instructions.
	cout << "Press enter for the name of a random animal!" << endl;

	// Loop forever.
	while (true)
	{
		// Wait for user input.
		cin.get();

		// Generate a random index.
		int randomIndex;
		randomIndex = rand() % animals.size();

		// Output the name of the randomly selected animal.
		cout << animals[randomIndex].c_str();
	}

	// Exit function.
	return 0;
}