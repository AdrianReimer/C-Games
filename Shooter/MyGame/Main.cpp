#include <irrlicht.h>
#include <ITimer.h>
#include <stdlib.h>
#include <string> 
#include "EventReceiver.h"
#include "Soldier.h"

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

// Player
#define PLAYER_HEALTH 100
#define PLAYER_MOVEMENT_SPEED 0.3
#define PLAYER_JUMP_HEIGHT 0.5
// World
#define WORLD_GRAVITY -3
// Window
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
// Light
#define BRIGHTNESS 1500
// Models
#define MAP_MODEL_PATH "media/models/static/map.obj"
#define DOT_MODEL_PATH "media/particle.bmp"
// Text
#define WON_TEXT L"You Won! Ending Mission."
#define LOST_TEXT L"You Died! Ending Mission."
#define GAME_WINDOW_TEXT L"My Shooter Game ["
// Dot
#define DOT_MAX_DISTANCE 1000

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


static IAnimatedMeshSceneNode* player_node; // Player model
static int player_health = PLAYER_HEALTH;
static bool is_dead = false;
static ICameraSceneNode* camera;
static IBillboardSceneNode* bill;
static IrrlichtDevice* device;
static MyEventReceiver receiver;
static IVideoDriver* driver;
static ISceneManager* smgr;
static IGUIEnvironment* guienv;

int setup();
int loop();
int main()
{
	// init game level
	setup();
	// render loop
	loop();
	// end game
	device->drop();
	return 0;
}

int setup() {
	// create device
	device = createDevice(EDT_OPENGL, dimension2d<u32>(WINDOW_WIDTH, WINDOW_HEIGHT), 16, false, false, false, &receiver);
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();
	// Add Map
	IAnimatedMesh* map = smgr->getMesh(MAP_MODEL_PATH);
	IMeshSceneNode* map_node = 0;
	// Add Light
	smgr->addLightSceneNode(0, vector3df(0, -1550, 0), SColorf(0.5, 0.5, 0.5, 0.05), BRIGHTNESS);
	smgr->addLightSceneNode(0, vector3df(0, 1550, 0), SColorf(0.5, 0.5, 0.5, 0.05), BRIGHTNESS);
	smgr->addLightSceneNode(0, vector3df(1550, 1550, 0), SColorf(0.5, 0.5, 0.5, 0.05), BRIGHTNESS);
	smgr->addLightSceneNode(0, vector3df(0, 1550, 1550), SColorf(0.5, 0.5, 0.5, 0.05), BRIGHTNESS);
	smgr->addLightSceneNode(0, vector3df(1550, 1550, 1550), SColorf(0.5, 0.5, 0.5, 0.05), BRIGHTNESS);
	smgr->addLightSceneNode(0, vector3df(-1550, 1550, 0), SColorf(0.5, 0.5, 0.5, 0.05), BRIGHTNESS);
	smgr->addLightSceneNode(0, vector3df(0, 1550, -1550), SColorf(0.5, 0.5, 0.5, 0.05), BRIGHTNESS);
	smgr->addLightSceneNode(0, vector3df(-1550, 1550, -1550), SColorf(0.5, 0.5, 0.5, 0.05), BRIGHTNESS);

	if (map)
		map_node = smgr->addOctreeSceneNode(map->getMesh(0), 0, -1);
	ITriangleSelector* selector = 0;
	if (map_node)
	{
		map_node->setPosition(irr::core::vector3df(0, 800, 0));
		selector = smgr->createOctreeTriangleSelector(map_node->getMesh(), map_node, 128);
		map_node->setTriangleSelector(selector);
	}
	// Manage key presses
	SKeyMap keyMap[10];
	keyMap[0].Action = EKA_MOVE_FORWARD;
	keyMap[0].KeyCode = KEY_UP;
	keyMap[1].Action = EKA_MOVE_FORWARD;
	keyMap[1].KeyCode = KEY_KEY_W;
	keyMap[2].Action = EKA_MOVE_BACKWARD;
	keyMap[2].KeyCode = KEY_DOWN;
	keyMap[3].Action = EKA_MOVE_BACKWARD;
	keyMap[3].KeyCode = KEY_KEY_S;
	keyMap[4].Action = EKA_STRAFE_LEFT;
	keyMap[4].KeyCode = KEY_LEFT;
	keyMap[5].Action = EKA_STRAFE_LEFT;
	keyMap[5].KeyCode = KEY_KEY_A;
	keyMap[6].Action = EKA_STRAFE_RIGHT;
	keyMap[6].KeyCode = KEY_RIGHT;
	keyMap[7].Action = EKA_STRAFE_RIGHT;
	keyMap[7].KeyCode = KEY_KEY_D;
	keyMap[8].Action = EKA_JUMP_UP;
	keyMap[8].KeyCode = KEY_SPACE;
	keyMap[9].Action = EKA_CROUCH;
	keyMap[9].KeyCode = KEY_KEY_C;

	// Set a jump speed of 0.5 units per second, which gives a fairly realistic jump
	// when used with the gravity of (0, -3, 0) in the collision response animator.
	camera = smgr->addCameraSceneNodeFPS(0, 100.0f, PLAYER_MOVEMENT_SPEED, -1, keyMap, 10, true, PLAYER_JUMP_HEIGHT);
	camera->setPosition(core::vector3df(50, 980, -60));
	camera->setTarget(core::vector3df(0, 980, 0));

	if (selector)
	{
		ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(selector, camera, vector3df(30, 50, 30), vector3df(0, WORLD_GRAVITY, 0), vector3df(0, 40, 0));
		selector->drop();
		camera->addAnimator(anim);
		anim->drop();
	}
	// get rid of the mouse cursor
	device->getCursorControl()->setVisible(false);
	// Add the billboard.
	bill = smgr->addBillboardSceneNode();
	bill->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);
	bill->setMaterialTexture(0, driver->getTexture(DOT_MODEL_PATH));
	bill->setMaterialFlag(EMF_LIGHTING, false);
	bill->setMaterialFlag(EMF_ZBUFFER, false);
	bill->setSize(dimension2d<f32>(20.0f, 20.0f));
	bill->setID(-1); // This ensures that we don't accidentally ray-pick it
	return 0;
}

int loop() {
	Soldier soldier(driver);
	player_node = soldier.create_soldier(smgr, camera, vector3df(0, -80, -15)); // player soldier model
	receiver.setPlayer(player_node);
	soldier.spawn_enemies(smgr);

	ISceneCollisionManager* collMan = smgr->getSceneCollisionManager();
	int lastFPS = -1;
	// game loop
	while (device->run())
		if (device->isWindowActive())
		{
			driver->beginScene(true, true, 0);
			if (!is_dead) {
				smgr->drawAll();
				if (player_health <= 0) {
					// Game Lost
					guienv->addStaticText(LOST_TEXT, rect<s32>(10, 10, 250, 30), true, true, 0, -1, true);
					is_dead = true;
				}
				if (soldier.get_soldiers_alive() <= 0){
					// Game Won
					guienv->addStaticText(WON_TEXT, rect<s32>(10, 10, 250, 30), true, true, 0, -1, true);
					is_dead = true;
				}
				soldier.update_behavior(camera, receiver.get_is_attacking(),collMan);
				soldier.check_ai(&player_health);
			}
			else {
				// Wait some time before game shutdown
				static int i;
				if (i > 10000) {
					return 0;
				}
				i++;
			}		
			guienv->drawAll();

			// All intersections in this example are done with a ray cast out from the camera to
			// a distance of 1000.  You can easily modify this to check (e.g.) a bullet
			// trajectory or a sword's position, or create a ray from a mouse click position using
			// ISceneCollisionManager::getRayFromScreenCoordinates()
			line3d<f32> ray;
			ray.start = camera->getPosition();
			ray.end = ray.start + (camera->getTarget() - ray.start).normalize() * DOT_MAX_DISTANCE;

			vector3df intersection; // Tracks the current intersection point with the level or a mesh
			triangle3df hitTriangle; // Used to show with triangle has been hit
			ISceneNode * selectedSceneNode = collMan->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, -1, 0);

			// If the ray hit anything, move the billboard to the collision position
			bill->setPosition(intersection);
			// We're all done drawing, so end the scene.
			driver->endScene();

			int fps = driver->getFPS();
			if (lastFPS != fps)
			{
				stringw str = GAME_WINDOW_TEXT;
				str += driver->getName();
				str += "] FPS:";
				str += fps;

				device->setWindowCaption(str.c_str());
				lastFPS = fps;
			}
		}
	return 0;
}
