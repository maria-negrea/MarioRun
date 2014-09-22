#pragma once
#include "Plant.h"
#include "Box.h"
#include "Mario.h"
#include "MarioCamera.h"
#include "Goomba.h"
#include "Ground.h"
#include "Coin.h"
#include "QuestionBlock.h"
#include "Tree.h"
#include "PlantTulip.h"
#include "PlantHead.h"
#include "PlantLeaf.h"
#include "Road.h"
#include "SnowMan.h"
#include "Scene.h"
#include <cmath>

class Environment: public Updatable
{
protected:
	Mario* mario;
	SnowMan* snowMan;
	Tree* tree;
	Coin *coin ;
	QuestionBlock *block;
	Road *road;
	Scene *scene;
	vector<Coin*> coins;
	vector<WorldObject*> obstacles;
	Camera* mainCamera;

public:
	Environment(void);
	vector<Coin*> GetCoins();
	vector<WorldObject*> GetObstacles();
	void InitializeCoins(double& lastZ);
	void InitializeObstacles();
	void GetOffRoadPosition();
	void AddObjectsToScene();
	Mario* GetMario();
	Scene* GetScene();
	void Update();
	~Environment(void);
};
