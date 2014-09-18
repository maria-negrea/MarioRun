#include "Scene.h"
#include"Plant.h"

#include "Box.h"
#include "Mario.h"
#include "MarioCamera.h"
#include "Textures.h"
#include "Goomba.h"
#include "Foot.h"
#include "Torso.h"
#include "Head.h"
#include "Ground.h"
#include "QuestionBlock.h"
#include "Tree.h"

Scene *scene;
Camera* mainCamera;
Goomba* goomba;
Goomba* goomba2;
Goomba* goomba3;
Mario* mario;
Box* test1;
Tree* tree;
QuestionBlock *block;

Point3D GetSquareOutside(Point3D pointIn, GLfloat angle)
{
	GLfloat complementAngle=90.0-angle;
	Point3D outside;
	GLfloat l1=pointIn.x*sin(angle*PI/180), l2=pointIn.z*cos(complementAngle*PI/180);
	outside.x=l1+l2;
	outside.z=pointIn.z*sin(complementAngle*PI/180)+pointIn.x*cos(angle*PI/180);
	outside.y=0;

	return outside;
}

void Initialize() 
{
	scene = new Scene();

	block = new QuestionBlock(2,2,2);
	block->Rotate(Point3D(0,-90,0));
	block->Translate(Point3D(0,5,20));
	
	Omi* omi = new Omi(GL_LIGHT1);
	block->AddChild(omi);
	omi->Translate(Point3D(0,1,0));

	/*scene->AddObject(block);*/

	mario = new Mario();
	mario->Translate(Point3D(0,0,30));

	mainCamera = new MarioCamera(mario);
	mainCamera->Translate(Point3D(0,10,0));
	scene->SetMainCamera(mainCamera);
	/*scene->AddObject(new Ground);*/
	/*scene->AddObject(mario);*/
	goomba=new Goomba();
	/*goomba->SetTarget(mario);*/
	goomba->Translate(Point3D(-5, 0, 20));
	scene->AddObject(goomba);
	tree=new Tree();
	tree->Translate(Point3D(-5, 0, 40));
	scene->AddObject(tree);
	
	/*test1 = new Box(2,2,10);
	test1->Translate(Point3D(0.0, 1.0, 90.0));
	test1->AddCollider();
	scene->AddObject(test1);*/
	
	Textures::GetInstance()->LoadGLTextures();
	glEnable(GL_TEXTURE_2D);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glEnable(GL_BLEND);
	
//	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//	glEnable(GL_LIGHTING);

	Textures::GetInstance()->LoadGLTextures();

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
		/*case GLUT_KEY_LEFT:
			mario->MoveLeft();
			break;
		case GLUT_KEY_RIGHT:
			mario->MoveRight();
			break;
		case GLUT_KEY_F1:
			block->Hit();
			mario->Jump();
			break;*/

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

	cout<<GetSquareOutside(Point3D(1, 1, 1), 45).x<<" "<<GetSquareOutside(Point3D(1, 1, 1), 45).y<<" "<<
		GetSquareOutside(Point3D(1, 1, 1), 30).z<<endl;

	glutSpecialFunc(specialKey);
	glutTimerFunc(30, Timer, 0);
	glutReshapeFunc(reshape);
	glutMainLoop();

	return 0;
}