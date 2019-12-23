#pragma once

#include <SFML/Graphics.hpp>
#include "Observer.h"
#include "RoundManager.h"

class Achievement : public Observer
{
public:

	Achievement() = default;
	Achievement(RoundManager * subject);
	virtual ~Achievement();

	virtual void update();

	virtual void attach();
	virtual void detach();

	int getKills();
	int getKillsBoss();
	int getRound();

	void renderRoundBadge(std::shared_ptr<sf::RenderWindow> window, sf::View view);
	void renderKillsBadge(std::shared_ptr<sf::RenderWindow> window, sf::View view);
	void renderBossBadge(std::shared_ptr<sf::RenderWindow> window, sf::View view);

private:

	RoundManager * subject;

	int kills;
	int kills_boss;
	int round;

	sf::Font font;

	sf::Text kills_t;
	sf::Text kills_boss_t;
	sf::Text round_t;

	sf::Text text;

	sf::Texture frame;

	float clock;
};

