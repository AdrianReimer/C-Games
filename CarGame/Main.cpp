#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreApplicationContext.h"
#include <OgreTrays.h>
#include <Windows.h>
#include <OgreRenderWindow.h>
#include <iostream>
#include "Forest.h"
#include "OgreTrays.h"
#include "Lane.h"

// TextBox Scale
#define TEXTBOX_WIDTH 180
#define TEXTBOX_HEIGHT 30
// GameBox Text
#define GAMEBOX_DIED_TEXT "You Died"
#define GAMEBOX_WON_TEXT "You Won"
// Player
#define PLAYER_CAR_VELOCITY_MIN -2
#define PLAYER_CAR_VELOCITY_MAX -5
#define PLAYER_CAR_START_POS_Z -300
#define PLAYER_CAR_SPEED_TEXT ("Car Speed = " + std::to_string(-player_car_speed))
#define PLAYER_POINTS_TEXT ("Points = " + std::to_string(player_points) + "/" + std::to_string(MAX_POINTS))
// Collision
#define CAR_COLLSION_BOX_SCALE 20
// Velocity
#define LEFT_LANE_VEHICLE_VELOCITY 2
#define RIGHT_LANE_VEHICLE_VELOCITY -1.5
// Scale
#define STREET_SCALE_XY 150
#define STREET_SCALE_Z 300
// Camera
#define CAM_POS_X 0
#define CAM_POS_Y 450
#define CAM_POS_Z -110


using namespace Ogre;
using namespace OgreBites;

extern struct Lane left_lane_array[LEFT_LANE_VEHICLE_AMOUNT];
extern struct Lane right_lane_array[RIGHT_LANE_VEHICLE_AMOUNT];
static const int MAX_POINTS = 10000; // amount of points to win the game
static SceneNode* car_node;
static SceneNode* camNode;
static SceneManager* scnMgr;
static int player_car_speed = PLAYER_CAR_VELOCITY_MIN; // speed of the player
static int player_points; // current points of the player
static String player_points_text = PLAYER_POINTS_TEXT;   
static String player_car_speed_text = PLAYER_CAR_SPEED_TEXT;
static float player_pos_z = PLAYER_CAR_START_POS_Z; // z position of the player relative to root
static bool did_not_collide = true; // false if player collided with a car
static bool is_on_right_lane = true;
static TextBox* car_speed_box;
static TextBox* points_box;
static TextBox* game_box;
static Button* retry_btn;


class BasicTutorial1: public ApplicationContext, public InputListener{
public:

	BasicTutorial1();
	virtual ~BasicTutorial1() {}

	void setup();
	bool keyPressed(const KeyboardEvent& evt);
protected:
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
};


BasicTutorial1::BasicTutorial1(): ApplicationContext("My Game"){
}

int restart_game(void) {
	clean_lanes(scnMgr);
	car_node->setPosition(Vector3(0, CAR_POS_Y, PLAYER_CAR_START_POS_Z));
	camNode->setPosition(CAM_POS_X, CAM_POS_Y, CAM_POS_Z);
	player_pos_z = PLAYER_CAR_START_POS_Z;
	is_on_right_lane = true;
	player_points = 0;
	make_left_lane(scnMgr);
	make_right_lane(scnMgr);
	did_not_collide = true;
	game_box->hide();
	return 0;
}

bool BasicTutorial1::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	static int i;
	if (did_not_collide) {
		car_node->translate(Vector3(0, 0, player_car_speed)); // translate player
		camNode->translate(Vector3(0, 0, player_car_speed)); // translate cam
		player_pos_z += player_car_speed;
		// Left Lane logic
		for (i = 0; i < LEFT_LANE_VEHICLE_AMOUNT; i++) {
			left_lane_array[i].vehicle_node->translate(Vector3(0, 0, LEFT_LANE_VEHICLE_VELOCITY));
			left_lane_array[i].pos_z += LEFT_LANE_VEHICLE_VELOCITY;
			if (player_pos_z - CAR_COLLSION_BOX_SCALE <= left_lane_array[i].pos_z && player_pos_z + CAR_COLLSION_BOX_SCALE >= left_lane_array[i].pos_z && !is_on_right_lane) {
				did_not_collide = false;
				game_box->setCaption(GAMEBOX_DIED_TEXT);
				game_box->show();
			}
		}
		// Right Lane logic
		for (i = 0; i < RIGHT_LANE_VEHICLE_AMOUNT; i++) {
			right_lane_array[i].vehicle_node->translate(Vector3(0, 0, RIGHT_LANE_VEHICLE_VELOCITY));
			right_lane_array[i].pos_z += RIGHT_LANE_VEHICLE_VELOCITY;
			if (player_pos_z - CAR_COLLSION_BOX_SCALE <= right_lane_array[i].pos_z && player_pos_z + CAR_COLLSION_BOX_SCALE >= right_lane_array[i].pos_z && is_on_right_lane) {
				did_not_collide = false;
				game_box->setCaption(GAMEBOX_DIED_TEXT);
				game_box->show();
			}
		}
		if (is_on_right_lane) {
			// Add Points Right
			player_points += 1 * std::abs(player_car_speed);
		}
		else {
			// Add Points Left
			player_points += 3 * std::abs(player_car_speed);
		}
		if (player_points >= MAX_POINTS) {
			// Game won!
			did_not_collide = false;
			game_box->setCaption(GAMEBOX_WON_TEXT);
			game_box->show();
			player_points_text = MAX_POINTS;
			points_box->setCaption(player_points_text);
		}
		else {
			// Display points
			player_points_text = PLAYER_POINTS_TEXT;
			points_box->setCaption(player_points_text);
		}
	}
	if (retry_btn->getState() == ButtonState::BS_DOWN) {
		restart_game();
	}
	return true;
}

void BasicTutorial1::setup(){
	// call the base
	ApplicationContext::setup();
	addInputListener(this);

	// get a pointer to the already created root
	Root* root = getRoot();
	scnMgr = root->createSceneManager();

	// register scene with the RTSS
	RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
	shadergen->addSceneManager(scnMgr);

	// Create GUI System
	RenderWindow* mWindow = getRenderWindow();
	TrayManager* mTrayMgr = new TrayManager("InterfaceName", mWindow);
	scnMgr->addRenderQueueListener(getOverlaySystem());
	mTrayMgr->showLogo(TL_RIGHT);
	addInputListener(mTrayMgr);
	points_box = mTrayMgr->createTextBox(TL_TOPLEFT, "Points", player_points_text, TEXTBOX_WIDTH, TEXTBOX_HEIGHT);
	car_speed_box = mTrayMgr->createTextBox(TL_BOTTOMLEFT, "CarSpeed", player_car_speed_text, TEXTBOX_WIDTH, TEXTBOX_HEIGHT);
	game_box = mTrayMgr->createTextBox(TL_BOTTOMRIGHT, "GameState", "", TEXTBOX_WIDTH, TEXTBOX_HEIGHT);
	game_box->hide();
	retry_btn = mTrayMgr->createButton(TL_BOTTOMRIGHT, "RestartButton", "Restart");

	// create left and right lane vehicles
	make_left_lane(scnMgr);
	make_right_lane(scnMgr);

	// create left and right forest entities
	make_left_forest(scnMgr);
	make_right_forest(scnMgr);
	
	root->addFrameListener(this);

	// create street
	Entity* street = scnMgr->createEntity("street.mesh");
	SceneNode* street_node = scnMgr->getRootSceneNode()->createChildSceneNode();
	street_node->setPosition(Vector3(0, 0, 0));
	street_node->setScale(Vector3(STREET_SCALE_XY, STREET_SCALE_XY, STREET_SCALE_Z));
	street_node->attachObject(street);

	// create player car
	Entity* car = scnMgr->createEntity("car1.mesh");
	car->setCastShadows(true);
	car_node = scnMgr->getRootSceneNode()->createChildSceneNode();
	car_node->setPosition(Vector3(0, CAR_POS_Y, PLAYER_CAR_START_POS_Z));
	car_node->setScale(Vector3(5, 5, 5));
	car_node->yaw(Ogre::Degree(180.0));
	car_node->attachObject(car);

	// create the camera
	Camera* cam = scnMgr->createCamera("myCam");
	cam->setNearClipDistance(1);
	camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	camNode->setPosition(CAM_POS_X, CAM_POS_Y, CAM_POS_Z);
	camNode->lookAt(car_node->getPosition(), Node::TransformSpace::TS_WORLD);
	camNode->attachObject(cam);

	// render into the main window
	Viewport* vp = getRenderWindow()->addViewport(cam);
	vp->setBackgroundColour(ColourValue(0, 0, 0));
	cam->setAspectRatio(Real(vp->getActualWidth()) / Real(vp->getActualHeight()));

	// create directional Light
	Light* directionalLight = scnMgr->createLight("DirectionalLight");
	directionalLight->setType(Light::LT_DIRECTIONAL);
	directionalLight->setDiffuseColour(ColourValue(1, 0.6, 0.3));
	directionalLight->setSpecularColour(ColourValue(1, 0.6, 0.3));
	SceneNode* directionalLightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	directionalLightNode->attachObject(directionalLight);
	directionalLightNode->setDirection(Vector3(5, -15, -10));
}


bool BasicTutorial1::keyPressed(const KeyboardEvent& evt){
	if (evt.keysym.sym == SDLK_ESCAPE){
		getRoot()->queueEndRendering();
	}else if (evt.keysym.sym == SDLK_UP && player_car_speed > PLAYER_CAR_VELOCITY_MAX){
		player_car_speed--;
		player_car_speed_text = PLAYER_CAR_SPEED_TEXT;
		car_speed_box->setCaption(player_car_speed_text);
	}else if (evt.keysym.sym == SDLK_DOWN && player_car_speed < PLAYER_CAR_VELOCITY_MIN){
		player_car_speed++;
		player_car_speed_text = PLAYER_CAR_SPEED_TEXT;
		car_speed_box->setCaption(player_car_speed_text);
	}else if (evt.keysym.sym == SDLK_LEFT && did_not_collide){
		// Turn Playercar LEFT
		car_node->setPosition(Vector3(LEFT_LANE_POS, 200, player_pos_z));
		is_on_right_lane = false;
	}else if (evt.keysym.sym == SDLK_RIGHT && did_not_collide){
		// Turn Playercar Right
		car_node->setPosition(Vector3(RIGHT_LANE_POS, 200, player_pos_z));
		is_on_right_lane = true;
	}
	return true;
}


int main(int argc, char **argv){
	try
	{
		BasicTutorial1 app;
		app.initApp();
		app.getRoot()->startRendering();
		app.closeApp();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error occurred during execution: " << e.what() << '\n';
		return 1;
	}

	return 0;
}
