#include "ball.hpp"
#include "bricks.hpp"
#include "paddle.hpp"
#include <gui.hpp>
#include <vector>

Ball::Ball(float x, float y, float width, float height, float step)
{
	ball.setFillColor(sf::Color(150, 150, 150));
	ball.setSize(sf::Vector2f(width, height));
	ball.setPosition(sf::Vector2f(x, y));
	ball.setOrigin(width / 2, height / 2);
	std::cout << step;
}

void Ball::drawTo(sf::RenderWindow& window, float dt)
{
	// If the s key is pressed spawn the ball and set it in motion
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		move = true;
	}

	if (move == true)
	{
		velocity.x = (step_x * dt) * cos(random_angle * M_PI / 180);
		velocity.y = (step_y * dt) * sin(random_angle * M_PI / 180);
		ball.move(velocity);
		window.draw(ball);
	}
}

void Ball::collision(Paddle& player_paddle, Gui& gui)
{
	auto paddle = player_paddle.paddle;
	auto top_rect = gui.top_border;
	auto left_rect = gui.left_border;
	auto right_rect = gui.right_border;

	// If ball collides with paddle reverse y direction and randomly
	// reverse x direction
	if (ball.getGlobalBounds().intersects(paddle.getGlobalBounds()))
	{
		ball.setPosition(ball.getPosition().x, paddle.getPosition().y - 10);
		step_y *= -1;
		int randSide = rand() % 2;
		if (randSide == 1)
		{
			velocity.y *= -1;
		}
	}

	// If ball hits top border reverse direction.
	// If goes beyond bottom barrier, set is_dead to true
	if (ball.getGlobalBounds().intersects(top_rect.getGlobalBounds()))
	{
		ball.setPosition(ball.getPosition().x, top_rect.getPosition().y + 35);
		step_y *= -1;
	}
	else if (ball.getPosition().y >= 910)
	{
		is_dead = true;
	}

	// If ball hits the left or right barrier, reverse direction
	if (ball.getPosition().x >= 685)
	{
		ball.setPosition(right_rect.getPosition().x - 15, ball.getPosition().y);
		step_x *= -1;
	}
	if (ball.getPosition().x <= 15)
	{
		ball.setPosition(left_rect.getPosition().x + 15, ball.getPosition().y);
		step_x *= -1;
	}
}

bool Ball::brickCollision(Bricks& brick_rect, bool& collision_check)
{
	auto bricks = brick_rect.bricks;
	// auto red_brick = brick_rect.red_brick;
	// auto orange_brick = brick_rect.orange_brick;
	// auto green_brick = brick_rect.green_brick;
	// auto yellow_brick = brick_rect.yellow_brick;

	// Detect collision with red bricks
	if (ball.getGlobalBounds().intersects(bricks.getGlobalBounds()))
	{
		std::cout << bricks.getPosition().x
				  << "\n";
		collision_check = true;
	}

	// // Detect collision with red bricks
	// if (ball.getGlobalBounds().intersects(red_brick.getGlobalBounds()))
	// {
	// 	std::cout << red_brick.getPosition().x
	// 			  << "\n";
	// 	collision_check = true;
	// }

	// // Detect collision with orange bricks
	// if (ball.getGlobalBounds().intersects(orange_brick.getGlobalBounds()))
	// {
	// 	std::cout << orange_brick.getPosition().x
	// 			  << "\n";
	// 	collision_check = true;
	// }

	// // Detect collision with green bricks
	// if (ball.getGlobalBounds().intersects(green_brick.getGlobalBounds()))
	// {
	// 	std::cout << green_brick.getPosition().x
	// 			  << "\n";
	// 	collision_check = true;
	// }

	// // Detect collision with yellow bricks
	// if (ball.getGlobalBounds().intersects(yellow_brick.getGlobalBounds()))
	// {
	// 	std::cout << yellow_brick.getPosition().x
	// 			  << "\n";
	// 	collision_check = true;
	// }
	return collision_check;
	// collision_check = false;
}

void Ball::killBall(int& lives_left)
{
	// If the ball is off the screen,
	// reset the position and get new random direction
	if (is_dead)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			random_angle = rand() % (225 - 360 + 1);
			std::cout << random_angle << "\n";
			ball.setPosition(sf::Vector2f(350, 500));
			lives_left++;
		}
	}
	is_dead = false;
}
