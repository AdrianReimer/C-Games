#include <irrlicht.h>
#include "driverChoice.h"
#include <stdlib.h>
#include <string> 

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif


int main()
{
	// create device
	IrrlichtDevice *device = createDevice(EDT_OPENGL, dimension2d<u32>(640, 480), 16, false);

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();

	// Add Map
	IAnimatedMesh* map = smgr->getMesh("../../media/models/static/map.obj");
	IMeshSceneNode* map_node = 0;

	// Add Light
	smgr->addLightSceneNode(0, vector3df(0, -1550, 0), SColorf(0.5, 0.5, 0.5, 0.05), 2000);
	smgr->addLightSceneNode(0, vector3df(0, 1550, 0), SColorf(0.5, 0.5, 0.5, 0.05), 2000);
	smgr->addLightSceneNode(0, vector3df(1550, 1550, 0), SColorf(0.5, 0.5, 0.5, 0.05), 2000);
	smgr->addLightSceneNode(0, vector3df(0, 1550, 1550), SColorf(0.5, 0.5, 0.5, 0.05), 2000);
	smgr->addLightSceneNode(0, vector3df(1550, 1550, 1550), SColorf(0.5, 0.5, 0.5, 0.05), 2000);
	smgr->addLightSceneNode(0, vector3df(-1550, 1550, 0), SColorf(0.5, 0.5, 0.5, 0.05), 2000);
	smgr->addLightSceneNode(0, vector3df(0, 1550, -1550), SColorf(0.5, 0.5, 0.5, 0.05), 2000);
	smgr->addLightSceneNode(0, vector3df(-1550, 1550, -1550), SColorf(0.5, 0.5, 0.5, 0.05), 2000);

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
	ICameraSceneNode* camera = smgr->addCameraSceneNodeFPS(0, 100.0f, .3f, -1, keyMap, 10, true, 0.5f);
	camera->setPosition(core::vector3df(50, 980, -60));
	camera->setTarget(core::vector3df(0, 980, 0));

	if (selector)
	{
		ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(selector, camera, vector3df(30, 50, 30),vector3df(0, -3, 0), vector3df(0, 40, 0));
		selector->drop();
		camera->addAnimator(anim);
		anim->drop();
	}

	// get rid of the mouse cursor
	device->getCursorControl()->setVisible(false);

	// Add the billboard.
	IBillboardSceneNode * bill = smgr->addBillboardSceneNode();
	bill->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);
	bill->setMaterialTexture(0, driver->getTexture("../../media/particle.bmp"));
	bill->setMaterialFlag(EMF_LIGHTING, false);
	bill->setMaterialFlag(EMF_ZBUFFER, false);
	bill->setSize(dimension2d<f32>(20.0f, 20.0f));
	bill->setID(-1); // This ensures that we don't accidentally ray-pick it

	// Player Model
	IAnimatedMeshSceneNode* soldier;
	SMaterial material;
	SMaterial material2;


	soldier = smgr->addAnimatedMeshSceneNode(smgr->getMesh("../../media/models/dynamic/soldier.md3"), camera, -1, vector3df(-3, -90, -18));
	material.setTexture(0, driver->getTexture("../../media/models/dynamic/demo_soldier_512.tga"));
	soldier->setRotation(vector3df(0, 180, 0));
	soldier->setAnimationSpeed(50);
	material.Lighting = true;
	material.NormalizeNormals = true;
	material2.setTexture(0, driver->getTexture("../../media/models/dynamic/demo_weapon.tga"));
	material2.Lighting = true;
	material2.NormalizeNormals = true;
	soldier->getMaterial(0) = material;
	soldier->getMaterial(1) = material2;


	ISceneCollisionManager* collMan = smgr->getSceneCollisionManager();
	int lastFPS = -1;

	// draw the selection triangle only as wireframe
	material.Wireframe = true;

	while (device->run())
		if (device->isWindowActive())
		{
			driver->beginScene(true, true, 0);
			smgr->drawAll();
			// All intersections in this example are done with a ray cast out from the camera to
			// a distance of 1000.  You can easily modify this to check (e.g.) a bullet
			// trajectory or a sword's position, or create a ray from a mouse click position using
			// ISceneCollisionManager::getRayFromScreenCoordinates()
			line3d<f32> ray;
			ray.start = camera->getPosition();
			ray.end = ray.start + (camera->getTarget() - ray.start).normalize() * 1000.0f;

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
				stringw str = L"My Game [";
				str += driver->getName();
				str += "] FPS:";
				str += fps;
				str += "  x: ";
				
				device->setWindowCaption(str.c_str());
				lastFPS = fps;
			}
		}

	device->drop();

	return 0;
}
