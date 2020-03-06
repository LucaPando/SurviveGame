#pragma once
#include "Character.h"
#include <ctime>

struct BoostPos;

enum Type {HP, MS};

enum Pos {TOP_LEFT , TOP_RIGHT, DOWN_LEFT, DOWN_RIGHT};

class Boost :
	public Entity
{
public:
	Boost(const std::shared_ptr<BoostPos> boost_pos);
	virtual ~Boost();

	bool checkCollide(sf::FloatRect character);
	void boostSubject(std::shared_ptr<Character> character);

	Type getType();
	void setTexturesSprite(sf::Texture texture);

private:
	void initHp();
	void initMs();

	void initPos();
	void initSpriteHp();
	void initHitBoxHp();

	void initSpriteMs();
	void initHitBoxMs();

	Type type;
	Pos position;

	sf::Vector2f pos;

	std::shared_ptr<BoostPos> boost_pos;
};

