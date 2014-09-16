#include "Scene.h"
#include"Mushroom.h"
#include"Textures.h"
#include"Box.h"
#include"Plant.h"
//Textures* Textures::instance = NULL;
Scene *scene;
Camera* mainCamera;
//Mushroom* newMushroom=new Mushroom(0.5,0.5,0.5);
Box* newBox=new Box(0.5,0.5,0.5);
Plant *newPlant=new Plant(0.5,0.5,0.5);


void Initialize() 
{
	scene = new Scene();
	//scene->AddObject(newBox);
    //newBox->Translate(Point3D(0,0,2));

	scene->AddObject(newPlant);
	newPlant->Translate(Point3D(0,0,2));

	mainCamera = new Camera();
	mainCamera->Translate(Point3D(0,1,0));
	scene->SetMainCamera(mainCamera);
	
	Textures::GetInstance()->LoadGLTextures();

	glEnable(GL_DEPTH_TEST); 
	glEnable(GL_TEXTURE_2D);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glEnable(GL_BLEND);
	//glEnable(GL_LIGHTING);
}

void Draw()
{
	scene->Render();
}

void Timer(int value)
{//glTranslatef(0,0,-2);

	scene->Update();
	newPlant->Rotate(Point3D(0,2,0));
    glutPostRedisplay();
    glutTimerFunc(30, Timer, 0);
}
// random comm
void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 0.1, 1000.0);
}


void specialKey(int key, int x, int y)
{

	scene->Update();
	 
switch(key)
   {
     case GLUT_KEY_UP :
		
		 newBox->Hit();
         
        break;
    }
	glutPostRedisplay();
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(768, 768);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Mario");
	Initialize();
	glutDisplayFunc(Draw);

	glutSpecialFunc(specialKey);
//	glutTimerFunc(30, Timer, 0);
	glutReshapeFunc(reshape);
	glutMainLoop();

	return 0;
}