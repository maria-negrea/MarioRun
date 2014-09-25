#pragma once
#include <cmath>

#include "Scene.h"
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
#include "SnowMan.h"
#include "PlantTulip.h"
#include "Score.h"
#include "SplitBox.h"
#include "Star.h"
#include "Fence.h"
#include "FullMountain.h"
#include "Sky.h"
#include "Hole.h"
#include "Pipe.h"

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
	vector<WorldObject*> offRoadObjects;
	vector<WorldObject*> blocks;
	Camera* mainCamera;
	Score* score;
	Sky* sky;

public:
	Environment(void);
	vector<Coin*> GetCoins();
	vector<WorldObject*> GetObstacles();
	void InitializeRandomBlocks(double& lastZ);
	void InitializeCoins(double& lastZ);
	void InitializeObstacles();
	void InitializeOffRoadObjects();
	void AddObjectsToScene();
	void AddObject(WorldObject *obj);
	Mario* GetMario();
	Scene* GetScene();
	void AddQuestionBlock(Point3D initialPoint, double& lastZ);
	void Update();
	~Environment(void);
};
