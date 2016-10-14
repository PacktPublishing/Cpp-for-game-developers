#include <iostream>

using namespace std;

int main()
{
	// Loop forever.
	while (true)
	{
		// Generate a number between 0 and 1.
		bool myBool = rand() % 2;

		if (myBool)
		{
			cout << "true";
		}
		else
		{
			cout << "false";
		}

		cin.get();
	}

	return 0;
}