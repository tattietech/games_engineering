#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

Vector2f ballVelocity;
bool server = false;
Font font;
Text score;
int p1Score = 0;
int p2Score = 0;
bool singlePlayer = true;

const Keyboard::Key controls[4] = {
	Keyboard::A, //Player1 up
	Keyboard::Z, //Player1 down
	Keyboard::Up, //Player2 up
	Keyboard::Down //Player2 down
};

const Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;

CircleShape ball;
RectangleShape paddles[2];
void Reset() {
	//Set size and origin point of ball
	ball.setRadius(ballRadius - 3);
	ball.setOrigin(ballRadius / 2, ballRadius / 2);

	//Reset paddle position
	paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
	paddles[1].setPosition(765 + paddleSize.x / 2, gameHeight / 2);

	//Reset ball position
	ball.setPosition(gameWidth / 2, gameHeight / 2);

	// inline if statement, if server true ballVelocity.x = 100, else -100
	ballVelocity = { (server ? 100.0f : -100.0f), 60.0f };

	// Set score
	score.setString(to_string(p1Score) + "   " + to_string(p2Score));

	// Positions score
	score.setPosition((gameWidth * .5f) - (score.getLocalBounds().width * .5f), 0);
}

void Load() {
	// Set size and origin point of paddles
	for (auto &p : paddles) {
		p.setSize(paddleSize - Vector2f(3, 3));
		p.setOrigin(paddleSize / 2.3f);
	}

	// Load font-face from res dir
	if (!font.loadFromFile("Roboto-Bold.ttf"))
	{
		cout << "can't load font" << endl;
	}
	// Set text element to use font
	score.setFont(font);
	// Set the char size
	score.setCharacterSize(24);
	// Set score to 0
	score.setString(to_string(0) + "   " + to_string(0));
	//Set fill color
	score.setFillColor(Color::White);


	Reset();
}

void Update(RenderWindow &window) {
	// Reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();

	// Check and consume events
	Event event;

	// Allow player to close and move the window
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}

	// Quit via ESC key
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}

	// Handle paddle movement
	float direction1 = 0.0f;
	float direction2 = 0.0f;
	if (Keyboard::isKeyPressed(controls[0])) {
		direction1--;
	}
	if (Keyboard::isKeyPressed(controls[1])) {
		direction1++;
	}

	if (ball.getPosition().y < paddles[1].getPosition().y && ballVelocity.x > 0) {
		direction2--;
	}
	if (ball.getPosition().y > paddles[1].getPosition().y && ballVelocity.x > 0) {
		direction2++;
	}

	// Moves paddles on key press
	if (paddles[0].getPosition().y > gameHeight - paddleSize.y / 2) {
		direction1--;
	}
	else if (paddles[0].getPosition().y < 0 + paddleSize.y / 2.3) {
		direction1++;
	} else if (paddles[1].getPosition().y > gameHeight - paddleSize.y / 2) {
		direction2--;
	}
	else if (paddles[1].getPosition().y < 0 + paddleSize.y / 2.3) {
		direction2++;
	}
	paddles[0].move(0, direction1 * paddleSpeed * dt);
	paddles[1].move(0, direction2 * paddleSpeed * dt);

	// Moves ball
	ball.move(ballVelocity * dt);

	// Checks ball collision
	const float bx = ball.getPosition().x;
	const float by = ball.getPosition().y;
	const float p1x = paddles[0].getPosition().x;
	const float p1y = paddles[0].getPosition().y;
	const float p2x = paddles[1].getPosition().x;
	const float p2y = paddles[1].getPosition().y;


	if (by > gameHeight) {
		//bottom wall
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, -10);
	}
	else if (by < 0) {
		// top wall
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, 10);
	}
	else if (bx > gameWidth) {
		// right wall
		p1Score += 1;
		Reset();
	}
	else if (bx < 0) {
		// left wall
		p2Score += 1;
		Reset();
	}
	else if (
		// left paddle
		// ball is inline or behind paddle
		bx < paddleSize.x &&
		// AND ball is below top edge of paddle
		by > p1y - (paddleSize.y * 0.5) &&
		// AND ball is above the bottom edge of the paddle
		by < p1y + (paddleSize.y * 0.5)
		) {
			ballVelocity.x *= -1.1f;
			ballVelocity.y *= 1.1f;
		}
	else if (
		// right paddle
		// ball is inline or behind paddle
		bx > 765 + paddleSize.x / 2 &&
		// AND ball is below top edge of paddle
		by > p2y - (paddleSize.y * 0.5) &&
		// AND ball is above the bottom edge of the paddle
		by < p2y + (paddleSize.y * 0.5)
		) {
		ballVelocity.x *= -1.1f;
		ballVelocity.y *= 1.1f;
	}
}

void Render(RenderWindow &window) {
	// Draw everything
	window.draw(paddles[0]);
	window.draw(paddles[1]);
	window.draw(ball);
	window.draw(score);
}

void Menu(RenderWindow &window) {

}

int main()
{
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
    return 0;
}