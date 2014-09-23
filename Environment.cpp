#include "Environment.h"

Environment::Environment(void)
{
	score=new Score();
	mario = new Mario();
	mario->Translate(Point3D(0.1,0.0,0.0));

	snowMan=new SnowMan();
	snowMan->Translate(Point3D(0, 0, 10));	

	road = new Road();
	//newRoad->SetRoadObject(mario);

	//goomba=new Goomba();
	//goomba->SetTarget(mario);
	//goomba->Translate(Point3D(-5, 0, 20));

	scene = new Scene();
	mainCamera = new MarioCamera(mario);
	scene->SetMainCamera(mainCamera);

	InitializeObstacles();
	InitializeOffRoadObjects();
}

void Environment:: InitializeCoins(double& lastZ)
{
	coins.clear();
	GLfloat groupX = GetRandomGLfloat(0.0, 1.0);
	Point3D initialPoint; 
	initialPoint.x=groupX;

	double step=PI/10.0;
	if(lastZ+1.5<road->GetRoadSize()-2)
	{
		for(int i = 0; i < 10; i++)
		{
			Coin *newCoin = new Coin;
			initialPoint.z=lastZ+ 0.15;
			lastZ=initialPoint.z;
			initialPoint.y+=0.5;
			Point3D currentPosition=road->GetOnRoadPosition(initialPoint, newCoin->width);
			currentPosition.y+=sin(step)* 5.0+ 3.0;
			newCoin->Translate(currentPosition);
			newCoin->Scale(Point3D(5.0, 5.0, 5.0));
			newCoin->AddCollider();
			obstacles.push_back(newCoin);
			step+=PI/10.0;
		}
	}
}

void Environment::AddObject(WorldObject *obj) {
	scene->AddObject(obj);
}

void Environment:: InitializeObstacles()
{
	GLfloat i=0;
	double lastZ=0.0;
	while(i<road->GetRoadSize()-2)
	{
		double type=rand()%25+1.0;
		cout<<type<<endl;
		Point3D initialPoint; 
		initialPoint.x=GetRandomGLfloat(0.0, 1.0);
		initialPoint.z=lastZ+rand()%3;
		switch((int)sqrt(type))
		{
			case 1:
			{
				int  value=rand()%2;
				QuestionBlock* questionBlock;
				if(value==0)
				{
					Mushroom* mushroom=new Mushroom(5, 5, 5);
					questionBlock=new QuestionBlock(mushroom, road, 5,5,5);
				}
				else
				{

					Mushroom* mushroom=new Mushroom(5, 5, 5);
					questionBlock=new QuestionBlock(mushroom, road, 5,5,5);


					/*Star* star=new Star(5, 5, 5);
					questionBlock=new QuestionBlock(star, road, 5,5,5);*/
				}

				
				Point3D currentPosition=road->GetOnRoadPosition(initialPoint, questionBlock->width);
				currentPosition.y=12;
				questionBlock->Translate(currentPosition);
				lastZ=initialPoint.z;
				obstacles.push_back(questionBlock);
				break;
			}
			case 2:
			{
				Goomba* goomba=new Goomba();
				goomba->SetTarget(mario);
				Point3D currentPosition=road->GetOnRoadPosition(initialPoint, goomba->width);				
				goomba->Translate(currentPosition);
				lastZ=initialPoint.z;
				obstacles.push_back(goomba);
				break;
			}
			case 3:
			{
				InitializeCoins(lastZ);
				break;
			}
			case 4:
			{
				SplitBox* splitBox=new SplitBox(2, 2, 2);
				Point3D currentPosition=road->GetOnRoadPosition(initialPoint, splitBox->width);
				splitBox->Translate(currentPosition);
				lastZ=initialPoint.z;
				obstacles.push_back(splitBox);
				break;
				
			}
			case 5:
			{
				Box* box=new Box(2, 2, 2);
				Point3D currentPosition=road->GetOnRoadPosition(initialPoint, box->width);
				box->Translate(currentPosition);
				lastZ=initialPoint.z;
				obstacles.push_back(box);
				break;
			}
		}
		i=lastZ;

	}
}

void Environment:: InitializeOffRoadObjects()
{
	GLfloat i=0;
	double lastZ=0.0;
	while(i<road->GetRoadSize()-2)
	{
		int type=rand()%2;
		cout<<type<<endl;
		Point3D initialPoint; 
		initialPoint.x=GetRandomGLfloat(2.0, 8.0);
		initialPoint.z=lastZ+rand()%3;
		switch(type)
		{
			case 0:
			{
				Tree*tree=new Tree();
				Point3D currentPosition=road->GetOnRoadPosition(initialPoint, tree->width);
				tree->Scale(Point3D(2,2,2));
				tree->Translate(currentPosition);
				lastZ=initialPoint.z;
				offRoadObjects.push_back(tree);
				break;
			}
			case 1:
			{
				PlantTulip* plant=new PlantTulip(2,2,2);
				//plant->SetTarget(mario);
				Point3D currentPosition=road->GetOnRoadPosition(initialPoint, plant->width);
				plant->Translate(currentPosition);
				plant->Scale(Point3D(3, 3, 3));
				lastZ=initialPoint.z;
				offRoadObjects.push_back(plant);
				break;
			}
		}

		i=lastZ;

	}
}

vector<WorldObject*> Environment:: GetObstacles()
{
	return obstacles;
}

vector<Coin*> Environment:: GetCoins()
{
	return coins;
}

void Environment:: AddObjectsToScene()
{
	scene->AddObject(score);
	scene->AddObject(road);
	scene->AddObject(new Ground);
	//scene->AddObject(particles);
	scene->AddObject(mario);	
//	scene->AddObject(goomba);

	for(int i = 0; i < obstacles.size(); i++)
		scene->AddObject(obstacles[i]);
	for(int i = 0; i < offRoadObjects.size(); i++)
		scene->AddObject(offRoadObjects[i]);

	road->AddRoadObject(mario);
}

Mario* Environment:: GetMario()
{
	return mario;
}

Scene* Environment:: GetScene()
{
	return scene;
}

void Environment:: Update()
{
}

Environment::~Environment(void)
{
}
