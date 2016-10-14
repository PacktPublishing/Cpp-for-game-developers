//-------------------------------------------------------------------------------------
// Enemy.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Written by Dale Green. Copyright (c) Packt Publishing. All rights reserved.
//-------------------------------------------------------------------------------------
#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "Level.h"

class Enemy : public Entity
{
public:
	/**
	 * Default constructor.
	 */
	Enemy();

	/**
	 * Overrides the default Update function of Entity.
	 * @param timeDelta The time that has elapsed since the last update.
	 */
	virtual void Update(float timeDelta) override;

	/**
	 * Recalculates the enemies path finding.
	 * @param level A reference to the level object.
	 * @param playerPosition The position of the player within the level.
	 */
	void UpdatePathfinding(Level& level, sf::Vector2f playerPosition);

	/**
	 * Applies the given amount of damage to the enemy.
	 * @param damage The amount of damage to deal to the enemy.
	 */
	void Damage(int damage);

	/**
	 * Checks if the enemy has taken enough damage that they are now dead.
	 * @return True if the enemy is dead.
	 */
	bool IsDead();

protected:
	/**
	 * The target position of the enemy.
	 */
	std::vector<sf::Vector2f> m_targetPositions;

	/**
	 * The current target of the enemy.
	 */
	sf::Vector2f m_currentTarget;
};
#endif