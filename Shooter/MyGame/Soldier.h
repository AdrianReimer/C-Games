#ifndef SOLDIER_H
#define SOLDIER_H

#include <irrlicht.h>
#include "driverChoice.h"
#include <stdlib.h>
#include <string> 

#define AMOUNT_OF_ENEMIES 9 // If change --> add more spawn positions
#define REACTION_TIME (rand() % 200 + 150) 

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;



class Soldier {
private:
	enum ai_states {
		IDLE_STATE,
		ATTACK_STATE,
		DEAD_STATE
	};

	typedef struct enemy {
		enum ai_states state;
		int reaction_time;
		int health;
	};

	int soldier_ai_alive = AMOUNT_OF_ENEMIES;
	enemy enemies_state[AMOUNT_OF_ENEMIES];
	IAnimatedMeshSceneNode* enemies[AMOUNT_OF_ENEMIES];
	const vector3df enemies_pos[AMOUNT_OF_ENEMIES] = { vector3df(868, 928, 475), vector3df(824, 861, -568), vector3df(947, 1120, -1001),
													   vector3df(35, 927, -956), vector3df(-579, 860, -941), vector3df(-757, 1185, 5),
													   vector3df(-104, 1058, 654), vector3df(107, 1182, -780), vector3df(-465, 860, 933)};
	SMaterial material_body;
	SMaterial material_weapon;
public:
	Soldier(IVideoDriver* driver);
	IAnimatedMeshSceneNode * create_soldier(ISceneManager* smgr, ISceneNode* parent, vector3df position);
	void spawn_enemies(ISceneManager* smgr);
	void update_behavior(ICameraSceneNode* camera, bool player_is_attacking, ISceneCollisionManager* collMan);
	void check_ai(int* player_health);
	int get_soldiers_alive();
};
#endif
