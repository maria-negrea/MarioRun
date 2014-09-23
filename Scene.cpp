#include "Scene.h"
#include "Collider.h"

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
	
	//LIGHTING
	glDisable (GL_LIGHTING);
	Point3D pos = sceneObjects[0]->GetTranslate() + sceneObjects[0]->GetForward()*50;
	GLfloat light_position[] = { pos.x, 5.0, pos.z, 1.0};
	glLightfv (GL_LIGHT0, GL_POSITION, light_position);
	glEnable (GL_LIGHTING);
	
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
	sceneObjects.push_back(object);
	object->SetScene(this);
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
	for (unsigned i=0; i<sceneObjects.size(); ++i)
	{
		if(sceneObjects[i] == object)
		{
			sceneObjects.erase(sceneObjects.begin()+i);
			
		cout<<"Removed"<<endl;
			break;
		}
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
		if(object != colliders[i])
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
