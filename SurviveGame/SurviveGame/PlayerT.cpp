#include "PlayerT.h"
#include "SelectionCharacter.h"
#include "StShotgunPlayerFight.h"
#include "StRiflePlayerFight.h"
#include "StGunPlayerFight.h"


PlayerT::PlayerT(Textures::ID id, StrategyFight* stf) : id(id)
{
	setStrategyFight(stf);
	setType();
	initVar();
	initSprite();
	initHitBox();
}

PlayerT::PlayerT()
{
}


PlayerT::~PlayerT()
{
}

void PlayerT::updateMove(sf::Time deltaTime)
{
	sf::Vector2f dir(0, 0);

	bool w_is_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	bool a_is_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	bool s_is_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	bool d_is_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

	if (w_is_pressed)
	{
		dir.y = -1;
	}

	if (a_is_pressed)
	{
		dir.x = -1;
	}

	if (s_is_pressed)
	{
		dir.y = +1;
	}

	if (d_is_pressed)
	{
		dir.x = +1;
	}

	updateMovSpeed(deltaTime);
	this->mov_dir = dir;

	hit_box.setPosition(getPosition() + sf::Vector2f((dir.x * this->mov_speed* deltaTime.asSeconds()), dir.y * this->mov_speed* deltaTime.asSeconds()));
	this->sprite.move((dir.x * this->mov_speed* deltaTime.asSeconds()) , dir.y * this->mov_speed* deltaTime.asSeconds());
}

void PlayerT::updateRotate(sf::Vector2f target)
{
	float dX = target.x - getPosition().x;
	float dY = target.y - getPosition().y;
	const float PI = 3.14159265f;
	float deg = atan2(dY, dX) * 180.f / PI;

	this->sprite.setRotation(deg + 360.f);
}

bool PlayerT::updateReload(sf::Time deltaTime)
{
	if (ammo == 0 || reloading)
	{
		reload_clock -= deltaTime;
		if (reload_clock < sf::seconds(0.f))
		{
			ammo = ammo_max;
			reload_clock = reload_cd;
			switch (this->id)
			{
			case(Textures::ID::ShotgunP):
			{
				this->type = CharacterType::Rifle;
				this->id = Textures::ID::RifleP;
				this->stf = new StRiflePlayerFight();
				break;
			}
			case(Textures::ID::RifleP):
			{
				this->type = CharacterType::Handgun;
				this->id = Textures::ID::HandgunP;
				this->stf = new StGunPlayerFight();
				break;
			}
			case(Textures::ID::HandgunP):
			{
				this->type = CharacterType::Shotgun;
				this->id = Textures::ID::ShotgunP;
				this->stf = new StShotgunPlayerFight();
				break;
			}
			}
			setRatioCd(stf->getRatio());
			reloading = false;
			return true;
		}
		return false;
	}
	return false;
}

void PlayerT::updateDash(sf::Time deltaTime, std::vector<sf::FloatRect> walls)
{
	bool space_is_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

	if (space_is_pressed && !is_dashing)
	{
		hit_box.setPosition(getPosition().x + (this->mov_dir.x * 160), (this->mov_dir.y * 160) + getPosition().y);
		collision->CollideWithWalls(this->hit_box.getGlobalBounds(), walls);
		if (!this->collision->isCollide())
		{
			is_dashing = true;
			this->sprite.setPosition(hit_box.getGlobalBounds().left, hit_box.getGlobalBounds().top);
		}
		else
			hit_box.setPosition(getPosition());
	}
	if (is_dashing && dash_clock > 0)
	{
		dash_clock -= deltaTime.asSeconds();
		if (dash_clock < 0)
		{
			is_dashing = false;
			dash_clock = dash_cd;
		}
	}
}

void PlayerT::updateMovSpeed(sf::Time deltaTime)
{
	if (this->mov_speed != this->mov_speed_default)
	{
		this->ms_clock -= deltaTime.asSeconds();
	}

	if (ms_clock < 0.f)
	{
		this->ms_clock = this->ms_cd;
		this->mov_speed = this->mov_speed_default;
	}
		
}

void PlayerT::updateHud()
{
	hud.updateText(getAmmo(), getHp(), this->dash_clock, getPosition());
}

void PlayerT::updateCollisionEnemies(std::vector<std::shared_ptr<Enemy>> enemies)
{
	sf::Vector2f ent(0, 0);

	for (int i = 0; i != enemies.size(); i++)
	{
		ent = this->collision->CollideWithEntity(this->hit_box.getGlobalBounds(), enemies[i]->getHitBox().getGlobalBounds());
		sprite.move(ent);
		if (ent.x != 0 || ent.y != 0)
			takeDamage();
	}
	hit_box.setPosition(getPosition());
	collision->resetOutMtv();
}

void PlayerT::updateCollisionBoss(sf::FloatRect boss_rect)
{
	sf::Vector2f ent(0, 0);

	ent = this->collision->CollideWithEntity(this->hit_box.getGlobalBounds(), boss_rect);
	sprite.move(ent);

	hit_box.setPosition(getPosition());
	collision->resetOutMtv();
}

void PlayerT::updateCollisionWalls(std::vector<sf::FloatRect> walls, float grid_size)
{
	sf::Vector2f dir(0, 0);

	dir = this->collision->CollideWithWalls(this->hit_box.getGlobalBounds(), walls);

	this->collision->setPreMtv(this->collision->getOutMtv());
	sprite.move(dir);
	hit_box.setPosition(getPosition());
	collision->resetOutMtv();
	setGridPosition(grid_size);
}

bool PlayerT::shooting(sf::Time deltaTime)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !reloading)
	{
		ratio_clock -= deltaTime;

		if (ratio_clock < sf::seconds(0.f))
		{
			ratio_clock = ratio_cd;

			if (this->ammo)
			{
				this->shoot = true;
				return true;
			}
			else
			{
				shoot = false;
				return false;
			}
		}
		else
		{
			shoot = false;
			return shoot;
		}
	}
	else
	{
		shoot = false;
		return shoot;
	}
}

void PlayerT::setStrategyFight(StrategyFight* stf)
{
	this->stf = stf;
}

void PlayerT::initVar()
{
	mov_speed_default = 200;
	mov_speed = mov_speed_default;

	hp_max = 100;
	hp = hp_max;

	reload_cd = sf::seconds(1.f);
	reload_clock = reload_cd;

	ammo_max = 100;
	ammo = ammo_max;

	setRatioCd(stf->getRatio());
	ratio_clock = ratio_cd;

	this->dash_speed = 1000;
	this->dash_cd = 10.f;
	this->dash_clock = dash_cd;
	this->is_dashing = false;

	this->ms_cd = 3.f;
	this->ms_clock = ms_cd;
}

void PlayerT::initSprite()
{
	sprite.setScale(0.3f, 0.3f);        //SCALE
	sprite.setPosition(600.f, 600.f); //POS
	sprite.setOrigin(92, 120);        //ORIGIN
}

void PlayerT::initHitBox()
{
	hit_box.setSize(sf::Vector2f(100.f, 100.f));     //SIZE
	hit_box.setOutlineColor(sf::Color::Transparent); //COLOR
	hit_box.setOutlineThickness(3.f);
	hit_box.setFillColor(sf::Color::Transparent);
	hit_box.setScale(sprite.getScale());             //SCALE
	hit_box.setPosition(getPosition());              //POS
	hit_box.setOrigin(45, 60);                       //ORIGIN
}

Textures::ID PlayerT::getId()
{
	return 
		this->id;
}

StrategyFight * PlayerT::getStf()
{
	return this->stf;
}

void PlayerT::setTexturesSprite(sf::Texture texture)
{
	sprite.setTexture(texture);
}

void PlayerT::setType()
{
	switch (this->id)
	{
	case(Textures::ID::ShotgunP):
		this->type = CharacterType::Shotgun;
		break;
	case(Textures::ID::RifleP):
		this->type = CharacterType::Rifle;
		break;
	case(Textures::ID::HandgunP):
		this->type = CharacterType::Handgun;
		break;
	}
}
