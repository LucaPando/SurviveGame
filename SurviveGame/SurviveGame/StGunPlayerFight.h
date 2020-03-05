#pragma once
#include "StrategyFight.h"

class StGunPlayerFight :
	public StrategyFight
{
public:
	StGunPlayerFight();
	virtual ~StGunPlayerFight() = default;

	virtual void shot(std::vector<std::shared_ptr<Bullet>>& bullets,
		sf::Vector2f owner_pos, sf::Vector2f target_pos);
};


 