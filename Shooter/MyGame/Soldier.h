#ifndef SOLDIER_H
#define SOLDIER_H

#include <irrlicht.h>
#include "driverChoice.h"
#include <stdlib.h>
#include <string> 

#define AMOUNT_OF_ENEMIES 9

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Soldier {
private:
	IAnimatedMeshSceneNode* enemies[AMOUNT_OF_ENEMIES];
	const vector3df enemies_pos[AMOUNT_OF_ENEMIES] = { vector3df(868, 925, 475), vector3df(824, 858, -568), vector3df(947, 1117, -1001),
													   vector3df(35, 924, -956), vector3df(-579, 857, -941), vector3df(-757, 1182, 5),
													   vector3df(-104, 1055, 654), vector3df(107, 1179, -780), vector3df(-465, 857, 933)};
	SMaterial material_body;
	SMaterial material_weapon;
public:
	Soldier(IVideoDriver* driver);
	IAnimatedMeshSceneNode * create_soldier(ISceneManager* smgr, ISceneNode* parent, vector3df position);
	void spawn_enemies(ISceneManager* smgr);
};

#endif
