#include <irrlicht.h>
#include "EventReceiver.h"
#include "Soldier.h"

static bool is_attacking;

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

bool MyEventReceiver::OnEvent(const SEvent& event) {
	// Remember the mouse state
	if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
	{
		switch (event.MouseInput.Event)
		{
		case EMIE_LMOUSE_PRESSED_DOWN:
			is_attacking = true;
			player_node->setAnimationSpeed(SHOOT_ANIMATION_SPEED);
			player_node->setFrameLoop(SHOOT_ANIMATION_FRAME_LOOP);
			MouseState.LeftButtonDown = true;
			break;

		case EMIE_LMOUSE_LEFT_UP:
			is_attacking = false;
			player_node->setAnimationSpeed(IDLE_ANIMATION_SPEED);
			player_node->setFrameLoop(IDLE_ANIMATION_FRAME_LOOP);
			MouseState.LeftButtonDown = false;
			break;

		case EMIE_MOUSE_MOVED:
			MouseState.Position.X = event.MouseInput.X;
			MouseState.Position.Y = event.MouseInput.Y;
			break;

		default:
			// We won't use the wheel
			break;
		}
	}
	return false;
}

const MyEventReceiver::SMouseState& MyEventReceiver::GetMouseState(void) const
{
	return MouseState;
}

void MyEventReceiver::setPlayer(IAnimatedMeshSceneNode* player_node) {
	MyEventReceiver::player_node = player_node;
}

bool MyEventReceiver::get_is_attacking() {
	return is_attacking;
}
