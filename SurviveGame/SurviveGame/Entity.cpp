#include "Entity.h"



Entity::Entity()
{
	this->alive = false;
	this->collideEnemy = false;
	this->collideWall = false;
}


Entity::~Entity()
{
}

void Entity::render(std::shared_ptr<sf::RenderWindow> target)
{
	target->draw(sprite);
	target->draw(hit_box);
}

bool Entity::isAlive()
{
	return
		this->alive;
}

void Entity::setAlive(const bool boolean)
{
	this->alive = boolean;
}

bool Entity::isCollideWall()
{
	return
		this->collideWall;
}

bool Entity::isCollideEnemy()
{
	return
		this->collideEnemy;
}

sf::Vector2f Entity::getPosition()
{
	return
		this->sprite.getPosition();
}

sf::RectangleShape Entity::getHitBox()
{
	return
		this->hit_box;
}

//bool Entity::sat_test(const sf::FloatRect &rectSp1, const sf::FloatRect &rectSp2, sf::Vector2f *out_mtv)
//{
//	float proj_x, proj_y, overlap_x, overlap_y;
//
//	// test overlap in x axis
//	proj_x = std::max(rectSp1.left + rectSp1.width, rectSp2.left + rectSp2.width) - std::min(rectSp1.left, rectSp2.left);
//	if (proj_x < rectSp1.width + rectSp2.width) {
//		if (out_mtv) {
//			// calculate mtv in x
//			overlap_x = rectSp1.width + rectSp2.width - proj_x;
//		}
//		// test overlap in y axis
//		proj_y = std::max(rectSp1.top + rectSp1.height, rectSp2.top + rectSp2.height) - std::min(rectSp1.top, rectSp2.top);
//		if (proj_y < rectSp1.height + rectSp2.height) {
//			if (out_mtv) {
//				// calculate mtv in y
//				overlap_y = rectSp1.height + rectSp2.height - proj_y;
//				out_mtv->x = out_mtv->y = 0;
//
//				// choose minimun overlap
//				if (overlap_x < overlap_y) {
//					out_mtv->x = overlap_x * (rectSp1.left < rectSp2.left ? -1 : 1);
//				}
//				else {
//					out_mtv->y = overlap_y * (rectSp1.top < rectSp2.top ? -1 : 1);
//				}
//			}
//			return true;
//		}
//	}
//	return false;
//}
