#include <irrlicht.h>
#include <stdlib.h>
#include "Soldier.h"
#include "EventReceiver.h"


#define PLAYER_HIT_RANGE 200
#define AGGRO_RANGE 400
#define DEATH_POSITION vector3df(0, -10000, 0)
// Textures
#define SOLDIER_BODY_TEXTURE_PATH "media/models/dynamic/demo_soldier_512.tga"
#define SOLDIER_WEAPON_TEXTURE_PATH "media/models/dynamic/demo_weapon.tga"
// Model
#define SOLDIER_MODEL_PATH "media/models/dynamic/soldier.md3"
// Damage
#define ATTACK_DAMAGE (rand() % 10 + 15)
// Health
#define HEALTH 1000


using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

Soldier::Soldier(IVideoDriver* driver) {
	material_body.setTexture(0, driver->getTexture(SOLDIER_BODY_TEXTURE_PATH));
	material_body.Lighting = true;
	material_body.NormalizeNormals = true;
	material_weapon.setTexture(0, driver->getTexture(SOLDIER_WEAPON_TEXTURE_PATH));
	material_weapon.Lighting = true;
	material_weapon.NormalizeNormals = true;
}

IAnimatedMeshSceneNode* Soldier::create_soldier(ISceneManager* smgr, ISceneNode* parent, vector3df position) {
	IAnimatedMeshSceneNode* soldier = smgr->addAnimatedMeshSceneNode(smgr->getMesh(SOLDIER_MODEL_PATH), parent, -1, vector3df(-3, -90, -18));
	soldier->setPosition(position);
	soldier->setRotation(vector3df(0, 180, 0));
	soldier->getMaterial(0) = material_body;
	soldier->getMaterial(1) = material_weapon;
	soldier->setAnimationSpeed(IDLE_ANIMATION_SPEED);
	soldier->setFrameLoop(IDLE_ANIMATION_FRAME_LOOP);
	return soldier;
}

void Soldier::spawn_enemies(ISceneManager* smgr) {
	for (int i = 0; i < AMOUNT_OF_ENEMIES; i++) {
		enemies[i] = create_soldier(smgr, NULL, enemies_pos[i]);
		enemies_state[i].state = IDLE_STATE;
		enemies_state[i].reaction_time = REACTION_TIME;
		enemies_state[i].health = HEALTH;
	}
}

void Soldier::update_behavior(ICameraSceneNode* camera, bool player_is_attacking) {
	line3d<f32> ray;
	ray.start = camera->getPosition();
	ray.end = ray.start + (camera->getTarget() - ray.start).normalize() * AGGRO_RANGE;
	for (int i = 0; i < AMOUNT_OF_ENEMIES; i++) {
		if ((camera->getAbsolutePosition().getDistanceFrom(enemies[i]->getAbsolutePosition())) < AGGRO_RANGE) {
			enemies_state[i].state = ATTACK_STATE;
			enemies[i]->setRotation(vector3df(0, camera->getRotation().Y, 0));
			if (player_is_attacking && ray.end.getDistanceFrom(enemies[i]->getAbsolutePosition()) < PLAYER_HIT_RANGE){
				enemies_state[i].health -= ATTACK_DAMAGE;
				if (enemies_state[i].health <= 0) {
					enemies[i]->setPosition(DEATH_POSITION);
					enemies_state[i].state = DEAD_STATE;
					soldier_ai_alive--;
				}
			}
		}
		else {
			enemies[i]->setFrameLoop(IDLE_ANIMATION_FRAME_LOOP);
			enemies_state[i].state = IDLE_STATE;
			enemies_state[i].reaction_time = REACTION_TIME;
		}
	}
}

void Soldier::check_ai(int* player_health) {
	for (int i = 0; i < AMOUNT_OF_ENEMIES; i++) {
		if (enemies_state[i].state == ATTACK_STATE) {
			enemies_state[i].reaction_time--;
			if (enemies_state[i].reaction_time <= 0) {
				*player_health -= ATTACK_DAMAGE;
				enemies[i]->setFrameLoop(SHOOT_ANIMATION_FRAME_LOOP);
				enemies_state[i].reaction_time = REACTION_TIME;
			}
		}
	}
}

int Soldier::get_soldiers_alive() {
	return soldier_ai_alive;
}
