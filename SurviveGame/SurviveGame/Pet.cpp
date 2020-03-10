#include "Pet.h"



Pet::Pet(sf::Texture texture, sf::Vector2f spawn_pos)
{
	initVar();
	initSprite(texture, spawn_pos);
	initHitbox();
}

Pet::Pet()
{
}


Pet::~Pet()
{
}

void Pet::takeDamage()
{
	this->hp--;
}

void Pet::updateMove(sf::Time deltaTime, sf::Vector2f parent_pos)
{
	sf::Vector2f dir = parent_pos - this->getPosition();

	this->sprite.move((dir.x * this->mov_speed * deltaTime.asSeconds()), (dir.y * this->mov_speed * deltaTime.asSeconds()));
	hit_box.setPosition(getPosition());
}

void Pet::updateRotate(sf::Vector2f target)
{
	float dX = target.x - getPosition().x;
	float dY = target.y - getPosition().y;
	const float PI = 3.14159265f;
	float deg = atan2(dY, dX) * 180.f / PI;

	this->sprite.setRotation(deg + 270.f);
}

void Pet::updateHud()
{
	hud.updateText(hp, getPosition());
}

void Pet::updateCollision(sf::FloatRect parent_rect)
{ //PLAYER
	sf::Vector2f ent(0, 0);
	sf::Vector2f dir(0, 0);

	ent = this->collision->CollideWithEntity(parent_rect, this->getHitBox().getGlobalBounds());
	sprite.move(-ent);
	
	collision->resetOutMtv();
}

void Pet::initVar()
{
	mov_speed_default = 1;
	mov_speed = mov_speed_default;

	hp_max = 25;
	hp = hp_max;

	range = 50;
}

void Pet::initSprite(sf::Texture texture, sf::Vector2f spawn_pos)
{
	sprite.setTexture(texture);     //TEXTURE
	sprite.setScale(0.1f, 0.1f);      //SCALE
	sprite.setPosition(spawn_pos);  //POS
	sprite.setOrigin(222.f, 188.f);      //ORIGIN
}

void Pet::initHitbox()
{
	hit_box.setSize(sf::Vector2f(445, 377));     //SIZE
	hit_box.setOutlineColor(sf::Color::Transparent); //COLOR
	hit_box.setOutlineThickness(3.f);
	hit_box.setFillColor(sf::Color::Transparent);
	hit_box.setScale(sprite.getScale());           //SCALE
	hit_box.setPosition(getPosition());              //POS
	hit_box.setOrigin(222.f, 188.f);                       //ORIGIN
}
