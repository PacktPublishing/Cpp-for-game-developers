#include "PCH.h"
#include "Slime.h"

// Default constructor.
Slime::Slime()
{
	// Load textures.
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)] = TextureManager::AddTexture("../resources/enemies/slime/spr_slime_walk_up.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)] = TextureManager::AddTexture("../resources/enemies/slime/spr_slime_walk_down.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_RIGHT)] = TextureManager::AddTexture("../resources/enemies/slime/spr_slime_walk_right.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_LEFT)] = TextureManager::AddTexture("../resources/enemies/slime/spr_slime_walk_left.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_UP)] = TextureManager::AddTexture("../resources/enemies/slime/spr_slime_idle_up.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_DOWN)] = TextureManager::AddTexture("../resources/enemies/slime/spr_slime_idle_down.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_RIGHT)] = TextureManager::AddTexture("../resources/enemies/slime/spr_slime_idle_right.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_LEFT)] = TextureManager::AddTexture("../resources/enemies/slime/spr_slime_idle_left.png");

	// Set initial sprite.
	SetSprite(TextureManager::GetTexture(m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)]), false, 8, 12);

	// Choose the random sprite color and set it.
	int r, g, b, a;

	r = rand() % 256;
	g = rand() % 256;
	b = rand() % 256;
	a = rand() % 156 + 100;
	sf::Color color(r, g, b, 255);

	m_sprite.setColor(color);

	// Generate a random scale between 0.5 and 1.5 and set it.
	float scale;
	scale = (rand() % 11 + 5) / 10.f;

	m_sprite.setScale(sf::Vector2f(scale, scale));
}