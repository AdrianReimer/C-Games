#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreApplicationContext.h"
#include <iostream>

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


int make_left_forest(SceneManager* scnMgr) {
	int i;
	for (i = 0; i < FOREST_ENTITY_AMOUNT; i++) {
		static int pos_z = 0;
		int random_rotation = rand() % 360;
		int random_forest_ent = rand() % 6;
		if (random_forest_ent == 0) {
			Entity* rock1 = scnMgr->createEntity("rock1.mesh");
			rock1->setCastShadows(true);
			SceneNode* rock1_node = scnMgr->getRootSceneNode()->createChildSceneNode();
			rock1_node->setPosition(Vector3(LEFT_ROCK3_SPACE, FOREST_ENT_POS_Y, pos_z));
			rock1_node->setScale(ROCK_SIZE);
			rock1_node->pitch(Ogre::Degree(270.0));
			rock1_node->roll(Ogre::Degree(random_rotation));
			rock1_node->attachObject(rock1);
		}
		if (random_forest_ent == 1) {
			Entity* rock2 = scnMgr->createEntity("rock2.mesh");
			rock2->setCastShadows(true);
			SceneNode* rock2_node = scnMgr->getRootSceneNode()->createChildSceneNode();
			rock2_node->setPosition(Vector3(LEFT_ROCK3_SPACE, FOREST_ENT_POS_Y, pos_z));
			rock2_node->setScale(ROCK_SIZE);
			rock2_node->pitch(Ogre::Degree(270.0));
			rock2_node->roll(Ogre::Degree(random_rotation));
			rock2_node->attachObject(rock2);
		}
		if (random_forest_ent == 2) {
			Entity* rock3 = scnMgr->createEntity("rock3.mesh");
			rock3->setCastShadows(true);
			SceneNode* rock3_node = scnMgr->getRootSceneNode()->createChildSceneNode();
			rock3_node->setPosition(Vector3(LEFT_ROCK3_SPACE, FOREST_ENT_POS_Y, pos_z));
			rock3_node->setScale(ROCK_SIZE);
			rock3_node->pitch(Ogre::Degree(270.0));
			rock3_node->roll(Ogre::Degree(random_rotation));
			rock3_node->attachObject(rock3);
		}
		if (random_forest_ent == 3) {
			Entity* tree1 = scnMgr->createEntity("tree1.mesh");
			tree1->setCastShadows(true);
			SceneNode* tree1_node = scnMgr->getRootSceneNode()->createChildSceneNode();
			tree1_node->setPosition(Vector3(LEFT_TREE1_SPACE, FOREST_ENT_POS_Y, pos_z));
			tree1_node->setScale(TREE_SIZE);
			tree1_node->pitch(Ogre::Degree(270.0));
			tree1_node->roll(Ogre::Degree(random_rotation));
			tree1_node->attachObject(tree1);
		}
		if (random_forest_ent == 4) {
			Entity* tree2 = scnMgr->createEntity("tree2.mesh");
			tree2->setCastShadows(true);
			SceneNode* tree2_node = scnMgr->getRootSceneNode()->createChildSceneNode();
			tree2_node->setPosition(Vector3(LEFT_TREE2_SPACE, FOREST_ENT_POS_Y, pos_z));
			tree2_node->setScale(TREE_SIZE);
			tree2_node->pitch(Ogre::Degree(270.0));
			tree2_node->roll(Ogre::Degree(random_rotation));
			tree2_node->attachObject(tree2);
		}
		if (random_forest_ent == 5) {
			Entity* tree3 = scnMgr->createEntity("tree3.mesh");
			tree3->setCastShadows(true);
			SceneNode* tree3_node = scnMgr->getRootSceneNode()->createChildSceneNode();
			tree3_node->setPosition(Vector3(LEFT_TREE3_SPACE, FOREST_ENT_POS_Y, pos_z));
			tree3_node->setScale(TREE_SIZE);
			tree3_node->pitch(Ogre::Degree(270.0));
			tree3_node->roll(Ogre::Degree(random_rotation));
			tree3_node->attachObject(tree3);
		}
		pos_z -= FOREST_RANDOM_Z;
	}
	return 0;
}

int make_right_forest(SceneManager* scnMgr) {
	int i;
	for (i = 0; i < FOREST_ENTITY_AMOUNT; i++) {
		static int pos_z = 0;
		int random_rotation = rand() % 360;
		int random_forest_ent = rand() % 6;
		if (random_forest_ent == 0) {
			Entity* rock1 = scnMgr->createEntity("rock1.mesh");
			rock1->setCastShadows(true);
			SceneNode* rock1_node = scnMgr->getRootSceneNode()->createChildSceneNode();
			rock1_node->setPosition(Vector3(RIGHT_ROCK3_SPACE, FOREST_ENT_POS_Y, pos_z));
			rock1_node->setScale(ROCK_SIZE);
			rock1_node->pitch(Ogre::Degree(270.0));
			rock1_node->roll(Ogre::Degree(random_rotation));
			rock1_node->attachObject(rock1);
		}
		if (random_forest_ent == 1) {
			Entity* rock2 = scnMgr->createEntity("rock2.mesh");
			rock2->setCastShadows(true);
			SceneNode* rock2_node = scnMgr->getRootSceneNode()->createChildSceneNode();
			rock2_node->setPosition(Vector3(RIGHT_ROCK3_SPACE, FOREST_ENT_POS_Y, pos_z));
			rock2_node->setScale(ROCK_SIZE);
			rock2_node->pitch(Ogre::Degree(270.0));
			rock2_node->roll(Ogre::Degree(random_rotation));
			rock2_node->attachObject(rock2);
		}
		if (random_forest_ent == 2) {
			Entity* rock3 = scnMgr->createEntity("rock3.mesh");
			rock3->setCastShadows(true);
			SceneNode* rock3_node = scnMgr->getRootSceneNode()->createChildSceneNode();
			rock3_node->setPosition(Vector3(RIGHT_ROCK3_SPACE, FOREST_ENT_POS_Y, pos_z));
			rock3_node->setScale(ROCK_SIZE);
			rock3_node->pitch(Ogre::Degree(270.0));
			rock3_node->roll(Ogre::Degree(random_rotation));
			rock3_node->attachObject(rock3);
		}
		if (random_forest_ent == 3) {
			Entity* tree1 = scnMgr->createEntity("tree1.mesh");
			tree1->setCastShadows(true);
			SceneNode* tree1_node = scnMgr->getRootSceneNode()->createChildSceneNode();
			tree1_node->setPosition(Vector3(RIGHT_TREE1_SPACE, FOREST_ENT_POS_Y, pos_z));
			tree1_node->setScale(TREE_SIZE);
			tree1_node->pitch(Ogre::Degree(270.0));
			tree1_node->roll(Ogre::Degree(random_rotation));
			tree1_node->attachObject(tree1);
		}
		if (random_forest_ent == 4) {
			Entity* tree2 = scnMgr->createEntity("tree2.mesh");
			tree2->setCastShadows(true);
			SceneNode* tree2_node = scnMgr->getRootSceneNode()->createChildSceneNode();
			tree2_node->setPosition(Vector3(RIGHT_TREE2_SPACE, FOREST_ENT_POS_Y, pos_z));
			tree2_node->setScale(TREE_SIZE);
			tree2_node->pitch(Ogre::Degree(270.0));
			tree2_node->roll(Ogre::Degree(random_rotation));
			tree2_node->attachObject(tree2);
		}
		if (random_forest_ent == 5) {
			Entity* tree3 = scnMgr->createEntity("tree3.mesh");
			tree3->setCastShadows(true);
			SceneNode* tree3_node = scnMgr->getRootSceneNode()->createChildSceneNode();
			tree3_node->setPosition(Vector3(RIGHT_TREE3_SPACE, FOREST_ENT_POS_Y, pos_z));
			tree3_node->setScale(TREE_SIZE);
			tree3_node->pitch(Ogre::Degree(270.0));
			tree3_node->roll(Ogre::Degree(random_rotation));
			tree3_node->attachObject(tree3);
		}
		pos_z -= FOREST_RANDOM_Z;
	}
	return 0;
}