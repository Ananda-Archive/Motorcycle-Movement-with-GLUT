/*
	NAMA		:	- Ananda Prabu Tritya Vijaya	(24060117130048)
					- Ramadhan Pratama				(24060117120022)
*/

/*
===============================================================================================================================================
																I N D E X
===============================================================================================================================================

1.0		------------------------------------------	DEKLARASI VARIABEL && HEADER
	1.1		------------------------------------------	LIBRARY
	1.2		------------------------------------------	DEKLARASI VARIABEL
	1.3		------------------------------------------	HEADER
2.0		------------------------------------------	LIGHTING
3.0		------------------------------------------	CAMERA
	3.1		------------------------------------------	MOUSE
	3.2		------------------------------------------	RESHAPE
4.0		------------------------------------------	KEYBOARD
5.0		------------------------------------------	OBJEK
	5.1		------------------------------------------	MOTOR
	5.2		------------------------------------------	ENVIRONMENT
	5.3		------------------------------------------	DISPLAY
6.0		------------------------------------------	MAIN
*/
/*
===============================================================================================================================================
1.0		D E K L A R A S I  V A R I A B E L  & &  H E A D E R
===============================================================================================================================================
*//*
=============== 1.1 L I B R A R Y ===============
*/
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "mmsystem.h"
/*
=============== 1.2 D E K L A R A S I  V A R I A B E L ===============
*/
float	angle = 1.0,
		deltaAngle =.0,
		ratio,
		x = .0f,
		y = .75f,
		z = 25.0f,
		lx = .0f,
		ly = .0f,
		lz = -1.0f;
int		deltaMove = 0,
		h,
		w,
		v = 0,
		b,
		n = -2,
		vv = 0,
		bb,
		nn = 2,
		pp = 60,
		bitMapHeight = 12,
		distance = 12,
		rotateR = 0,
		rotateL = 0,
		kk = 0;
bool	kiri = false,
		kanan = false,
		belok = false,
		reverse = false;

/*
=============== 1.3 H E A D E R ===============
*/
void mouseCallback(int button, int state, int x, int y);
void mouseMotionCallback(int x, int y);
void idleCallback();
void Reshape(int w1, int h1);
void Motor();
void environment();
void keyboard(unsigned char key, int x, int y);
void display();
void lighting();
void init(void);
void exit();
/*
===============================================================================================================================================
2.0		L I G H T I N G
===============================================================================================================================================
*/
void timer(int id){
	if(pp>= 10){
	pp-=2;
	glutPostRedisplay();
	glutTimerFunc(1, timer, 0);
	}
}
const GLfloat light_ambient[] = { 0.5f, 0.5f, 0.5f, 0.0f };
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 0.0f, 20.0f, 10.0f, 1.0f };
const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

void lighting(){
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}
/*
===============================================================================================================================================
3.0		C A M E R A
===============================================================================================================================================
*//*
=============== 3.1	M O U S E ===============
*/
class RenderState{
	public:
		float mouseX,mouseY,cameraX,cameraY,cameraZ,dragX,dragY;
		bool mouseLeftDown, mouseRightDown;
		RenderState (){
		    this->mouseX = 0;
		    this->mouseY = 0;
		    this->dragX = 0;
		    this->dragY = 0;
		    this->mouseLeftDown = false;
		    this->mouseRightDown = false;
		    this->cameraX = 0.0f;
		    this->cameraY = 0.0f;
		    this->cameraZ = -15.0f;
		}
};RenderState rs;

void mouseCallback(int button, int state, int x, int y){
    rs.mouseX = x;
    rs.mouseY = y;

    if(button == GLUT_LEFT_BUTTON){
        if(state == GLUT_DOWN){
            rs.mouseLeftDown = true;
        }else if(state == GLUT_UP){
            rs.mouseLeftDown = false;
        }
    }
    if(button == GLUT_RIGHT_BUTTON){
        if(state == GLUT_DOWN){   
            rs.mouseRightDown = true;
        }else if(state == GLUT_UP){
            rs.mouseRightDown = false;
        }
    }
    if(button == 3){
       rs.cameraZ += 1.0;
    }
    if(button == 4){
        rs.cameraZ -= 1.0;
    }
}

void mouseMotionCallback(int x, int y){
    if(rs.mouseLeftDown){
        rs.cameraY += (x - rs.mouseX);
        rs.cameraX += (y - rs.mouseY);
        rs.mouseX = x;
        rs.mouseY = y;
    }
    if(rs.mouseRightDown){
        rs.dragX += (x - rs.mouseX)/50;
        rs.dragY -= (y - rs.mouseY)/50;
        rs.mouseX = x;
        rs.mouseY = y;
    }
}

void idleCallback(){
    glutPostRedisplay();
}

void init(void){
	glEnable (GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	RenderState *rsp = new RenderState();
  	rs = *rsp;
}
 /*
 =============== 3.2 R E S H A P E ===============
*/
void Reshape(int w1, int h1){
	if(h1 == 0) h1 = 1;
	w = w1;
	h = h1;
	ratio = 1.0f * w / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(95,ratio,0.1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
/*
===============================================================================================================================================
4.0		K E Y B O A R D
===============================================================================================================================================
*/
void keyboard(unsigned char key, int x, int y){
    switch (key){
    	case 'w':
    		if(reverse == true){
    			rotateL = 0;
    			kiri = false;
    			reverse = false;
    			belok = false;
			}
			if((v<14 && n == -2 && rotateL == 0) || (v<14 && n == 2 && rotateR == 0)){
				v+=1;
			}
			if(kiri){
				if(v == 14 && n > -21 && rotateL == 90){
					n -= 1;
				}else{
					if(v >-14 && n == -21 && rotateL == 180){
						v -= 1;
					}else{
						if(v == -14 && n >= -21 && n < -2 && rotateL == 270){
							n += 1;
						}else{
							if(v >= -14 && n == - 2 && v<=0 && rotateL == 360){
								v += 1;
							}
							if( v == -13 && n == -2){
								
								reverse = true;
							}
						}
					}
				}
			}
			if(kanan){
				if(v == 14 && n >=2 && rotateR == -90 && n <24){
					n+=1;
				}
				if(n >= 23){
					PlaySound(TEXT("smb.wav"),NULL,SND_ASYNC);
					timer(20);
				}
			}
			if(v == 14 && n == -21) kiri = false;
			if(v == -14 && n == -21) kiri = false;
			if(v == -14 && n == -2) kiri = false;
			if(v == 0 && n == -2) kiri = false;
			printf("Move to =>\t(\tx: %d\ty: %d\tz: %d\tkk: %d\trotateL: %d\trotateR: %d\t)\n",v,b,n,kk,rotateL,rotateR);
			break;
		case 'a':
			if(n == 2 && !kanan){
				nn = 2;
				n = -2;
			}
			if(rotateL < 90 && v == 14 && n == -2){
				belok = true;
				rotateL += 5;
				kiri = true;
				if(rotateL <= 45){
					kk -= 6;
				}
				if(rotateL > 45){
					kk += 6;
				}
			}
			if(rotateL < 180 && n == -21 && v == 14){
				rotateL += 5;
				kiri = true;
				if(rotateL <= 135){
					kk -= 6;
				}
				if(rotateL > 135){
					kk += 6;
				}
			}
			if(rotateL < 270 && n == -21 && v == -14){
				rotateL += 5;
				kiri = true;
				if(rotateL <= 225){
					kk -= 6;
				}
				if(rotateL > 225){
					kk += 6;
				}
			}
			if(rotateL < 360 && n == -2 && v == -14){
				rotateL += 5;
				kiri = true;
				if(rotateL <= 315){
					kk -= 6;
				}
				if(rotateL > 315){
					kk += 6;
				}
			}
			break;
		case 'd':
			if(!belok){
				n = 2;
				nn = -2;
				if(rotateR > -90 && n == 2 && v == 14){
					rotateR -= 5;
					kanan = true;
					if(rotateR >= -45){
					kk += 6;
					}
					if(rotateR < -45){
						kk -= 6;
					}
				}
			}
			break;			
        default:
        	break;
    }
	glutPostRedisplay();
} 
/*
===============================================================================================================================================
5.0		O B J E K
===============================================================================================================================================
*//*
=============== 5.1	M O T O R ===============
*/
void Motor(){
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	glEnable(GL_LIGHTING);
	glRotatef(0,1,0,0);
	glRotatef(90,0,1,0);
	glRotatef(45,0,0,1);
	glPushMatrix();
		glTranslatef(v,b,n);
		glColor3f(1,0,0);
		glutSolidCube(1);
		glRotatef(rotateL,0,1,0);
		glRotatef(rotateR,0,1,0);
		glPushMatrix();
			glTranslatef(vv,bb,nn);
			glScalef(.3,.3,.3);
			glRotatef(kk,1,0,0);
			//Ban belakang
			glPushMatrix();
				glColor3f(0,0,0);
				glTranslatef(-3.1,-2.5,0);
				glutSolidTorus(0.3,1,50,50);
			glPopMatrix();
			//penyambung antara pipe di roda belakang
			glPushMatrix();
				glColor3f(0,0,0);
				glTranslatef(-3.12,-2.35,-.9);
				gluCylinder(quadratic,0.1f,0.1f,1.8f,320,320);
			glPopMatrix();
			//pipe penyambung stang dan tangki
			glPushMatrix();
				glColor3f(0,0,0);
				glTranslatef(1.28,-.5,0.7);
				glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
				glRotatef(-5.0f, 0.0f, 1.0f, 0.0f);
				gluCylinder(quadratic,0.1f,.1f,1.0f,320,320);
			glPopMatrix();
			//pipe penyambung stang dan tangki
			glPushMatrix();
				glColor3f(0,0,0);
				glTranslatef(1.28,-.5,-0.7);
				glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
				glRotatef(-5.0f, 0.0f, 1.0f, 0.0f);
				gluCylinder(quadratic,0.1f,.1f,1.0f,320,320);
			glPopMatrix();
			//penyambung antara pipe di roda depan
			glPushMatrix();
				glColor3f(0,0,0);
				glTranslatef(1.6,-2.35,-.7);
				gluCylinder(quadratic,0.1f,0.1f,1.4f,320,320);
			glPopMatrix();
			//ban depan
			glPushMatrix();
				glColor3f(0,0,0);
				glTranslatef(1.6,-2.5,0);
				glutSolidTorus(0.3,1,50,50);
			glPopMatrix();
			//tangki bensin
			glPushMatrix();
				glColor3f(1,0,0);
				glScalef(2.5,1,1.2);
				glutSolidCube(1);
			glPopMatrix();
			//tutup tangki bensin
			glPushMatrix();
				glColor3f(0,0,0);
				glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
				glTranslatef(.7,0,.5);
				gluCylinder(quadratic,0.1f,0.1f,.05f,320,320);
			glPopMatrix();
			//dudukan
			glPushMatrix();
				glColor3f(1,0,0);
				glTranslatef(-2.5,-.2,.0);
				glScalef(3.5,1.4,1.5);
				glutSolidCube(1);
			glPopMatrix();
			glPushMatrix();
				glColor3f(1,0,0);
				glTranslatef(-.85,-.2,.0);
				glScalef(1.3,.8,1);
				glRotatef(15,0,0,1);
				glutSolidCube(1);
			glPopMatrix();
			//jok
			glPushMatrix();
				glColor3f(0,0,0);
				glTranslatef(-2.5,.7,0);
				glScalef(3,.4,1);
				glutSolidCube(1);
			glPopMatrix();
			glPushMatrix();
				glColor3f(0,0,0);
				glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
				glRotatef(5.0f,.0f,1.0f,.0f);
				glTranslatef(-2.9,-.8,-2.8);
				gluCylinder(quadratic,0.1f,0.1f,1.8f,320,320);
			glPopMatrix();
			glPushMatrix();
				glColor3f(0,0,0);
				glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
				glRotatef(5.0f,.0f,1.0f,.0f);
				glTranslatef(-2.9,.8,-2.8);
				gluCylinder(quadratic,0.1f,0.1f,1.8f,320,320);
			glPopMatrix();
			//lampu
			glPushMatrix();
				glColor3f(1,1,0);
				glRotatef(90.0f,.0f,1.0f,.0f);
				glTranslatef(.0,.0,1.3);
				glutSolidCube(.4);
			glPopMatrix();
			//stang
			glPushMatrix();
				glColor3f(0,0,0);
				glTranslatef(1.6,-2.57,0.7);
				glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
				glRotatef(-5.0f, 0.0f, 1.0f, 0.0f);
				gluCylinder(quadratic,0.1f,.1f,4.8f,320,320);
			glPopMatrix();
			//stang
			glPushMatrix();
				glColor3f(0,0,0);
				glTranslatef(1.6,-2.57,-0.7);
				glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
				glRotatef(-5.0f, 0.0f, 1.0f, 0.0f);
				gluCylinder(quadratic,0.1f,.1f,4.8f,320,320);
			glPopMatrix();
			//penyambung stang
			glPushMatrix();
				glColor3f(0,0,0);
				glTranslatef(1.2,2.1,-.7);
				gluCylinder(quadratic,0.1f,0.1f,1.4f,320,320);
			glPopMatrix();
			//stang kanan
			glPushMatrix();
				glColor3f(1,0,0);
				glTranslatef(1.18,2.1,.7);
				glRotatef(-8.0f, 0.0f, 1.0f, 1.0f);
				gluCylinder(quadratic,0.1f,0.1f,1.4f,320,320);
			glPopMatrix();
			//stang kiri
			glPushMatrix();
				glColor3f(1,0,0);
				glTranslatef(1.05,2.1,-2.1);
				glRotatef(8.0f, 0.0f, 1.0f, 1.0f);
				gluCylinder(quadratic,0.1f,0.1f,1.4f,320,320);
			glPopMatrix();
			//speedometer 1
			glPushMatrix();
				glColor3f(0.8,0.8,0.8);
				glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
				glTranslatef(1.45,0.25,2);
				gluCylinder(quadratic,0.0f,0.25f,.1f,1000,1000);
			glPopMatrix();
			//speedometer 2
			glPushMatrix();
				glColor3f(0.8,0.8,0.8);
				glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
				glTranslatef(1.45,-0.25,2);
				gluCylinder(quadratic,0.0f,0.25f,.1f,1000,1000);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	glDisable(GL_LIGHTING);
}
/*
=============== 5.2	E N V I R O N M E N T ===============
*/
void pohon(){
	glColor3f(.85,.26,.08);
	glScalef(1,3,1);
	glutSolidCube(5);
	glColor3f(.17,.34,.17);
	glTranslatef(.0,3,.0);
	glScalef(3,1,3);
	glutSolidCube(4);
}
void environment(){
	glScalef(.3,.3,.3);
	glTranslatef(.0,-5.35,.0);	
	glPushMatrix();
		glColor3f(.5,.5,.5);	
		glScalef(distance+12,.8,3);			
		glutSolidCube(4);
		glTranslatef(.0,.0,4.0);
		glColor3f(0.43,0.28,0.233);
		glutSolidCube(4);
		glTranslatef(.0,.0,-8);
		glutSolidCube(4);
	glPopMatrix();
	glPushMatrix();
		glRotatef(90,0,1,0);
		glTranslatef(0,0,54);
		glColor3f(.5,.5,.5);
		glScalef(distance+30,.8,3);
		glutSolidCube(4);
		glTranslatef(.0,.0,4.0);
		glColor3f(0.43,0.28,0.233);
		glutSolidCube(4);
	glPopMatrix();
	glPushMatrix();
		glRotatef(90,0,1,0);
		glTranslatef(39,0,-54);
		glColor3f(.5,.5,.5);
		glScalef(distance+10.5,.8,3);
		glutSolidCube(4);
		glTranslatef(.0,.0,-4.0);
		glColor3f(0.43,0.28,0.233);
		glutSolidCube(4);
	glPopMatrix();
	glPushMatrix();
		glColor3f(0.43,0.28,0.233);
		glScalef(distance+12,.8,6);
		glTranslatef(.0,.0,12);
		glutSolidCube(4);
	glPopMatrix();
	glPushMatrix();
		glColor3f(.5,.5,.5);
		glTranslatef(0,0,-78);	
		glScalef(distance+12,.8,3);			
		glutSolidCube(4);
		glTranslatef(.0,.0,4.0);
		glColor3f(0.43,0.28,0.233);
		glutSolidCube(4);
		glTranslatef(.0,.0,-8.0);
		glColor3f(0.43,0.28,0.233);
		glScalef(1.5,1,1);
		glutSolidCube(4);
	glPopMatrix();
	glPushMatrix();
		glRotatef(90,0,1,0);
		glTranslatef(39,0,42);
		glScalef(11,.8,3);
		glutSolidCube(4);
		glTranslatef(0,0,-28);
		glutSolidCube(4);
		glTranslatef(-7,0,0);
		glutSolidCube(4);
		glTranslatef(0,0,28);
		glutSolidCube(4);
	glPopMatrix();	
	glPushMatrix();
		glTranslatef(5.0,7,13.0);
		pohon();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(13,7,-13);
		pohon();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-23,7,13);
		pohon();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-30,7,-13);
		pohon();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(13,7,-90);
		pohon();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-40,7,-90);
		pohon();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(40,7,-65);
		pohon();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(65,7,-40);
		pohon();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(65,7,40);
		pohon();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(40,7,40);
		pohon();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(4,7,70);
		pohon();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-24,7,70);
		pohon();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-44,7,30);
		pohon();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(53,pp,73);
		glScalef(3,5,3);
		glColor3f(1,0,0);
		glutSolidCube(4);
	glPopMatrix();	
}
/*
=============== 5.3	D I S P L A Y ===============
*/
void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(
	x,		y,		z,
	x + lx,	y + ly,	z + lz,
	0.0f,	1.0f,	0.0f
	);
	glClearColor(1.0,1.0,1.0,1.0);
	glRotatef(rs.cameraX, 1, 0, 0);
    glRotatef(rs.cameraY, 0, 1, 0);
    glPushMatrix();
		Motor();
		environment();
    glPopMatrix();
	glutSwapBuffers();
}
/*
===============================================================================================================================================
6.0		M A I N
===============================================================================================================================================
*/
void exit(){
	delete &rs;
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(640,640);
	glutCreateWindow("MOTOR BROS ULTIMATE");
	PlaySound(TEXT("ost.wav"),NULL,SND_ASYNC|SND_LOOP);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutIdleFunc(display); // Fungsi display-nya dipanggil terusmenerus
	glutIdleFunc(idleCallback);
	glutMouseFunc(mouseCallback);
    glutMotionFunc(mouseMotionCallback);
	glutReshapeFunc(Reshape);
	lighting();
	init();
	glutMainLoop();
	return(0);
}
