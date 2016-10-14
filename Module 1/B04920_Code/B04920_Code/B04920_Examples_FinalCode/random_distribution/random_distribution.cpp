#include <iostream>

using namespace std;

// Entry method of the application.
int main()
{
	// Create and initialize our variables.
	int upperLimit = 0;

	// Output instructions.
	cout << "Enter a number, and we'll split it into three random smaller numbers:" << endl;
	cin >> upperLimit;
	cout << endl;

	float number1Bias = rand() % 101;
	float number2Bias = rand() % 101;
	float number3Bias = rand() % 101;

	float total = number1Bias + number2Bias + number3Bias;

	// Output the numbers.
	cout << "value 0: " << upperLimit * (number1Bias / total) << endl;
	cout << "value 1: " << upperLimit * (number2Bias / total) << endl;
	cout << "value 2: " << upperLimit * (number3Bias / total) << endl;

	// Pause so we can see output.
	cin.get();
	cin.get();

	// Exit function.
	return 0;
}