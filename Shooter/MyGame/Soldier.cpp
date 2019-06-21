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
// Collision
#define CAMERA_COLLISION_OFFSET_VECTOR vector3df(0,20,0)


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

/**
 * Spawns a new Soldier.
 *
 * @param smgr Current SceneManager.
 * @param parent Possible Parent of the Soldier. Can be NULL.
 * @param position Position of the Soldier.
 * @return Pointer to the created Soldier.
 */
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

/**
 * Spawns the Soldier enemies. Enemies get a unique ID.
 *
 * @param smgr Current SceneManager.
 */
void Soldier::spawn_enemies(ISceneManager* smgr) {
	for (int i = 0; i < AMOUNT_OF_ENEMIES; i++) {
		enemies[i] = create_soldier(smgr, NULL, enemies_pos[i]);
		enemies[i]->setID(-2); // special enemy ID
		enemies[i]->setName("soldier" + i);
		enemies_state[i].state = IDLE_STATE;
		enemies_state[i].reaction_time = REACTION_TIME;
		enemies_state[i].health = HEALTH;
	}
}

/**
 * Updates the enemy Soldiers Ai behavior (StateMachines).
 *
 * @param camera Player Camera.
 * @param player_is_attacking true if player is attacking.
 * @param collMan Current CollisonManager.
 */
void Soldier::update_behavior(ICameraSceneNode* camera, bool player_is_attacking, ISceneCollisionManager* collMan) {
	line3d<f32> ray; // for collision detection
	ray.start = camera->getPosition() + CAMERA_COLLISION_OFFSET_VECTOR;
	ray.end = camera->getTarget();
	core::vector3df intersection;
	core::triangle3df hitTriangle;
	for (int i = 0; i < AMOUNT_OF_ENEMIES; i++) {
		if ((camera->getAbsolutePosition().getDistanceFrom(enemies[i]->getAbsolutePosition())) < AGGRO_RANGE) {
			enemies_state[i].state = ATTACK_STATE;
			enemies[i]->setRotation(vector3df(0, camera->getRotation().Y, 0)); // Look to the Player
			if (player_is_attacking && collMan->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, -2, 0) == enemies[i]){
				enemies_state[i].health -= ATTACK_DAMAGE;
				if (enemies_state[i].health <= 0) {
					// Enemy Died
					enemies[i]->setPosition(DEATH_POSITION);
					enemies_state[i].state = DEAD_STATE;
					soldier_ai_alive--;
				}
			}
		}
		else {
			// Player out of Range. Back to IDLE State.
			enemies[i]->setFrameLoop(IDLE_ANIMATION_FRAME_LOOP);
			enemies_state[i].state = IDLE_STATE;
			enemies_state[i].reaction_time = REACTION_TIME;
		}
	}
}

/**
 * Checks the Ai States of the enemy Soldiers. Performes tasks on what State the enemy is in.
 *
 * @param player_health Current Health of the Player.
 */
void Soldier::check_ai(int* player_health) {
	for (int i = 0; i < AMOUNT_OF_ENEMIES; i++) {
		if (enemies_state[i].state == ATTACK_STATE) {
			enemies_state[i].reaction_time--;
			if (enemies_state[i].reaction_time <= 0) {
				// Enemy shoots
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
