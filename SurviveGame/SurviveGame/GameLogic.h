#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "RoundManager.h"
#include "Hud.h"
#include "TileMap.h"
#include "TextureHolder.h"
#include "Enemy.h"
#include "PlayerT.h"
#include "Boost.h"
#include <vector>

class GameLogic :
	public State
{
public:
    GameLogic();
	virtual ~GameLogic();


private:
	void update(sf::Time deltaTime);
	void render();

	void updatePlayer(std::shared_ptr<EntityData> entitydata);
	void updateEnemies(std::shared_ptr<EntityData> entitydata);
	void updateBoost(std::shared_ptr<EntityData> entitydata);
	void updateGameView(sf::Time deltaTime);
	void updateEntityData(sf::Time deltaTime);
	void updateHud();

	void renderEnemies();
	void renderPlayer();
	void renderBoost();

	void entitiesInit();
	void gameViewInit();
	void textureInit();
	void varInit();
	void entitydataInit();

	TileMap tile_map;
	sf::View game_view;
	Hud hud;
	RoundManager round;
	TextureHolder textures;

    std::vector<std::shared_ptr<Character>> * enemies;
	std::shared_ptr<Character> player;
	std::vector<std::shared_ptr<Entity>> boost;

	std::shared_ptr<EntityData> entitydata;
	std::shared_ptr<BoostPos> boost_pos;

	int max_enemies;
	int enemies_alive;
	int kill_counter;

	float game_view_speed;
	sf::Clock boost_time;
	sf::Time rand_time;

};