#ifndef EVENT_RECEIVER_H
#define EVENT_RECEIVER_H

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

// Animation Speed
#define IDLE_ANIMATION_SPEED 50
#define SHOOT_ANIMATION_SPEED 100
// Animation Frames ({FROM FRAME}, {TO FRAME})
#define IDLE_ANIMATION_FRAME_LOOP 30, 130
#define SHOOT_ANIMATION_FRAME_LOOP 0, 15

class MyEventReceiver : public IEventReceiver
{
public:
	IAnimatedMeshSceneNode* player_node; // player
												
	struct SMouseState // We'll create a struct to record info on the mouse state
	{
		core::position2di Position;
		bool LeftButtonDown;
		SMouseState() : LeftButtonDown(false) { }
	} MouseState;

	// This is the one method that we have to implement
	virtual bool OnEvent(const SEvent& event);

	const SMouseState & GetMouseState(void) const;
	void setPlayer(IAnimatedMeshSceneNode* player_node);
	bool get_is_attacking();
};

#endif
