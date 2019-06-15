#include <irrlicht.h>
#include "driverChoice.h"
#include <stdlib.h>
#include <string> 
#include "Soldier.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

Soldier::Soldier(IVideoDriver* driver) {
	material_body.setTexture(0, driver->getTexture("../../media/models/dynamic/demo_soldier_512.tga"));
	material_body.Lighting = true;
	material_body.NormalizeNormals = true;
	material_weapon.setTexture(0, driver->getTexture("../../media/models/dynamic/demo_weapon.tga"));
	material_weapon.Lighting = true;
	material_weapon.NormalizeNormals = true;
}

IAnimatedMeshSceneNode* Soldier::create_soldier(ISceneManager* smgr, ISceneNode* parent, vector3df position) {
	IAnimatedMeshSceneNode* soldier = smgr->addAnimatedMeshSceneNode(smgr->getMesh("../../media/models/dynamic/soldier.md3"), parent, -1, vector3df(-3, -90, -18));
	soldier->setPosition(position);
	soldier->setRotation(vector3df(0, 180, 0));
	soldier->getMaterial(0) = material_body;
	soldier->getMaterial(1) = material_weapon;
	soldier->setAnimationSpeed(50);
	soldier->setFrameLoop(30, 130);
	return soldier;
}

void Soldier::spawn_enemies(ISceneManager* smgr) {
	for (int i = 0; i < AMOUNT_OF_ENEMIES; i++) {
		create_soldier(smgr, NULL, enemies_pos[i]);
	}
}