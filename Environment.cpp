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
	int value=rand()%2;
	if(lastZ+1.5<road->GetRoadSize()-2)
	{
		for(int i = 0; i < 10; i++)
		{
			Coin *newCoin = new Coin;
			initialPoint.z=lastZ+ 0.15;
			lastZ=initialPoint.z;
			initialPoint.y+=0.5;
			Point3D currentPosition=road->GetOnRoadPosition(initialPoint, newCoin->width);			
			if(value==0)
			{
				currentPosition.y+=sin(step)* 5.0+ 3.0;
			}
			else
				if(value==1)
				{
					currentPosition.y+= 3.0;

				}
				else
				{
					/*currentPosition.y+=cos(step)* 5.0;*/
				}
			
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
		double type=rand()%35+1.0;
		cout<<type<<endl;
		Point3D initialPoint; 
		initialPoint.x=GetRandomGLfloat(0.0, 1.0);
		initialPoint.z=lastZ+rand()%3;
		switch((int)sqrt(type))
		{
			case 1:
			{
				AddQuestionBlock(initialPoint);
				if(initialPoint.x-2.5/10 > -1.0)
				{
					initialPoint.x-=2.5/10;
					AddQuestionBlock(initialPoint);
				}
				if(initialPoint.x+2.5/10 < 1.0)
				{
					initialPoint.x+=2.5/10;
					AddQuestionBlock(initialPoint);
				}
				lastZ=initialPoint.z;
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
				SplitBox* splitBox=new SplitBox(5, 5, 5);
				splitBox->AddCollider();
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
	int fenceIndex=rand()%3;
	while(i<road->GetRoadSize()-2)
	{
		int type=rand()%4;
		cout<<"*******************************************"<<endl;
		Point3D initialPoint; 
		initialPoint.x=GetRandomGLfloat(1.0, 3.0);
		initialPoint.z=lastZ+rand()%2;
		
		switch(type)
		{
			case 0:
			{
				Tree*tree=new Tree();
				if(initialPoint.x<0)
				{
					initialPoint.x-=tree->width;
				}
				else
				{
					initialPoint.x+=tree->width;
				}
				Point3D currentPosition=road->GetOnRoadPosition(initialPoint, 0.0);
				tree->Scale(Point3D(2,2,2));
				tree->Translate(currentPosition);
				lastZ=initialPoint.z;
				offRoadObjects.push_back(tree);
				cout<<"TREE"<<endl;
				break;
			}
			case 1:
			{
				PlantTulip* plant=new PlantTulip(2,2,2);
				if(initialPoint.x<0)
				{
					initialPoint.x-=plant->width;
				}
				else
				{
					initialPoint.x+=plant->width;
				}
				//plant->SetTarget(mario);
				Point3D currentPosition=road->GetOnRoadPosition(initialPoint, 0.0);
				plant->Translate(currentPosition);
				plant->Scale(Point3D(3, 3, 3));
				lastZ=initialPoint.z;
				offRoadObjects.push_back(plant);
				cout<<"PLANT"<<endl;
				break;
			}
			case 2:
			{
				Fence* fence=new Fence(2, 10 , 3, 7);
				/*if(initialPoint.x<0)
				{
					initialPoint.x-=fence->length;
				}
				else
				{
					initialPoint.x+=fence->length;
				}*/
				
				int value=rand()%2;
				Point3D currentPosition;
				Point3D fenceDirection;
				if(value==0)
				{
					currentPosition=road->GetLeft()[fenceIndex];
					fenceDirection=road->GetLeft()[fenceIndex+1]-road->GetLeft()[fenceIndex];
				}
				else
				{
					currentPosition=road->GetRight()[fenceIndex];
					fenceDirection=road->GetRight()[fenceIndex+1]-road->GetRight()[fenceIndex];
				}

				fence->Translate(currentPosition);
				GLfloat angle= fenceDirection.AngleBetween(Point3D(0, 0, 1));                                                              
				fence->Rotate(Point3D(0, angle, 0));
				lastZ=initialPoint.z;
				offRoadObjects.push_back(fence);
				cout<<"FENCE"<<endl;
				fenceIndex+=rand()%4;
				break;
			}
			case 3:
			{
				FullMountain* mountain=new FullMountain(15, 15, 15);
				if(initialPoint.x<0)
				{
					initialPoint.x-=mountain->length;
				}
				else
				{
					initialPoint.x+=mountain->length;
				}
				
				Point3D currentPosition=road->GetOnRoadPosition(initialPoint, 0.0);
				mountain->Translate(currentPosition);
				mountain->Rotate(Point3D(0, 180, 0));
				lastZ=initialPoint.z;
				offRoadObjects.push_back(mountain);
				cout<<"MOUNTAIN"<<endl;
				break;
			}
		}

		i=lastZ;

	}
}

void Environment:: AddQuestionBlock(Point3D initialPoint)
{
	int value=rand()%2;
	QuestionBlock*questionBlock;
	if(value==0)
	{
		Mushroom* mushroom=new Mushroom(5, 5, 5);
		questionBlock=new QuestionBlock(mushroom, road, 5,5,5);
	}
	else
	{
		Star* star=new Star(5, 5, 5);
		star->Scale(Point3D(5, 5, 5));
		questionBlock=new QuestionBlock(star, road, 5,5,5);
	}
	Point3D currentPosition=road->GetOnRoadPosition(initialPoint, questionBlock->width);
	currentPosition.y=12;
	questionBlock->Translate(currentPosition);	
	obstacles.push_back(questionBlock);
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
