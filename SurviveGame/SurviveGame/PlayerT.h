#pragma once
#include "Character.h"
#include "StrategyFight.h"

class PlayerT : public Character
{
public:
	explicit PlayerT(Textures::ID id, StrategyFight* stf);

	PlayerT();
	virtual ~PlayerT();

	virtual void renderBullets(std::shared_ptr<sf::RenderWindow> target);

	void updateMove(sf::Time deltaTime);
	void updateRotate(sf::Vector2f target);
	bool updateReload(sf::Time deltaTime);
	void updateDash(sf::Time deltaTime, std::vector<sf::FloatRect> walls);
	void updateMovSpeed(sf::Time deltaTime);
	void updateHud();

	void updateCollisionEnemies(std::vector<std::shared_ptr<Enemy>> enemies);
	void updateCollisionBoss(sf::FloatRect boss_rect);
	void updateCollisionWalls(std::vector<sf::FloatRect> walls, float grid_size);

	bool shooting(sf::Time deltaTime);
	void setStrategyFight(StrategyFight* stf);

	void initVar();
	void initSprite();
	void initHitBox();

	virtual void takeDamage();

	Textures::ID getId();
	StrategyFight * getStf();

	void setTexturesSprite(sf::Texture texture);

	sf::Texture texture_movspeed;
	sf::Texture texture_bullet;

	sf::Vector2f mov_dir;

private:

	Textures::ID id;
	StrategyFight* stf;
	void setType();

	int kills;
	int kills_boss;

	float dash_speed;
	float dash_cd;
	float dash_clock;

	float ms_cd;
	float ms_clock;

	bool is_dashing;

};

