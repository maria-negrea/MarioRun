#include "Scene.h"
#include "Box.h"
#include "Mario.h"
#include "Textures.h"

Scene *scene;
Camera* mainCamera;
Mario* mario;
Omi* omi;

void Initialize() 
{
	scene = new Scene();
	
	Box* pelvis = new Box(1,0.5,1);
	mario = new Mario();
	mario->AddChild(pelvis);
	
	Box* neck = new Box(0.25,0.25,0.25);
	Box* head = new Box(1,1,1);
	head->Rotate(Point3D(0,0,0));
	Box* body = new Box(1,1,1);

	pelvis->AddAnimationStep(AnimationStep(1.5,Point3D(0,20,0)));
	pelvis->AddAnimationStep(AnimationStep(1.5,Point3D(0,-20,0)));

	Box* upperLegRight = new Box(0.4,0.5,0.4);
	upperLegRight->Rotate(Point3D(180,0,0));

	upperLegRight->AddAnimationStep(AnimationStep(1.5,Point3D(290,0,0)));
	upperLegRight->AddAnimationStep(AnimationStep(1.5,Point3D(80,0,0)));

	Box* lowerLegRight = new Box(0.4,0.5,0.4);

	lowerLegRight->AddAnimationStep(AnimationStep(1.5,Point3D(-40,0,0)));
	lowerLegRight->AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0)));

	Box* rightFoot = new Box(0.4,0.25,0.5);

	rightFoot->AddAnimationStep(AnimationStep(1.5,Point3D(50,0,0)));
	rightFoot->AddAnimationStep(AnimationStep(1.5,Point3D(-50,0,0)));

	Box* upperLegLeft = new Box(0.4,0.5,0.4);
	upperLegLeft->Rotate(Point3D(180,0,0));


	upperLegLeft->AddAnimationStep(AnimationStep(1.5,Point3D(80,0,0)));
	upperLegLeft->AddAnimationStep(AnimationStep(1.5,Point3D(290,0,0)));

	Box* lowerLegLeft = new Box(0.4,0.5,0.4);

	lowerLegLeft->AddAnimationStep(AnimationStep(1.5,Point3D(-40,0,0)));
	lowerLegLeft->AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0)));

	Box* leftFoot = new Box(0.4,0.25,0.5);

	leftFoot->AddAnimationStep(AnimationStep(1.5,Point3D(50,0,0)));
	leftFoot->AddAnimationStep(AnimationStep(1.5,Point3D(-50,0,0)));


	pelvis->AddChild(body);
	body->Translate(Point3D(0,1,0));
	body->AddChild(neck);
	neck->Translate(Point3D(0,2,0));
	neck->AddChild(head);
	head->Translate(Point3D(0,0.5,0));

	pelvis->AddChild(upperLegRight);
	upperLegRight->Translate(Point3D(0.5,0.0,0));	
	upperLegRight->AddChild(lowerLegRight);
	lowerLegRight->Translate(Point3D(0,1.1,0));
	lowerLegRight->AddChild(rightFoot);
	rightFoot->Translate(Point3D(0,1.1,0.125));

	pelvis->AddChild(upperLegLeft);
	upperLegLeft->Translate(Point3D(-0.5,0.0,0));	
	upperLegLeft->AddChild(lowerLegLeft);
	lowerLegLeft->Translate(Point3D(0,1.1,0));
	lowerLegLeft->AddChild(leftFoot);
	leftFoot->Translate(Point3D(0,1.1,0.125));


	omi = new Omi(GL_LIGHT1);
	mario->AddChild(omi);

	mario->Translate(Point3D(0,0,30));

	mainCamera = new Camera();
	scene->SetMainCamera(mainCamera);
	scene->AddObject(omi);
	scene->AddObject(mario);

	Textures::GetInstance()->LoadGLTextures();

	glEnable(GL_TEXTURE_2D);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glEnable(GL_BLEND);

	//glEnable(GL_LIGHTING);

	glEnable(GL_DEPTH_TEST);
}

void Draw()
{
	scene->Render();
}

void Timer(int value)
{
	scene->Update();

    glutPostRedisplay();
    glutTimerFunc(30, Timer, 0);
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 0.1, 1000.0);
}


void specialKey(int key, int x, int y)
{ 

	switch(key) 
	{
		case GLUT_KEY_RIGHT :
			mario->Rotate(Point3D(0,10,0));
			break;
		case GLUT_KEY_LEFT :
			mario->Rotate(Point3D(0,-10,0));
			break;
		case GLUT_KEY_UP :
			mario->Rotate(Point3D(0,0,10));
			break;
		case GLUT_KEY_DOWN :
			mario->Rotate(Point3D(0,0,-10));
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
	glutTimerFunc(30, Timer, 0);
	glutReshapeFunc(reshape);
	glutMainLoop();

	return 0;
}