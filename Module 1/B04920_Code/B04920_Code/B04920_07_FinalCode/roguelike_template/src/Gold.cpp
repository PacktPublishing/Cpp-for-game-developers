#include "PCH.h"
#include "Gold.h"

// Default constructor.
Gold::Gold()
{
	// Randomly generate the value of the pickup.
	this->goldValue = std::rand() % 21 + 5;

	// Choose a sprite based on the gold value.
	int textureID;

	if (this->goldValue < 9)
	{
		textureID = TextureManager::AddTexture("../resources/loot/gold/spr_pickup_gold_small.png");
	}
	else if (this->goldValue >= 16)
	{
		textureID = TextureManager::AddTexture("../resources/loot/gold/spr_pickup_gold_large.png");
	}
	else
	{
		textureID = TextureManager::AddTexture("../resources/loot/gold/spr_pickup_gold_medium.png");
	}

	// Set the sprite.
	this->SetSprite(TextureManager::GetTexture(textureID), false, 8, 12);

	// Set the item type.
	m_type = ITEM::GOLD;
}

//  Returns the amount of gold this pickup has.
int Gold::GetGoldValue() const
{
	return this->goldValue;
}