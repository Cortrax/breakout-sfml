#include "game.hpp"
#include "ball.hpp"
#include "bricks.hpp"
#include "gui.hpp"
#include "logic.hpp"
#include "paddle.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

void gameFunction(sf::RenderWindow& window, float window_width, float window_height)
{
	std::srand(time(NULL));
	sf::Clock clock;
	float dt;
	int lives_left = 0;
	int score = 0;
	bool end_game = false;

	// Create window borders
	float side_width = 10;
	float side_height = window_height;
	float top_width = window_width;
	float top_height = 30;
	float color_height = 10;
	float color_width = 30;
	Gui gui(side_width, side_height, top_width, top_height, color_height, color_width);

	// Create ball and set paddle / ball collision to false
	float ball_x = 350;
	float ball_y = 500;
	float ball_width = 10;
	float ball_height = 8;
	Ball ball(ball_x, ball_y, ball_width, ball_height);
	bool collision_check = false;
	bool ball_paddle_collision = false;
	bool ball_border_collision = false;

	// Create paddle
	float paddle_width = 700;
	float paddle_height = 14;
	float paddle_x = 350;
	float paddle_y = 855;
	Paddle paddle(paddle_x, paddle_y, paddle_width, paddle_height);

	// Create vector which stores bricks and create brick variables
	std::vector<Bricks> bricks_vector;
	long unsigned int max_bricks = 144;
	sf::Color brick_color = sf::Color(162, 30, 30);
	float brick_x = 10;
	float brick_y = 152;
	float brick_width = 34;
	float brick_height = 9;
	int brick_column_spacing = 38;
	int brick_row_spacing = 15;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color(3, 3, 3));

		// Create Bricks
		Bricks bricks(brick_width, brick_height, brick_x, brick_y, brick_color);

		// Create brick rows and columns
		brick_x += brick_column_spacing;
		if (brick_x >= window_width - brick_width)
		{
			brick_y += brick_row_spacing;
			brick_x = 10;
		}

		if (bricks_vector.size() < max_bricks)
		{
			bricks_vector.push_back(bricks);
		}

		for (auto& brick : bricks_vector)
		{
			brick.changeColor(bricks_vector, brick_color);
			brick.drawBricks(window);
			brick.setPos();

			// Check if the ball has collided with a brick and if so destroy
			// the brick, increment the score, and reverse the balls y direction
			ball.brickCollision(brick, collision_check, score);
			if (collision_check)
			{
				ball.getBrickCollisionSound();
				ball.playBrickCollisionSound();
				brick.kill();
			}
		}

		// If ball collides with border, play border collision sound
		if (ball_border_collision)
		{
			ball.getBorderCollisionSound();
			ball.playBorderCollisionSound();
			ball_border_collision = false;
		}

		// If ball collides with paddle, play paddle sound
		if (ball_paddle_collision)
		{
			ball.getPaddleCollisionSound();
			ball.playPaddleCollisionSound();
			ball_paddle_collision = false;
		}

		dt = clock.restart().asSeconds();
		gui.drawBorders(window);
		ball.borderCollision(gui, ball_border_collision);
		ball.paddleCollision(paddle, ball_paddle_collision);
		ball.drawTo(window, dt);
		ball.killBall(lives_left);
		paddle.drawTo(window);
		paddle.movePaddle(dt);

		// Generate score, lives_left, and other text on screen
		Logic logic(lives_left, score);
		logic.drawLives(window);
		logic.drawScore(window);
		logic.endGameText(window, lives_left, end_game);

		// If the game has ended, run endGame function and reset brick vector
		if (end_game)
		{
			logic.endGame(score, lives_left, paddle_width, paddle_height, brick_x, brick_y, end_game);
			bricks_vector.clear();
		}
		window.display();
	}
}