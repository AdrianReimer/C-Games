#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreApplicationContext.h"
#include <iostream>


#define ROCK1_MESH_NAME "rock1.mesh"
#define ROCK2_MESH_NAME "rock2.mesh"
#define ROCK3_MESH_NAME "rock3.mesh"
#define TREE1_MESH_NAME "tree1.mesh"
#define TREE2_MESH_NAME "tree2.mesh"
#define TREE3_MESH_NAME "tree3.mesh"
#define RANDOM_ROTATION (rand() % 360)
#define RANDOM_FOREST_ENT (rand() % 6)
#define LEFT_ROCK1_SPACE (rand() % 170 - 300)
#define LEFT_ROCK2_SPACE (rand() % 200 - 300)
#define LEFT_ROCK3_SPACE (rand() % 220 - 300)
#define LEFT_TREE1_SPACE (rand() % 170 - 320)
#define LEFT_TREE2_SPACE (rand() % 200 - 300)
#define LEFT_TREE3_SPACE (rand() % 220 - 400)
#define RIGHT_ROCK1_SPACE (-(rand() % 170) + 300)
#define RIGHT_ROCK2_SPACE (-(rand() % 200) + 300)
#define RIGHT_ROCK3_SPACE (-(rand() % 220) + 280)
#define RIGHT_TREE1_SPACE (-(rand() % 170) + 250)
#define RIGHT_TREE2_SPACE (-(rand() % 200) + 300)
#define RIGHT_TREE3_SPACE (-(rand() % 220) + 400)
#define FOREST_ENTITY_AMOUNT 800
#define FOREST_ENT_POS_Y 20
#define ROCK_SIZE Vector3(230, 230, 230)
#define TREE_SIZE Vector3(300, 300, 300)
#define FOREST_RANDOM_Z (rand() % 40 + 35)

using namespace Ogre;
using namespace OgreBites;

/**
 * Initializes the Forest entity by setting Pitch, Roll etc.
 */
static void init_forest_entity(SceneManager* scnMgr, Entity* ent, SceneNode* ent_node, int random_rotation) {
	ent->setCastShadows(true);
	ent_node->pitch(Ogre::Degree(270.0));
	ent_node->roll(Ogre::Degree(random_rotation));
	ent_node->attachObject(ent);
}

/**
* Creates the Left Forest by filling it with random Forest entities.
* @return 0 if no error occure.
*/
int make_left_forest(SceneManager* scnMgr) {
	int i;
	for (i = 0; i < FOREST_ENTITY_AMOUNT; i++) {
		static int pos_z;
		int random_rotation = RANDOM_ROTATION;
		int random_forest_ent = RANDOM_FOREST_ENT;
		Entity* ent;
		SceneNode* ent_node = scnMgr->getRootSceneNode()->createChildSceneNode();
		if (random_forest_ent == 0) {
			ent = scnMgr->createEntity(ROCK1_MESH_NAME);
			ent_node->setPosition(Vector3(LEFT_ROCK1_SPACE, FOREST_ENT_POS_Y, pos_z));
			ent_node->setScale(ROCK_SIZE);
			init_forest_entity(scnMgr, ent, ent_node, random_rotation);
		} else if (random_forest_ent == 1) {
			ent = scnMgr->createEntity(ROCK2_MESH_NAME);
			ent_node->setPosition(Vector3(LEFT_ROCK2_SPACE, FOREST_ENT_POS_Y, pos_z));
			ent_node->setScale(ROCK_SIZE);
			init_forest_entity(scnMgr, ent, ent_node, random_rotation);
		} else if (random_forest_ent == 2) {
			ent = scnMgr->createEntity(ROCK3_MESH_NAME);
			ent_node->setPosition(Vector3(LEFT_ROCK3_SPACE, FOREST_ENT_POS_Y, pos_z));
			ent_node->setScale(ROCK_SIZE);
			init_forest_entity(scnMgr, ent, ent_node, random_rotation);
		} else if (random_forest_ent == 3) {
			ent = scnMgr->createEntity(TREE1_MESH_NAME);
			ent_node->setPosition(Vector3(LEFT_TREE1_SPACE, FOREST_ENT_POS_Y, pos_z));
			ent_node->setScale(TREE_SIZE);
			init_forest_entity(scnMgr, ent, ent_node, random_rotation);
		} else if (random_forest_ent == 4) {
			ent = scnMgr->createEntity(TREE2_MESH_NAME);
			ent_node->setPosition(Vector3(LEFT_TREE2_SPACE, FOREST_ENT_POS_Y, pos_z));
			ent_node->setScale(TREE_SIZE);
			init_forest_entity(scnMgr, ent, ent_node, random_rotation);
		} else if (random_forest_ent == 5) {
			ent = scnMgr->createEntity(TREE3_MESH_NAME);
			ent_node->setPosition(Vector3(LEFT_TREE3_SPACE, FOREST_ENT_POS_Y, pos_z));
			ent_node->setScale(TREE_SIZE);
			init_forest_entity(scnMgr, ent, ent_node, random_rotation);
		}
		pos_z -= FOREST_RANDOM_Z;
	}
	return 0;
}

/**
* Creates the Right Forest by filling it with random Forest entities.
* @return 0 if no error occure.
*/
int make_right_forest(SceneManager* scnMgr) {
	int i;
	for (i = 0; i < FOREST_ENTITY_AMOUNT; i++) {
		static int pos_z;
		int random_rotation = RANDOM_ROTATION;
		int random_forest_ent = RANDOM_FOREST_ENT;
		Entity* ent;
		SceneNode* ent_node = scnMgr->getRootSceneNode()->createChildSceneNode();
		if (random_forest_ent == 0) {
			ent = scnMgr->createEntity(ROCK1_MESH_NAME);
			ent_node->setPosition(Vector3(RIGHT_ROCK1_SPACE, FOREST_ENT_POS_Y, pos_z));
			ent_node->setScale(ROCK_SIZE);
			init_forest_entity(scnMgr, ent, ent_node, random_rotation);
		} else if (random_forest_ent == 1) {
			ent = scnMgr->createEntity(ROCK2_MESH_NAME);
			ent_node->setPosition(Vector3(RIGHT_ROCK2_SPACE, FOREST_ENT_POS_Y, pos_z));
			ent_node->setScale(ROCK_SIZE);
			init_forest_entity(scnMgr, ent, ent_node, random_rotation);
		} else if (random_forest_ent == 2) {
			ent = scnMgr->createEntity(ROCK3_MESH_NAME);
			ent_node->setPosition(Vector3(RIGHT_ROCK3_SPACE, FOREST_ENT_POS_Y, pos_z));
			ent_node->setScale(ROCK_SIZE);
			init_forest_entity(scnMgr, ent, ent_node, random_rotation);
		} else if (random_forest_ent == 3) {
			ent = scnMgr->createEntity(TREE1_MESH_NAME);
			ent_node->setPosition(Vector3(RIGHT_TREE1_SPACE, FOREST_ENT_POS_Y, pos_z));
			ent_node->setScale(TREE_SIZE);
			init_forest_entity(scnMgr, ent, ent_node, random_rotation);
		} else if (random_forest_ent == 4) {
			ent = scnMgr->createEntity(TREE2_MESH_NAME);
			ent_node->setPosition(Vector3(RIGHT_TREE2_SPACE, FOREST_ENT_POS_Y, pos_z));
			ent_node->setScale(TREE_SIZE);
			init_forest_entity(scnMgr, ent, ent_node, random_rotation);
		} else if (random_forest_ent == 5) {
			ent = scnMgr->createEntity(TREE3_MESH_NAME);
			ent_node->setPosition(Vector3(RIGHT_TREE3_SPACE, FOREST_ENT_POS_Y, pos_z));
			ent_node->setScale(TREE_SIZE);
			init_forest_entity(scnMgr, ent, ent_node, random_rotation);
		}
		pos_z -= FOREST_RANDOM_Z;
	}
	return 0;
}
