#include <iostream>

// We're using namespace std here to avoid having to fully qualify everything with std::.
using namespace std;

int main()
{

	// Here we define a base Weapon struct.
	// It provides a single data type, and a method to return it.
	struct Weapon
	{
		string itemType = "Generic Weapon";

		virtual string GetItemType()
		{
			return itemType;
		}
	};

	// Here we inherit from the generic Weapon struct to make a specific Sword struct.
	// We override the GetItemType() function to change the itemType variable before returning it.
	struct Sword : public Weapon
	{
		string GetItemType() override
		{
			itemType = "Sword";
			return itemType;
		}
	};


	Weapon myWeapon = Sword();

	// Output the type of item that weapon is then wait.
	cout << myWeapon.GetItemType().c_str() << endl;
	std::cin.get();

	return 0;
}
