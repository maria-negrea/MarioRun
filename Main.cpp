#include "Scene.h"
#include "Box.h"
#include "Mario.h"
#include "MarioCamera.h"
#include "Textures.h"
#include "Ground.h"
#include "Body.h"
#include "Coin.h"
#include "Particles.h"


Scene *scene;
Camera* mainCamera;
Mario* mario;
Omi* omi;
Coin *coin ;
Particles *particles = new Particles();
bool collision = false;
int score = 0;
void Initialize() 
{
	scene = new Scene();
	
	Box* pelvis = new Box(1,0.5,1);
	coin = new Coin();
	mario = new Mario();
	pelvis->Translate(Point3D(0,2.5,0));
	mario->AddChild(pelvis);
	
	Box* neck = new Box(0.25,0.25,0.25);
	Box* head = new Box(1,1,1);
	head->Rotate(Point3D(0,0,0));
	Box* body = new Box(1,1,1);

	pelvis->AddAnimationStep(AnimationStep(1.5,Point3D(0,200,0)));
	pelvis->AddAnimationStep(AnimationStep(1.5,Point3D(0,160,0)));

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

	mainCamera = new MarioCamera(mario);
	mainCamera->Translate(Point3D(0,10,0));
	scene->SetMainCamera(mainCamera);
	scene->AddObject(omi);
	//scene->AddObject(new Ground);
	//scene->AddObject(coin);
	
	//scene->AddObject(mario);
	
	Textures::GetInstance()->LoadGLTextures();
	
	coin->Translate(Point3D(0.0, 6.0, 60.0));
	coin->Scale(Point3D(5.0, 5.0, 5.0));
	
	scene->AddObject(particles);
	particles->Translate(mario->GetTranslate() + mario->GetForward()*10);

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
	vector<Point3D> res = coin->GetBoundingBox();
	vector<Point3D> res2= mario->GetBoundingBox();
	//cout<<score<<endl;
	collision = Collider::check(res, res2);
	if(collision == true) {
		scene->RemoveObject(coin);
		coin = new Coin();
		scene->AddObject(coin);
		coin->Translate(mario->GetTranslate() + mario->GetForward()*30 + Point3D(0.0, 6.0, 0.0));
		coin->Scale(Point3D(5.0, 5.0, 5.0));
		score += 10;
	}
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
			particles->Rotate(Point3D(0.0, 3.0, 0.0));
			break;
		case GLUT_KEY_LEFT :
			particles->Rotate(Point3D(0.0, -3.0, 0.0));
			break;
		case GLUT_KEY_UP:
			particles->Rotate(Point3D(0.0, 0.0, 3.0));
			break;
		case GLUT_KEY_DOWN:
			particles->Rotate(Point3D(0.0, 0.0, -3.0));
			break;
		case GLUT_KEY_F1:
			mario->Jump();
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