#include "Scene.h"
#include "Collider.h"
#include "OnRoadObject.h"
#include <algorithm> 

Scene::Scene()
{
	predraw = 5;
}

Scene::~Scene()
{
}

bool SortByDepth(Cutout* a,Cutout* b)
{
	return a->GetDepth() > b->GetDepth();
}

void Scene::Render()
{
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glLoadIdentity();

	//Sets the perspective to the perspective of the main camera
	mainCamera->Perspective();

	/*for(unsigned i=0;i<lightSources.size();++i)
	{
		lightSources[i]->Illuminate();
	}*/

	for(unsigned i = 0; i < predraw; i++)
		sceneObjects[i]->Draw();

	 //Draws the objects on screen
	for(unsigned i = predraw; i<sceneObjects.size(); ++i)
	{
		if((mainCamera->GetTranslate() - sceneObjects[i]->GetTranslate()).Magnitude() < 1000 * (sceneObjects[i]->width + 0.1))
			sceneObjects[i]->Draw();
	}

	sort(cutouts.begin(), cutouts.end(), SortByDepth); 
	//cout<<cutouts.size()<<endl;
	for(unsigned i = 3; i<cutouts.size(); ++i)
	{
		 if(cutouts[i]->GetDepth() < 400)
			cutouts[i]->DrawCutout();
		 else
			cutouts.erase(cutouts.begin()+i);
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

void Scene::DeleteUntil(WorldObject* untilObject)
{
	OnRoadObject* mario = dynamic_cast<OnRoadObject*>(untilObject);

	for(int i = predraw+1; i < sceneObjects.size(); i++)
	{
		OnRoadObject* obj = dynamic_cast<OnRoadObject*>(sceneObjects[i]);

		if(obj != NULL)
		{
			if(obj->GetIndex() < 1)
			{
				RemoveObject(sceneObjects[i]);
			}
		}
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

void Scene::RemoveCutout(Cutout* cutout)
{
	for (unsigned i=0; i<cutouts.size(); ++i)
	{
		if(cutouts[i] == cutout)
		{
			cutouts.erase(cutouts.begin()+i);
			break;
		}
	}
}

void Scene::RemoveCollider(WorldObject* object)
{
	for (unsigned i=0; i<colliders.size(); ++i)
	{
		if(colliders[i] == object)
		{
			colliders.erase(colliders.begin()+i);
			break;
		}
	}
}


void Scene::SetMainCamera(Camera* camera)
{
	mainCamera = camera;

	Updatable* updatableObject = dynamic_cast<Updatable*>(camera);
	if(updatableObject != NULL)
	{
		updateObjects.push_back(updatableObject);
	}
}

void Scene::AddObject(WorldObject* object)
{
	object->SetScene(this);

	Cutout* cutout = dynamic_cast<Cutout*>(object);
	if(cutout == NULL)
	{
		sceneObjects.push_back(object);
	}
	else
	{
		cutouts.push_back(cutout);
	}
	AddSpecialObject(object);
}

void Scene::AddSpecialObject(WorldObject* object)
{
	Updatable* updatableObject = dynamic_cast<Updatable*>(object);
	if(updatableObject != NULL)
	{
		updateObjects.push_back(updatableObject);
	}

	if(object->HasCollider())
	{
		colliders.push_back(object);
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
	Cutout* cutout = dynamic_cast<Cutout*>(object);
	if(cutout == NULL)
	{
		for (unsigned i=0; i<sceneObjects.size(); ++i)
		{
			if(sceneObjects[i] == object)
			{
				sceneObjects.erase(sceneObjects.begin()+i);
				break;
			}
		}
	}
	else
	{
		//cout<<"Q";
		RemoveCutout(cutout);
	}
	Updatable* updatableObject = dynamic_cast<Updatable*>(object);
	if(updatableObject != NULL)
	{
		RemoveUpdatable(updatableObject);
	}

	if(object->HasCollider())
	{
		RemoveCollider(object);
	}
}

Camera* Scene::GetCamera() {
	return mainCamera;
}

void Scene::CollisionCheck(WorldObject* object,Point3D direction)
{
	for(unsigned i=0;i<colliders.size();++i)
	{
		if(object != colliders[i] && (object->GetTranslate() - colliders[i]->GetTranslate()).Magnitude() < 10)
		{
			Collision collision = colliders[i]->GetCollider()->Check(object);
			if(collision.IsCollision())
			{
				collision.SetDirection(direction);
				object->GetCollider()->Affected(collision);
			}
		}
	}
}
