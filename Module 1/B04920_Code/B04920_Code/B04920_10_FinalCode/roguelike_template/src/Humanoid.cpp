#include "PCH.h"
#include "Humanoid.h"

// Default constructor.
Humanoid::Humanoid()
{
	// Generate a humanoid type. (Skeleton or Goblin)
	HUMANOID humanoidType = static_cast<HUMANOID>(rand() % static_cast<int>(HUMANOID::COUNT));
	std::string enemyName;

	// Set enemy specific variables.
	switch (humanoidType)
	{
	case HUMANOID::GOBLIN:
		enemyName = "goblin";
		break;

	case HUMANOID::SKELETON:
		enemyName = "skeleton";
		break;
	}

	// Load textures.
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)] = TextureManager::AddTexture("../resources/enemies/" + enemyName + "/spr_" + enemyName + "_walk_up.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)] = TextureManager::AddTexture("../resources/enemies/" + enemyName + "/spr_" + enemyName + "_walk_down.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_RIGHT)] = TextureManager::AddTexture("../resources/enemies/" + enemyName + "/spr_" + enemyName + "_walk_right.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_LEFT)] = TextureManager::AddTexture("../resources/enemies/" + enemyName + "/spr_" + enemyName + "_walk_left.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_UP)] = TextureManager::AddTexture("../resources/enemies/" + enemyName + "/spr_" + enemyName + "_idle_up.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_DOWN)] = TextureManager::AddTexture("../resources/enemies/" + enemyName + "/spr_" + enemyName + "_idle_down.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_RIGHT)] = TextureManager::AddTexture("../resources/enemies/" + enemyName + "/spr_" + enemyName + "_idle_right.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_LEFT)] = TextureManager::AddTexture("../resources/enemies/" + enemyName + "/spr_" + enemyName + "_idle_left.png");

	// Set initial sprite.
	SetSprite(TextureManager::GetTexture(m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)]), false, 8, 12);

	// Copy textures.
	for (int i = 0; i < static_cast<int>(ANIMATION_STATE::COUNT); i++)
	{
		m_textures[i] = TextureManager::GetTexture(m_textureIDs[i]);
	}

	// Generate armor.
	GenerateArmor();
}

// Generates random armor for the humanoid.
void Humanoid::GenerateArmor()
{
	// Create arrays of textures for our armor, and the final versions.
	const int textureCount = static_cast<int>(ANIMATION_STATE::COUNT);
	sf::RenderTexture armorTextures[textureCount];
	sf::RenderTexture finalTextures[textureCount];
	sf::Image renderImage;

	// Setup all render textures.
	for (int i = 0; i < static_cast<int>(ANIMATION_STATE::COUNT); i++)
	{
		sf::Vector2u textureSize = m_textures[i].getSize();

		armorTextures[i].create(textureSize.x, textureSize.y);
		finalTextures[i].create(textureSize.x, textureSize.y);
	}

	// Create variables to determine what armor be created.
	int hasHelmet(0), hasTorso(0), hasLegs(0);

	hasHelmet = rand() % 5;
	hasTorso = rand() % 5;
	hasLegs = rand() % 5;

	// Spawn helmet.
	if (hasHelmet == 0)
	{
		// Load the default helmet textures.
		int defaultHelmetTextureIDs[static_cast<int>(ANIMATION_STATE::COUNT)];

		defaultHelmetTextureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)] = TextureManager::AddTexture("../resources/armor/helmet/spr_helmet_walk_front.png");
		defaultHelmetTextureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)] = TextureManager::AddTexture("../resources/armor/helmet/spr_helmet_walk_front.png");
		defaultHelmetTextureIDs[static_cast<int>(ANIMATION_STATE::WALK_RIGHT)] = TextureManager::AddTexture("../resources/armor/helmet/spr_helmet_walk_side.png");
		defaultHelmetTextureIDs[static_cast<int>(ANIMATION_STATE::WALK_LEFT)] = TextureManager::AddTexture("../resources/armor/helmet/spr_helmet_walk_side.png");
		defaultHelmetTextureIDs[static_cast<int>(ANIMATION_STATE::IDLE_UP)] = TextureManager::AddTexture("../resources/armor/helmet/spr_helmet_idle_front.png");
		defaultHelmetTextureIDs[static_cast<int>(ANIMATION_STATE::IDLE_DOWN)] = TextureManager::AddTexture("../resources/armor/helmet/spr_helmet_idle_front.png");
		defaultHelmetTextureIDs[static_cast<int>(ANIMATION_STATE::IDLE_RIGHT)] = TextureManager::AddTexture("../resources/armor/helmet/spr_helmet_idle_side.png");
		defaultHelmetTextureIDs[static_cast<int>(ANIMATION_STATE::IDLE_LEFT)] = TextureManager::AddTexture("../resources/armor/helmet/spr_helmet_idle_side.png");

		// Generate random number to determine tier.
		sf::Color tierColor;
		int tierValue = rand() % 100 + 1;

		// Select which tier armor should be created.
		if (tierValue < 51)
		{
			tierColor = sf::Color(110, 55, 28, 255);	// Bronze.
		}
		else if (tierValue < 86)
		{
			tierColor = sf::Color(209, 208, 201, 255);	// Silver.
		}
		else
		{
			tierColor = sf::Color(229, 192, 21, 255);	// Gold.
		}

		// Render helmet to armor texture.
		for (int i = 0; i < static_cast<int>(ANIMATION_STATE::COUNT); i++)
		{
			// Load the default helmet texture and set its color.
			sf::Sprite tempSprite;
			tempSprite.setTexture(TextureManager::GetTexture(defaultHelmetTextureIDs[i]));
			tempSprite.setColor(tierColor);

			// Flip the texture vertically.
			sf::Vector2u size = armorTextures[i].getTexture().getSize();
			tempSprite.setTextureRect(sf::IntRect(0, size.y, size.x, -static_cast<int>(size.y)));

			// Draw the texture.
			armorTextures[i].draw(tempSprite);
		}
	}

	// Spawn torso.
	if (hasTorso == 0)
	{
		// Load the default torso textures.
		int defaultTorsoTextureIDs[static_cast<int>(ANIMATION_STATE::COUNT)];

		defaultTorsoTextureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)] = TextureManager::AddTexture("../resources/armor/torso/spr_torso_walk_front.png");
		defaultTorsoTextureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)] = TextureManager::AddTexture("../resources/armor/torso/spr_torso_walk_front.png");
		defaultTorsoTextureIDs[static_cast<int>(ANIMATION_STATE::WALK_RIGHT)] = TextureManager::AddTexture("../resources/armor/torso/spr_torso_walk_side.png");
		defaultTorsoTextureIDs[static_cast<int>(ANIMATION_STATE::WALK_LEFT)] = TextureManager::AddTexture("../resources/armor/torso/spr_torso_walk_side.png");
		defaultTorsoTextureIDs[static_cast<int>(ANIMATION_STATE::IDLE_UP)] = TextureManager::AddTexture("../resources/armor/torso/spr_torso_idle_front.png");
		defaultTorsoTextureIDs[static_cast<int>(ANIMATION_STATE::IDLE_DOWN)] = TextureManager::AddTexture("../resources/armor/torso/spr_torso_idle_front.png");
		defaultTorsoTextureIDs[static_cast<int>(ANIMATION_STATE::IDLE_RIGHT)] = TextureManager::AddTexture("../resources/armor/torso/spr_torso_idle_side.png");
		defaultTorsoTextureIDs[static_cast<int>(ANIMATION_STATE::IDLE_LEFT)] = TextureManager::AddTexture("../resources/armor/torso/spr_torso_idle_side.png");

		// Generate random number to determine tier.
		sf::Color tierColor;
		int tierValue = rand() % 100 + 1;

		// Select which tier armor should we created.
		if (tierValue < 51)
		{
			tierColor = sf::Color(110, 55, 28, 255);	// Bronze.
		}
		else if (tierValue < 86)
		{
			tierColor = sf::Color(209, 208, 201, 255);	// Silver.
		}
		else
		{
			tierColor = sf::Color(229, 192, 21, 255);	// Gold.
		}

		// Render torso to armor texture.
		for (int i = 0; i < static_cast<int>(ANIMATION_STATE::COUNT); i++)
		{
			sf::Sprite tempSprite;
			tempSprite.setTexture(TextureManager::GetTexture(defaultTorsoTextureIDs[i]));
			tempSprite.setColor(tierColor);

			// Flip the texture vertically.
			sf::Vector2u size = armorTextures[i].getTexture().getSize();
			tempSprite.setTextureRect(sf::IntRect(0, size.y, size.x, -static_cast<int>(size.y)));

			// Draw the texture.
			armorTextures[i].draw(tempSprite);
		}
	}

	// Spawn legs.
	if (hasLegs == 0)
	{
		// Load the default legs textures.
		int defaultLegsTextureIDs[static_cast<int>(ANIMATION_STATE::COUNT)];

		defaultLegsTextureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)] = TextureManager::AddTexture("../resources/armor/legs/spr_legs_walk_front.png");
		defaultLegsTextureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)] = TextureManager::AddTexture("../resources/armor/legs/spr_legs_walk_front.png");
		defaultLegsTextureIDs[static_cast<int>(ANIMATION_STATE::WALK_RIGHT)] = TextureManager::AddTexture("../resources/armor/legs/spr_legs_walk_side.png");
		defaultLegsTextureIDs[static_cast<int>(ANIMATION_STATE::WALK_LEFT)] = TextureManager::AddTexture("../resources/armor/legs/spr_legs_walk_side.png");
		defaultLegsTextureIDs[static_cast<int>(ANIMATION_STATE::IDLE_UP)] = TextureManager::AddTexture("../resources/armor/legs/spr_legs_idle_front.png");
		defaultLegsTextureIDs[static_cast<int>(ANIMATION_STATE::IDLE_DOWN)] = TextureManager::AddTexture("../resources/armor/legs/spr_legs_idle_front.png");
		defaultLegsTextureIDs[static_cast<int>(ANIMATION_STATE::IDLE_RIGHT)] = TextureManager::AddTexture("../resources/armor/legs/spr_legs_idle_side.png");
		defaultLegsTextureIDs[static_cast<int>(ANIMATION_STATE::IDLE_LEFT)] = TextureManager::AddTexture("../resources/armor/legs/spr_legs_idle_side.png");

		// Generate random number to determine tier.
		sf::Color tierColor;
		int tierValue = rand() % 100 + 1;

		// Select which tier armor should we created.
		if (tierValue < 51)
		{
			tierColor = sf::Color(110, 55, 28, 255);	// Bronze.
		}
		else if (tierValue < 86)
		{
			tierColor = sf::Color(209, 208, 201, 255);	// Silver.
		}
		else
		{
			tierColor = sf::Color(229, 192, 21, 255);	// Gold.
		}

		// Render legs to armor texture.
		for (int i = 0; i < static_cast<int>(ANIMATION_STATE::COUNT); i++)
		{
			sf::Sprite tempSprite;
			tempSprite.setTexture(TextureManager::GetTexture(defaultLegsTextureIDs[i]));
			tempSprite.setColor(tierColor);

			// Flip the texture vertically.
			sf::Vector2u size = armorTextures[i].getTexture().getSize();
			tempSprite.setTextureRect(sf::IntRect(0, size.y, size.x, -static_cast<int>(size.y)));

			// Draw the texture.
			armorTextures[i].draw(tempSprite);
		}
	}

	// Create the final textures.
	for (int i = 0; i < static_cast<int>(ANIMATION_STATE::COUNT); i++)
	{
		sf::Sprite baseSprite, armorSprite;

		// Draw the default texture.
		baseSprite.setTexture(m_textures[i]);
		finalTextures[i].draw(baseSprite);

		// Draw armor on top.
		armorSprite.setTexture(armorTextures[i].getTexture());
		finalTextures[i].draw(armorSprite);

		// Flip the texture vertically.
		sf::Image img = finalTextures[i].getTexture().copyToImage();
		img.flipVertically();

		// Store the resulting texture.
		m_textures[i].loadFromImage(img);
	}
}

// Overrides the update event of Enemy.
void Humanoid::Update(float timeDelta)
{
	// Call parent functionality.
	Enemy::Update(timeDelta);

	// Update the texture with our custom textures.
	m_sprite.setTexture(m_textures[m_currentTextureIndex]);
}