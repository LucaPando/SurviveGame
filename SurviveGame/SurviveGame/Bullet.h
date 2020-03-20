#pragma once
#include "Character.h"
#include "Enemy.h"
#include "Boss.h"
#include "PlayerT.h"
#include "Pet.h"

class Bullet :
	public Entity
{
public:
	Bullet(BulletOwner::Owner owner, sf::Vector2f owner_pos,const sf::Texture & texture);
	Bullet();
	virtual ~Bullet();

	void updateMove(const sf::Time& delta_time);
	void updateRotate();

	void calculateDir(const sf::Vector2f owner_pos, const sf::Vector2f target);

	void setDir(sf::Vector2f dir);

	bool isAllied();
	BulletOwner::Owner getOwner();

private:
	void initSpritePlayer(const sf::Vector2f owner_pos,const sf::Texture & texture);
	void initSpritePet(const sf::Vector2f owner_pos, const sf::Texture & texture);
	void initSpriteBoss(const sf::Vector2f owner_pos, const sf::Texture & texture);
	void initHitBox();

	sf::Vector2f dir;

	BulletOwner::Owner owner;

	bool allied;
};

