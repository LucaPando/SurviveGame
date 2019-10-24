#include "Game.h"
#include "Player.h"
#include "Enemy.h"


Game::Game() : window(sf::VideoMode(1920, 1080), "Survive.io"), game_view(sf::Vector2f(0.f, 0.f), sf::Vector2f(1280.f, 720.f)) 
{
	//ENEMY
	for (int i = 0 ; i <0; i++)
	{
		std::shared_ptr<Enemy> enemy(new Enemy(rand() % 1000, rand() % 1000));
		enemies.push_back(enemy); //std:move(enemy) per unique_ptr
	}
	   //GUN
	ammo = 0;
	for (int i = 0; i < 30; i++)
	{
		std::shared_ptr<Bullet> bullet(new Bullet());
		p_bullets.push_back(bullet);
	}

	game_view.setCenter(player.getPosition());
	walls_collision = tile_map.getWalls();
}

void Game::run()
{
	sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Clock clock;

	while (window.isOpen()) 
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame) 
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
				window.close();
			break;
		case sf::Event::Closed:
			window.close();
			break;
		}
	}
}

void Game::update(sf::Time deltaTime)
{
	mouse_pos_view = (window).mapPixelToCoords(sf::Mouse::getPosition(window));
	player.update(deltaTime, mouse_pos_view, walls_collision, enemies);

	//GUN
	if (player.shoot() && ammo!=29)
	{
		ammo = 0;
		p_shooting = p_bullets[ammo]->init(&player, mouse_pos_view);
		ammo++;
	}
	if(p_shooting)
	{
		for (int i = 0; i < ammo; i++)
		{
			p_bullets[i]->update(deltaTime, walls_collision, enemies);
		}
	}
	//ENEMY
	for(auto i = enemies.begin(); i != enemies.end(); i++)
	{
		(*i)->update(deltaTime,&player, walls_collision, enemies);
	}

	game_view.setCenter(player.getPosition());
	window.setView(game_view);
}


void Game::render()
{
	window.clear();

	tile_map.render(window);
	player.render(&window);

	//GUN
	for (auto i = p_bullets.begin(); i != p_bullets.end(); i++)
	{
		(*i)->render(&window);
		window.draw((*i)->hit_box);
	}

	window.draw(player.hit_box);

	//ENEMY
	for (auto i = enemies.begin(); i != enemies.end(); i++)
	{
		(*i)->render(&window);
		window.draw((*i)->hit_box);
	}
	
	window.display();
}


