#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreApplicationContext.h"
#include <iostream>
#include "Lane.h"

#define LEFT_CAR1_SPACE (rand() % 200 + 350)
#define LEFT_CAR2_SPACE (rand() % 250 + 400)
#define LEFT_CAR3_SPACE (rand() % 350 + 500)
#define LEFT_CAR4_SPACE (rand() % 450 + 600)
#define LEFT_CAR5_SPACE (rand() % 550 + 400)
#define LEFT_BUS1_SPACE (rand() % 650 + 650)
#define RIGHT_CAR1_SPACE (rand() % 400 + 550)
#define RIGHT_CAR2_SPACE (rand() % 450 + 600)
#define RIGHT_CAR3_SPACE (rand() % 550 + 700)
#define RIGHT_CAR4_SPACE (rand() % 650 + 800)
#define RIGHT_CAR5_SPACE (rand() % 750 + 600)
#define RIGHT_BUS1_SPACE (rand() % 850 + 850)
#define RIGHT_LANE_START_POS -1000
#define LEFT_LANE_START_POS -600
#define CAR_SCALE Vector3(5, 5, 5)


struct Lane left_lane_array[LEFT_LANE_VEHICLE_AMOUNT];
struct Lane right_lane_array[RIGHT_LANE_VEHICLE_AMOUNT];

using namespace Ogre;
using namespace OgreBites;

int make_left_lane(SceneManager* scnMgr) {
	int z = LEFT_LANE_START_POS;
	int left_car_random_space;
	int i;
	for (i = 0; i < LEFT_LANE_VEHICLE_AMOUNT; i++) {
		Lane lane;
		int random_vehicle = rand() % 6;
		if (random_vehicle == 0) {
			lane.vehicle = scnMgr->createEntity("car1.mesh");
			lane.vehicle_node = scnMgr->getRootSceneNode()->createChildSceneNode();
			lane.vehicle_node->setPosition(Vector3(LEFT_LANE_POS, CAR_POS_Y, z));
			lane.pos_z = z;
			lane.vehicle_node->setScale(CAR_SCALE);
			lane.vehicle_node->attachObject(lane.vehicle);
			z -= LEFT_CAR1_SPACE;
			left_lane_array[i] = lane;
		}
		else if (random_vehicle == 1) {
			lane.vehicle = scnMgr->createEntity("car2.mesh");
			lane.vehicle_node = scnMgr->getRootSceneNode()->createChildSceneNode();
			lane.vehicle_node->setPosition(Vector3(LEFT_LANE_POS, CAR_POS_Y, z));
			lane.pos_z = z;
			lane.vehicle_node->setScale(CAR_SCALE);
			lane.vehicle_node->attachObject(lane.vehicle);
			z -= LEFT_CAR2_SPACE;
			left_lane_array[i] = lane;
		}
		else if (random_vehicle == 2) {
			lane.vehicle = scnMgr->createEntity("car3.mesh");
			lane.vehicle_node = scnMgr->getRootSceneNode()->createChildSceneNode();
			lane.pos_z = z;
			lane.vehicle_node->setPosition(Vector3(LEFT_LANE_POS, CAR_POS_Y, z));
			lane.vehicle_node->setScale(CAR_SCALE);
			lane.vehicle_node->attachObject(lane.vehicle);
			z -= LEFT_CAR3_SPACE;
			left_lane_array[i] = lane;
		}
		else if (random_vehicle == 3) {
			lane.vehicle = scnMgr->createEntity("car4.mesh");
			lane.vehicle_node = scnMgr->getRootSceneNode()->createChildSceneNode();
			lane.pos_z = z;
			lane.vehicle_node->setPosition(Vector3(LEFT_LANE_POS, CAR_POS_Y, z));
			lane.vehicle_node->setScale(CAR_SCALE);
			lane.vehicle_node->attachObject(lane.vehicle);
			z -= LEFT_CAR4_SPACE;
			left_lane_array[i] = lane;
		}
		else if (random_vehicle == 4) {
			lane.vehicle = scnMgr->createEntity("car5.mesh");
			lane.vehicle_node = scnMgr->getRootSceneNode()->createChildSceneNode();
			lane.vehicle_node->setPosition(Vector3(LEFT_LANE_POS, CAR_POS_Y, z));
			lane.pos_z = z;
			lane.vehicle_node->setScale(CAR_SCALE);
			lane.vehicle_node->attachObject(lane.vehicle);
			z -= LEFT_CAR5_SPACE;
			left_lane_array[i] = lane;
		}
		else if (random_vehicle == 5) {
			lane.vehicle = scnMgr->createEntity("bus1.mesh");
			lane.vehicle_node = scnMgr->getRootSceneNode()->createChildSceneNode();
			lane.vehicle_node->setPosition(Vector3(LEFT_LANE_POS, CAR_POS_Y, z));
			lane.pos_z = z;
			lane.vehicle_node->setScale(CAR_SCALE);
			lane.vehicle_node->attachObject(lane.vehicle);
			z -= LEFT_BUS1_SPACE;
			left_lane_array[i] = lane;
		}
	}
	return 0;
}

int make_right_lane(SceneManager* scnMgr) {
	int z = RIGHT_LANE_START_POS;
	int car_random_space;
	int i;
	for (i = 0; i < RIGHT_LANE_VEHICLE_AMOUNT; i++) {
		Lane lane;
		int random_vehicle = rand() % 6;
		if (random_vehicle == 0) {
			lane.vehicle = scnMgr->createEntity("car1.mesh");
			lane.vehicle_node = scnMgr->getRootSceneNode()->createChildSceneNode();
			lane.vehicle_node->setPosition(Vector3(RIGHT_LANE_POS, CAR_POS_Y, z));
			lane.pos_z = z;
			lane.vehicle_node->setScale(CAR_SCALE);
			lane.vehicle_node->yaw(Ogre::Degree(180.0));
			lane.vehicle_node->attachObject(lane.vehicle);
			z -= RIGHT_CAR1_SPACE;
			right_lane_array[i] = lane;
		}
		else if (random_vehicle == 1) {
			lane.vehicle = scnMgr->createEntity("car2.mesh");
			lane.vehicle_node = scnMgr->getRootSceneNode()->createChildSceneNode();
			lane.vehicle_node->setPosition(Vector3(RIGHT_LANE_POS, CAR_POS_Y, z));
			lane.pos_z = z;
			lane.vehicle_node->setScale(CAR_SCALE);
			lane.vehicle_node->yaw(Ogre::Degree(180.0));
			lane.vehicle_node->attachObject(lane.vehicle);
			z -= RIGHT_CAR2_SPACE;
			right_lane_array[i] = lane;
		}
		else if (random_vehicle == 2) {
			lane.vehicle = scnMgr->createEntity("car3.mesh");
			lane.vehicle_node = scnMgr->getRootSceneNode()->createChildSceneNode();
			lane.vehicle_node->setPosition(Vector3(RIGHT_LANE_POS, CAR_POS_Y, z));
			lane.pos_z = z;
			lane.vehicle_node->setScale(CAR_SCALE);
			lane.vehicle_node->yaw(Ogre::Degree(180.0));
			lane.vehicle_node->attachObject(lane.vehicle);
			z -= RIGHT_CAR3_SPACE;
			right_lane_array[i] = lane;
		}
		else if (random_vehicle == 3) {
			lane.vehicle = scnMgr->createEntity("car4.mesh");
			lane.vehicle_node = scnMgr->getRootSceneNode()->createChildSceneNode();
			lane.vehicle_node->setPosition(Vector3(RIGHT_LANE_POS, CAR_POS_Y, z));
			lane.pos_z = z;
			lane.vehicle_node->setScale(CAR_SCALE);
			lane.vehicle_node->yaw(Ogre::Degree(180.0));
			lane.vehicle_node->attachObject(lane.vehicle);
			z -= RIGHT_CAR4_SPACE;
			right_lane_array[i] = lane;
		}
		else if (random_vehicle == 4) {
			lane.vehicle = scnMgr->createEntity("car5.mesh");
			lane.vehicle_node = scnMgr->getRootSceneNode()->createChildSceneNode();
			lane.vehicle_node->setPosition(Vector3(RIGHT_LANE_POS, CAR_POS_Y, z));
			lane.pos_z = z;
			lane.vehicle_node->setScale(CAR_SCALE);
			lane.vehicle_node->yaw(Ogre::Degree(180.0));
			lane.vehicle_node->attachObject(lane.vehicle);
			z -= RIGHT_CAR5_SPACE;
			right_lane_array[i] = lane;
		}
		else if (random_vehicle == 5) {
			lane.vehicle = scnMgr->createEntity("bus1.mesh");
			lane.vehicle_node = scnMgr->getRootSceneNode()->createChildSceneNode();
			lane.vehicle_node->setPosition(Vector3(RIGHT_LANE_POS, CAR_POS_Y, z));
			lane.pos_z = z;
			lane.vehicle_node->setScale(CAR_SCALE);
			lane.vehicle_node->yaw(Ogre::Degree(180.0));
			lane.vehicle_node->attachObject(lane.vehicle);
			z -= RIGHT_BUS1_SPACE;
			right_lane_array[i] = lane;
		}
	}
	return 0;
}

int clean_lanes(SceneManager* scnMgr) {
	static int i;
	for (i = 0; i < LEFT_LANE_VEHICLE_AMOUNT; i++) {
		scnMgr->destroySceneNode(left_lane_array[i].vehicle_node);
		scnMgr->destroyEntity(left_lane_array[i].vehicle);
	}
	for (i = 0; i < RIGHT_LANE_VEHICLE_AMOUNT; i++) {
		scnMgr->destroySceneNode(right_lane_array[i].vehicle_node);
		scnMgr->destroyEntity(right_lane_array[i].vehicle);
	}
	return 0;
}