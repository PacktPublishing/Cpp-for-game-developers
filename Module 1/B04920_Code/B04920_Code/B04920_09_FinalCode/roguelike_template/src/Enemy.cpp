#include "PCH.h"
#include "Enemy.h"

// Default constructor.
Enemy::Enemy() :
m_currentTarget({ 0.f, 0.f })
{
	// Set stats.
	m_health = std::rand() % 41 + 80;
	m_attack = std::rand() % 5 + 6;
	m_defense = std::rand() % 5 + 6;
	m_strength = std::rand() % 5 + 6;
	m_dexterity = std::rand() % 5 + 6;
	m_stamina = std::rand() % 5 + 6;

	// Set speed.
	m_speed = rand() % 51 + 150;
}

// Overrides the default Update function of Entity.
void Enemy::Update(float timeDelta)
{
	// Move towards current target location.
	if (!m_targetPositions.empty())
	{
		sf::Vector2f targetLocation = m_targetPositions.front();
		m_velocity = sf::Vector2f(targetLocation.x - m_position.x, targetLocation.y - m_position.y);

		if (abs(m_velocity.x) < 10.f && abs(m_velocity.y) < 10.f)
		{
			m_targetPositions.erase(m_targetPositions.begin());
		}
		else
		{
			float length = sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);
			m_velocity.x /= length;
			m_velocity.y /= length;

			m_position.x += m_velocity.x * (m_speed * timeDelta);
			m_position.y += m_velocity.y * (m_speed * timeDelta);

			m_sprite.setPosition(m_position);
		}
	}

	// Call Entity update.
	Entity::Update(timeDelta);
}

// Recalculates the enemies path finding.
void Enemy::UpdatePathfinding(Level& level, sf::Vector2f playerPosition)
{
	// Create all variables.
	std::vector<Tile*> openList;
	std::vector<Tile*> closedList;
	std::vector<Tile*> pathList;
	std::vector<Tile*>::iterator position;
	Tile* currentNode;

	// Reset all nodes.
	level.ResetNodes();

	// Store the start and goal nodes.
	Tile* startNode = level.GetTile(m_position);
	Tile* goalNode = level.GetTile(playerPosition);

	// Check we have a valid path to find. If not we can just end the function as there's no path to find.
	if (startNode == goalNode)
	{
		// Clear the vector of target positions.
		m_targetPositions.clear();

		// Exit the function.
		return;
	}

	// Pre-compute our H cost (estimated cost to goal) for each node.
	for (int i = 0; i < level.GetSize().x; i++)
	{
		for (int j = 0; j < level.GetSize().y; j++)
		{
			int rowOffset, heightOffset;
			Tile* node = level.GetTile(i, j);

			heightOffset = abs(node->rowIndex - goalNode->rowIndex);
			rowOffset = abs(node->columnIndex - goalNode->columnIndex);

			node->H = heightOffset + rowOffset;
		}
	}

	// Add the start node to the open list.
	openList.push_back(startNode);

	// While we have values to check in the open list.
	while (!openList.empty())
	{
		// Find the node in the open list with the lowest F value and mark it as current.
		int lowestF = INT_MAX;

		for (Tile* tile : openList)
		{
			if (tile->F < lowestF)
			{
				lowestF = tile->F;
				currentNode = tile;
			}
		}

		// Remove the current node from the open list and add it to the closed list.
		position = std::find(openList.begin(), openList.end(), currentNode);
		if (position != openList.end())
			openList.erase(position);

		closedList.push_back(currentNode);

		// Find all valid adjacent nodes.
		std::vector<Tile*> adjacentTiles;
		Tile* node;

		// Top.
		node = level.GetTile(currentNode->columnIndex, currentNode->rowIndex - 1);
		if ((node != nullptr) && (level.IsFloor(*node)))
		{
			adjacentTiles.push_back(level.GetTile(currentNode->columnIndex, currentNode->rowIndex - 1));
		}

		// Right.
		node = level.GetTile(currentNode->columnIndex + 1, currentNode->rowIndex);
		if ((node != nullptr) && (level.IsFloor(*node)))
		{
			adjacentTiles.push_back(level.GetTile(currentNode->columnIndex + 1, currentNode->rowIndex));
		}

		// Bottom.
		node = level.GetTile(currentNode->columnIndex, currentNode->rowIndex + 1);
		if ((node != nullptr) && (level.IsFloor(*node)))
		{
			adjacentTiles.push_back(level.GetTile(currentNode->columnIndex, currentNode->rowIndex + 1));
		}

		// Left.
		node = level.GetTile(currentNode->columnIndex - 1, currentNode->rowIndex);
		if ((node != nullptr) && (level.IsFloor(*node)))
		{
			adjacentTiles.push_back(level.GetTile(currentNode->columnIndex - 1, currentNode->rowIndex));
		}

		// For all adjacent nodes.
		for (Tile* node : adjacentTiles)
		{
			// If the node is our goal node.
			if (node == goalNode)
			{
				// Parent the goal node to current.
				node->parentNode = currentNode;

				// Store the current path.
				while (node->parentNode != nullptr)
				{
					pathList.push_back(node);
					node = node->parentNode;
				}

				// Empty the open list and break out of our for loop.
				openList.clear();
				break;
			}
			else
			{
				// If the node is not in the closed list.
				position = std::find(closedList.begin(), closedList.end(), node);
				if (position == closedList.end())
				{
					// If the node is not in the open list.
					position = std::find(openList.begin(), openList.end(), node);
					if (position == openList.end())
					{
						// Add the node to the open list.
						openList.push_back(node);

						// Set the parent of the node to the current node.
						node->parentNode = currentNode;

						// Calculate G (total movement cost so far) cost.
						node->G = currentNode->G + 10;

						// Calculate the F (total movement cost + heuristic) cost.
						node->F = node->G + node->H;
					}
					else
					{
						// Check if this path is quicker that the other.
						int tempG = currentNode->G + 10;

						// Check if tempG is faster than the other. I.e, whether it's faster to go A->C->B that A->C.
						if (tempG < node->G)
						{
							// Re-parent node to this one.
							node->parentNode = currentNode;
						}
					}
				}
			}
		}
	}

	// Clear the vector of target positions.
	m_targetPositions.clear();

	// Store the node locations as the enemies target locations.
	for (Tile* tile : pathList)
	{
		m_targetPositions.push_back(level.GetActualTileLocation(tile->columnIndex, tile->rowIndex));
	}

	// Reverse the target position as we read them from goal to origin and we need them the other way around.
	std::reverse(m_targetPositions.begin(), m_targetPositions.end());
}

// Applies the given amount of damage to the enemy.
void Enemy::Damage(int damage)
{
	m_health -= damage;
}

// Checks if the enemy has taken enough damage that they are now dead.
bool Enemy::IsDead()
{
	return (m_health <= 0);
}