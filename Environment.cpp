#include "Environment.h"
#include "Skin.h"
#include "Coin.h"
#include "QuestionBlock.h"
#include<fstream>

Environment::Environment()
{
	count=0;
	sky=new Sky(30000);
	score=new Score();
	mario = new Mario(this);

	snowMan=new SnowMan();
	snowMan->Translate(Point3D(0, 0, 10));	

	road = new Road();
	road->AddRoadObject(mario);

	scene = new Scene();
	mainCamera = new MarioCamera(mario);
	scene->SetMainCamera(mainCamera);

	scene->AddObject(score);
	scene->AddObject(road);
	scene->AddObject(new Ground);
	scene->AddObject(sky);
	//scene->AddObject(particles);
	scene->AddObject(mario);

	ClearFiles();
	InitializeObstacles(2.0, 29);
	InitializeOffRoadObjects(2.0, 29);
}

void Environment:: InitializeCoins(double& lastZ)
{
	GLfloat groupX = GetRandomGLfloat(0.0, 1.0);
	Point3D initialPoint; 
	initialPoint.x=groupX;

	double step=PI/10.0;
	int value=rand()%2;
	if(lastZ + (1.5 / 20)<road->GetRoadSize())
	{
		for(int i = 0; i < 10; i++)
		{
			Coin *newCoin = new Coin(0.5, 0.5, 0.1);
			initialPoint.z=lastZ + 1.5 / 20;
			lastZ=initialPoint.z+newCoin->width/40.0;
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

			std::ofstream outfile;
			outfile.open("CoinsCoordinates.cpp", std::ios_base::app);
			outfile << initialPoint<<"              "<<count<<endl;
			outfile.close();
			
			newCoin->Translate(currentPosition);
			newCoin->Scale(Point3D(5.0, 5.0, 5.0));
			newCoin->AddCollider();
			road->AddRoadObject(newCoin);
			scene->AddObject(newCoin);
			//obstacles.push_back(newCoin);
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
	
	if(lastZ+stepZ<road->GetRoadSize())
	{
		for(int i = 0; i < 4; i++)
		{
			initialPoint.z=lastZ;
 			int value=rand()%2;
			if(value==0)
			{
				AddQuestionBlock(initialPoint, lastZ);
				lastZ+=stepZ;
			}

			else
			{
				SplitBox* splitBox=new SplitBox(5, 5, 5);
				splitBox->AddCollider();
				Point3D currentPosition=road->GetOnRoadPosition(initialPoint, splitBox->width);
				currentPosition.y=12.0;
				splitBox->Translate(currentPosition);
				lastZ+=stepZ;
				road->AddRoadObject(splitBox);
				scene->AddObject(splitBox);
				//obstacles.push_back(splitBox);
			}
		}
		
	}
}

void Environment::AddObject(WorldObject *obj) {
	scene->AddObject(obj);
}

void Environment::InitializeObstacles(double firstLimit, double lastLimit)
{
	//obstacles.clear();
	double lastZ=firstLimit;

	while(firstLimit<lastLimit)
	{
		double type = rand() % 48 + 1;
		//cout<<type<<endl;
		Point3D initialPoint; 
		initialPoint.x = GetRandomGLfloat(0.0, 1.0);
		initialPoint.z = lastZ+ 0.9;

		switch((int)sqrt(type))
		{
			case 1:
			{
				//if((int)type%2==0)
				//{
				//	Point3D p1=road->GetOnRoadPosition(Point3D(-1, 0, initialPoint.z), 0.0);
				//	Point3D p2=road->GetOnRoadPosition(Point3D(-1, 0, initialPoint.z+0.3), 0.0);
				//	Point3D p3=road->GetOnRoadPosition(Point3D(1, 0, initialPoint.z+0.3), 0.0);
				//	Point3D p4=road->GetOnRoadPosition(Point3D(1, 0, initialPoint.z), 0.0);
				//	Hole* hole=new Hole(mario, p1, p2, p3, p4);
				//	lastZ=initialPoint.z+0.4;
				//	scene->AddObject(hole);
				//	road->AddRoadObject(hole);
				//	//obstacles.push_back(hole);

				//	std::ofstream outfile;
				//	outfile.open("HoleCoordinates.cpp", std::ios_base::app);
				//	outfile << initialPoint<<"           "<<count<<endl;	
				//	outfile.close();
				//}
				break;
			}
			case 2:
			{
				InitializeRandomBlocks(lastZ);				
				break;
			}
			case 3:
			{
				if((int)type%2==0)
				{
					Goomba* goomba=new Goomba();
					goomba->SetTarget(mario);
					Point3D currentPosition=road->GetOnRoadPosition(initialPoint, goomba->width);				
					goomba->Translate(currentPosition);
					lastZ=initialPoint.z+goomba->length/20.0;
					road->AddRoadObject(goomba);
					scene->AddObject(goomba);
					//obstacles.push_back(goomba);
					break;
				}
				
			}
			case 4:
			{
 				InitializeCoins(lastZ);
				break;
			}
			case 5:
			{
				GLfloat size=5.0;
				SplitBox* splitBox=new SplitBox(size, 5, size);
				splitBox->AddCollider();
				Point3D currentPosition=road->GetOnRoadPosition(initialPoint, splitBox->width);
				splitBox->Translate(currentPosition);
				lastZ = initialPoint.z+splitBox->length/20.0;
				road->AddRoadObject(splitBox);
				scene->AddObject(splitBox);

				std::ofstream outfile;
				outfile.open("SplitBoxCoordinates.cpp", std::ios_base::app);
				outfile << initialPoint<<"           "<<count<<endl;				
				outfile.close();
				//obstacles.push_back(splitBox);
				break;				
			}
			case 6:
			{
				AddQuestionBlock(initialPoint, lastZ);
				if(initialPoint.x-5.0/20 > -1.0)
				{
					initialPoint.x-=5.0/20;
					AddQuestionBlock(initialPoint, lastZ);
				}
				break;
			}
		}
		firstLimit=lastZ;
	}
}

void Environment:: InitializeOffRoadObjects(double firstLimit, double lastLimit)
{
	double lastZ=firstLimit;
	int fenceIndex=rand()%3;
	while(firstLimit<lastLimit)
	{
		double type=rand()%49+1.0;
		//cout<<"*******************************************"<<endl;
		Point3D initialPoint; 
		
		initialPoint.z=lastZ+0.3;
		//cout<<type<<endl;
		switch((int)sqrt(type))
		{
			case 1:
			{
				initialPoint.x=GetRandomGLfloat(1.0, 3.0);
				Pipe* pipe=new Pipe(scene, 1,3,1);
				pipe->Scale(Point3D(1, 1, 1));
				if(initialPoint.x<0)
				{
					initialPoint.x=-1-pipe->width/20.0;
				}
				else
				{
					initialPoint.x=1+pipe->width/20.0;
				}
				pipe->SetTarget(mario);
				Point3D currentPosition=road->GetOnRoadPosition(initialPoint, 0.0);
				pipe->Translate(currentPosition);
				
				lastZ=initialPoint.z+pipe->length/20.0;
				pipe->index=initialPoint.z;
				scene->AddObject(pipe);
				offRoadObjects.push_back(pipe);
				cout<<"PLANT"<<endl;
				std::ofstream outfile;
				outfile.open("PipeCoordinates.cpp", std::ios_base::app);
				outfile << initialPoint<<"           "<<count<<endl;	
				outfile.close();
				break;				
			}
			case 2:
			{
				initialPoint.x=GetRandomGLfloat(2.5, 3.5);
				FullMountain* mountain=new FullMountain(100, 100, 100);
				if(initialPoint.x<0)
				{
					initialPoint.x-=mountain->width/20.0;
				}
				else
				{
					initialPoint.x+=mountain->width/20.0;
				}
				Point3D currentPosition=road->GetOnRoadPosition(initialPoint, 0.0);
				
				mountain->Translate(currentPosition);
				mountain->Rotate(Point3D(0, 180, 0));
				lastZ=initialPoint.z+ mountain->length/20.0;
				scene->AddObject(mountain);
				mountain->index=initialPoint.z;
				offRoadObjects.push_back(mountain);
				std::ofstream outfile;
				outfile.open("MountainCoordinates.cpp", std::ios_base::app);
				outfile << initialPoint<<"           "<<count<<endl;	
				outfile.close();
				//cout<<"MOUNTAIN"<<endl;
				break;

			}
			case 3:
			{
				initialPoint.x=GetRandomGLfloat(1.5, 2.0);
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
				lastZ=initialPoint.z+tree->length/20.0;
				scene->AddObject(tree);
				tree->index=initialPoint.z;
				offRoadObjects.push_back(tree);
				std::ofstream outfile;
				outfile.open("TreeCoordinates.cpp", std::ios_base::app);
				outfile << initialPoint<<"           "<<count<<endl;	
				outfile.close();
				//cout<<"TREE"<<endl;
				break;
			}
			case 4:
			{
				initialPoint.x=GetRandomGLfloat(1.0, 3.0);
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

				GLfloat fenceWidth=1;
				GLfloat fenceSize=fenceDirection.Magnitude()/(fenceWidth+0.8);
				GLfloat fenceLength=3;

				Fence* fence=new Fence(fenceWidth, 10 , fenceLength, fenceSize);

				fence->Translate(currentPosition);
				GLfloat angle= fenceDirection.AngleBetween(Point3D(0, 0, 1));                                                              
				if(fenceDirection.x < 0)
				{
					angle = -angle;
				}

				fence->Rotate(Point3D(0, angle-90, 0));

				lastZ=initialPoint.z+(fence->width*fenceSize)/20.0;
				scene->AddObject(fence);
				fence->index=initialPoint.z;
				offRoadObjects.push_back(fence);
				std::ofstream outfile;
				outfile.open("FenceCoordinates.cpp", std::ios_base::app);
				outfile << initialPoint<<"           "<<count<<endl;	
				outfile.close();
				//cout<<"FENCE"<<endl;
				fenceIndex+=rand()%4;
				break;
			}
			default:
			{
				lastZ+=0.6;
			}
		}

		firstLimit=lastZ;
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
	questionBlock->SetTranslate(currentPosition);
	scene->AddObject(questionBlock);
	//obstacles.push_back(questionBlock);
	/*lastZ += 0.1;*/
	lastZ=initialPoint.z+questionBlock->length/20.0;

	std::ofstream outfile;
	outfile.open("QuestionBlockCoordinates.cpp", std::ios_base::app);
	outfile << initialPoint<<"           "<<count<<endl;	
	outfile.close();
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
	//scene->AddObject(game);
	//scene->AddObject(score);
	//scene->AddObject(road);
	//scene->AddObject(new Ground);
	//scene->AddObject(sky);
	//scene->AddObject(particles);
	//scene->AddObject(mario);
    //scene->AddObject(goomba);
//	scene->AddObject(goomba);

	/*for(int i = 0; i < obstacles.size(); i++)
		scene->AddObject(obstacles[i]);
	for(int i = 0; i < offRoadObjects.size(); i++)
		scene->AddObject(offRoadObjects[i]);*/


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

void Environment:: GenerateEnvironment()
{
	count++;
	cout<<"**************************************************************"<<count<<endl;
	cout<<"-----------------------------------------------"<<offRoadObjects.size()<<endl;
	InitializeObstacles(29, 30);
	InitializeOffRoadObjects(29, 30);
	for(int i=0;i<offRoadObjects.size();i++)
	{
		offRoadObjects[i]->index--;
		if(offRoadObjects[i]->index==0)
		{
			offRoadObjects.erase(offRoadObjects.begin()+i);
			cout<<"Q"<<endl;
			i--;
		}
	}
}

void Environment:: ClearFile(char* fileName)
{
	std::ofstream outfile;
	outfile.open(fileName, std::fstream::out);
	outfile <<"";
	outfile.close();
}

void Environment:: ClearFiles()
{
	ClearFile("TreeCoordinates.cpp");
	ClearFile("MountainCoordinates.cpp");
	ClearFile("FenceCoordinates.cpp");
	ClearFile("QuestionBlockCoordinates.cpp");
	ClearFile("SplitBoxCoordinates.cpp");
	ClearFile("PipeCoordinates.cpp");
	ClearFile("CoinsCoordinates.cpp");
	ClearFile("HoleCoordinates.cpp");
}

Environment::~Environment(void)
{

}


