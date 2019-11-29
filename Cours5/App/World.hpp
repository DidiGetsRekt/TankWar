#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "pch.h"
class Entity {
public:
	sf::RectangleShape * shape;
	sf::FloatRect  rect;
};

class Wall : public Entity {
public:
	Wall(RectangleShape* sha, Vector2f pos) {
		shape = sha;
		shape->setPosition(pos);
		rect = shape->getGlobalBounds();

	}
};

class Projectile : public Entity {
public:
	Vector2f Dir;
	int WallHit;
	bool hitonce = false;
	bool ToDelete = false;
	bool CanKillOwner = false;
	int Owner;
	float attspeed =1;
	Projectile(RectangleShape* sha, Vector2f di, float spd) {
		Dir = di;
		shape = sha;
		
		attspeed = spd;
		rect = shape->getGlobalBounds();
	}

	void PushProjectile() {
		Vector2f pos = shape->getPosition();

		pos.x += attspeed * Dir.x;
		
		pos.y += attspeed * Dir.y;
	//	printf("%f %f \n", pos.x, pos.y);
		shape->setPosition(pos);
		rect = shape->getGlobalBounds();
		
		
	}
	void DrawProjectile(sf::RenderWindow & win) {
		
		win.draw(*shape);
	}
	Vector2f GetPos() {
		Vector2f pos = shape->getPosition();
		return Vector2f(pos);
	}
	
};
class Tank : public Entity {
public:
	int speed = 2;
	Tank(RectangleShape* sha, Vector2f pos) {
		shape = sha;
		rect = shape->getGlobalBounds();
		shape->setPosition(pos);
	}

};

class World {
	public:
	std::vector<Tank*> Tanks;
	
	std::vector<Wall*> Walls;
	std::vector<Projectile*>  Projectiles;

	void IntersectProWall() {
		int sizewal = Walls.size();
		int sizepro = Projectiles.size();
		for (int i = 0; i < sizepro; i++) {
			for (int j = 0; j < sizewal; j++) {
				//printf("%d %d %d \n", sizepro,sizewal, j);
				Projectile& thispro = *Projectiles.at(i);
				Wall& thiswal = *Walls.at(j);
				if (thispro.rect.intersects(thiswal.rect)) {
					if(thispro.hitonce == true && j != Projectiles.at(i)->WallHit)
					Projectiles.at(i)->ToDelete = true;
					else if (!Projectiles.at(i)->hitonce) {
						Projectiles.at(i)->hitonce = true;
						Projectiles.at(i)->WallHit = j;
						Projectiles.at(i)->CanKillOwner = true;
						FloatRect returned;
						thispro.rect.intersects(thiswal.rect, returned);
						Vector2f RectCenter = GetRectCenter(returned);
						printf("%f %f %f %f \n", Projectiles.at(i)->GetPos().x, RectCenter.x, Projectiles.at(i)->GetPos().y, RectCenter.y);
						if (RectCenter.x> Projectiles.at(i)->GetPos().x || RectCenter.x < Projectiles.at(i)->GetPos().x) {
							
							Projectiles.at(i)->Dir.x= -Projectiles.at(i)->Dir.x;
							
						}
						 if (RectCenter.y > Projectiles.at(i)->GetPos().y || RectCenter.y < Projectiles.at(i)->GetPos().y) {
							Projectiles.at(i)->Dir.y = -Projectiles.at(i)->Dir.y;
							
						}
					   
							
					}
					
				}
			
			}
			
		}
		//ERASE LE PROJECTILE CACA
		for (auto it = Projectiles.begin(); it != Projectiles.end();) {
			int index = std::distance(Projectiles.begin(), it);
			auto thispro = Projectiles.at(index);
			if (Projectiles.at(index)->ToDelete == true)
				it = Projectiles.erase(it);
			else
				it++;
			
		}

	}

	void IntersectTankWall() {
		int sizewal = Walls.size();
		int sizetank = Tanks.size();
		for (int i = 0; i < sizetank; i++) {
			for (int j = 0; j < sizewal; j++) {
				
				Tank& thistank = *Tanks.at(i);
				Wall& thiswal = *Walls.at(j);
				if (thistank.rect.intersects(thiswal.rect)) {
						
						FloatRect returned;
						thistank.rect.intersects(thiswal.rect, returned);
						Vector2f RectCenter = GetRectCenter(returned);
						if (RectCenter.x > thistank.shape->getPosition().x) {
							thistank.shape->setPosition(thistank.shape->getPosition().x - thistank.speed, thistank.shape->getPosition().y);
						}
						if (RectCenter.x < thistank.shape->getPosition().x) {
							thistank.shape->setPosition(thistank.shape->getPosition().x + thistank.speed, thistank.shape->getPosition().y);
						}
						if (RectCenter.y > thistank.shape->getPosition().y) {
							thistank.shape->setPosition(thistank.shape->getPosition().x , thistank.shape->getPosition().y - thistank.speed);
						}
						if (RectCenter.y < thistank.shape->getPosition().y) {
							thistank.shape->setPosition(thistank.shape->getPosition().x, thistank.shape->getPosition().y + thistank.speed);
						}
				}

				}

			}

		}
	Vector2f GetRectCenter(FloatRect thisrect) {
		Vector2f result;
		result.x = thisrect.left + thisrect.width / 2;
		result.y = thisrect.top + thisrect.height / 2;
		return result;
	}
	
	
	
};




