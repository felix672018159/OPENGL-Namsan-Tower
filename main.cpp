#include <iostream>
#include <GL/glut.h>

using namespace std;

float cla(int warna){
	return (float) warna/255;
};

int main(int argc,char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(80, 250);
	glutCreateWindow("TUGAS RANCANG - NAMSAN TOWER [672018159 - 672018161]");
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glutMainLoop();
	cout<<cla(100)<<endl;
return 0;
};