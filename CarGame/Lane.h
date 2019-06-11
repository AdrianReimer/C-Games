#ifndef LANE_H
#define LANE_H

#define LEFT_LANE_VEHICLE_AMOUNT 150
#define RIGHT_LANE_VEHICLE_AMOUNT 60
#define RIGHT_LANE_POS 0
#define LEFT_LANE_POS -27
#define CAR_POS_Y 200

using namespace Ogre;
using namespace OgreBites;

struct Lane {
	Entity* vehicle;
	SceneNode* vehicle_node;
	float pos_z;
};

int make_left_lane(SceneManager* scnMgr);
int make_right_lane(SceneManager* scnMgr);
int clean_lanes(SceneManager* scnMgr);

#endif
