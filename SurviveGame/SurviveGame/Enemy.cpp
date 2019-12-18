#include "Enemy.h"


Enemy::Enemy(const std::shared_ptr<EntityData> entitydata)
{
	this->entitydata = entitydata;

	initVar();
	initSprite();
	initHitBox();
}

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::updateMove()
{
	float dx = entitydata->player->getPosition().x - this->sprite.getPosition().x;
	float dy = entitydata->player->getPosition().y - this->sprite.getPosition().y;

	float lenght = sqrt(pow(dx, 2) + pow(dy, 2));

	sf::Vector2f normVect(dx / lenght, dy / lenght);

	this->sprite.move((normVect.x * this->mov_speed * entitydata->deltaTime.asSeconds()), (normVect.y * this->mov_speed * entitydata->deltaTime.asSeconds()));
	hit_box.setPosition(getPosition());
}

void Enemy::updateRotate()
{
	float dX = entitydata->player->getPosition().x - this->sprite.getPosition().x;
	float dY = entitydata->player->getPosition().y - this->sprite.getPosition().y;
	const float PI = 3.14159265f;
	float deg = atan2(dY, dX) * 180.f / PI;

	this->sprite.setRotation(deg + 90.f);
}

void Enemy::updateHud()
{
	hud.updateText(hp, getPosition());
}

void Enemy::updateCollision()
{
	sf::Vector2f ent(0, 0);
	sf::Vector2f dir(0, 0);

	//PLAYER
	ent = this->collision->CollideWithEntity(entitydata->player->getHitBox().getGlobalBounds(), this->getHitBox().getGlobalBounds());
	sprite.move(-ent);
	if (ent.x != 0 || ent.y != 0)
		entitydata->player->takeDamage();
	collision->resetOutMtv();

	//PET
	if (entitydata->pet)
	{
		ent = this->collision->CollideWithEntity(entitydata->pet->getHitBox().getGlobalBounds(), this->getHitBox().getGlobalBounds());
		sprite.move(-ent);
		if (ent.x != 0 || ent.y != 0)
			entitydata->pet->takeDamage();
		collision->resetOutMtv();
	}

	//OTHER ENEMY
	std::vector<std::shared_ptr<Character>> enemies;
	enemies = *entitydata->enemies;

	for(int i = 0; i < enemies.size(); i++)
	{
		ent = this->collision->CollideWithEntity(enemies[i]->getHitBox().getGlobalBounds(), this->getHitBox().getGlobalBounds());
		sprite.move(-ent);
		collision->resetOutMtv();
	}

	//WALLS
	dir = this->collision->CollideWithWalls(this->getHitBox().getGlobalBounds(), entitydata->map->findWalls(sprite.getPosition().x, sprite.getPosition().y));
 	sprite.move(dir);
	hit_box.setPosition(getPosition());
	collision->resetOutMtv();
}

void Enemy::update()
{
	updateMove();
	updateRotate();
	updateHud();
	updateCollision();
}

void Enemy::renderBullets(std::shared_ptr<sf::RenderWindow> target)
{
		/*for (int i = 0; i < bullets.size(); i++)
			bullets[i]->render(target);*/
}


void Enemy::initVar()
{
	mov_speed = 100;
	hp = 10;
}

void Enemy::initSprite()
{
	sprite.setTexture(entitydata->textures->get(Textures::Enemy));
	sprite.setScale(0.9f, 0.9f);
	sprite.setPosition(rand() % 400 + 500.f , rand() % 400 + 500.f);
	sprite.setOrigin(+34.f, +34.f);
	sprite.setTextureRect(sf::IntRect(0, 0, 68, 68));
}

void Enemy::initHitBox()
{
	this->hit_box.setSize(sf::Vector2f(60.f, 60.f));
	this->hit_box.setOutlineColor(sf::Color::Blue);
	this->hit_box.setFillColor(sf::Color::Transparent);
	this->hit_box.setScale(sprite.getScale());
	this->hit_box.setPosition(getPosition());
	this->hit_box.setOrigin(30, 30);
}

void Enemy::takeDamage()
{// a seconda del tipo di proiettile da cui viene colpito take dmg
	this->hp--;
}

