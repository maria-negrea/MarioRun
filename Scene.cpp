#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Render()
{
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glLoadIdentity();

	//Sets the perspective to the perspective of the main camera
	mainCamera->Perspective();

	for(unsigned i=0;i<lightSources.size();++i)
	{
		lightSources[i]->Illuminate();
	}

	//Draws the objects on screen
	for(unsigned i=0;i<sceneObjects.size();++i)
	{
		sceneObjects[i]->Draw();
	}
	glFlush();

}

void Scene::Update()
{
	for(unsigned i=0;i<updateObjects.size();++i)
	{
		updateObjects[i]->Update();
	}
}

void Scene::RemoveUpdatable(Updatable* object)
{
	for (unsigned i=0; i<updateObjects.size(); ++i)
	{
		if(updateObjects[i] == object)
		{
			updateObjects.erase(updateObjects.begin()+i);
			break;
		}
	}
}

void Scene::SetMainCamera(Camera* camera)
{
	mainCamera = camera;
}

void Scene::AddObject(WorldObject* object)
{
	sceneObjects.push_back(object);
	AddSpecialObject(object);
}

void Scene::AddSpecialObject(WorldObject* object)
{
	Updatable* updatableObject = dynamic_cast<Updatable*>(object);
	if(updatableObject != NULL)
	{
		updateObjects.push_back(updatableObject);
	}

	Omi* omi = dynamic_cast<Omi*>(object);

	if(omi != NULL)
	{
		lightSources.push_back(omi);
	}

	for(int i=0;i<object->ChildrenCount();++i)
	{
		AddSpecialObject(object->GetChild(i));
	}
}

void Scene::RemoveObject(WorldObject* object)
{
	for (unsigned i=0; i<sceneObjects.size(); ++i)
	{
		if(sceneObjects[i] == object)
		{
			sceneObjects.erase(sceneObjects.begin()+i);
			break;
		}
	}

	Updatable* updatableObject = dynamic_cast<Updatable*>(object);
	if(updatableObject != NULL)
	{
		RemoveUpdatable(updatableObject);
	}
}