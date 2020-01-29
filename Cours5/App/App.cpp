// App.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include <math.h>
#include "Lib.hpp"
#include "World.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2D/Box2D.h>
int resettime = 0;
int count = 0;
using namespace sf;
int winframecount = 0;
int mapnumber = 0;
float mapnumberF = 0;
int lastmap = 0;
int mapcount = 8;
Clock genclock;
//Cours 6
std::vector<RectangleShape*> SmokePro;
std::vector<ExplosionParticle*> ExploPro;
bool canpress = true;

Shader blur;
bool Menu1 = true;;
bool Menu2 = false;
bool Game = false;
Color blu(0, 188, 255);
Color blak(60, 60, 60);
Color gre(155, 155, 155);
Color whit(222, 222, 222);
float angleA = 3.14 / 4;
float angleB = (5 * 3.14) / 4;
float angleC = (3 * 3.14) / 4;
float angleD = (7 * 3.14) / 4;
float TargetA = 3.14 / 4;
float TargetB = (5 * 3.14) / 4;
float TargetC = (3 * 3.14) / 4;
float TargetD = (7 * 3.14) / 4;

bool autoaim = true;


//sound
sf::SoundBuffer Explosion;
sf::SoundBuffer Shoot;
sf::SoundBuffer Select;
sf::SoundBuffer Bounce;
sf::SoundBuffer Death;
sf::Sound explo;
sf::Sound shoot;
sf::Sound select;
sf::Sound boun;
sf::Sound desu;

sf::SoundBuffer BGMusic;
sf::Sound BGM;


float presstime = 0;

//Jeu
static World gameworld;

void World::SoundMethod(int soundnum) {
	

	switch (soundnum) {
	case 0:
		select.play();
		break;
	case 1:
		shoot.setVolume(70);
		shoot.play();
		break;
	case 2:
		explo.setVolume(70);
		explo.play();
		break;
	case 3:
		boun.setVolume(70);
		boun.play();
		break;
	case 4:
		desu.setVolume(100);
		desu.play();
		break;
	}
	


	



}
void pressmethod(float time) {
	if (genclock.getElapsedTime().asMilliseconds()-presstime >= 500)
		canpress = true;
	
}
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



void InitSquare(int owner) {
	sf::RectangleShape *rect = new RectangleShape(Vector2f(16,16)); //16;16
	rect->setOrigin(8, 8); //8;8
	RectangleShape * cannon = new RectangleShape(Vector2f(16, 4));
	cannon->setOrigin(0, 2);
	//printf("%d \n", owner);
	Tank * MainTank;
	switch (owner) {
	case 0:
		MainTank = new Tank(rect,cannon, Vector2f(100, 100), owner);
		break;
	case 1:
		MainTank = new Tank(rect,cannon, Vector2f(700, 500), owner);
		break;
	case 2:
		MainTank = new Tank(rect,cannon, Vector2f(700, 100), owner);
		break;
	case 3:
		MainTank = new Tank(rect,cannon, Vector2f(100, 500), owner);
		break;

	}
	
	gameworld.Tanks.push_back(MainTank);
}

void DrawMovingSquare(sf::RenderWindow & win) {

	int size = gameworld.Tanks.size();
	for (int i = 0; i < size; i++) {
	
		Tank& MainTank = *gameworld.Tanks.at(i);
		

		MainTank.shape->setFillColor(sf::Color::Transparent);
		MainTank.Cannon->setFillColor(sf::Color::Transparent);
		
		MainTank.shape->setOutlineThickness(1);
		MainTank.Cannon->setOutlineThickness(1);
		switch (i) {
		case 0:
			MainTank.shape->setOutlineColor(sf::Color::Green);
			MainTank.Cannon->setOutlineColor(sf::Color::Green);
			break;
		case 1:
			MainTank.shape->setOutlineColor(blu);
			MainTank.Cannon->setOutlineColor(blu);
			break;
		case 2:
			MainTank.shape->setOutlineColor(sf::Color::Red);
			MainTank.Cannon->setOutlineColor(sf::Color::Red);
			break;
		case 3:
			MainTank.shape->setOutlineColor(sf::Color::Yellow);
			MainTank.Cannon->setOutlineColor(sf::Color::Yellow);
			break;
		}
		
		win.draw(*MainTank.shape);
		win.draw(*MainTank.Cannon);
	}

}
void DrawDeadSmoke(sf::RenderWindow & win, int owner) {

	sf::RectangleShape *rect = new RectangleShape(Vector2f(4, 4)); 
	rect->setFillColor(sf::Color::Transparent);
	

	rect->setOutlineThickness(1);
	switch (owner) {
	case 0:
		rect->setOutlineColor(sf::Color::Green);
		break;
	case 1:
		rect->setOutlineColor(blu);
		break;
	case 2:
		rect->setOutlineColor(sf::Color::Red);
		break;
	case 3:
		rect->setOutlineColor(sf::Color::Yellow);
		break;
	}
	rect->setPosition(gameworld.Tanks[owner]->shape->getPosition());

	if (SmokePro.size() == 0) {
		SmokePro.push_back(rect);
	 }
	else if (SmokePro.at(SmokePro.size() - 1)->getScale().x > 4) {
		SmokePro.push_back(rect);
	}
	if(SmokePro.at(0)->getScale().x > 16){

		SmokePro.erase(SmokePro.begin());
	}
	
	for (RectangleShape* thisrec : SmokePro) {
		thisrec->setScale(thisrec->getScale().x+0.05, thisrec->getScale().y+0.05);
		thisrec->setPosition(thisrec->getPosition().x + 0.2, thisrec->getPosition().y - 0.3);
		if(thisrec->getOutlineColor().a>0)
		thisrec->setOutlineColor(Color(thisrec->getOutlineColor().r, thisrec->getOutlineColor().g, thisrec->getOutlineColor().b, thisrec->getOutlineColor().a - 1));
		win.draw(*thisrec);
	};
	
}



static Vector2f GetMousePos(sf::RenderWindow & win) {
	
	return (Vector2f)sf::Mouse::getPosition(win);
}
Vector2f AimingMethod(Vector2f TankPos, float angle) {
	
	Vector2f aimpos(TankPos.x + 50 * cos(angle), TankPos.y + 50 * sin(angle));

	return aimpos;
}
void DrawAimingMethod(Vector2f Aimpos, float angle,RenderWindow & win, int owner) {

	gameworld.Tanks[owner]->Cannon->setRotation((angle*180)/3.14);
	CircleShape tri(3, 3);
	tri.setFillColor(sf::Color::Transparent);
	switch (owner) {
	case 0:
		tri.setOutlineColor(sf::Color::Green);
		break;
	case 1:
		tri.setOutlineColor(blu);
		break;
	case 2:
		tri.setOutlineColor(sf::Color::Red);
		break;
	case 3:
		tri.setOutlineColor(sf::Color::Yellow);
		break;
	}
	tri.setOutlineThickness(1);
	tri.setPosition(Aimpos);
	win.draw(tri);
	
}

void ShootCannon(Vector2f MousPos, Vector2f TankPos, int owner) {
	
	
	float angle = atan2f(MousPos.y-TankPos.y,MousPos.x- TankPos.x);
	//sf::Vector2f DirVer(MousPos.x - TankPos.x, MousPos.y - TankPos.y);
	sf::Vector2f DirVer(cos(angle), sin(angle));
	


	//printf("%f \n", angle);
	sf::RectangleShape * attack = new RectangleShape(Vector2f(4, 4));
	
	attack->setPosition(Vector2f(TankPos.x+DirVer.x*16, TankPos.y+DirVer.y*16));
	attack->setOrigin(2, 2);
	attack->setFillColor(sf::Color::Transparent);
	switch (owner) {
	case 0:
		attack->setOutlineColor(sf::Color::Green);
		break;
	case 1:
		attack->setOutlineColor(blu);
		break;
	case 2:
		attack->setOutlineColor(sf::Color::Red);
		break;
	case 3:
		attack->setOutlineColor(sf::Color::Yellow);
		break;
	}
	attack->setOutlineThickness(1);
	
	Projectile * attackpoint = new Projectile(attack, DirVer, 4);
	attackpoint->Owner = owner;
	gameworld.Projectiles.push_back(attackpoint);
	World::SoundMethod(1);
	

}
void World::MakeExplosion(Vector2f pos, int owner) {
	std::vector<CircleShape*> allshapes;
	allshapes.clear();
	for (int i = 0; i < 16; i++) {
		
		std::srand(genclock.getElapsedTime().asMilliseconds()+i*200);
		CircleShape* circle = new CircleShape(std::rand() % 13 + 4, std::rand() % 3 + 3);
		circle->setPosition(pos);
		circle->setFillColor(sf::Color::Transparent);
		circle->setOrigin((std::rand() % 16 + 4) / 2, (std::rand() % 16 + 4) / 2);
		circle->setOutlineThickness(1);
		allshapes.push_back(circle);
	}
	int i = 0;
	for (CircleShape* cir : allshapes) {
		i++;
		switch (owner) {
		case 0:
			cir->setOutlineColor(sf::Color::Green);
			break;
		case 1:
			cir->setOutlineColor(blu);
			break;
		case 2:
			cir->setOutlineColor(sf::Color::Red);
			break;
		case 3:
			cir->setOutlineColor(sf::Color::Yellow);
			break;
			
		}
		std::srand(genclock.getElapsedTime().asMilliseconds() + i*200);
		ExplosionParticle * par = new ExplosionParticle(cir, Vector2f(std::rand() % 3-1, std::rand() % 3-1), (std::rand() % 3 ));
		std::srand(genclock.getElapsedTime().asMilliseconds() + 2);
		par->fadespeed = std::rand() % 5 + 2;
		ExploPro.push_back(par);
		SoundMethod(2);
	}

	
}

void MakeBorderWalls(int mapnum) {
	gameworld.Walls.clear();
	RectangleShape *bg = new RectangleShape(Vector2f(800, 600));
	bg->setFillColor(sf::Color::Transparent);
	bg->setOutlineColor(sf::Color::Transparent);
	bg->setOutlineThickness(1);
	Wall * BG = new Wall(bg, Vector2f(0, 0));
	BG->NoRect();



	RectangleShape *left = new RectangleShape(Vector2f(16,600));
	left->setFillColor(sf::Color::Transparent);
	left->setOutlineColor(sf::Color::White);
	left->setOutlineThickness(1);
	Wall * Left = new Wall(left, Vector2f(0, 0));

	RectangleShape *up = new RectangleShape(Vector2f(800, 16));
	up->setFillColor(sf::Color::Transparent);
	up->setOutlineColor(sf::Color::White);
	up->setOutlineThickness(1);
	Wall *Up = new Wall(up, Vector2f(0, 0));

	RectangleShape *down = new RectangleShape(Vector2f(800, 16));
	down->setFillColor(sf::Color::Transparent);
	down->setOutlineColor(sf::Color::White);
	down->setOutlineThickness(1);
	Wall *Down = new Wall(down, Vector2f(0, 600 -16));

	RectangleShape *right= new RectangleShape(Vector2f(16, 600));
	right->setFillColor(sf::Color::Transparent);
	right->setOutlineColor(sf::Color::White);
	right->setOutlineThickness(1);
	Wall *Right = new Wall(right, Vector2f(800-16, 0));

	gameworld.Walls.push_back(BG);
	gameworld.Walls.push_back(Left);
	gameworld.Walls.push_back(Up);
	gameworld.Walls.push_back(Down);
	gameworld.Walls.push_back(Right);
	//MAPS

	switch (mapnumber)
	{
	
	case 1:
	
	{RectangleShape * WallA = new RectangleShape(Vector2f(16, 400));
	WallA->setFillColor(sf::Color::Transparent);
	WallA->setOutlineColor(sf::Color::White);
	WallA->setOutlineThickness(1);
	WallA->setOrigin(8, 200);
	Wall * wallA = new Wall(WallA, Vector2f(400, 300));

	RectangleShape * WallB = new RectangleShape(Vector2f(400, 16));
	WallB->setFillColor(sf::Color::Transparent);
	WallB->setOutlineColor(sf::Color::White);
	WallB->setOutlineThickness(1);
	WallB->setOrigin(200, 8);
	Wall * wallB = new Wall(WallB, Vector2f(400, 300));

	gameworld.Walls.push_back(wallA);
	gameworld.Walls.push_back(wallB); }
	for (Wall * wal : gameworld.Walls) {
		wal->shape->setOutlineColor(sf::Color::Magenta);
	}
		break;
		//RED FORTRESS
	case 2:
		for (Wall * wal : gameworld.Walls) {
			wal->shape->setOutlineColor(Color::Red);
		}
		{RectangleShape * WallA = new RectangleShape(Vector2f(16, 120));
		WallA->setFillColor(sf::Color::Transparent);
		WallA->setOutlineColor(sf::Color::Red);
		WallA->setOutlineThickness(1);
		WallA->setOrigin(8, 60);
		Wall * wallA = new Wall(WallA, Vector2f(298, 210));

		RectangleShape * WallB = new RectangleShape(Vector2f(16, 120));
		WallB->setFillColor(sf::Color::Transparent);
		WallB->setOutlineColor(sf::Color::Red);
		WallB->setOutlineThickness(1);
		WallB->setOrigin(8, 60);
		Wall * wallB = new Wall(WallB, Vector2f(298, 390));

		RectangleShape * WallC = new RectangleShape(Vector2f(16, 120));
		WallC->setFillColor(sf::Color::Transparent);
		WallC->setOutlineColor(sf::Color::Red);
		WallC->setOutlineThickness(1);
		WallC->setOrigin(8, 60);
		Wall * wallC = new Wall(WallC, Vector2f(508, 210));

		RectangleShape * WallD = new RectangleShape(Vector2f(16, 120));
		WallD->setFillColor(sf::Color::Transparent);
		WallD->setOutlineColor(sf::Color::Red);
		WallD->setOutlineThickness(1);
		WallD->setOrigin(8, 60);
		Wall * wallD = new Wall(WallD, Vector2f(508, 390));

		RectangleShape * WallE = new RectangleShape(Vector2f(90, 16));
		WallE->setFillColor(sf::Color::Transparent);
		WallE->setOutlineColor(sf::Color::Red);
		WallE->setOutlineThickness(1);
		WallE->setOrigin(45, 8);
		Wall * wallE = new Wall(WallE, Vector2f(471, 158));

		RectangleShape * WallF = new RectangleShape(Vector2f(90, 16));
		WallF->setFillColor(sf::Color::Transparent);
		WallF->setOutlineColor(sf::Color::Red);
		WallF->setOutlineThickness(1);
		WallF->setOrigin(45, 8);
		Wall * wallF = new Wall(WallF, Vector2f(335, 158));

		RectangleShape * WallG = new RectangleShape(Vector2f(90, 16));
		WallG->setFillColor(sf::Color::Transparent);
		WallG->setOutlineColor(sf::Color::Red);
		WallG->setOutlineThickness(1);
		WallG->setOrigin(45, 8);
		Wall * wallG = new Wall(WallG, Vector2f(335, 442));

		RectangleShape * WallH = new RectangleShape(Vector2f(90, 16));
		WallH->setFillColor(sf::Color::Transparent);
		WallH->setOutlineColor(sf::Color::Red);
		WallH->setOutlineThickness(1);
		WallH->setOrigin(45, 8);
		Wall * wallH = new Wall(WallH, Vector2f(471, 442));

		RectangleShape * WallI = new RectangleShape(Vector2f(130, 16));
		WallI->setFillColor(sf::Color::Transparent);
		WallI->setOutlineColor(sf::Color::Red);
		WallI->setOutlineThickness(1);
		WallI->setOrigin(45, 8);
		Wall * wallI = new Wall(WallI, Vector2f(62, 208));

		RectangleShape * WallJ = new RectangleShape(Vector2f(16, 130));
		WallJ->setFillColor(sf::Color::Transparent);
		WallJ->setOutlineColor(sf::Color::Red);
		WallJ->setOutlineThickness(1);
		WallJ->setOrigin(8, 45);
		Wall * wallJ = new Wall(WallJ, Vector2f(140, 62));

		RectangleShape * WallK = new RectangleShape(Vector2f(130, 16));
		WallK->setFillColor(sf::Color::Transparent);
		WallK->setOutlineColor(sf::Color::Red);
		WallK->setOutlineThickness(1);
		WallK->setOrigin(45, 8);
		Wall * wallK = new Wall(WallK, Vector2f(800-62-16-16-8, 208));

		RectangleShape * WallL = new RectangleShape(Vector2f(16, 130));
		WallL->setFillColor(sf::Color::Transparent);
		WallL->setOutlineColor(sf::Color::Red);
		WallL->setOutlineThickness(1);
		WallL->setOrigin(8, 45);
		Wall * wallL = new Wall(WallL, Vector2f(800-140, 62));

		RectangleShape * WallM = new RectangleShape(Vector2f(130, 16));
		WallM->setFillColor(sf::Color::Transparent);
		WallM->setOutlineColor(sf::Color::Red);
		WallM->setOutlineThickness(1);
		WallM->setOrigin(45, 8);
		Wall * wallM = new Wall(WallM, Vector2f(800 - 62 - 16 - 16 - 8, 600-208));

		RectangleShape * WallN = new RectangleShape(Vector2f(16, 130));
		WallN->setFillColor(sf::Color::Transparent);
		WallN->setOutlineColor(sf::Color::Red);
		WallN->setOutlineThickness(1);
		WallN->setOrigin(8, 45);
		Wall * wallN = new Wall(WallN, Vector2f(800 - 140,600-62 -32-8));

		RectangleShape * WallO = new RectangleShape(Vector2f(130, 16));
		WallO->setFillColor(sf::Color::Transparent);
		WallO->setOutlineColor(sf::Color::Red);
		WallO->setOutlineThickness(1);
		WallO->setOrigin(45, 8);
		Wall * wallO = new Wall(WallO, Vector2f( 62, 600 - 208));

		RectangleShape * WallP = new RectangleShape(Vector2f(16, 130));
		WallP->setFillColor(sf::Color::Transparent);
		WallP->setOutlineColor(sf::Color::Red);
		WallP->setOutlineThickness(1);
		WallP->setOrigin(8, 45);
		Wall * wallP = new Wall(WallP, Vector2f(140, 600 - 62 - 32 - 8));

		gameworld.Walls.push_back(wallA);
		gameworld.Walls.push_back(wallB);
		gameworld.Walls.push_back(wallC);
		gameworld.Walls.push_back(wallD);
		gameworld.Walls.push_back(wallE);
		gameworld.Walls.push_back(wallF);
		gameworld.Walls.push_back(wallG);
		gameworld.Walls.push_back(wallH);
	
		gameworld.Walls.push_back(wallI);
		gameworld.Walls.push_back(wallJ);
		gameworld.Walls.push_back(wallK);
		gameworld.Walls.push_back(wallL);
		gameworld.Walls.push_back(wallM);
		gameworld.Walls.push_back(wallN);
		gameworld.Walls.push_back(wallO);
		gameworld.Walls.push_back(wallP);
		}
		break;
		case 3:
			for (Wall * wal : gameworld.Walls) {
				wal->shape->setOutlineColor(Color::Green);
			}
		for(int i = 0; i <54; i++){
			srand(genclock.getElapsedTime().asMilliseconds() + 3.14*pow(i, 2));
			RectangleShape * WallA = new RectangleShape(Vector2f(24, 24));
			WallA->setFillColor(sf::Color::Transparent);
			WallA->setOutlineColor(sf::Color::Green);
			WallA->setOutlineThickness(1);
			WallA->setOrigin(12, 12);
			Wall * wall = new Wall(WallA, Vector2f(rand()%784+8, rand()%550+25));
			gameworld.Walls.push_back(wall);
		}
		break;
		case 4:
			for (Wall * wal : gameworld.Walls) {
				wal->shape->setOutlineColor(Color::Yellow);
			}
			{
				RectangleShape * WallA = new RectangleShape(Vector2f(512,16));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(sf::Color::Yellow);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(256, 8);
				Wall * wallA = new Wall(WallA, Vector2f(400+8, 68));
				gameworld.Walls.push_back(wallA);

				WallA = new RectangleShape(Vector2f(16, 256));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(sf::Color::Yellow);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(8, 256);
				wallA = new Wall(WallA, Vector2f(400 + 16-256, 68+256+64));
				gameworld.Walls.push_back(wallA);

				WallA = new RectangleShape(Vector2f(16, 256));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(sf::Color::Yellow);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(8, 256);
				wallA = new Wall(WallA, Vector2f(800-(400  - 256), 68 + 256 + 64));
				gameworld.Walls.push_back(wallA);

				WallA = new RectangleShape(Vector2f(256-64, 16));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(sf::Color::Yellow);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(128-32, 8);
				wallA = new Wall(WallA, Vector2f(400 + 8-128-32, 68 + 256 + 64-8));
				gameworld.Walls.push_back(wallA);

				WallA = new RectangleShape(Vector2f(256 - 64, 16));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(sf::Color::Yellow);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(128 - 32, 8);
				wallA = new Wall(WallA, Vector2f(800-(400 + 8 - 128 - 32)+16, 68 + 256 + 64 - 8));
				gameworld.Walls.push_back(wallA);

				//Pillars
				WallA = new RectangleShape(Vector2f(16, 16));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(sf::Color::Yellow);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(8, 8);
				wallA = new Wall(WallA, Vector2f(400 +32 +32 -256, 68+32+16));
				gameworld.Walls.push_back(wallA);

				WallA = new RectangleShape(Vector2f(16, 16));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(sf::Color::Yellow);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(8, 8);
				wallA = new Wall(WallA, Vector2f(400 + 32 + 32 - 256 + 128-16, 68 + 32 + 16));
				gameworld.Walls.push_back(wallA);

				WallA = new RectangleShape(Vector2f(16, 16));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(sf::Color::Yellow);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(8, 8);
				wallA = new Wall(WallA, Vector2f(400 + 32 + 32 - 256 + 128 - 16, 68 + 32 + 16+64));
				gameworld.Walls.push_back(wallA);

				WallA = new RectangleShape(Vector2f(16, 16));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(sf::Color::Yellow);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(8, 8);
				wallA = new Wall(WallA, Vector2f(400 + 32 + 32 - 256, 68 + 32 + 16+64));
				gameworld.Walls.push_back(wallA);

				WallA = new RectangleShape(Vector2f(16, 16));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(sf::Color::Yellow);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(8, 8);
				wallA = new Wall(WallA, Vector2f(400 + 32 + 32 - 256 + 128 - 16, 68 + 32 + 16 + 64 +64));
				gameworld.Walls.push_back(wallA);

				WallA = new RectangleShape(Vector2f(16, 16));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(sf::Color::Yellow);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(8, 8);
				wallA = new Wall(WallA, Vector2f(400 + 32 + 32 - 256, 68 + 32 + 16 + 64 +64));
				gameworld.Walls.push_back(wallA);

				WallA = new RectangleShape(Vector2f(16, 16));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(sf::Color::Yellow);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(8, 8);
				wallA = new Wall(WallA, Vector2f(400 + 32 + 32 - 256 + 128 - 16, 68 + 32 + 16 + 64 + 64 +64));
				gameworld.Walls.push_back(wallA);

				WallA = new RectangleShape(Vector2f(16, 16));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(sf::Color::Yellow);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(8, 8);
				wallA = new Wall(WallA, Vector2f(400 + 32 + 32 - 256, 68 + 32 + 16 + 64 + 64 +64));
				gameworld.Walls.push_back(wallA);


				//Pillars2
				WallA = new RectangleShape(Vector2f(16, 16));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(sf::Color::Yellow);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(8, 8);
				wallA = new Wall(WallA, Vector2f(800-(400 + 32 + 32 - 256) + 8, 68 + 32 + 16));
				gameworld.Walls.push_back(wallA);

				WallA = new RectangleShape(Vector2f(16, 16));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(sf::Color::Yellow);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(8, 8);
				wallA = new Wall(WallA, Vector2f(800-(400 + 32 + 32 - 256 + 128 - 16) + 8, 68 + 32 + 16));
				gameworld.Walls.push_back(wallA);

				WallA = new RectangleShape(Vector2f(16, 16));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(sf::Color::Yellow);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(8, 8);
				wallA = new Wall(WallA, Vector2f(800-(400 + 32 + 32 - 256 + 128 - 16) + 8, 68 + 32 + 16 + 64));
				gameworld.Walls.push_back(wallA);

				WallA = new RectangleShape(Vector2f(16, 16));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(sf::Color::Yellow);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(8, 8);
				wallA = new Wall(WallA, Vector2f(800-(400 + 32 + 32 - 256) + 8, 68 + 32 + 16 + 64));
				gameworld.Walls.push_back(wallA);

				WallA = new RectangleShape(Vector2f(16, 16));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(sf::Color::Yellow);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(8, 8);
				wallA = new Wall(WallA, Vector2f(800-(400 + 32 + 32 - 256 + 128 - 16) + 8, 68 + 32 + 16 + 64 + 64));
				gameworld.Walls.push_back(wallA);

				WallA = new RectangleShape(Vector2f(16, 16));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(sf::Color::Yellow);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(8, 8);
				wallA = new Wall(WallA, Vector2f(800-(400 + 32 + 32 - 256) + 8, 68 + 32 + 16 + 64 + 64));
				gameworld.Walls.push_back(wallA);

				WallA = new RectangleShape(Vector2f(16, 16));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(sf::Color::Yellow);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(8, 8);
				wallA = new Wall(WallA, Vector2f(800-(400 + 32 + 32 - 256 + 128 - 16) + 8, 68 + 32 + 16 + 64 + 64 + 64));
				gameworld.Walls.push_back(wallA);

				WallA = new RectangleShape(Vector2f(16, 16));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(sf::Color::Yellow);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(8, 8);
				wallA = new Wall(WallA, Vector2f(800-(400 + 32 + 32 - 256)+8, 68 + 32 + 16 + 64 + 64 + 64));
				gameworld.Walls.push_back(wallA);

			
			}
		break;
		case 5:
			for (Wall * wal : gameworld.Walls) {
				wal->shape->setOutlineColor(blak);
			}
			for (int i = 0; i < 200; i++) {
				srand(genclock.getElapsedTime().asMilliseconds() + 3.14*pow(i, 2));
				RectangleShape * WallA = new RectangleShape(Vector2f(rand()%16+8, rand() % 16 + 8));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(blak);
				WallA->setOutlineThickness(1);
				WallA->setOrigin((rand() % 16 + 8)/2, (rand() % 16 + 8) / 2);
				Wall * wall = new Wall(WallA, Vector2f(rand() % 784 + 8, rand() % 550 + 25));
				gameworld.Walls.push_back(wall);
			}
			break;
		case 6:
			for (Wall * wal : gameworld.Walls) {
				wal->shape->setOutlineColor(gre);
			}
			{RectangleShape * WallA = new RectangleShape(Vector2f(256, 256));
			WallA->setFillColor(sf::Color::Transparent);
			WallA->setOutlineColor(gre);
			WallA->setOutlineThickness(1);
			WallA->setOrigin(128, 128);
			Wall * wallA = new Wall(WallA, Vector2f(400, 300));
			gameworld.Walls.push_back(wallA); }


			srand(genclock.getElapsedTime().asMilliseconds() + 3.14*pow(genclock.getElapsedTime().asMilliseconds(), 2));
			for (int i = 0; i < rand()%20+6; i++) {
				srand(genclock.getElapsedTime().asMilliseconds() + 3.14*pow(i, 2));
				RectangleShape * WallA = new RectangleShape(Vector2f(rand() % 16 + 8, rand() % 16 + 8));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(gre);
				WallA->setOutlineThickness(1);
				WallA->setOrigin((rand() % 16 + 8) / 2, (rand() % 16 + 8) / 2);
				Wall * wall = new Wall(WallA, Vector2f(rand() % 100 + 8, rand() % 550 + 25));
				gameworld.Walls.push_back(wall);
			}
			for (int i = 0; i < rand() % 20 + 6; i++) {
				srand(genclock.getElapsedTime().asMilliseconds() + 3.14*pow(i, 2));
				RectangleShape * WallA = new RectangleShape(Vector2f(rand() % 16 + 8, rand() % 16 + 8));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(gre);
				WallA->setOutlineThickness(1);
				WallA->setOrigin((rand() % 16 + 8) / 2, (rand() % 16 + 8) / 2);
				Wall * wall = new Wall(WallA, Vector2f(rand() % 100 + 8+600, rand() % 550 + 25));
				gameworld.Walls.push_back(wall);
			}
			for (int i = 0; i < rand() % 20 + 6; i++) {
				srand(genclock.getElapsedTime().asMilliseconds() + 3.14*pow(i, 2));
				RectangleShape * WallA = new RectangleShape(Vector2f(rand() % 16 + 8, rand() % 16 + 8));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(gre);
				WallA->setOutlineThickness(1);
				WallA->setOrigin((rand() % 16 + 8) / 2, (rand() % 16 + 8) / 2);
				Wall * wall = new Wall(WallA, Vector2f(rand() % 768 + 8, rand() % 100 + 25));
				gameworld.Walls.push_back(wall);
			}
			for (int i = 0; i < rand() % 20 + 6; i++) {
				srand(genclock.getElapsedTime().asMilliseconds() + 3.14*pow(i, 2));
				RectangleShape * WallA = new RectangleShape(Vector2f(rand() % 16 + 8, rand() % 16 + 8));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(gre);
				WallA->setOutlineThickness(1);
				WallA->setOrigin((rand() % 16 + 8) / 2, (rand() % 16 + 8) / 2);
				Wall * wall = new Wall(WallA, Vector2f(rand() % 768 + 8, rand() % 100 + 25+500-8));
				gameworld.Walls.push_back(wall);
			}
			break;
		case 7:
			for (Wall * wal : gameworld.Walls) {
				wal->shape->setOutlineColor(blu);
			}
			{
				//Spawn Points
				RectangleShape *WallA = new RectangleShape(Vector2f(128, 64));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(blu);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(64, 32);
				Wall *wallA = new Wall(WallA, Vector2f(256, 64));
				gameworld.Walls.push_back(wallA);


				WallA = new RectangleShape(Vector2f(128, 64));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(blu);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(64, 32);
				wallA = new Wall(WallA, Vector2f(128-32, 128+32));
				gameworld.Walls.push_back(wallA);

				WallA = new RectangleShape(Vector2f(128, 64));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(blu);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(64, 32);
				wallA = new Wall(WallA, Vector2f(800-256, 64));
				gameworld.Walls.push_back(wallA);


				WallA = new RectangleShape(Vector2f(128, 64));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(blu);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(64, 32);
				wallA = new Wall(WallA, Vector2f(800-(128 - 32), 128 + 32));
				gameworld.Walls.push_back(wallA);

				WallA = new RectangleShape(Vector2f(128, 64));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(blu);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(64, 32);
				wallA = new Wall(WallA, Vector2f(800 - 256, 600-64));
				gameworld.Walls.push_back(wallA);


				WallA = new RectangleShape(Vector2f(128, 64));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(blu);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(64, 32);
				wallA = new Wall(WallA, Vector2f(800 - (128 - 32), 600-(128 + 32)));
				gameworld.Walls.push_back(wallA);

				WallA = new RectangleShape(Vector2f(128, 64));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(blu);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(64, 32);
				wallA = new Wall(WallA, Vector2f(256, 600 - 64));
				gameworld.Walls.push_back(wallA);


				WallA = new RectangleShape(Vector2f(128, 64));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(blu);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(64, 32);
				wallA = new Wall(WallA, Vector2f(128 - 32, 600 - (128 + 32)));
				gameworld.Walls.push_back(wallA);

				//Town
				WallA = new RectangleShape(Vector2f(64, 128));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(blu);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(32, 64);
				wallA = new Wall(WallA, Vector2f(256-32, 128 + 32));
				gameworld.Walls.push_back(wallA);

				WallA = new RectangleShape(Vector2f(64, 128));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(blu);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(32, 64);
				wallA = new Wall(WallA, Vector2f(256 - 32, 256+ 32+32));
				gameworld.Walls.push_back(wallA);

				WallA = new RectangleShape(Vector2f(128, 64));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(blu);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(64, 32);
				wallA = new Wall(WallA, Vector2f(128 - 32, 600 - (128 + 32+32+32+32)));
				gameworld.Walls.push_back(wallA);

				WallA = new RectangleShape(Vector2f(64, 128));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(blu);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(32, 64);
				wallA = new Wall(WallA, Vector2f(128, 256 + 64-8));
				gameworld.Walls.push_back(wallA);

				WallA = new RectangleShape(Vector2f(64, 128));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(blu);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(32, 64);
				wallA = new Wall(WallA, Vector2f(256+64-32, 600-(128 + 32)+64));
				gameworld.Walls.push_back(wallA);

				WallA = new RectangleShape(Vector2f(128, 64));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(blu);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(64, 32);
				wallA = new Wall(WallA, Vector2f(256+64, 128 + 32 + 32 + 32 + 32+32));
				gameworld.Walls.push_back(wallA);

				WallA = new RectangleShape(Vector2f(128, 64));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(blu);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(64, 32);
				wallA = new Wall(WallA, Vector2f(256 + 64+128+32, 128 + 32 + 32 + 32 + 32 + 32));
				gameworld.Walls.push_back(wallA);

				WallA = new RectangleShape(Vector2f(64, 128));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(blu);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(32, 64);
				wallA = new Wall(WallA, Vector2f(256 - 32+128, 256 + 32 + 32));
				gameworld.Walls.push_back(wallA);

				WallA = new RectangleShape(Vector2f(64, 128));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(blu);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(32, 64);
				wallA = new Wall(WallA, Vector2f(256 - 32 + 128+64+32, 256 + 32 + 32));
				gameworld.Walls.push_back(wallA);

				WallA = new RectangleShape(Vector2f(128, 64));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(blu);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(64, 32);
				wallA = new Wall(WallA, Vector2f(256 + 64, 128 + 32 + 32 ));
				gameworld.Walls.push_back(wallA);

				WallA = new RectangleShape(Vector2f(64, 128));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(blu);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(32, 64);
				wallA = new Wall(WallA, Vector2f(256 - 32 + 128 + 64 + 32, 256 + 32 + 32+64+32));
				gameworld.Walls.push_back(wallA);

				WallA = new RectangleShape(Vector2f(64, 128));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(blu);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(32, 64);
				wallA = new Wall(WallA, Vector2f(256 - 32 + 128 + 64 + 32+64+32, 256 + 32 + 32 + 64 +32));
				gameworld.Walls.push_back(wallA);

				WallA = new RectangleShape(Vector2f(64, 128));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(blu);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(32, 64);
				wallA = new Wall(WallA, Vector2f(256 - 32+64+32+32, 128-32));
				gameworld.Walls.push_back(wallA);

				WallA = new RectangleShape(Vector2f(128, 64));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(blu);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(64, 32);
				wallA = new Wall(WallA, Vector2f(256 + 64+128+32, 128 + 32 + 32));
				gameworld.Walls.push_back(wallA);

				WallA = new RectangleShape(Vector2f(64, 128));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(blu);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(32, 64);
				wallA = new Wall(WallA, Vector2f(256 - 32 + 64 + 32 + 32+64+32, 128 - 32));
				gameworld.Walls.push_back(wallA);

				WallA = new RectangleShape(Vector2f(128, 64));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(blu);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(64, 32);
				wallA = new Wall(WallA, Vector2f(256 + 64 + 128 + 32+128+32, 128 + 32 + 32+128-32));
				gameworld.Walls.push_back(wallA);                    

				WallA = new RectangleShape(Vector2f(64, 128));
				WallA->setFillColor(sf::Color::Transparent);
				WallA->setOutlineColor(blu);
				WallA->setOutlineThickness(1);
				WallA->setOrigin(32, 64);
				wallA = new Wall(WallA, Vector2f(256 + 64 + 128 + 32 + 128 + 32+32, 128 + 32 + 32 + 128 - 32+32));
				gameworld.Walls.push_back(wallA);
			}
			break;
		
			
	}

	
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


void ScoreMethod(int playercount, Font font, RenderWindow & win ) {
	sf::Text ScoreA;
	sf::Text ScoreB;
	sf::Text ScoreC;
	sf::Text ScoreD;
	ScoreA.setFont(font);
	ScoreB.setFont(font);
	ScoreC.setFont(font);
	ScoreD.setFont(font);
	ScoreA.setOutlineColor(sf::Color::Green);
	ScoreB.setOutlineColor(blu);
	ScoreC.setOutlineColor(sf::Color::Red);
	ScoreD.setOutlineColor(sf::Color::Yellow);
	ScoreA.setFillColor(sf::Color::Green);
	ScoreB.setFillColor(blu);
	ScoreC.setFillColor(sf::Color::Red);
	ScoreD.setFillColor(sf::Color::Yellow);
	ScoreA.setCharacterSize(10);
	ScoreB.setCharacterSize(10);
	ScoreC.setCharacterSize(10);
	ScoreD.setCharacterSize(10);
	
	int i = 0;
	gameworld.Tanks[i]->kills;
	gameworld.Tanks[i]->deaths;	
	ScoreA.setString("P1: K:" + std::to_string(gameworld.Tanks[i]->kills) + " D:" + std::to_string(gameworld.Tanks[i]->deaths) + " W:" + std::to_string(gameworld.Tanks[i]->win) + " ");
	ScoreA.setPosition(20, 4);
	if (playercount > 1) {
		i++;
		ScoreB.setString("P2: K:" + std::to_string(gameworld.Tanks[i]->kills) + " D:" + std::to_string(gameworld.Tanks[i]->deaths) + " W:" + std::to_string(gameworld.Tanks[i]->win) + " " " ");
		ScoreB.setPosition(120, 4);
	}
	if (playercount > 2) {
		i++;
		ScoreC.setString("P3: K:" + std::to_string(gameworld.Tanks[i]->kills) + " D:" + std::to_string(gameworld.Tanks[i]->deaths) + " W:" + std::to_string(gameworld.Tanks[i]->win) + " "" ");
		ScoreC.setPosition(220, 4);
	}
	if (playercount > 3) {
		i++;
		ScoreD.setString("P4: K:" + std::to_string(gameworld.Tanks[i]->kills) + " D:" + std::to_string(gameworld.Tanks[i]->deaths) + " W:" + std::to_string(gameworld.Tanks[i]->win) + " " " ");
		ScoreD.setPosition(320, 4);
	}
	win.draw(ScoreA);
	win.draw(ScoreB);
	win.draw(ScoreC);
	win.draw(ScoreD);
}
void WinDisplay(int wintank, Font font, RenderWindow & win) {
	
	sf::Text WinText;
	
	WinText.setFont(font);
	if (wintank != 5 && gameworld.Tanks[wintank]->winconfirmed == false) {
		gameworld.Tanks[wintank]->win += 1;
		gameworld.Tanks[wintank]->winconfirmed = true;

	}

	switch (wintank) {
	case 0:
		WinText.setOutlineColor(sf::Color::Green);

		WinText.setFillColor(sf::Color::Green);
		WinText.setString("P1 wins!");
		break;
	case 1:
		WinText.setOutlineColor(blu);

		WinText.setFillColor(blu);
		WinText.setString("P2 wins!");
		break;
	case 2:
		WinText.setOutlineColor(sf::Color::Red);

		WinText.setFillColor(sf::Color::Red);
		WinText.setString("P3 wins!");
		break;
	case 3:
		WinText.setOutlineColor(sf::Color::Yellow);

		WinText.setFillColor(sf::Color::Yellow);
		WinText.setString("P4 wins!");
		break;
	case 5:
		WinText.setOutlineColor(sf::Color::White);

		WinText.setFillColor(sf::Color::White);
		WinText.setString("Everyone died!!!");
		break;
	}
	WinText.setPosition(250, 250);
	
	
	WinText.setCharacterSize(50);

	
	win.draw(WinText);
}
void DrawMenu(Font font, Font font2, RenderWindow & win) {
	//Menu1
	sf::Text TitleText;
	sf::Text StartText;
	TitleText.setOutlineColor(sf::Color::White);

	TitleText.setFillColor(sf::Color::White);
	StartText.setOutlineColor(sf::Color::White);
	StartText.setFillColor(sf::Color::White);
	StartText.setString("press START to play");
	TitleText.setString("Tank War!");
	TitleText.setFont(font);
	TitleText.setPosition(250, 250);
	StartText.setFont(font);
	StartText.setPosition(220, 350);


	TitleText.setCharacterSize(70);
	StartText.setCharacterSize(40);
	if (Menu1) {
		win.draw(TitleText);
		win.draw(StartText);

	}
	//Menu2
	sf::Text ScreenTitleText;
	sf::Text MapText;
	sf::Text AimText;
	sf::Text PressXText;
	ScreenTitleText.setOutlineColor(sf::Color::White);
	ScreenTitleText.setFillColor(sf::Color::White);
	ScreenTitleText.setString("Select a map!");
	ScreenTitleText.setFont(font);
	ScreenTitleText.setPosition(220, 40);
	ScreenTitleText.setCharacterSize(60);

	AimText.setOutlineColor(sf::Color::White);
	AimText.setFillColor(sf::Color::White);
	AimText.setString("Press X to change aim mode!");
	AimText.setFont(font);
	AimText.setPosition(160, 200);
	AimText.setCharacterSize(40);

	PressXText.setOutlineColor(sf::Color::White);
	PressXText.setFillColor(sf::Color::White);
	if(!autoaim)

	PressXText.setString("Manual");
	else
		PressXText.setString("Automatic");
	PressXText.setFont(font);
	PressXText.setPosition(160, 230);
	PressXText.setCharacterSize(30);



	MapText.setOutlineColor(sf::Color::White);
	MapText.setFillColor(sf::Color::White);

	MapText.setFont(font2);
	MapText.setPosition(220, 400);
	MapText.setCharacterSize(40);
	switch (mapnumber) {
	case 0:
		MapText.setString("<< Map 1: White Field >>");
		break;
	case 1:
		MapText.setString("<< Map 2: Magenta Cross >>");
		MapText.setOutlineColor(sf::Color::Magenta);
		MapText.setFillColor(sf::Color::Magenta);
		break;
	case 2:
		MapText.setString("<< Map 3: Red Fortress >>");
		MapText.setOutlineColor(sf::Color::Red);
		MapText.setFillColor(sf::Color::Red);
		break;
	case 3:
		MapText.setString("<< Map 4: Green Forest >>");
		MapText.setOutlineColor(sf::Color::Green);
		MapText.setFillColor(sf::Color::Green);
		break;
	case 4:
		MapText.setString("<< Map 5: Yellow Temple >>");
		MapText.setOutlineColor(sf::Color::Yellow);
		MapText.setFillColor(sf::Color::Yellow);
		break;
	case 5:
		MapText.setString("<< Map 6: Black Cave >>");
		MapText.setOutlineColor(blak);
		MapText.setFillColor(blak);
		break;
	case 6:
		MapText.setString("<< Map 7: Grey Mountain >>");
		MapText.setOutlineColor(gre);
		MapText.setFillColor(gre);
		break;
	case 7:
		MapText.setString("<< Map 8: Blue City >>");
		MapText.setOutlineColor(blu);
		MapText.setFillColor(blu);
		break;
	}

	if (Menu2) {
		win.draw(ScreenTitleText);
		win.draw(MapText);
		win.draw(PressXText);
		win.draw(AimText);

	}
}
void ResetGameMethod(int winner) {
	winframecount = 0;
	gameworld.ClearPro();

	angleA = 3.14 / 4;
	angleB = (5 * 3.14) / 4;
	angleC = (3 * 3.14) / 4;
	angleD = (7 * 3.14) / 4;
	for (int i = 0; i < gameworld.Tanks.size(); i++) {
		Tank& thistank = *gameworld.Tanks.at(i);
		thistank.dead = false;
		thistank.shape->setPosition(thistank.defaultpos);
		thistank.rect = thistank.shape->getGlobalBounds();
		SmokePro.clear();
		ExploPro.clear();
		thistank.winconfirmed = false;
	}

}
void ScoreReset(int playercount) {
	int i = 0;
	gameworld.Tanks[i]->kills = 0;
	gameworld.Tanks[i]->deaths = 0;
	gameworld.Tanks[i]->canshoot = true;
	gameworld.Tanks[i]->TimeSet = false;
	gameworld.Tanks[i]->Time = 0;
	gameworld.Tanks[i]->win = 0;

	if (playercount > 1) {
		i++;
		gameworld.Tanks[i]->kills = 0;
		gameworld.Tanks[i]->deaths = 0;
		gameworld.Tanks[i]->canshoot = true;
		gameworld.Tanks[i]->TimeSet = false;
		gameworld.Tanks[i]->Time = 0;
		gameworld.Tanks[i]->win = 0;
	}
	if (playercount > 2) {
		i++;
		gameworld.Tanks[i]->kills = 0;
		gameworld.Tanks[i]->deaths = 0;
		gameworld.Tanks[i]->canshoot = true;
		gameworld.Tanks[i]->TimeSet = false;
		gameworld.Tanks[i]->Time = 0;
		gameworld.Tanks[i]->win = 0;
	}
	if (playercount > 3) {
		i++;
		gameworld.Tanks[i]->kills = 0;
		gameworld.Tanks[i]->deaths = 0;
		gameworld.Tanks[i]->canshoot = true;
		gameworld.Tanks[i]->TimeSet = false;
		gameworld.Tanks[i]->Time = 0;
		gameworld.Tanks[i]->win = 0;
	}
}
//sound

int main()
{
	
	//sound
	Explosion.loadFromFile("Explosion.wav");
	Select.loadFromFile("Blip_Select.wav");
	Shoot.loadFromFile("Laser_Shoot.wav");
	Death.loadFromFile("Death.wav");
	Bounce.loadFromFile("Rebond.wav");
	select.setBuffer(Select);
	shoot.setBuffer(Shoot);
	explo.setBuffer(Explosion);
	desu.setBuffer(Death);
	boun.setBuffer(Bounce);
	BGMusic.loadFromFile("RainbowTanks.wav");
	BGM.setBuffer(BGMusic);
	BGM.setLoop(true);
	

	sf::ContextSettings settings;
	settings.antialiasingLevel = 2;

	sf::RenderWindow window(sf::VideoMode(800, 600), "Tank War!",sf::Style::Default, settings);
	sf::Clock clock;
	genclock = clock;
//	Clock.restart();
	sf::Time appStart = clock.getElapsedTime();
	sf::CircleShape shape(20.f, 2*3.141569*100);
	shape.setFillColor(sf::Color::Red);
	window.setVerticalSyncEnabled(true);
	sf::Time frameStart;
	float fps[4] = { 0.f, 0.f, 0.f, 0.f };
	int step = 0;
	sf::Font font;
	font.loadFromFile("ARCADECLASSIC.TTF");
	sf::Font font2;
	font2.loadFromFile("arial.ttf");
		
	sf::Text myFpsCounter;
	
	sf::Time PrevFrameStart = clock.getElapsedTime();
	int playercount=1;
	/*if (sf::Joystick::isConnected(0))
		playercount++;*/
	if (sf::Joystick::isConnected(1))
		playercount++;
	if (sf::Joystick::isConnected(2))
		playercount++;
	if (sf::Joystick::isConnected(3))
		playercount++;
	//printf("players: %d", playercount);

	//TEST
	// 
	// playercount = 4;

	for (int i = 0; i < playercount; i++) {
		InitSquare(i);
	//	printf("i = %d \n", i);
	}
	
	int every = 0;
	


	

	angleA = 3.14/4;
	angleB = (5*3.14)/4;
	angleC = (3*3.14)/4;
	angleD = (7 * 3.14) / 4;
	while (window.isOpen())
	{
		BGM.setVolume(70);
		if(BGM.getStatus() != sf::SoundSource::Playing)
			BGM.play();
		int i = 0;
		Tank& TankA = *gameworld.Tanks.at(i);
		Vector2f PosTankA = TankA.shape->getPosition();
	
		
		if (playercount > 1)
			i++;
		
		Tank& TankB = *gameworld.Tanks.at(i);
		Vector2f PosTankB = TankB.shape->getPosition();
	
		if (playercount > 2)
			i++;
		Tank& TankC = *gameworld.Tanks.at(i);
		Vector2f PosTankC = TankC.shape->getPosition();
		if (playercount > 3)
			i++;
		Tank& TankD = *gameworld.Tanks.at(i);
		Vector2f PosTankD = TankD.shape->getPosition();

		//printf("Tank1 pos: %f %f Tank 2 pos: %f %f \n", PosTankA.x, PosTankA.y, PosTankB.x, PosTankB.y);
		//printf("TankA owner: %d TankB owner: %d \n", TankA.owner, TankB.owner);
		frameStart = clock.getElapsedTime();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			/*if (event.type == sf::Event::MouseButtonReleased)
				if(event.mouseButton.button == sf::Mouse::Left)
					ShootCannon(GetMousePos(window), PosTank);*/
			int i = 0;
			if (Menu1) {
				if (sf::Joystick::isButtonPressed(0, 7)) {
					Menu2 = true;
					Menu1 = false;
					
					World::SoundMethod(0);
					
				
					continue;
				}
			}
			if (Menu2) {
				if (sf::Joystick::isButtonPressed(0, 0)) {
					Menu2 = false;
					Game = true;
					World::SoundMethod(0);
					MakeBorderWalls(mapnumber);
				}
				if (sf::Joystick::isButtonPressed(0, 2)&& canpress) {
					if (!autoaim)
						autoaim = true;
					else
						autoaim = false;
					World::SoundMethod(0);
					canpress = false;
					presstime = genclock.getElapsedTime().asMilliseconds();
					
					
				}
			}
			if (Game) {
				if (sf::Joystick::isButtonPressed(0, 5) && TankA.canshoot && !TankA.dead) {
					ShootCannon(AimingMethod(PosTankA, angleA), PosTankA, 0);
					TankA.SetTimeReset(clock);
				}
				if (sf::Joystick::isButtonPressed(0, 7)) {
					ScoreReset(playercount);
					ResetGameMethod(4);
					Menu2 = true;
					Game = false;
				}
				if (playercount > 1) {
					i++;
					if (sf::Joystick::isButtonPressed(i, 5) && TankB.canshoot && !TankB.dead) {
						ShootCannon(AimingMethod(PosTankB, angleB), PosTankB, i);
						TankB.SetTimeReset(clock);
					}
					if (sf::Joystick::isButtonPressed(i, 7)) {
						ScoreReset(playercount);
						ResetGameMethod(4);
						Menu2 = true;
						Game = false;
					}
				}
				if (playercount > 2) {
					i++;
					if (sf::Joystick::isButtonPressed(i, 5) && TankC.canshoot && !TankC.dead) {
						ShootCannon(AimingMethod(PosTankC, angleC), PosTankC, i);
						TankC.SetTimeReset(clock);
					}
					if (sf::Joystick::isButtonPressed(i, 7)) {
						ScoreReset(playercount);
						ResetGameMethod(4);
						Menu2 = true;
						Game = false;
					}
				}
				if (playercount > 3) {
					i++;
					if (sf::Joystick::isButtonPressed(i, 5) && TankD.canshoot && !TankD.dead) {
						ShootCannon(AimingMethod(PosTankD, angleD), PosTankD, i);
						TankD.SetTimeReset(clock);
					}
					if (sf::Joystick::isButtonPressed(i, 7)) {
						ScoreReset(playercount);
						ResetGameMethod(4);
						Menu2 = true;
						Game = false;
					}



				}
			}
			
			}
		
		
		//myFpsCounter.setPosition(8, 8);
		//myFpsCounter.setFillColor(sf::Color::Red);
		

		/*if (every == 0) {
			myFpsCounter.setString(std::string("FPS:") + std::to_string(fps[(step - 1) % 4]));
			every = 30;
		}*/


		window.clear();
	
		//if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			

		if (Game) {
			DrawAllWalls(window);
			DrawMovingSquare(window);
			ScoreMethod(playercount, font2, window);
			int size = gameworld.Tanks.size();
			i = 0;


			DrawAimingMethod(AimingMethod(PosTankA, angleA), angleA, window, i);

			if (playercount > 1) {
				i++;
				DrawAimingMethod(AimingMethod(PosTankB, angleB), angleB, window, i);
			}
			if (playercount > 2) {
				i++;
				DrawAimingMethod(AimingMethod(PosTankC, angleC), angleC, window, i);
			}
			if (playercount > 3) {
				i++;
				DrawAimingMethod(AimingMethod(PosTankD, angleD), angleD, window, i);
			}


		}
	
	
		//Dessine tous les projectiles
			
				int sizepro = gameworld.Projectiles.size();
				for (int i = 0; i < sizepro; i++) {
					//printf("%d\n", sizepro);
					Projectile& thispro = *gameworld.Projectiles.at(i);
					thispro.DrawProjectile(window);
				}
				for (ExplosionParticle * par : ExploPro) {
					par->DrawParticle(window);
				}

			//Menu
				DrawMenu(font, font2,window);
		

		//window.draw(myFpsCounter);
		sf::Time BeforeDisplay = clock.getElapsedTime();
		
		
		sf::Time frameEnd = clock.getElapsedTime();

		sf::Time frameDuration = frameEnd - frameStart;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			//printed = true;
			/*printf("%f  ", appStart.asSeconds());
			printf("%f  ", frameStart.asSeconds());
			printf("%f  ", BeforeDisplay.asSeconds());
			printf("%f  ", frameEnd.asSeconds());
			printf("%f  \n", frameDuration.asSeconds());
			printf("fps %f\n", 0.25f*(fps[0] + fps[1] + fps[2] + fps[3]));*/

		};
		if (Menu2) {
			if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) / 100 > 0 && sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) / 100 > 0.20f) {
				mapnumberF += 0.05f;
				if (mapnumberF >= mapcount)
					mapnumberF = 0;
			}
			if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) / 100 < 0 && sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) / 100 < -0.20f) {
				mapnumberF -= 0.05f;
				if (mapnumberF < 0)
					mapnumberF = mapcount - 0.05;
			}
			for (int i = 0; i < mapcount; i++) {
				if (mapnumberF >= i && mapnumberF < i + 1) {
					mapnumber = floor(mapnumberF);
					if(lastmap!=mapnumber)
						World::SoundMethod(0);
					lastmap = mapnumber;
				}
					
			
			}
		}
		if (Game) {
			i = 0;
			if (!TankA.dead) {


				int speed;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
					speed = TankA.speed * 2;
				else
					speed = TankA.speed;


				if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::X) / 100 > 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::X) / 100 > 0.20f) {
					PosTankA.x += speed;
				}
				if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::X) / 100 < 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::X) / 100 < -0.20f) {
					PosTankA.x -= speed;
				}
				if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::Y) / 100 > 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::Y) / 100 > 0.20f) {
					PosTankA.y += speed;
				}
				if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::Y) / 100 < 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::Y) / 100 < -0.20f) {
					PosTankA.y -= speed;
				}

				//printf("X axis: %f   Y axis: %f     \n", sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U), sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::V));
				if (!autoaim) {
					if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::R) / 100 > 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::R) / 100 > 0.20f) {
						angleA += 0.05;
					}
					if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::R) / 100 < 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::R) / 100 < -0.20f) {
						angleA -= 0.05;
					}
					if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) / 100 > 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) / 100 > 0.20f) {
						angleA += 0.05;
					}
					if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) / 100 < 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) / 100 < -0.20f) {
						angleA -= 0.05;
					}

					angleA = fmod(angleA, 2 * 3.1416);

				}
				else {
					if ((sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::V) / 100 > 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::V) / 100 > 0.20f
						|| sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::V) / 100 < 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::V) / 100 < -0.20f) ||
						(sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) / 100 > 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) / 100 > 0.20f
							|| sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) / 100 < 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) / 100 < 0.20f)) {
						if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) >= 0)
							angleA = atan((sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::V) / sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U)));
						if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) < 0)
							angleA = 3.1416 + atan((sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::V) / sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U)));
						int u = 2;
					}
				}

				//The TRIGO way
				
			/*	if (abs(TargetA - angleA) >= abs(((2*3.1416)+angleA)-TargetA) && abs(TargetA - angleA) > 0.10 &&abs(abs(TargetA - angleA)-abs(((2 * 3.1416) + angleA) - TargetA)) >=0.20)
					
					angleA += 0.09;
				
				 else if(abs(TargetA - angleA) > 0.10)
					angleA -= 0.09;
				
				/*if (angleA < 0)
					angleA = 2*3.1416 - 0.05;
				if (angleA > 2*3.1416)
					angleA = 0.05;*/
				//printf("TargetA %f  AngleA %f \n", TargetA, angleA); 
				// angleA -= 2 * 3.1416 * floor(angleA / 2 * 3.1416);

			}
			if (playercount > 1) {
				i++;
				if (!TankB.dead) {


					int speed;
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
						speed = TankB.speed * 2;
					else
						speed = TankB.speed;


					if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::X) / 100 > 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::X) / 100 > 0.20f) {
						PosTankB.x += speed;
					}
					if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::X) / 100 < 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::X) / 100 < -0.20f) {
						PosTankB.x -= speed;
					}
					if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::Y) / 100 > 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::Y) / 100 > 0.20f) {
						PosTankB.y += speed;
					}
					if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::Y) / 100 < 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::Y) / 100 < -0.20f) {
						PosTankB.y -= speed;
					}


				
					if (!autoaim) {
						if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::R) / 100 > 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::R) / 100 > 0.20f) {
							angleB += 0.05;
						}
						if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::R) / 100 < 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::R) / 100 < -0.20f) {
							angleB -= 0.05;
						}
						if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) / 100 > 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) / 100 > 0.20f) {
							angleB += 0.05;
						}
						if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) / 100 < 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) / 100 < -0.20f) {
							angleB -= 0.05;
						}

						angleB = fmod(angleB, 2 * 3.1416);
					}
					else {
						if ((sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::V) / 100 > 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::V) / 100 > 0.20f
							|| sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::V) / 100 < 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::V) / 100 < -0.20f) ||
							(sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) / 100 > 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) / 100 > 0.20f
								|| sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) / 100 < 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) / 100 < 0.20f)) {
							if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) >= 0)
								angleB = atan((sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::V) / sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U)));
							if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) < 0)
								angleB = 3.1416 + atan((sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::V) / sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U)));
							int u = 2;
						}
					}
				}
			}
			if (playercount > 2) {
				i++;
				if (!TankC.dead) {


					int speed;
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
						speed = TankC.speed * 2;
					else
						speed = TankC.speed;


					if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::X) / 100 > 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::X) / 100 > 0.20f) {
						PosTankC.x += speed;
					}
					if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::X) / 100 < 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::X) / 100 < -0.20f) {
						PosTankC.x -= speed;
					}
					if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::Y) / 100 > 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::Y) / 100 > 0.20f) {
						PosTankC.y += speed;
					}
					if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::Y) / 100 < 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::Y) / 100 < -0.20f) {
						PosTankC.y -= speed;
					}


					if (!autoaim) {

						if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::R) / 100 > 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::R) / 100 > 0.20f) {
							angleC += 0.05;
						}
						if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::R) / 100 < 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::R) / 100 < -0.20f) {
							angleC -= 0.05;
						}
						if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) / 100 > 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) / 100 > 0.20f) {
							angleC += 0.05;
						}
						if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) / 100 < 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) / 100 < -0.20f) {
							angleC -= 0.05;
						}

						angleC = fmod(angleC, 2 * 3.1416);
					}
					else {
						if ((sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::V) / 100 > 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::V) / 100 > 0.20f
							|| sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::V) / 100 < 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::V) / 100 < -0.20f) ||
							(sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) / 100 > 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) / 100 > 0.20f
								|| sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) / 100 < 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) / 100 < 0.20f)) {
							if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) >= 0)
								angleC = atan((sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::V) / sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U)));
							if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) < 0)
								angleC = 3.1416 + atan((sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::V) / sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U)));
							int u = 2;
						}
					}
				}
			}
			if (playercount > 3) {
				i++;
				if (!TankD.dead) {


					int speed;
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
						speed = TankD.speed * 2;
					else
						speed = TankD.speed;


					if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::X) / 100 > 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::X) / 100 > 0.20f) {
						PosTankD.x += speed;
					}
					if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::X) / 100 < 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::X) / 100 < -0.20f) {
						PosTankD.x -= speed;
					}
					if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::Y) / 100 > 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::Y) / 100 > 0.20f) {
						PosTankD.y += speed;
					}
					if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::Y) / 100 < 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::Y) / 100 < -0.20f) {
						PosTankD.y -= speed;
					}


					if (!autoaim) {

						if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::R) / 100 > 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::R) / 100 > 0.20f) {
							angleD += 0.05;
						}
						if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::R) / 100 < 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::R) / 100 < -0.20f) {
							angleD -= 0.05;
						}
						if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) / 100 > 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) / 100 > 0.20f) {
							angleD += 0.05;
						}
						if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) / 100 < 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) / 100 < -0.20f) {
							angleD -= 0.05;
						}

						angleD = fmod(angleD, 2 * 3.1416);
					}
					else {
						if ((sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::V) / 100 > 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::V) / 100 > 0.20f
							|| sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::V) / 100 < 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::V) / 100 < -0.20f) ||
							(sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) / 100 > 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) / 100 > 0.20f
								|| sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) / 100 < 0 && sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) / 100 < 0.20f)) {
							if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) >= 0)
								angleD = atan((sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::V) / sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U)));
							if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) < 0)
								angleD = 3.1416 + atan((sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::V) / sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U)));
							int u = 2;
						}
					}




				}
			}
			//TEST
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				PosTankA.x -= 2;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				PosTankA.x += 2;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				PosTankA.y -= 2;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				PosTankA.y += 2;
			i = 0;
			TankA.shape->setPosition(PosTankA);
			TankA.Cannon->setPosition(PosTankA);
			TankA.rect = TankA.shape->getGlobalBounds();
			if (playercount > 1) {
				i++;
				TankB.shape->setPosition(PosTankB);
				TankB.Cannon->setPosition(PosTankB);
				TankB.rect = TankB.shape->getGlobalBounds();
			}
			if (playercount > 2) {
				i++;
				TankC.shape->setPosition(PosTankC);
				TankC.Cannon->setPosition(PosTankC);
				TankC.rect = TankC.shape->getGlobalBounds();
			}
			if (playercount > 3) {
				i++;
				TankD.shape->setPosition(PosTankD);
				TankD.Cannon->setPosition(PosTankD);
				TankD.rect = TankD.shape->getGlobalBounds();
			}

	
			TankA.ResetShoot(clock);
			if (playercount > 1) {
				TankB.ResetShoot(clock);
			}
			if (playercount > 2) {
				TankC.ResetShoot(clock);
			}
			if (playercount > 3) {
				TankD.ResetShoot(clock);
			}
		}
		//Deplace les projectiles
		for (int i = 0; i < sizepro; i++) {
			//gameworld.Projectiles.at(i).PushProjectile(window);
			Projectile& thispro = *gameworld.Projectiles.at(i);
			thispro.PushProjectile();
		}
		for (ExplosionParticle * par : ExploPro) {
			par->PushParticle();
		}
		for (auto it = ExploPro.begin(); it != ExploPro.end();) {
			int index = std::distance(ExploPro.begin(), it);
			auto thispro = ExploPro.at(index);
			if (ExploPro.at(index)->ToDelete == true)
				it = ExploPro.erase(it);
			else
				it++;

		}
		
		//Collisions
		if (Game) {
			gameworld.IntersectProWall();
			gameworld.IntersectTankWall();
			gameworld.IntersectProTank();
			gameworld.IntersectTankTank();
		}
		

		sf::Time PrevFrameEnd = frameEnd;
		fps[step % 4] = 1.0f / (frameStart - PrevFrameStart).asSeconds();
		PrevFrameStart = frameStart;
		step++;
		//WINCONDITION
		if (Game) {
			int alivetank = 0;
			int wintank = 0;
			for (int i = 0; i < gameworld.Tanks.size(); i++) {
				Tank& thistank = *gameworld.Tanks.at(i);
				if (!thistank.dead) {
					alivetank++;
					wintank = i;
				}
				if (thistank.dead) {
					DrawDeadSmoke(window, i);
				}

			}
			if (alivetank == 0)
				wintank = 5;
			if (alivetank <= 1) {
				WinDisplay(wintank, font, window);
				winframecount++;
				if (winframecount > 120)
					ResetGameMethod(wintank);
			}
		}
		if(!canpress)
		pressmethod(presstime);
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
