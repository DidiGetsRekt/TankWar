#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "pch.h"
//#include "App.cpp"
class Entity {
public:
	sf::RectangleShape * shape;
	sf::FloatRect  rect;
};
class Particle : public Entity {
public:
	Vector2f Dir;
	bool ToDelete = false;
	sf::CircleShape * shape;
	int Owner;
	float attspeed = 1;
	

	void PushParticle() {
		Vector2f pos = shape->getPosition();

		pos.x += attspeed * Dir.x;

		pos.y += attspeed * Dir.y;
		//	printf("%f %f \n", pos.x, pos.y);
		shape->setPosition(pos);
		rect = shape->getGlobalBounds();


	}
	void DrawParticle(sf::RenderWindow & win) {

		win.draw(*shape);
	}
	Vector2f GetPos() {
		Vector2f pos = shape->getPosition();
		return Vector2f(pos);
	}

};
class ExplosionParticle : public Particle {
public:

	sf::CircleShape * shape;
	int fadespeed = 2;
	ExplosionParticle(sf::CircleShape* sha, Vector2f di, float spd) {
		Dir = di;
		shape = sha;

		attspeed = spd;
		// = shape->getGlobalBounds();
	}
	void PushParticle() {
		Vector2f pos = shape->getPosition();

		pos.x += attspeed * Dir.x;

		pos.y += attspeed * Dir.y;
		if (shape->getOutlineColor().a - fadespeed >0)
			shape->setOutlineColor(Color(shape->getOutlineColor().r, shape->getOutlineColor().g, shape->getOutlineColor().b, shape->getOutlineColor().a - fadespeed));
		else
			ToDelete = true;
		//	printf("%f %f \n", pos.x, pos.y);
		shape->setPosition(pos);

	}
	void DrawParticle(sf::RenderWindow & win) {

		win.draw(*shape);
	}
	Vector2f GetPos() {
		Vector2f pos = shape->getPosition();
		return Vector2f(pos);
	}
};
class Wall : public Entity {
public:
	Wall(RectangleShape* sha, Vector2f pos) {
		shape = sha;
		shape->setPosition(pos);
		rect = shape->getGlobalBounds();

	}
	void NoRect() {
		rect.height = 0;
		rect.width = 0;
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
	RectangleShape * Cannon;
	int speed = 2;
	bool dead = false;
	bool canshoot = true;
	bool TimeSet = false;
	int Time = 0;
	int owner;
	Vector2f defaultpos;

	//score
	int deaths = 0;
	int kills = 0;
	int win = 0;
	bool winconfirmed = false;

	Tank(RectangleShape* sha, RectangleShape* Can, Vector2f pos, int own) {
		shape = sha;
		Cannon = Can;
		
		owner = own;
	//	printf("%f %f %d", pos.x, pos.y, owner);
		shape->setPosition(pos);
		Cannon->setPosition(pos);
		rect = shape->getGlobalBounds();
		defaultpos = pos;
		
	}
	void SetTimeReset(Clock clo) {
		TimeSet = true;
		Time = clo.getElapsedTime().asSeconds();
	}
	void ResetShoot(Clock clo) {
		int ThisTime = clo.getElapsedTime().asSeconds();
		if (TimeSet == true && ThisTime != Time + 1) {
			canshoot = false;
		}
		else if (TimeSet == true) {
			canshoot = true;
			TimeSet = false;
		}
	}
	void printstats() {
	//	printf("%d", owner);
	}

	void KillPlus() {
		kills++;
	}
	void DeathsPlus() {
		deaths++;
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
					if(thispro.hitonce == true /*&& j != Projectiles.at(i)->WallHit*/)
					Projectiles.at(i)->ToDelete = true;
					else if (!Projectiles.at(i)->hitonce) {
						SoundMethod(3);
						Projectiles.at(i)->hitonce = true;
						Projectiles.at(i)->WallHit = j;
						Projectiles.at(i)->CanKillOwner = true;
						FloatRect returned;
						thispro.rect.intersects(thiswal.rect, returned);
						Vector2f RectCenter = GetRectCenter(returned);
					//	printf("%f %f %f %f \n", Projectiles.at(i)->GetPos().x, RectCenter.x, Projectiles.at(i)->GetPos().y, RectCenter.y);
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
			if (Projectiles.at(index)->ToDelete == true) {
				MakeExplosion(Projectiles.at(index)->GetPos(), Projectiles.at(index)->Owner);
				it = Projectiles.erase(it);
			}
			
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
	void IntersectProTank() {
		int sizetank = Tanks.size();
		int sizepro = Projectiles.size();
		for (int i = 0; i < sizepro; i++) {
			for (int j = 0; j < sizetank; j++) {
				//printf("%d %d %d \n", sizepro,sizewal, j);
				Projectile& thispro = *Projectiles.at(i);
				Tank& thistank = *Tanks.at(j);
				if (thispro.rect.intersects(thistank.rect)) {
					if (thispro.CanKillOwner == true && thispro.Owner == j) {
						Projectiles.at(i)->ToDelete = true;
						if (!thistank.dead) {
							SoundMethod(4);
							thistank.DeathsPlus();
						}
							
						thistank.dead = true;
						
					}
						
					else if (thispro.Owner != j) {
						if (!thistank.dead) {
							Tanks.at(thispro.Owner)->KillPlus();
							thistank.DeathsPlus();
							SoundMethod(4);
						}
						
						Projectiles.at(i)->ToDelete = true;
						
						thistank.dead = true;

					}

				}

			}

		}
		//ERASE LE PROJECTILE CACA
		for (auto it = Projectiles.begin(); it != Projectiles.end();) {
			int index = std::distance(Projectiles.begin(), it);
			auto thispro = Projectiles.at(index);
			if (Projectiles.at(index)->ToDelete == true){
				MakeExplosion(Projectiles.at(index)->GetPos(), Projectiles.at(index)->Owner);
				it = Projectiles.erase(it);
			}
				
			else
				it++;

		}

	}
	void IntersectTankTank() {
		int sizetank = Tanks.size();
		for (int i = 0; i < sizetank; i++) {
			for (int j = 0; j < sizetank; j++) {

				Tank& thistank = *Tanks.at(i);
				Tank& othertank = *Tanks.at(j);
				if (thistank.rect.intersects(othertank.rect)) {
					if (i == j)
						continue;
					FloatRect returned;
					thistank.rect.intersects(othertank.rect, returned);
					Vector2f RectCenter = GetRectCenter(returned);
					if (RectCenter.x > thistank.shape->getPosition().x) {
						thistank.shape->setPosition(thistank.shape->getPosition().x - thistank.speed, thistank.shape->getPosition().y);
					}
					if (RectCenter.x < thistank.shape->getPosition().x) {
						thistank.shape->setPosition(thistank.shape->getPosition().x + thistank.speed, thistank.shape->getPosition().y);
					}
					if (RectCenter.y > thistank.shape->getPosition().y) {
						thistank.shape->setPosition(thistank.shape->getPosition().x, thistank.shape->getPosition().y - thistank.speed);
					}
					if (RectCenter.y < thistank.shape->getPosition().y) {
						thistank.shape->setPosition(thistank.shape->getPosition().x, thistank.shape->getPosition().y + thistank.speed);
					}
				}

			}

		}

	}

	void ClearPro() {
		int sizepro = Projectiles.size();
		for (auto it = Projectiles.begin(); it != Projectiles.end();) {
				it = Projectiles.erase(it);
			

		}
	}
	Vector2f GetRectCenter(FloatRect thisrect) {
		Vector2f result;
		result.x = thisrect.left + thisrect.width / 2;
		result.y = thisrect.top + thisrect.height / 2;
		return result;
	}
	
	void MakeExplosion(Vector2f pos, int owner);
	static void SoundMethod(int soundnum);
		
};




