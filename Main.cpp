#include "Scene.h"
#include "Box.h"
#include "Mario.h"
#include "MarioCamera.h"
#include "Textures.h"
#include "Goomba.h"
#include "Foot.h"
#include "Torso.h"
#include "Head.h"
#include "Ground.h"
#include "Body.h"

Scene *scene;
Camera* mainCamera;
Goomba* goomba;
Mario* mario;
Omi* omi;
Box* test1;

void Initialize() 
{
	scene = new Scene();
	
	/*Box* pelvis = new Box(1,0.5,1);
	mario = new Mario();
	pelvis->Translate(Point3D(0,2.5,0));
	mario->AddChild(pelvis);
	
	Box* neck = new Box(0.25,0.25,0.25);
	Box* head = new Box(1,1,1);
	head->Rotate(Point3D(0,0,0));
	Box* body = new Box(1,1,1);

	pelvis->AddAnimationStep(AnimationStep(1.5,Point3D(0,200,0),pelvis->GetTranslate()));
	pelvis->AddAnimationStep(AnimationStep(1.5,Point3D(0,160,0),pelvis->GetTranslate()));

	Box* upperLegRight = new Box(0.4,0.5,0.4);
	upperLegRight->Rotate(Point3D(180,0,0));
	upperLegRight->Translate(Point3D(0.5,0.0,0));	

	upperLegRight->AddAnimationStep(AnimationStep(1.5,Point3D(290,0,0),upperLegRight->GetTranslate()));
	upperLegRight->AddAnimationStep(AnimationStep(1.5,Point3D(80,0,0),upperLegRight->GetTranslate()));

	Box* lowerLegRight = new Box(0.4,0.5,0.4);
	lowerLegRight->Translate(Point3D(0,1.1,0));

	lowerLegRight->AddAnimationStep(AnimationStep(1.5,Point3D(-40,0,0),lowerLegRight->GetTranslate()));
	lowerLegRight->AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),lowerLegRight->GetTranslate()));

	Box* rightFoot = new Box(0.4,0.25,0.5);
	rightFoot->Translate(Point3D(0,1.1,0.125));

	rightFoot->AddAnimationStep(AnimationStep(1.5,Point3D(50,0,0),rightFoot->GetTranslate()));
	rightFoot->AddAnimationStep(AnimationStep(1.5,Point3D(-50,0,0),rightFoot->GetTranslate()));

	Box* upperLegLeft = new Box(0.4,0.5,0.4);
	upperLegLeft->Rotate(Point3D(180,0,0));
	upperLegLeft->Translate(Point3D(-0.5,0.0,0));	

	upperLegLeft->AddAnimationStep(AnimationStep(1.5,Point3D(80,0,0),upperLegLeft->GetTranslate()));
	upperLegLeft->AddAnimationStep(AnimationStep(1.5,Point3D(290,0,0),upperLegLeft->GetTranslate()));

	Box* lowerLegLeft = new Box(0.4,0.5,0.4);
	lowerLegLeft->Translate(Point3D(0,1.1,0));

	lowerLegLeft->AddAnimationStep(AnimationStep(1.5,Point3D(-40,0,0),lowerLegLeft->GetTranslate()));
	lowerLegLeft->AddAnimationStep(AnimationStep(1.5,Point3D(0,0,0),lowerLegLeft->GetTranslate()));

	Box* leftFoot = new Box(0.4,0.25,0.5);
	leftFoot->Translate(Point3D(0,1.1,0.125));*/

	mainCamera = new Camera();
	goomba=new Goomba();
	goomba->Translate(Point3D(0,0,10));
	//foot=new Foot();
	//torso=new Torso();
	//head=new Head();
	/*torso->Translate(Point3D(0,0,10));
	head->Translate(Point3D(0,0,10));
	foot->Translate(Point3D(0,0,9));*/
	scene->SetMainCamera(mainCamera);
	scene->AddObject(goomba);

	Textures::GetInstance()->LoadGLTextures();

	glEnable(GL_DEPTH_TEST);

	/*leftFoot->AddAnimationStep(AnimationStep(1.5,Point3D(50,0,0),leftFoot->GetTranslate()));
	leftFoot->AddAnimationStep(AnimationStep(1.5,Point3D(-50,0,0),leftFoot->GetTranslate()));


	pelvis->AddChild(body);
	body->Translate(Point3D(0,1,0));
	body->AddChild(neck);
	neck->Translate(Point3D(0,2,0));
	neck->AddChild(head);
	head->Translate(Point3D(0,0.5,0));

	pelvis->AddChild(upperLegRight);
	upperLegRight->AddChild(lowerLegRight);
	lowerLegRight->AddChild(rightFoot);

	pelvis->AddChild(upperLegLeft);
	upperLegLeft->AddChild(lowerLegLeft);
	lowerLegLeft->AddChild(leftFoot);

	omi = new Omi(GL_LIGHT1);
	mario->AddChild(omi);

	mario->Translate(Point3D(0,0,30));

	mainCamera = new MarioCamera(mario);
	mainCamera->Translate(Point3D(0,10,0));
	scene->SetMainCamera(mainCamera);
	scene->AddObject(omi);
	scene->AddObject(new Ground);
	scene->AddObject(mario);
	
	test1 = new Box(2,2,10);
	test1->Translate(Point3D(0.0, 1.0, 90.0));
	scene->AddObject(test1);
	
	Textures::GetInstance()->LoadGLTextures();*/
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
		goomba->Rotate(Point3D(0,10,0));
		break;
	case GLUT_KEY_LEFT :
		goomba->Rotate(Point3D(0,-10,0));
		break;
	case GLUT_KEY_UP :
		goomba->Rotate(Point3D(10,0,0));
		break;
	case GLUT_KEY_DOWN :
		goomba->Rotate(Point3D(-10,0,0));
		break;

		/*case GLUT_KEY_RIGHT :
		torso->Rotate(Point3D(0,10,0));
		break;
	case GLUT_KEY_LEFT :
		torso->Rotate(Point3D(0,-10,0));
		break;
	case GLUT_KEY_UP :
		torso->Rotate(Point3D(10,0,0));
		break;
	case GLUT_KEY_DOWN :
		torso->Rotate(Point3D(-10,0,0));
		break;*/

	case GLUT_KEY_F1 :
		mainCamera->Translate(Point3D(0.0, 0.0, -1.0));
		break;
	case GLUT_KEY_F2 :
		mainCamera->Translate(Point3D(0.0, 0.0, 1.0));
		break;
	case GLUT_KEY_F3:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
		break;
	case GLUT_KEY_F4:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
		break;
}
	/*switch(key) 
	{
		case GLUT_KEY_RIGHT :
			mario->MoveRight();
			break;
		case GLUT_KEY_LEFT :
			mario->MoveLeft();
			break;
		case GLUT_KEY_F1:
			mario->Jump();
			break;
	}*/
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