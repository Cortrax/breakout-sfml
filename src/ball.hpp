#ifndef BALL_HPP
#define BALL_HPP

#include "bricks.hpp"
#include "gui.hpp"
#include "paddle.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class Ball
{
public:
	Ball(float x, float y, float width, float height);
	void drawTo(sf::RenderWindow& window, float dt);
	void killBall(int& lives_left);
	void borderCollision(Gui& gui, bool& ball_border_collision);
	void getBorderCollisionSound();
	void playBorderCollisionSound();
	void paddleCollision(Paddle& player_paddle, bool& ball_paddle_collision);
	void getPaddleCollisionSound();
	void playPaddleCollisionSound();
	void brickCollision(Bricks& brick_rect, bool& collision_check, int& score);
	void getBrickCollisionSound();
	void playBrickCollisionSound();

private:
	sf::RectangleShape ball;
	sf::Vector2f velocity;
	float random_angle = (rand() % 60) + 120;
	int step_x = 400;
	int step_y = 500;
	bool move = false;
	bool is_dead = false;
	int rand_side;

	sf::SoundBuffer ball_border_buffer;
	sf::Sound ball_border_sound;

	sf::SoundBuffer ball_paddle_buffer;
	sf::Sound ball_paddle_sound;

	sf::SoundBuffer ball_brick_buffer;
	sf::Sound ball_brick_sound;
};

#endif