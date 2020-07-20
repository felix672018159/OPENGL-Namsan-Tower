#include <iostream>
#include <GL/glut.h>

using namespace std;

struct konfigurasi{
	int is_depth;
	float rotasilokat[3];
};

struct konfigurasi conf;

int x,y,lock;
float lokasixyz[3] = {0.0f,0.0f,0.0f};
int vektorrotasi[3] = {0,0,0};
float fx,fy;
float xrot = 0;
float yrot = 0;
float xdiff = 0;
float ydiff = 0;
bool mousedown =false;

float cla(int warna){//fungsi yang digunakan untuk menormalisasi dari bit kode warna menjadi rentang 0 hingga 1 dalam desimal
	if(warna>255){
		warna = 255;
	};
	return (float) warna/255;
};

float w[100][4]={{cla(221),cla(221),cla(221),1.0f},//0	abuabu putih
					{cla(127),cla(127),cla(127),1.0f},//1	abu abu pekat
					{cla(80),cla(186),cla(164),0.5f},//2	biru tower
					{cla(152),cla(15),cla(23),1.0f},//3	merah
					{cla(191),cla(191),cla(191),1.0f},//4	abu abu putih kedua
					{cla(161),cla(161),cla(161),1.0f},//5	abu abu putih ketiga
					{cla(130),cla(132),cla(31),1.0f}, //6	hijau tua
					{cla(161),cla(162),cla(42),1.0f}, //7	hijau sedang
					{cla(155),cla(155),cla(41),1.0f}, //8	hijau sekali
					{cla(251),cla(176),cla(95),1.0f},//9	tanah depan
					{cla(237),cla(173),cla(101),1.0f},//10	tanah kanan
					{cla(222),cla(118),cla(67),1.0f},//11	tanah dalam depan
					{cla(210),cla(116),cla(65),1.0f},//12	tanah dalam kanan
					{cla(156),cla(83),cla(42),1.0f}, //13	inti tanah depan 
					{cla(141),cla(83),cla(59),1.0f}  //14	inti tanah kanan
				};
void tabung(float radius_atas,float radius_bawah,float tinggi,float x,float y,float z,float warna_atas[4],float warna_selimut[4],float warna_bawah[4]){
/*
void bulan(void){
	glBegin(GL_POLYGON);
	glColor3f(cl(255), cl(201), cl(14));
	int i;
	float theta;
	for(i = 90;i<360;i++){
		theta= i*3.14/180;
		glVertex2f(60+50*cos(theta),400+50*sin(theta));
	};
	glEnd();
};
*/ 
	int i =0;
	float theta,theti;
	glPushMatrix();
		glTranslatef(0.0f,0.0f,0.0f);
		glPushMatrix();
		glRotatef(0.0f,0.0f,0.0f,0.0f);
		glBegin(GL_POLYGON);
		glColor4f(warna_bawah[0],warna_bawah[1],warna_bawah[2],warna_bawah[3]);
		for(i = 0;i<360;i++){
			theta= i*3.14/180;
			glVertex3f(x+radius_bawah*cos(theta),	y,	z+radius_bawah*sin(theta));
		};
		glEnd();
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0f,0.0f,0.0f);
		glPushMatrix();
		glRotatef(0.0f,0.0f,0.0f,0.0f);
		glBegin(GL_POLYGON);
		glColor4f(warna_atas[0],warna_atas[1],warna_atas[2],warna_atas[3]);
		for(i = 0;i<360;i++){
			theta= i*3.14/180;
			glVertex3f(x+radius_atas*cos(theta),	y+tinggi,	z+radius_atas*sin(theta));
		};
		glEnd();
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0f,0.0f,0.0f);
		glPushMatrix();
		glRotatef(0.0f,0.0f,0.0f,0.0f);
	
		for(i = 1;i<360;i++){
			theta= i*3.14/180;
			theti = (i+1)*3.14/180;
			glBegin(GL_POLYGON);
			glColor4f(warna_selimut[0],warna_selimut[1],warna_selimut[2],warna_selimut[3]);
				glVertex3f(x+radius_bawah*cos(theta),	y		,	z+radius_bawah*sin(theta));
				glVertex3f(x+radius_atas*cos(theta),	y+tinggi,	z+radius_atas*sin(theta));
				glVertex3f(x+radius_atas*cos(theti),	y+tinggi,	z+radius_atas*sin(theti));
				glVertex3f(x+radius_bawah*cos(theti),	y		,	z+radius_bawah*sin(theti));
			glEnd();
		};
		
		glPopMatrix();
	glPopMatrix();
};
void balok(float panjang, float tinggi, float lebar,float x,float y,float z,float depan[4],float belakang[4],float atas[4],float bawah[4],float kiri[4], float kanan[4]){
	float p=panjang/2;
	float t=tinggi/2;
	float l=lebar/2;
	glPushMatrix();//bawah
	  glRotatef(0.0f,0.0f,0.0f,0.0f);
	  glBegin(GL_POLYGON);
	  glColor4f(bawah[0],bawah[1],bawah[2],bawah[3]);
	  glVertex3f( -p+x, y, -l+z);
	  glVertex3f( -p+x, y, l+z);
	  glVertex3f( p+x, y, l+z);
	  glVertex3f( p+x, y, -l+z);
	  glEnd();
	  
	  glBegin(GL_POLYGON);//atas
	  glColor4f(atas[0],atas[1],atas[2],atas[3]);
	  glVertex3f( -p+x, y+tinggi, -l+z);
	  glVertex3f( -p+x, y+tinggi, l+z);
	  glVertex3f( p+x, y+tinggi, l+z);
	  glVertex3f( p+x, y+tinggi, -l+z);
	  glEnd();

	  glBegin(GL_POLYGON);//depan
	  glColor4f(depan[0],depan[1],depan[2],depan[3]);
	  glVertex3f( -p+x, y, l+z);
	  glVertex3f( -p+x, y+tinggi, l+z);
	  glVertex3f( p+x, y+tinggi, l+z);
	  glVertex3f( p+x, y, l+z);
	  glEnd();

	  glBegin(GL_POLYGON);//belakang
	  glColor4f(belakang[0],belakang[1],belakang[2],belakang[3]);
	  glVertex3f( -p+x, y, -l+z);
	  glVertex3f( -p+x, y+tinggi, -l+z);
	  glVertex3f( p+x, y+tinggi, -l+z);
	  glVertex3f( p+x, y, -l+z);
	  glEnd();

	  glBegin(GL_POLYGON);//kiri
	  glColor4f(kiri[0],kiri[1],kiri[2],kiri[3]);
	  glVertex3f( -p+x, y, l+z);
	  glVertex3f( -p+x, y+tinggi, l+z);
	  glVertex3f( -p+x, y+tinggi, -l+z);
	  glVertex3f( -p+x, y, -l+z);
	  glEnd();

	  glBegin(GL_POLYGON);//kiri
	  glColor4f(kanan[0],kanan[1],kanan[2],kanan[3]);
	  glVertex3f( p+x, y, l+z);
	  glVertex3f( p+x, y+tinggi, l+z);
	  glVertex3f( p+x, y+tinggi, -l+z);
	  glVertex3f( p+x, y, -l+z);
	  glEnd();
	glPopMatrix();
};
void balokw(float panjang, float tinggi, float lebar,float x,float y,float z,float depan[4],float belakang[4],float atas[4],float bawah[4],float kiri[4], float kanan[4],int a,int b,int c,int d,int e, int f){
	float p=panjang/2;
	float t=tinggi/2;
	float l=lebar/2;
	glPushMatrix();
	  glRotatef(0.0f,0.0f,0.0f,0.0f);

	  if(a!=0){
		  glBegin(GL_POLYGON);//bawah
		  glColor4f(bawah[0],bawah[1],bawah[2],bawah[3]);
		  glVertex3f( -p+x, y, -l+z);
		  glVertex3f( -p+x, y, l+z);
		  glVertex3f( p+x, y, l+z);
		  glVertex3f( p+x, y, -l+z);
		  glEnd();
	  };

	  if(b!=0){
		  glBegin(GL_POLYGON);//atas
		  glColor4f(atas[0],atas[1],atas[2],atas[3]);
		  glVertex3f( -p+x, y+tinggi, -l+z);
		  glVertex3f( -p+x, y+tinggi, l+z);
		  glVertex3f( p+x, y+tinggi, l+z);
		  glVertex3f( p+x, y+tinggi, -l+z);
		  glEnd();
	  };

	  if(c!=0){
		  glBegin(GL_POLYGON);//depan
		  glColor4f(depan[0],depan[1],depan[2],depan[3]);
		  glVertex3f( -p+x, y, l+z);
		  glVertex3f( -p+x, y+tinggi, l+z);
		  glVertex3f( p+x, y+tinggi, l+z);
		  glVertex3f( p+x, y, l+z);
		  glEnd();
	  };
	  if(d!=0){
		  glBegin(GL_POLYGON);//belakang
		  glColor4f(belakang[0],belakang[1],belakang[2],belakang[3]);
		  glVertex3f( -p+x, y, -l+z);
		  glVertex3f( -p+x, y+tinggi, -l+z);
		  glVertex3f( p+x, y+tinggi, -l+z);
		  glVertex3f( p+x, y, -l+z);
		  glEnd();
	  };
	  if(e!=0){
		  glBegin(GL_POLYGON);//kiri
		  glColor4f(kiri[0],kiri[1],kiri[2],kiri[3]);
		  glVertex3f( -p+x, y, l+z);
		  glVertex3f( -p+x, y+tinggi, l+z);
		  glVertex3f( -p+x, y+tinggi, -l+z);
		  glVertex3f( -p+x, y, -l+z);
		  glEnd();
	  };
	  if(f!=0){
		  glBegin(GL_POLYGON);//kiri
		  glColor4f(kanan[0],kanan[1],kanan[2],kanan[3]);
		  glVertex3f( p+x, y, l+z);
		  glVertex3f( p+x, y+tinggi, l+z);
		  glVertex3f( p+x, y+tinggi, -l+z);
		  glVertex3f( p+x, y, -l+z);
		  glEnd();
	  };
	glPopMatrix();
};
void inisialisasi(void){
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glMatrixMode(GL_PROJECTION);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// intensitas dan warna
	GLfloat qaAmbientLight[]	= {0.2, 0.2, 0.2, 0.5};
	GLfloat qaDiffuseLight[]	= {0.8, 0.8, 0.8, 1.0};
	GLfloat qaSpecularLight[]	= {1.0, 1.0, 1.0, 1.0};
	/*set kedua
	GLfloat qaAmbientLight[]	= {0.2, 0.2, 0.2, 0.5};
	GLfloat qaDiffuseLight[]	= {0.8, 0.8, 0.8, 1.0};
	GLfloat qaSpecularLight[]	= {1.0, 1.0, 1.0, 1.0};
	GLfloat qaAmbientLight[]	= {0.5, 0.5, 0.5, 1.0};
	GLfloat qaDiffuseLight[]	= {1.0, 1.0, 1.0, 1.0};
	GLfloat qaSpecularLight[]	= {1.0, 1.0, 1.0, 1.0};
	*/
	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

	// posisi pencahayaan
	GLfloat qaLightPosition[]	= {0.0, 0.0, -0.9, 0.1};
	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);

	conf.is_depth = 1;
	conf.rotasilokat[0]=0.0f;
	conf.rotasilokat[1]=0.0f;
	conf.rotasilokat[2]=0.0f;
	glMatrixMode(GL_MODELVIEW);
	glPointSize(9.0);
	glLineWidth(6.0f);
};
void kubusku(void){
	glPushMatrix();
		glTranslatef(0.0,	30.0,	0.0);
		glPushMatrix();
		glRotatef(45.0	,0.0	,0.0	,1.0);
		
		glBegin(GL_POLYGON); //atas
			glColor4f(cla(255),	cla(0),cla(0)	,0.5);
			glVertex3f(10.0	,10.0,	10.0);
			glVertex3f(10.0	,10.0,	-10.0);
			glVertex3f(-10.0	,10.0,	-10.0);
			glVertex3f(-10.0	,10.0,	10.0);
		glEnd();
		glBegin(GL_POLYGON); //bawah
			glColor4f(cla(255),	cla(0),cla(0)	,0.5);
			glVertex3f(10.0	,-10.0,	10.0);
			glVertex3f(10.0	,-10.0,	-10.0);
			glVertex3f(-10.0	,-10.0,	-10.0);
			glVertex3f(-10.0	,-10.0,	10.0);
		glEnd();
		glBegin(GL_POLYGON); //depan
			glColor4f(cla(0),	cla(255),cla(0)	,0.5);
			glVertex3f(-10.0	,-10.0,	10.0);
			glVertex3f(10.0		,-10.0,	10.0);
			glVertex3f(10.0	,10.0,	10.0);
			glVertex3f(-10.0	,10.0,	10.0);
		glEnd();
		glBegin(GL_POLYGON); //belakang
			glColor4f(cla(0),	cla(255),cla(0)	,0.5);
			glVertex3f(-10.0	,-10.0,	-10.0);
			glVertex3f(10.0		,-10.0,	-10.0);
			glVertex3f(10.0		,10.0,	-10.0);
			glVertex3f(-10.0	,10.0,	-10.0);
		glEnd();
		glBegin(GL_POLYGON); //kiri
			glColor4f(cla(0),	cla(0),cla(255)	,0.5);
			glVertex3f(-10.0	,-10.0,	-10.0);
			glVertex3f(-10.0	,10.0,	-10.0);
			glVertex3f(-10.0	,10.0,	10.0);
			glVertex3f(-10.0	,-10.0,	10.0);
		glEnd();
		glBegin(GL_POLYGON); //kanan
			glColor4f(cla(0),	cla(0),cla(255)	,0.5);
			glVertex3f(10.0	,-10.0,	-10.0);
			glVertex3f(10.0	,10.0,	-10.0);
			glVertex3f(10.0	,10.0,	10.0);
			glVertex3f(10.0	,-10.0,	10.0);
		glEnd();
		glPopMatrix();
	glPopMatrix();
};

void towern(void){
	glPushMatrix();
		glTranslatef(0.0f,-50.0f,0.0f);
		glPushMatrix();
			tabung(0.5f,0.5f,4.0f,0.0f,145.0f,0.0f,w[0],w[0],w[0]);
			//
			tabung(2.0f,2.0f,1.0f,0.0f,144.0f,0.0f,w[1],w[0],w[1]);
			tabung(1.0f,1.0f,6.0f,0.0f,139.0f,0.0f,w[0],w[0],w[0]);
			tabung(1.0f,1.0f,3.0f,0.0f,136.0f,0.0f,w[0],w[3],w[0]);
			tabung(1.0f,1.0f,4.0f,0.0f,132.0f,0.0f,w[0],w[0],w[0]);
			tabung(1.0f,1.0f,3.0f,0.0f,129.0f,0.0f,w[0],w[3],w[0]);
			//
			tabung(2.5f,2.5f,1.0f,0.0f,128.0f,0.0f,w[1],w[0],w[1]);
			tabung(1.5f,1.5f,12.0f,0.0f,116.0f,0.0f,w[0],w[0],w[0]);
			tabung(1.5f,1.5f,3.0f,0.0f,113.0f,0.0f,w[0],w[3],w[0]);
			//
			tabung(3.5f,3.5f,1.0f,0.0f,112.0f,0.0f,w[1],w[0],w[1]);
			tabung(2.5f,2.5f,12.0f,0.0f,100.0f,0.0f,w[0],w[0],w[0]);
			tabung(2.5f,2.5f,3.0f,0.0f,97.0f,0.0f,w[0],w[3],w[0]);
			//
			tabung(3.0f,3.0f,3.0f,0.0f,94.0f,0.0f,w[0],w[0],w[0]);
			tabung(6.0f,6.0f,5.0f,0.0f,89.0f,0.0f,w[0],w[0],w[0]);
			tabung(7.0f,7.0f,1.0f,0.0f,88.0f,0.0f,w[0],w[4],w[0]);
			tabung(7.0f,7.0f,3.0f,0.0f,85.0f,0.0f,w[1],w[2],w[1]);
			tabung(7.0f,7.0f,1.0f,0.0f,84.0f,0.0f,w[0],w[4],w[0]);
			tabung(7.0f,7.0f,3.0f,0.0f,81.0f,0.0f,w[1],w[2],w[1]);
			tabung(7.0f,7.0f,3.0f,0.0f,78.0f,0.0f,w[1],w[4],w[1]);
			//
			tabung(10.0f,10.0f,1.0f,0.0f,77.0f,0.0f,w[1],w[4],w[1]);
			tabung(10.0f,10.0f,3.0f,0.0f,74.0f,0.0f,w[1],w[2],w[1]);//
			tabung(10.0f,10.0f,1.0f,0.0f,73.0f,0.0f,w[1],w[4],w[1]);
			tabung(10.0f,10.0f,3.0f,0.0f,70.0f,0.0f,w[1],w[2],w[1]);//
			tabung(10.0f,10.0f,1.0f,0.0f,69.0f,0.0f,w[1],w[4],w[1]);
			tabung(10.0f,10.0f,3.0f,0.0f,66.0f,0.0f,w[1],w[2],w[1]);
			tabung(10.0f,10.0f,1.0f,0.0f,65.0f,0.0f,w[1],w[4],w[1]);
			//
			tabung(3.0f,3.0f,70.0f,0.0f,-5.0f,0.0f,w[1],w[0],w[1]);
			tabung(7.0f,7.0f,2.0f,0.0f,-7.0f,0.0f,w[1],w[0],w[1]);
			tabung(7.0f,7.0f,4.0f,0.0f,-11.0f,0.0f,w[1],w[2],w[1]);
			tabung(7.0f,7.0f,2.0f,0.0f,-13.0f,0.0f,w[1],w[0],w[1]);
			balokw(28.0f,2.0f,28.0f,0.0f,-15.0f,0.0f,w[0],w[0],w[4],w[4],w[5],w[5],0,1,1,1,1,1);
			//balokw(28.0f,10.0f,28.0f,0.0f,-20.0f,0.0f,w[0],w[0],w[4],w[4],w[5],w[5],0,1,1,1,1,1);
			balokw(7.0f,5.0f,28.0f,10.5f,-20.0f,0.0f,w[0],w[0],w[4],w[4],w[5],w[5],0,0,1,1,0,0);//depan belakang kanan
			balokw(7.0f,5.0f,28.0f,-10.5f,-20.0f,0.0f,w[0],w[0],w[4],w[4],w[5],w[5],0,0,1,1,0,0);//depan belakang kiri
			balokw(14.0f,5.0f,28.0f,0.0f,-20.0f,0.0f,w[2],w[2],w[4],w[4],w[5],w[5],0,0,1,1,0,0);//depan belakan kaca
			balokw(28.0f,5.0f,7.0f,0.0f,-20.0f,10.5f,w[0],w[0],w[4],w[4],w[5],w[5],0,0,0,0,1,1);//kiri kanan samping kanan
			balokw(28.0f,5.0f,7.0f,0.0f,-20.0f,-10.5f,w[0],w[0],w[4],w[4],w[5],w[5],0,0,0,0,1,1);//kiri kanan samping kiri
			balokw(28.0f,5.0f,14.0f,0.0f,-20.0f,0.0f,w[0],w[0],w[4],w[4],w[2],w[2],0,0,0,0,1,1);//kiri kanan kaca
			balokw(28.0f,2.0f,28.0f,0.0f,-22.0f,0.0f,w[0],w[0],w[4],w[4],w[5],w[5],0,1,1,1,1,1);
			balokw(35.0f,1.0f,35.0f,0.0f,-23.0f,0.0f,w[0],w[0],w[1],w[1],w[5],w[5],1,1,1,1,1,1);
			balok(100.0f,1.0f,100.0f,0.0f,-24.0f,0.0f,w[7],w[7],w[6],w[6],w[8],w[8]);//rumput
			balok(100.0f,2.0f,100.0f,0.0f,-26.0f,0.0f,w[10],w[10],w[9],w[9],w[10],w[10]);//tanah lapis 1
			balok(100.0f,4.0f,100.0f,0.0f,-30.0f,0.0f,w[11],w[11],w[12],w[12],w[11],w[11]);//tanah lapis 2
			balok(100.0f,4.0f,100.0f,0.0f,-34.0f,0.0f,w[13],w[13],w[14],w[14],w[13],w[13]);//tanah lapis 3
		glPopMatrix();
	glPopMatrix();
};
void titiktengah(void){
		glPushMatrix();
			glBegin(GL_POINTS);
				glColor4f(cla(255),	cla(0),cla(0)	,0.5);
				glVertex3f(0.0,0.0,0.0);
			glEnd();
		glPopMatrix();

	

		glPushMatrix();
			glBegin(GL_POLYGON); //depan
			glColor4f(cla(0),	cla(255),cla(0)	,0.5);
			glVertex3f(1.0	,0.0,	1.0);
			glVertex3f(1.0	,0.0,	-1.0);
			glVertex3f(-1.0	,0.0,	-1.0);
			glVertex3f(-1.0	,0.0,	1.0);
			glEnd();
		glPopMatrix();
};
void tampilkan(void){
	if (conf.is_depth){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}else{
		glClear(GL_COLOR_BUFFER_BIT);
	};
	glPushMatrix();
		glScalef(0.5f,0.5f,0.5f);
		towern();
		titiktengah();
		
	glPopMatrix();
	glutSwapBuffers();
};
void ukurancanvas(int lebar,int tinggi){
	if (tinggi == 0){
		tinggi = 1;
	};
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, lebar / tinggi, 5.0, 500.0);
	glTranslatef(0.0f, -5.0f, -150.0f);
	glMatrixMode(GL_MODELVIEW);
};
void mouse2(int button, int state, int x, int y){
	if(button == GLUT_LEFT_BUTTON&& state == GLUT_DOWN){
		mousedown=true;
		xdiff=x-yrot;
		ydiff=-y+xrot;
	}else{
		mousedown = false;
	};

	if(button == GLUT_LEFT && state==GLUT_UP){
		vektorrotasi[0] = 0;
		vektorrotasi[1] = 0;
		vektorrotasi[2] = 0;
		lock = 0;
	};

	glutPostRedisplay();
};
void gerakmouse(int x, int y){
	

	if (mousedown){
		if(lokasixyz[2]==360.0f||lokasixyz[2]==-360.0f){
			lokasixyz[2]=0.0f;
		};

		if(lokasixyz[1]==360.0f||lokasixyz[1]==-360.0f){
			lokasixyz[1]=0.0f;
		};

		if(lokasixyz[0]==360.0f||lokasixyz[0]==-360.0f){
			lokasixyz[0]=0.0f;
		};

		yrot=x-xdiff;
		xrot=y+ydiff;
		
		if(lock ==0){
			
			lock=1;
		};
		/*
		if((fy<y)&&(fx<x)){
			glRotatef(1.0f,1.0f,1.0f,0.0f);
			lokasixyz[1] += 1.0f;
			lokasixyz[0] += 1.0f;
		}else if((fy>y)&&(fx>x)){
			glRotatef(-1.0f,1.0f,1.0f,0.0f);
			lokasixyz[1] -= 1.0f;
			lokasixyz[0] -= 1.0f;
		};*/
		/*if((fy<y)&&(fx<x)){
			glRotatef(1.0f,1.0f,1.0f,0.0f);
			lokasixyz[1] += 1.0f;
			lokasixyz[0] += 1.0f;
		}else if((fy>y)&&(fx>x)){
			glRotatef(-1.0f,1.0f,1.0f,0.0f);
			lokasixyz[1] -= 1.0f;
			lokasixyz[0] -= 1.0f;
		};*/
		/*
		if(fx<x){
			glRotatef(1.0f,0.0f,1.0f,0.0f);
			lokasixyz[0] += 1.0f;
		};*/
		
		//;

		if(fx<x){
			glRotatef(3.0f,0.0f,1.0f,0.0f);
			lokasixyz[0] += 3.0f;
		}else if(fx>x){
			glRotatef(-3.0f,0.0f,1.0f,0.0f);
			lokasixyz[0] -= 3.0f;
		}; if(fy<y){
			glRotatef(3.0f,1.0f,0.0f,0.0f);
			lokasixyz[1] += 3.0f;
		}else if(fy>y){
			glRotatef(-3.0f,1.0f,0.0f,0.0f);
			lokasixyz[1] -= 3.0f;
		};
		cout<<"pos x = "<< lokasixyz[0]<<"; pos y = "<<lokasixyz[1]<<endl;
		tampilkan();
		
		glutPostRedisplay();
		fx = x;
		fy = y;
	}
};

int main(int argc,char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(80, 100);
	glutCreateWindow("TUGAS RANCANG - NAMSAN TOWER [672018159 - 672018161]");
	inisialisasi();
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glutDisplayFunc(tampilkan);
	glutReshapeFunc(ukurancanvas);
	glutMouseFunc(mouse2);
	glutMotionFunc(gerakmouse);
	glutMainLoop();
	
return 0;
};
