#include "CollisionManager.h"
#include <iostream>



CollisionManager::CollisionManager()
{
	this->collide = false;
}


CollisionManager::~CollisionManager()
{
}

sf::Vector2f CollisionManager::CollideWithWalls(const sf::FloatRect & rectSp1, const std::vector<sf::FloatRect> walls)
{
	sf::Vector2f dir(0, 0);
	for (int i = 0; i != walls.size(); i++)
	{
		if (sat_test(rectSp1, walls[i]))
		{
			this->collide = true;
			if((premtv.x == 0 && out_mtv.x == 0) || (premtv.y == 0 && out_mtv.y == 0))
			{
				dir += out_mtv;
			}
		}
	}
	if (dir.x == 0 && dir.y == 0)
	{
		this->collide = false;
		out_mtv = sf::Vector2f(0, 0);
		return
			sf::Vector2f(0, 0);
	}
	else
		return dir;
}

sf::Vector2f CollisionManager::CollideWithEntity(const sf::FloatRect & rectSp1, const sf::FloatRect & rectSp2)
{
	if (rectSp1 != rectSp2)
	{
		if (sat_test(rectSp1, rectSp2))
		{
			collide = true;
			return out_mtv;
		}
		collide = false;
		return out_mtv = sf::Vector2f(0.f, 0.f);
	}
	else 
		return out_mtv = sf::Vector2f(0.f, 0.f);
}

void CollisionManager::resetOutMtv()
{
	this->out_mtv = sf::Vector2f(0.f, 0.f);
}

bool CollisionManager::isCollide()
{
	return
		this->collide;
}

void CollisionManager::setPreMtv(sf::Vector2f vec)
{
	this->premtv = vec;
}

sf::Vector2f CollisionManager::getOutMtv()
{
	return
		this->out_mtv;
}

bool CollisionManager::sat_test(const sf::FloatRect & rectSp1, const sf::FloatRect & rectSp2)
{
	float proj_x, proj_y, overlap_x, overlap_y;

	// test overlap in x axis
	proj_x = std::max(rectSp1.left + rectSp1.width, rectSp2.left + rectSp2.width) - std::min(rectSp1.left, rectSp2.left);
	if (proj_x < rectSp1.width + rectSp2.width) {
		/*if (out_mtv)*/ {
			// calculate mtv in x
			overlap_x = rectSp1.width + rectSp2.width - proj_x;
		}
		// test overlap in y axis
		proj_y = std::max(rectSp1.top + rectSp1.height, rectSp2.top + rectSp2.height) - std::min(rectSp1.top, rectSp2.top);
		if (proj_y < rectSp1.height + rectSp2.height) {
			/*if (out_mtv)*/ {
				// calculate mtv in y
				overlap_y = rectSp1.height + rectSp2.height - proj_y;
				out_mtv.x = out_mtv.y = 0;

				// choose minimun overlap
				if (overlap_x < overlap_y) {
					out_mtv.x = overlap_x * (rectSp1.left < rectSp2.left ? -1 : 1);
				}
				else {
					out_mtv.y = overlap_y * (rectSp1.top < rectSp2.top ? -1 : 1);
				}
			}
			return true;
		}
	}
	return false;
}
