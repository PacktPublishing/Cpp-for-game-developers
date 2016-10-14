//-------------------------------------------------------------------------------------
// Player.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Written by Dale Green. Copyright (c) Packt Publishing. All rights reserved.
//-------------------------------------------------------------------------------------
#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Input.h"
#include "Level.h"
#include "Projectile.h"

class Player : public Entity
{
public:
	/**
	 * Default constructor.
	 */
	Player();

	/**
	 * Updates the player object.
	 * The main purpose of this function is to update the players position.
	 * @param timeDelta The time, in MS, since the last game tick.
	 * @param level A reference to the level object.
	 */
	void Update(float timeDelta, Level& level);

	/**
	 * Gets the player's current traits.
	 * @return The player's current traits.
	 */
	PLAYER_TRAIT* GetTraits();

	/**
	 * Gets the number of traits the player has.
	 */
	int GetTraitCount() const;

	/**
	* Gets the player's mana.
	* @return The player's mana.
	*/
	int GetMana() const;

	/**
	* Gets the player's max mana.
	* @return The player's max mana.
	*/
	int GetMaxMana() const;

	/**
	 * Set the player's health.
	 * @param healthValue The player's new health.
	 */
	void SetHealth(int healthValue);

	/**
	 * Set the player's mana level.
	 * @param mana The new mana value.
	 */
	void SetMana(int manaValue);

	/**
	 * Chooses random traits for the character.
	 */
	void SetRandomTraits();

	/**
	 * Gets the player's class.
	 * @return The player's class.
	 */
	PLAYER_CLASS GetClass() const;

	/**
	 * Gets the player's aim sprite.
	 * return The player's aim sprite.
	 */
	sf::Sprite& GetAimSprite();

	/**
	 * Checks if the player is currently attacking.
	 * @return True if the player is attacking.
	 */
	bool IsAttacking();

	/**
	 * Checks if the player can take damage.
	 * @return True if the player can take damage.
	 */
	bool CanTakeDamage();

	/**
	 * Apply the given amount of damage to the player.
	 * @param damage The amount of damage to deal to the player.
	 */
	void Damage(int damage);

private:

	/**
	 * Checks if the given movement will result in a collision.
	 * @param movement The movement to check.
	 * @param level A reference to the level object.
	 * @return True if the given movement will result in a collision.
	 */
	bool CausesCollision(sf::Vector2f movement, Level& level);

private:

	/**
	 * The number of traits that the player can have.
	 */
	static const int PLAYER_TRAIT_COUNT = 2;

	/**
	 * An array containing the character's traits.
	 */
	PLAYER_TRAIT m_traits[PLAYER_TRAIT_COUNT];

	/**
	 * The player's class.
	 */
	PLAYER_CLASS m_class;

	/**
	 * The sprite for the player's aim cross hair.
	 */
	sf::Sprite m_aimSprite;

	/**
	 * The time since the player's last attack.
	 */
	float m_attackDelta;

	/**
	 * The time since the player last took damage.
	 */
	float m_damageDelta;

	/**
	 * The time since the last mana regeneration.
	 */
	float m_manaDelta;

	/**
	 * Is the player attacking.
	 */
	bool m_isAttacking;

	/**
	 * Can the player take damage.
	 */
	bool m_canTakeDamage;

	/**
	* The number of stat points the entities has to distribute.
	*/
	int m_statPoints;
};
#endif