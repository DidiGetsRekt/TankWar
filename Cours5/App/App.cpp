// App.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include <math.h>
#include "Lib.hpp"
#include "World.hpp"

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
int resettime = 0;
int count = 0;
using namespace sf;

static sf::Shader * simpleshader = nullptr;
Texture * WhiteTex;


static World gameworld;
sf::Color hsv(int hue, float sat, float val)
{
	hue %= 360;
	while (hue < 0) hue += 360;

	if (sat < 0.f) sat = 0.f;
	if (sat > 1.f) sat = 1.f;

	if (val < 0.f) val = 0.f;
	if (val > 1.f) val = 1.f;

	int h = hue / 60;
	float f = float(hue) / 60 - h;
	float p = val * (1.f - sat);
	float q = val * (1.f - sat * f);
	float t = val * (1.f - sat * (1 - f));

	switch (h)
	{
	default:
	case 0:
	case 6: return sf::Color(val * 255, t * 255, p * 255);
	case 1: return sf::Color(q * 255, val * 255, p * 255);
	case 2: return sf::Color(p * 255, val * 255, t * 255);
	case 3: return sf::Color(p * 255, q * 255, val * 255);
	case 4: return sf::Color(t * 255, p * 255, val * 255);
	case 5: return sf::Color(val * 255, p * 255, q * 255);
	}
}

void DrawCurve(sf::RenderWindow &win, sf::Clock clock) {
	sf::VertexArray va(sf::LineStrip);
	sf::VertexArray va2(sf::LineStrip);
	sf::VertexArray va3(sf::LineStrip);
	sf::Color red = sf::Color::Green;
	sf::Color blue = sf::Color::Black;
	sf::Color three = sf::Color::Black;
	int nb = 100;
	float Stride = 800 / nb;
	
	for (int i = clock.getElapsedTime().asSeconds(); i < 1000+clock.getElapsedTime().asSeconds(); i++) {
		sf::Color col = red;
		if (remainder(i, 2) == 0) {
			col = blue;
		}
		else if (remainder(i, 2) == 1) {
			col = three;
		}
		else
		col = red;
		sf::Vertex vertex(Vector2f(sin(Stride) * (i-clock.getElapsedTime().asSeconds())*1, 300+ 100*sin(i) + 50*sin(10*clock.getElapsedTime().asSeconds())), col);
		sf::Vertex vertex2(Vector2f(Stride * (i - clock.getElapsedTime().asSeconds()) * 1, 300 + 100 * sin(i) + 100 * sin(1 * clock.getElapsedTime().asSeconds())), col);
		sf::Vertex vertex3(Vector2f(Stride * (i - clock.getElapsedTime().asSeconds()) * 1, 300 + 100 * sin(i) + 10 * sin(1 * clock.getElapsedTime().asSeconds())), col);

		
		va.append(vertex);
		va2.append(vertex2);
		va3.append(vertex3);
	}
	
	win.draw(va);
	win.draw(va2);
	win.draw(va3);
}

void InitSquare(int owner) {
	sf::RectangleShape *rect = new RectangleShape(Vector2f(64, 64)); //16;16
	rect->setOrigin(32, 32); //8;8
	
	Tank * MainTank = new Tank(rect, Vector2f(100,100));
	gameworld.Tanks.push_back(MainTank);
}

void DrawMovingSquare(sf::RenderWindow & win) {
	Tank& MainTank = *gameworld.Tanks.at(0);
	MainTank.shape->setTexture(WhiteTex);
	//MainTank.shape->setFillColor(sf::Color::Transparent);
	//MainTank.shape->setOutlineColor(sf::Color::Green);
	MainTank.shape->setOutlineThickness(1);
	win.draw(*MainTank.shape, simpleshader);
}
static Vector2f vec1 = Vector2f(0,0);
static Vector2f vec2 = Vector2f(0, 0);
static Vector2f vec3 = Vector2f(0, 0);
static Vector2f vec4 = Vector2f(0, 0);

static Vector2f GetMousePos(sf::RenderWindow & win) {
	
	return (Vector2f)sf::Mouse::getPosition(win);
}

void ShootCannon(Vector2f MousPos, Vector2f TankPos) {
	
	
	float angle = atan2f(MousPos.y-TankPos.y,MousPos.x- TankPos.x);
	//sf::Vector2f DirVer(MousPos.x - TankPos.x, MousPos.y - TankPos.y);
	sf::Vector2f DirVer(cos(angle), sin(angle));
	

	//printf("%f \n", angle);
	sf::RectangleShape * attack = new RectangleShape(Vector2f(4, 4));
	
	attack->setPosition(TankPos);
	attack->setOrigin(2, 2);
	attack->setFillColor(sf::Color::Transparent);
	attack->setOutlineColor(sf::Color::Green);
	attack->setOutlineThickness(1);
	
	Projectile * attackpoint = new Projectile(attack, DirVer, 4);
	gameworld.Projectiles.push_back(attackpoint);

}
void MakeBorderWalls() {
	RectangleShape *left = new RectangleShape(Vector2f(16,600));
	left->setFillColor(sf::Color::Transparent);
	left->setOutlineColor(sf::Color::Green);
	left->setOutlineThickness(1);
	Wall * Left = new Wall(left, Vector2f(0, 0));

	RectangleShape *up = new RectangleShape(Vector2f(800, 16));
	up->setFillColor(sf::Color::Transparent);
	up->setOutlineColor(sf::Color::Green);
	up->setOutlineThickness(1);
	Wall *Up = new Wall(up, Vector2f(0, 0));

	RectangleShape *down = new RectangleShape(Vector2f(800, 16));
	down->setFillColor(sf::Color::Transparent);
	down->setOutlineColor(sf::Color::Green);
	down->setOutlineThickness(1);
	Wall *Down = new Wall(down, Vector2f(0, 600 -16));

	RectangleShape *right= new RectangleShape(Vector2f(16, 600));
	right->setFillColor(sf::Color::Transparent);
	right->setOutlineColor(sf::Color::Green);
	right->setOutlineThickness(1);
	Wall *Right = new Wall(right, Vector2f(800-16, 0));

	
	gameworld.Walls.push_back(Left);
	gameworld.Walls.push_back(Up);
	gameworld.Walls.push_back(Down);
	gameworld.Walls.push_back(Right);
	

	
}
void DrawAllWalls(sf::RenderWindow &win) {
	int sizepro = gameworld.Walls.size();
	for (int i = 0; i < sizepro; i++) {
		//gameworld.Projectiles.at(i).PushProjectile(window);
		Wall& thiswall = *gameworld.Walls.at(i);
		win.draw(*thiswall.shape);
	}
}
bool ready = false;
void DrawCatmull(sf::RenderWindow &win, sf::Clock clock) {
	sf::VertexArray va(sf::LineStrip);
	
	sf::Color red = sf::Color::Green;
	
	int nb = 100;
	float Stride = 800 / nb;

	std::vector<Vector2f> points;

	/*for (int j = 0; j < 8; ++j) {
		Vector2f v(j * 50, j * 50);
		if (j == 0) v.x += 100;
		if (j == 3)v.x += 200;
		points.push_back(v);
	}*/
	
		points.push_back(vec1);
		points.push_back(vec2);
		points.push_back(vec3);
		points.push_back(vec4);
		
	
	




		for (int i = 0; i < nb + 1; ++i) {
			double ratio = 1.0 * i / nb;
			double x = 0.0;
			double y = 0.0;


			sf::Color col = hsv(ratio * 360, 0.8, 0.8);

			Vector2f pos = Lib::plot2(ratio, points);
			x = pos.x;
			y = pos.y;
			sf::Vertex vertex(Vector2f(x, y), col);




			va.append(vertex);

		}
		sf::CircleShape circle(10.f, 2 * 3.141569 * 100);
		circle.setOrigin(10, 10);

		if (clock.getElapsedTime().asSeconds() - resettime > 12) {
			resettime = clock.getElapsedTime().asSeconds();
			count++;
		}
		if (remainder(count, 2) == 0)
			circle.setPosition(Lib::plot2(10 * (clock.getElapsedTime().asSeconds() - resettime) / nb, points));
		else
			circle.setPosition(Lib::plot2(10 * (resettime + 12 - clock.getElapsedTime().asSeconds()) / nb, points));
			

		
		win.draw(va);
		
	
}
int main()
{
	
	WhiteTex = new Texture();
	if (!WhiteTex->create(1, 1)) printf("create failed \n");
	WhiteTex->setSmooth(true);
	unsigned int col = 0xffffffff;
	WhiteTex->update((const sf::Uint8*)&col, 1, 1, 0, 0);
	sf::ContextSettings settings;
	settings.antialiasingLevel = 2;

	sf::RenderWindow window(sf::VideoMode(800, 600), "Tank War!",sf::Style::Default, settings);
	sf::Clock Clock;
//	Clock.restart();
	sf::Time appStart = Clock.getElapsedTime();
	sf::CircleShape shape(20.f, 2*3.141569*100);
	shape.setFillColor(sf::Color::Red);
	window.setVerticalSyncEnabled(true);
	sf::Time frameStart;
	float fps[4] = { 0.f, 0.f, 0.f, 0.f };
	int step = 0;
	sf::Font font;
	//font.loadFromFile("arial.ttf");
		
	sf::Text myFpsCounter;
	
	sf::Time PrevFrameStart = Clock.getElapsedTime();
	int every = 0;
	InitSquare(0);
	/*if (sf::Joystick::isConnected(0))
		InitSquare(1);*/
	
	MakeBorderWalls();
	if (!sf::Shader::isAvailable())
		printf("noshader\n");
	simpleshader = new Shader();
	if (!simpleshader->loadFromFile("res/simple.vert", "res/simple.frag"))
		printf(" unable to lead shader \n");
	while (window.isOpen())
	{
		simpleshader->setUniform("TimeVar", Clock.getElapsedTime().asSeconds());
		Tank& MainTank = *gameworld.Tanks.at(0);
		Vector2f PosTank = MainTank.shape->getPosition();
		
		frameStart = Clock.getElapsedTime();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			/*if (event.type == sf::Event::MouseButtonReleased)
				if(event.mouseButton.button == sf::Mouse::Left)
					ShootCannon(GetMousePos(window), PosTank);*/
			if (sf::Joystick::isButtonPressed(0, 5))
				ShootCannon(GetMousePos(window), PosTank);
		}
		
		//myFpsCounter.setPosition(8, 8);
		//myFpsCounter.setFillColor(sf::Color::Red);
		

		/*if (every == 0) {
			myFpsCounter.setString(std::string("FPS:") + std::to_string(fps[(step - 1) % 4]));
			every = 30;
		}*/


		window.clear();
	
		//if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			


		DrawAllWalls(window);
		DrawMovingSquare(window);
		//Dessine tous les projectiles
		int sizepro = gameworld.Projectiles.size();
		for (int i = 0; i < sizepro; i++) {
			//printf("%d\n", sizepro);
			Projectile& thispro = *gameworld.Projectiles.at(i);
			thispro.DrawProjectile(window);
		}
		


		//window.draw(myFpsCounter);
		sf::Time BeforeDisplay = Clock.getElapsedTime();
		
		
		sf::Time frameEnd = Clock.getElapsedTime();

		sf::Time frameDuration = frameEnd - frameStart;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			//printed = true;
			printf("%f  ", appStart.asSeconds());
			printf("%f  ", frameStart.asSeconds());
			printf("%f  ", BeforeDisplay.asSeconds());
			printf("%f  ", frameEnd.asSeconds());
			printf("%f  \n", frameDuration.asSeconds());
			printf("fps %f\n", 0.25f*(fps[0] + fps[1] + fps[2] + fps[3]));

		}
		;
		int speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			speed = MainTank.speed * 2;
		else
			speed = MainTank.speed;
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			PosTank.x -= speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			PosTank.x += speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			PosTank.y -= speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			PosTank.y += speed;
		MainTank.shape->setPosition(PosTank);
		MainTank.rect = MainTank.shape->getGlobalBounds();
		//Deplace les projectiles
		for (int i = 0; i < sizepro; i++) {
			//gameworld.Projectiles.at(i).PushProjectile(window);
			Projectile& thispro = *gameworld.Projectiles.at(i);
			thispro.PushProjectile();
		}


		//Collisions
		gameworld.IntersectProWall();
		gameworld.IntersectTankWall();

		sf::Time PrevFrameEnd = frameEnd;
		fps[step % 4] = 1.0f / (frameStart - PrevFrameStart).asSeconds();
		PrevFrameStart = frameStart;
		step++;
		window.display();
		
	}

	return 0;
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Conseils pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
