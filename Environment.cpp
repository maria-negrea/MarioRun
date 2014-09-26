#include "Environment.h"
#include "Skin.h"

Environment::Environment(void)
{
	sky=new Sky(3000);
	score=new Score();
	mario = new Mario();

	snowMan=new SnowMan();
	snowMan->Translate(Point3D(0, 0, 10));	

	road = new Road();

	scene = new Scene();
	mainCamera = new MarioCamera(mario);
	scene->SetMainCamera(mainCamera);

	InitializeObstacles();
	InitializeOffRoadObjects();
}

void Environment:: InitializeCoins(double& lastZ)
{
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
			lastZ=initialPoint.z+newCoin->length/40.0;
			initialPoint.y+=0.5;
			Point3D currentPosition=road->GetOnRoadPosition(initialPoint, newCoin->width);			
			if(value==0)
			{
				currentPosition.y+=sin(step)* 10.0+ 3.0;
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
			road->AddRoadObject(newCoin);
			obstacles.push_back(newCoin);
			step+=PI/10.0;
		}
	}
}

void Environment:: InitializeRandomBlocks(double& lastZ)
{
	GLfloat groupX = GetRandomGLfloat(0.0, 1.0);
	Point3D initialPoint; 
	initialPoint.x=groupX;
	initialPoint.y=3.0;

	double stepZ=2.5/20;
	
	if(lastZ+stepZ<road->GetRoadSize()-2)
	{
		for(int i = 0; i < 4; i++)
		{
			initialPoint.z=lastZ;
 			int value=rand()%2;
			if(value==0)
			{
				AddQuestionBlock(initialPoint, lastZ);
				lastZ=initialPoint.z+stepZ;
			}
			else
			{
				SplitBox* splitBox=new SplitBox(5, 5, 5);
				splitBox->AddCollider();
				Point3D currentPosition=road->GetOnRoadPosition(initialPoint, splitBox->width);
				currentPosition.y=12.0;
				splitBox->Translate(currentPosition);
				lastZ=initialPoint.z+stepZ;
				road->AddRoadObject(splitBox);
				obstacles.push_back(splitBox);
			}
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
		double type=rand()%35;
		//cout<<type<<endl;
		Point3D initialPoint; 
		initialPoint.x=GetRandomGLfloat(0.0, 1.0);
		initialPoint.z=lastZ+rand()%3+0.1;
		switch((int)sqrt(type))
		{
			case 1:
			{
				Point3D p1=road->GetOnRoadPosition(Point3D(-1, 0, initialPoint.z), 0.0);
				Point3D p2=road->GetOnRoadPosition(Point3D(-1, 0, initialPoint.z+0.3), 0.0);
				Point3D p3=road->GetOnRoadPosition(Point3D(1, 0, initialPoint.z+0.3), 0.0);
				Point3D p4=road->GetOnRoadPosition(Point3D(1, 0, initialPoint.z), 0.0);
				Hole* hole=new Hole(mario, p1, p2, p3, p4);
				lastZ=initialPoint.z+0.3;
				obstacles.push_back(hole);

				break;
			}
			case 2:
			{
				AddQuestionBlock(initialPoint, lastZ);
				if(initialPoint.x-5.0/20 > -1.0)
				{
					initialPoint.x-=5.0/20;
					AddQuestionBlock(initialPoint, lastZ);
				}
				/*else
					if(initialPoint.x+5.0/20 < 1.0)
					{
						initialPoint.x+=5.0/20;
						AddQuestionBlock(initialPoint);
					}*/
				break;
			}
			case 3:
			{
				Goomba* goomba=new Goomba();
				goomba->SetTarget(mario);
				Point3D currentPosition=road->GetOnRoadPosition(initialPoint, goomba->width);				
				goomba->Translate(currentPosition);
				lastZ=initialPoint.z+goomba->length/20.0;
				road->AddRoadObject(goomba);
				obstacles.push_back(goomba);
				break;
			}
			case 4:
			{
				InitializeCoins(lastZ);
				break;
			}
			case 5:
			{
				SplitBox* splitBox=new SplitBox(5, 5, 5);
				splitBox->AddCollider();
				Point3D currentPosition=road->GetOnRoadPosition(initialPoint, splitBox->width);
				splitBox->Translate(currentPosition);
				lastZ=initialPoint.z+splitBox->length/20.0;
				road->AddRoadObject(splitBox);
				obstacles.push_back(splitBox);
				break;				
			}
			case 6:
			{
				InitializeRandomBlocks(lastZ);
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
		double type=rand()%25+1.0;
		//cout<<"*******************************************"<<endl;
		Point3D initialPoint; 
		initialPoint.x=GetRandomGLfloat(1.0, 3.0);
		initialPoint.z=lastZ+rand()%2+0.1;
		//cout<<type<<endl;
		switch((int)sqrt(type))
		{
			case 1:
			{
				PlantTulip* plant=new PlantTulip(2,2,2);
				if(initialPoint.x<0)
				{
					initialPoint.x-=plant->width;
					/*initialPoint.x=-1-plant->width/20.0;*/
				}
				else
				{
					initialPoint.x+=plant->width;
					/*initialPoint.x=1+plant->width/20.0;*/
				}
				//plant->SetTarget(mario);
				Point3D currentPosition=road->GetOnRoadPosition(initialPoint, 0.0);
				plant->Translate(currentPosition);
				plant->Scale(Point3D(3, 3, 3));
				lastZ=initialPoint.z/*+plant->length/20*/;
				offRoadObjects.push_back(plant);
				//cout<<"PLANT"<<endl;
				break;				
			}
			case 2:
			{
				int value=rand()%2;
				Point3D currentPosition;
				Point3D fenceDirection;
				if(value==0)
				{
					currentPosition=road->GetLeft()[fenceIndex];
					fenceDirection=(road->GetLeft()[fenceIndex+1]-road->GetLeft()[fenceIndex]);
				}
				else
				{
					fenceDirection=(road->GetRight()[fenceIndex+1]-road->GetRight()[fenceIndex]);
					currentPosition=road->GetRight()[fenceIndex]+(road->GetRight()[fenceIndex]-road->GetLeft()[fenceIndex])*0.075;
				}

				GLfloat fenceWidth=2;

				GLfloat fenceSize=fenceDirection.Magnitude()/(fenceWidth+0.8);

				Fence* fence=new Fence(fenceWidth, 10 , 3, fenceSize);

				fence->Translate(currentPosition);
				GLfloat angle= fenceDirection.AngleBetween(Point3D(0, 0, 1));                                                              
				if(fenceDirection.x < 0)
				{
					angle = -angle;
				}

				fence->Rotate(Point3D(0, angle-90, 0));

				lastZ=initialPoint.z/*+fence->length/20*/;
				offRoadObjects.push_back(fence);
				//cout<<"FENCE"<<endl;
				fenceIndex+=rand()%4;
				break;

			}
			case 3:
			{
				
				Tree*tree=new Tree();
				if(initialPoint.x<0)
				{
					initialPoint.x-=tree->width/20;
				}
				else
				{
					initialPoint.x+=tree->width/20;
				}
				Point3D currentPosition=road->GetOnRoadPosition(initialPoint, 0.0);
				tree->Scale(Point3D(2,2,2));
				tree->Translate(currentPosition);
				lastZ=initialPoint.z/*+tree->length/20*/;
				offRoadObjects.push_back(tree);
				//cout<<"TREE"<<endl;
				break;
			}
			case 4:
			{
				FullMountain* mountain=new FullMountain(200, 200, 200);
				if(initialPoint.x<0)
				{
					initialPoint.x-=mountain->length/20.0+5;
				}
				else
				{
					initialPoint.x+=mountain->length/20.0+5;
				}
				Point3D currentPosition=road->GetOnRoadPosition(initialPoint, 0.0);
				
				mountain->Translate(currentPosition);
				mountain->Rotate(Point3D(0, 180, 0));
				lastZ=initialPoint.z+ mountain->length/20.0;
				offRoadObjects.push_back(mountain);
				//cout<<"MOUNTAIN"<<endl;
				break;
			}
		}

		i=lastZ;

	}
}

void Environment:: AddQuestionBlock(Point3D initialPoint, double& lastZ)
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
	lastZ=initialPoint.z+questionBlock->length/20;
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
	scene->AddObject(sky);
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
