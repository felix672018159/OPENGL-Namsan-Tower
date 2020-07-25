#include <iostream>
#include <GL/glut.h>
#include <loadergambar.h>
using namespace std;
//init texturing 
GLuint _textureID;
GLuint texturegembok;
//selesai init texturing
struct konfigurasi{
	int is_depth;
	float rotasilokat[3];
};
struct objek{
	float rx,ry,rz; //rotasi
	float tx,ty,tz; //translasi
	float sx,sy,sz; //skala
};

struct konfigurasi conf;
struct objek ob[5];

int x,y,lock;
float lokasixyz[3] = {0.0f,0.0f,0.0f};
int vektorrotasi[3] = {0,0,0};
int tdinding[4] = {1,1,1,1};
int pintu = 1;
int tjendela =1;
float fx,fy;
float xrot = 0;
float yrot = 0;
float xdiff = 0;
float ydiff = 0;
float animasirotasipohon=0.0;
int enablerotasipohon = 1;
bool mousedown =false;

float cla(int warna){//fungsi yang digunakan untuk menormalisasi dari bit kode warna menjadi rentang 0 hingga 1 dalam desimal
	if(warna>255){
		warna = 255;
		
	};
	return (float) warna/255;
};
float cd[100][10][4]		=   { //cd = penentu warna sebuah objek 
										{ //0 warna kustom
											{cla(255),cla(54),cla(23),0.3f}, //depan
											{cla(0),cla(255),cla(0),0.5f}, //belakang
											{cla(0),cla(0),cla(255),0.5f}, //kiri
											{cla(255),cla(0),cla(255),0.5f}, //kanan
											{cla(255),cla(255),cla(0),0.5f}, // atas
											{cla(0),cla(255),cla(255),0.5f}  //bawah
										},
										{//1 warna tanah
											{cla(104),cla(65),cla(50),1.0f}, //depan
											{cla(104),cla(65),cla(50),1.0f}, //belakang
											{cla(90),cla(55),cla(41),1.0f}, //kiri
											{cla(90),cla(55),cla(41),1.0f}, //kanan
											{cla(65),cla(152),cla(10),1.0f}, // atas
											{cla(74),cla(41),cla(28),1.0f}  //bawah
										},
										{ //2 warna dinding depan
											{cla(255),cla(54),cla(23),1.0f}, //depan
											{cla(0),cla(255),cla(0),1.0f}, //belakang
											{cla(0),cla(0),cla(255),1.0f}, //kiri
											{cla(255),cla(0),cla(255),1.0}, //kanan
											{cla(255),cla(255),cla(0),1.0f}, // atas
											{cla(0),cla(255),cla(255),1.0f}  //bawah
										},
										{ //3 warna pagar
											{cla(33),cla(129),cla(203),1.0f}, //depan
											{cla(33),cla(129),cla(203),1.0f}, //belakang
											{cla(11),cla(104),cla(181),1.0f}, //kiri
											{cla(11),cla(104),cla(181),1.0f}, //kanan
											{cla(6),cla(76),cla(134),1.0f}, // atas
											{cla(6),cla(76),cla(134),1.0f}  //bawah
										},
										{ //4 warna alas rumah
											{cla(65),cla(63),cla(66),1.0f}, //depan
											{cla(255),cla(255),cla(255),1.0f}, //belakang
											{cla(255),cla(255),cla(255),1.0f}, //kiri
											{cla(255),cla(255),cla(255),1.0f}, //kanan
											{cla(255),cla(255),cla(255),1.0f}, // atas
											{cla(255),cla(255),cla(255),1.0f}  //bawah
										},
										{ //5 warna kustom kuning oranye
											{cla(255),cla(201),cla(14),1.0f},
											{cla(0),cla(0),cla(255),0.3f}, //warna jendela
											{cla(131),cla(89),cla(149),1.0f},
											{cla(238),cla(125),cla(0),1.0f},//warna pintu 5 3
											{cla(0),cla(0),cla(0),1.0f},
											{cla(0),cla(0),cla(0),1.0f},
										}
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
void segitigarumah(float akiri, float akanan, float tinggi , float lebar,float x,float y, float z,float d[4],float b[4],float ki[4], float ka[4],float ba[4]){

	glBegin(GL_POLYGON); //depan
	glColor4f(d[0],d[1],d[2],d[3]);
	glVertex3f(0+x     ,0+y     ,0+z);
	glVertex3f(akanan+x,0+y     ,0+z);
	glVertex3f(0+x     ,tinggi+y,0+z);
	glVertex3f(-akiri+x ,0+y     ,0+z);
	glEnd();

	glBegin(GL_POLYGON); //belakang
	glColor4f(b[0],b[1],b[2],b[3]);
	glVertex3f(0+x     ,0+y     ,-lebar+z);
	glVertex3f(akanan+x,0+y     ,-lebar+z);
	glVertex3f(0+x     ,tinggi+y,-lebar+z);
	glVertex3f(-akiri+x ,0+y     ,-lebar+z);
	glEnd();

	glBegin(GL_POLYGON); //kiri
	glColor4f(ki[0],ki[1],ki[2],ki[3]);
	glVertex3f(-akiri+x,0+y      ,0+z);
	glVertex3f(-akiri+x,0+y      ,-lebar+z);
	glVertex3f(0+x    ,tinggi+y ,-lebar+z);
	glVertex3f(0+x    ,tinggi+y ,0+z);
	glEnd();

	glBegin(GL_POLYGON); //kanan
	glColor4f(ka[0],ka[1],ka[2],ka[3]);
	glVertex3f(akanan+x,0+y     ,0+z);
	glVertex3f(akanan+x,0+y     ,-lebar+z);
	glVertex3f(0+x    ,tinggi+y ,-lebar+z);
	glVertex3f(0+x    ,tinggi+y ,0+z);
	glEnd();

	glBegin(GL_POLYGON); // bawah
	glColor4f(ba[0],ba[1],ba[2],ba[3]);
	glVertex3f(0+x     ,0+y  ,0+z);
	glVertex3f(akanan+x,0+y  ,0+z);
	glVertex3f(akanan+x,0+y  ,-lebar+z);
	glVertex3f(0+x     ,0+y  ,-lebar+z);

	glVertex3f(akiri+x ,0+y  ,-lebar+z);
	glVertex3f(akiri+x ,0+y  ,0+z);
	glEnd();

};
void balokrumah(float panjang, float tinggi , float lebar,float x,float y, float z,float d[4],float b[4],float ki[4], float ka[4],float at[4],float ba[4]){
	

	glBegin(GL_POLYGON); //depan
	glColor4f(d[0],d[1],d[2],d[3]);
	glVertex3f(0+x      ,0+y     ,0+z);
	glVertex3f(0+x      ,tinggi+y,0+z);
	glVertex3f(panjang+x,tinggi+y,0+z);
	glVertex3f(panjang+x,0+y     ,0+z);
	glEnd();

	glBegin(GL_POLYGON); //belakang
	glColor4f(b[0],b[1],b[2],b[3]);
	glVertex3f(0+x      ,0+y      ,-lebar+z);
	glVertex3f(0+x      ,tinggi+y ,-lebar+z);
	glVertex3f(panjang+x,tinggi+y ,-lebar+z);
	glVertex3f(panjang+x,0+y      ,-lebar+z);
	glEnd();
	

	glBegin(GL_POLYGON); //kiri
	glColor4f(ki[0],ki[1],ki[2],ki[3]);
	glVertex3f(0+x,0+y     ,0+z      );
	glVertex3f(0+x,tinggi+y,0+z      );
	glVertex3f(0+x,tinggi+y,-lebar+z );
	glVertex3f(0+x,0+y      ,-lebar+z);
	glEnd();

	glBegin(GL_POLYGON); //kanan
	glColor4f(ka[0],ka[1],ka[2],ka[3]);
	glVertex3f(panjang+x,0+y     ,0+z      );
	glVertex3f(panjang+x,tinggi+y,0+z      );
	glVertex3f(panjang+x,tinggi+y,-lebar+z );
	glVertex3f(panjang+x,0+y      ,-lebar+z);
	glEnd();

	glBegin(GL_POLYGON); //atas
	glColor4f(at[0],at[1],at[2],at[3]);
	glVertex3f(0+x      ,tinggi+y ,0+z);
	glVertex3f(0+x      ,tinggi+y ,-lebar+z);
	glVertex3f(panjang+x,tinggi+y ,-lebar+z);
	glVertex3f(panjang+x,tinggi+y ,0+z);
	glEnd();

	glBegin(GL_POLYGON); //bawah
	glColor4f(ba[0],ba[1],ba[2],ba[3]);
	glVertex3f(0+x      ,0+y ,0+z);
	glVertex3f(0+x      ,0+y ,-lebar+z);
	glVertex3f(panjang+x,0+y ,-lebar+z);
	glVertex3f(panjang+x,0+y ,0+z);
	glEnd();
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
		glPushMatrix();
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
	glPopMatrix();
};
void tabungtexture(float radius_atas,float radius_bawah,float tinggi,float x,float y,float z,float warna_atas[4],float warna_selimut[4],float warna_bawah[4]){
	
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
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,_textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		for(i = 1;i<360;i++){
			theta= i*3.14/180;
			theti = (i+1)*3.14/180;
			glBegin(GL_POLYGON);
			glColor4f(warna_selimut[0],warna_selimut[1],warna_selimut[2],warna_selimut[3]);
				glTexCoord3f(x+radius_atas*cos(theta),	y+tinggi,	z+radius_atas*sin(theta));
				glVertex3f(x+radius_atas*cos(theta),	y+tinggi,	z+radius_atas*sin(theta));
				glTexCoord3f(x+radius_atas*cos(theti),	y+tinggi,	z+radius_atas*sin(theti));
				glVertex3f(x+radius_atas*cos(theti),	y+tinggi,	z+radius_atas*sin(theti));
				glTexCoord3f(x+radius_bawah*cos(theti),	y		,	z+radius_bawah*sin(theti));
				glVertex3f(x+radius_bawah*cos(theti),	y		,	z+radius_bawah*sin(theti));
				glTexCoord3f(x+radius_bawah*cos(theta),	y		,	z+radius_bawah*sin(theta));
				glVertex3f(x+radius_bawah*cos(theta),	y		,	z+radius_bawah*sin(theta));
				
			glEnd();
		};
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
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
void baloktexture(float panjang, float tinggi, float lebar,float x,float y,float z,float depan[4],float belakang[4],float atas[4],float bawah[4],float kiri[4], float kanan[4]){
	float p=panjang/2;
	float t=tinggi/2;
	float l=lebar/2;
	glPushMatrix();//bawah

	  glRotatef(0.0f,0.0f,0.0f,0.0f);
	  glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texturegembok);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		 glBegin(GL_POLYGON);//depan
	  glColor4f(depan[0],depan[1],depan[2],depan[3]);
	  glTexCoord3f(-p+x, y+tinggi, l+z);
	  glVertex3f( -p+x, y+tinggi, l+z);

	  glTexCoord3f(p+x, y+tinggi, l+z);
	  glVertex3f( p+x, y+tinggi, l+z);

	  glTexCoord3f(p+x, y, l+z);
	  glVertex3f( p+x, y, l+z);

	  glTexCoord3f(-p+x, y, l+z);
	  glVertex3f( -p+x, y, l+z);
	  glEnd();
	  glDisable(GL_TEXTURE_2D);

	  
	  glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texturegembok);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		  glBegin(GL_POLYGON);//belakang
		  glColor4f(belakang[0],belakang[1],belakang[2],belakang[3]);
		  glVertex3f( -p+x, y, -l+z);
		  glVertex3f( -p+x, y+tinggi, -l+z);
		  glVertex3f( p+x, y+tinggi, -l+z);
		  glVertex3f( p+x, y, -l+z);
		  glEnd();
	  glDisable(GL_TEXTURE_2D);

	  glBegin(GL_POLYGON);//bawah
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
void donat(float radtengah, float radonat,float x,float y, float z,float w[4]){
	int i,j;
	float theta,theti;
	float posx;
	float posy;
	float posz;

	float gudx;
	float gudy;
	float gudz;
	float r;
	glPushMatrix();
		glTranslatef(0.0	,0.0	,-20.0);
		glPushMatrix();
		//glRotatef(180.0,0.1,0.0,0.0);
		
		for(i = 0;i<90;i++){
			theta = i*3.14/180;
			posx =  x+radtengah*cos(theta);
			posy =  y+radtengah*sin(theta);
			r = (float) i;
			glPushMatrix();
				glTranslatef(0.0,0.0,0.0);
				glPushMatrix();
				glRotatef(90.0,0.0	,0.0	,1.0);
				glBegin(GL_POLYGON);
				glColor4f(w[0],w[1],w[2],w[3]);
				for(j=0;j<360;j++){
					theti = j*3.14/180;
					gudx = posx+radonat*cos(theti);
					gudy = posy;
					gudz = z   +radonat*sin(theti);
					glVertex3f(gudx,gudy,gudz);
				};
				glEnd();	
				glPopMatrix();
			glPopMatrix();
		};
		
		glPopMatrix();
	glPopMatrix();
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
void rumah(void){
	int i;
	int a=12;
	for(i=0;i<a;i++){
		float geser = (float) i*4.5f;
		glPushMatrix(); // atap rumah kanan
			glRotatef(-38.5f,0.0f,0.0f,1.0f);
			glTranslatef(-34.25f,43.0f,16.25f-geser);
			balokrumah(35.0f,2.0f,4.0f,0.0f,0.0f,0.0f,	    cd[2][0], //depan
															cd[2][1], //belakang
															cd[2][2], //kiri
															cd[2][3], //kanan
															cd[2][4], //atas
															cd[2][5]); //bawah
			if (i!=a-1) {
				balokrumah(35.0f,3.0f,0.5f,0.0f,0.0f,-4.0f,			cd[2][3], cd[2][3], cd[2][3], cd[2][3], cd[2][3], cd[2][3]);
			};
			glPushMatrix();
				glRotatef(-90.0f,0.0f,1.0f,0.0f);
				glRotatef(-90.0f,1.0f,0.0f,0.0f);	
				segitigarumah(2.0f,2.0f,5.0f,2.0f,-2.0f,35.0f,2.0f,	cd[2][4], //depan
																cd[2][5], //belakang
																cd[2][0], //kiri
																cd[2][0], //kanan
																cd[2][4]); //bawah
			glPopMatrix();
		glPopMatrix();
	};

	for(i=0;i<a;i++){
		float geser = (float) i*4.5f;
		glPushMatrix(); // atap rumah kiri
			glRotatef(218.5f,0.0f,0.0f,1.0f);
			glRotatef(180.0f,1.0f,0.0f,0.0f);
			glTranslatef(-34.25f,43.0f,-12.25f+geser);
			balokrumah(35.0f,2.0f,4.0f,0.0f,0.0f,0.0f,			cd[2][1], //depan
															cd[2][0], //belakang
															cd[2][2], //kiri
															cd[2][3], //kanan
															cd[2][4], //atas
															cd[2][5]); //bawah
		
			if (i!=a-1) {
				balokrumah(35.0f,3.0f,0.5f,0.0f,0.0f,0.5f,			cd[2][3], cd[2][3], cd[2][3], cd[2][3], cd[2][3], cd[2][3]);
			};

			glPushMatrix();
				glRotatef(-90.0f,0.0f,1.0f,0.0f);
				glRotatef(-90.0f,1.0f,0.0f,0.0f);	
				segitigarumah(2.0f,2.0f,5.0f,2.0f,-2.0f,35.0f,2.0f,	cd[2][4], //depan
																cd[2][5], //belakang
																cd[2][0], //kiri
																cd[2][0], //kanan
																cd[2][4]); //bawah
			glPopMatrix();
		glPopMatrix();
	};
	///////////////////////////////////////////////////////////////////////////////////////////////////


	glPushMatrix(); //alas
		balokrumah(50.0f,1.5f,50.0f,-25.0f,-15.0f,15.0f,	    cd[2][0], //depan //alas bawah
														cd[5][2], //belakang
														cd[2][2], //kiri
														cd[2][2], //kanan
														cd[4][4], //atas
														cd[4][5]); //bawah

		balokrumah(47.0f,2.5f,47.0f,-23.5f,8.25f,13.5f,	    cd[4][0], //depan //alas atas
														cd[4][1], //belakang
														cd[4][2], //kiri
														cd[4][3], //kanan
														cd[4][4], //atas
														cd[4][5]); //bawah
	glPopMatrix();
	if(tdinding[0]==1){
	glPushMatrix(); //dinding depan
		balokrumah(8.0f,50.0f,1.5f,-25.0f,-15.0f,15.0f,	    cd[2][0], //depan
														cd[2][1], //belakang
														cd[2][2], //kiri
														cd[2][3], //kanan
														cd[2][4], //atas
														cd[2][5]); //bawah
		
		balokrumah(5.0f,50.0f,1.5f,-10.0f,-15.0f,15.0f,	    cd[2][0], //depan
														cd[2][1], //belakang
														cd[2][3], //kiri
														cd[2][3], //kanan
														cd[2][4], //atas
														cd[2][5]); //bawah


		balokrumah(10.0f,30.0f,1.5f,-5.0f,5.0f,15.0f,	    cd[2][0], //depan
														cd[2][1], //belakang
														cd[2][3], //kiri
														cd[2][3], //kanan
														cd[2][4], //atas
														cd[2][5]); //bawah

		balokrumah(5.0f,50.0f,1.5f,5.0f,-15.0f,15.0f,	    cd[2][0], //depan
														cd[2][1], //belakang
														cd[2][3], //kiri
														cd[2][3], //kanan
														cd[2][4], //atas
														cd[2][5]); //bawah

		balokrumah(8.0f,50.0f,1.5f,17.0f,-15.0f,15.0f,	    cd[2][0], //depan
														cd[2][1], //belakang
														cd[2][3], //kiri
														cd[2][2], //kanan
														cd[2][4], //atas
														cd[2][5]); //bawah
	glPopMatrix();
	};
	if(tdinding[2]==1){
	glPushMatrix(); //dinding belakang
		balokrumah(50.0f,10.0f,1.5f,-25.0f,-15.0f,-33.5f,	cd[5][0], //depan
														cd[5][2], //belakang
														cd[2][2], //kiri
														cd[2][2], //kanan
														cd[2][4], //atas
														cd[2][5]); //bawah

		balokrumah(50.0f,15.0f,1.5f,-25.0f,5.0f,-33.5f,	cd[5][0], //depan
														cd[5][2], //belakang
														cd[2][2], //kiri
														cd[2][2], //kanan
														cd[2][4], //atas
														cd[2][5]); //bawah
		balokrumah(50.0f,5.0f,1.5f,-25.0f,30.0f,-33.5f,	cd[5][0], //depan
														cd[5][2], //belakang
														cd[2][2], //kiri
														cd[2][2], //kanan
														cd[2][4], //atas
														cd[2][5]); //bawah

		
	glPopMatrix();
	};
	if(tdinding[3]==1){
	glPushMatrix(); //dinding kiri
		balokrumah(1.5f,10.0f,50.0f,-25.0f,-15.0f,15.0f,    cd[2][0], //depan
														cd[5][2], //belakang
														cd[2][2], //kiri
														cd[2][3], //kanan
														cd[2][4], //atas
														cd[2][5]); //bawah

		balokrumah(1.5f,15.0f,50.0f,-25.0f,5.0f,15.0f,    cd[2][0], //depan
														cd[5][2], //belakang
														cd[2][2], //kiri
														cd[2][3], //kanan
														cd[2][4], //atas
														cd[2][5]); //bawah

		balokrumah(1.5f,5.0f,50.0f,-25.0f,30.0f,15.0f,    cd[2][0], //depan
														cd[5][2], //belakang
														cd[2][2], //kiri
														cd[2][3], //kanan
														cd[2][4], //atas
														cd[2][5]); //bawah

		balokrumah(1.5f,40.0f,10.0f,-25.0f,-5.0f,15.0f,    cd[2][0], //depan
														cd[5][2], //belakang
														cd[2][2], //kiri
														cd[2][3], //kanan
														cd[2][4], //atas
														cd[2][5]); //bawah

		balokrumah(1.5f,40.0f,10.0f,-25.0f,-5.0f,-5.0f,    cd[2][0], //depan
														cd[5][2], //belakang
														cd[2][2], //kiri
														cd[2][3], //kanan
														cd[2][4], //atas
														cd[2][5]); //bawah

		balokrumah(1.5f,40.0f,10.0f,-25.0f,-5.0f,-25.0f,    cd[2][0], //depan
														cd[5][2], //belakang
														cd[2][2], //kiri
														cd[2][3], //kanan
														cd[2][4], //atas
														cd[2][5]); //bawah
	glPopMatrix();
	};

	if(tdinding[1]==1){
	glPushMatrix(); //dinding kanan
		balokrumah(1.5f,10.0f,50.0f,23.5f,-15.0f,15.0f,    cd[2][0], //depan
														cd[5][2], //belakang
														cd[2][3], //kiri
														cd[2][2], //kanan
														cd[2][4], //atas
														cd[2][5]); //bawah
		balokrumah(1.5f,15.0f,50.0f,23.5f,5.0f,15.0f,    cd[2][0], //depan
														cd[5][2], //belakang
														cd[2][3], //kiri
														cd[2][2], //kanan
														cd[2][4], //atas
														cd[2][5]); //bawah
		balokrumah(1.5f,5.0f,50.0f,23.5f,30.0f,15.0f,    cd[2][0], //depan
														cd[5][2], //belakang
														cd[2][3], //kiri
														cd[2][2], //kanan
														cd[2][4], //atas
														cd[2][5]); //bawah

		balokrumah(1.5f,50.0f,10.0f,23.5f,-15.0f,15.0f,    cd[2][0], //depan
														cd[5][2], //belakang
														cd[2][3], //kiri
														cd[2][2], //kanan
														cd[2][4], //atas
														cd[2][5]); //bawah

		balokrumah(1.5f,50.0f,10.0f,23.5f,-15.0f,-5.0f,    cd[2][0], //depan
														cd[5][2], //belakang
														cd[2][3], //kiri
														cd[2][2], //kanan
														cd[2][4], //atas
														cd[2][5]); //bawah

		balokrumah(1.5f,50.0f,10.0f,23.5f,-15.0f,-25.0f,    cd[2][0], //depan
														cd[5][2], //belakang
														cd[2][3], //kiri
														cd[2][2], //kanan
														cd[2][4], //atas
														cd[2][5]); //bawah
	glPopMatrix();
	};
	

};
void jendelarumah(void){
	if(tdinding[0]==1){
	glPushMatrix(); // jendela rumah depan kiri
		balokrumah(7.0f,10.0f,1.5f,-17.0f,-15.0f,15.0f,	    cd[2][0], //depan
														cd[2][1], //belakang
														cd[2][2], //kiri
														cd[2][3], //kanan
														cd[2][4], //atas
														cd[2][5]); //bawah
		balokrumah(7.0f,5.0f,1.5f,-17.0f,5.0f,15.0f,	    cd[2][0], //depan
														cd[2][1], //belakang
														cd[2][2], //kiri
														cd[2][3], //kanan
														cd[2][4], //atas
														cd[2][5]); //bawah

		balokrumah(7.0f,10.0f,1.5f,-17.0f,-5.0f,15.0f,	    cd[5][1], //depan   //jendela depan, kiri bawah
														cd[5][1], //belakang
														cd[5][1], //kiri
														cd[5][1], //kanan
														cd[5][1], //atas
														cd[5][1]); //bawah

		balokrumah(7.0f,10.0f,1.5f,-17.0f,10.0f,15.0f,	    cd[2][0], //depan
														cd[2][1], //belakang
														cd[2][2], //kiri
														cd[2][3], //kanan
														cd[2][4], //atas
														cd[2][5]); //bawah

		balokrumah(7.0f,5.0f,1.5f,-17.0f,30.0f,15.0f,	    cd[2][0], //depan
														cd[2][1], //belakang
														cd[2][2], //kiri
														cd[2][3], //kanan
														cd[2][4], //atas
														cd[2][5]); //bawah

		balokrumah(7.0f,10.0f,0.5f,-17.0f,20.0f,14.5f,	    cd[5][1], //depan   //jendela depan, kiri atas
														cd[5][1], //belakang
														cd[5][1], //kiri
														cd[5][1], //kanan
														cd[5][1], //atas
														cd[5][1]); //bawah
		
		balokrumah(1.0f,10.0f,1.5f,-14.0f,20.0f,15.0f,	    cd[1][4], //depan
														cd[1][4], //belakang
														cd[1][4], //kiri
														cd[1][4], //kanan
														cd[1][4], //atas
														cd[1][4]); //bawah

		balokrumah(7.0f,1.0f,1.5f,-17.0f,24.5f,15.0f,	    cd[1][4], //depan
														cd[1][4], //belakang
														cd[1][4], //kiri
														cd[1][4], //kanan
														cd[1][4], //atas
														cd[1][4]); //bawah
		glPushMatrix(); // jendela rumah depan kanan
			glTranslatef(27.0f,0.0f,0.0f);
			balokrumah(7.0f,10.0f,1.5f,-17.0f,-15.0f,15.0f,	    cd[2][0], //depan
															cd[2][1], //belakang
															cd[2][2], //kiri
															cd[2][3], //kanan
															cd[2][4], //atas
															cd[2][5]); //bawah
			balokrumah(7.0f,5.0f,1.5f,-17.0f,5.0f,15.0f,	    cd[2][0], //depan
															cd[2][1], //belakang
															cd[2][2], //kiri
															cd[2][3], //kanan
															cd[2][4], //atas
															cd[2][5]); //bawah

			balokrumah(7.0f,10.0f,1.5f,-17.0f,-5.0f,15.0f,	    cd[5][1], //depan   //jendela depan, kiri bawah
															cd[5][1], //belakang
															cd[5][1], //kiri
															cd[5][1], //kanan
															cd[5][1], //atas
															cd[5][1]); //bawah

			balokrumah(7.0f,10.0f,1.5f,-17.0f,10.0f,15.0f,	    cd[2][0], //depan
															cd[2][1], //belakang
															cd[2][2], //kiri
															cd[2][3], //kanan
															cd[2][4], //atas
															cd[2][5]); //bawah

			balokrumah(7.0f,5.0f,1.5f,-17.0f,30.0f,15.0f,	    cd[2][0], //depan
															cd[2][1], //belakang
															cd[2][2], //kiri
															cd[2][3], //kanan
															cd[2][4], //atas
															cd[2][5]); //bawah

			balokrumah(7.0f,10.0f,0.5f,-17.0f,20.0f,14.5f,	    cd[5][1], //depan   //jendela depan, kiri atas
															cd[5][1], //belakang
															cd[5][1], //kiri
															cd[5][1], //kanan
															cd[5][1], //atas
															cd[5][1]); //bawah
		
			balokrumah(1.0f,10.0f,1.5f,-14.0f,20.0f,15.0f,	    cd[1][4], //depan
															cd[1][4], //belakang
															cd[1][4], //kiri
															cd[1][4], //kanan
															cd[1][4], //atas
															cd[1][4]); //bawah

			balokrumah(7.0f,1.0f,1.5f,-17.0f,24.5f,15.0f,	    cd[1][4], //depan
															cd[1][4], //belakang
															cd[1][4], //kiri
															cd[1][4], //kanan
															cd[1][4], //atas
															cd[1][4]); //bawah

		glPopMatrix();
	glPopMatrix();
	};

	if(tdinding[2]==1){
	glPushMatrix(); //jendela belakang
		balokrumah(47.0f,10.0f,1.5f,-23.5f,-5.0f,-33.5f,	cd[5][1], //depan
														cd[5][1], //belakang
														cd[5][1], //kiri
														cd[5][1], //kanan
														cd[5][1], //atas
														cd[5][1]); //bawah

		balokrumah(47.0f,10.0f,1.5f,-23.5f,20.0f,-33.5f,	cd[5][1], //depan
														cd[5][1], //belakang
														cd[5][1], //kiri
														cd[5][1], //kanan
														cd[5][1], //atas
														cd[5][1]); //bawah
	glPopMatrix();
	};

	if(tdinding[3]==1){
	/////////////////////////////////////////////////////////////////////////////////////////jendela samping kiri
	glPushMatrix();
		balokrumah(1.5f,10.0f,1.0f,-25.0f,20.0f,0.5f,	    cd[1][4], //depan
														cd[1][4], //belakang
														cd[1][4], //kiri
														cd[1][4], //kanan
														cd[1][4], //atas
														cd[1][4]); //bawah

		balokrumah(1.5f,10.0f,1.0f,-25.0f,-5.0f,0.5f,	    cd[1][4], //depan
														cd[1][4], //belakang
														cd[1][4], //kiri
														cd[1][4], //kanan
														cd[1][4], //atas
														cd[1][4]); //bawah

		balokrumah(1.5f,10.0f,1.0f,-25.0f,20.0f,-19.5f,	    cd[1][4], //depan
														cd[1][4], //belakang
														cd[1][4], //kiri
														cd[1][4], //kanan
														cd[1][4], //atas
														cd[1][4]); //bawah

		balokrumah(1.5f,10.0f,1.0f,-25.0f,-5.0f,-19.5f,	    cd[1][4], //depan
														cd[1][4], //belakang
														cd[1][4], //kiri
														cd[1][4], //kanan
														cd[1][4], //atas
														cd[1][4]); //bawah
		///////////////////////////////////////////
		balokrumah(1.5f,1.0f,10.0f,-25.0f,24.5f,5.0f,	    cd[1][4], //depan
														cd[1][4], //belakang
														cd[1][4], //kiri
														cd[1][4], //kanan
														cd[1][4], //atas
														cd[1][4]); //bawah

		balokrumah(1.5f,1.0f,10.0f,-25.0f,-0.5f,5.0f,	    cd[1][4], //depan
														cd[1][4], //belakang
														cd[1][4], //kiri
														cd[1][4], //kanan
														cd[1][4], //atas
														cd[1][4]); //bawah

		balokrumah(1.5f,1.0f,10.0f,-25.0f,24.5f,-15.0f,	    cd[1][4], //depan
														cd[1][4], //belakang
														cd[1][4], //kiri
														cd[1][4], //kanan
														cd[1][4], //atas
														cd[1][4]); //bawah

		balokrumah(1.5f,1.0f,10.0f,-25.0f,-0.5f,-15.0f,	    cd[1][4], //depan
														cd[1][4], //belakang
														cd[1][4], //kiri
														cd[1][4], //kanan
														cd[1][4], //atas
														cd[1][4]); //bawah
		///////////////////////////////////////////////////////////////////////
		balokrumah(0.5f,10.0f,10.0f,-24.5f,-5.0f,-15.0f,	    cd[5][1], //depan
														cd[5][1], //belakang
														cd[5][1], //kiri
														cd[5][1], //kanan
														cd[5][1], //atas
														cd[5][1]); //bawah

		balokrumah(0.5f,10.0f,10.0f,-24.5f,-5.0f,5.0f,	    cd[5][1], //depan
														cd[5][1], //belakang
														cd[5][1], //kiri
														cd[5][1], //kanan
														cd[5][1], //atas
														cd[5][1]); //bawah

		balokrumah(0.5f,10.0f,10.0f,-24.5f,20.0f,-15.0f,	    cd[5][1], //depan
														cd[5][1], //belakang
														cd[5][1], //kiri
														cd[5][1], //kanan
														cd[5][1], //atas
														cd[5][1]); //bawah

		balokrumah(0.5f,10.0f,10.0f,-24.5f,20.0f,5.0f,	    cd[5][1], //depan
														cd[5][1], //belakang
														cd[5][1], //kiri
														cd[5][1], //kanan
														cd[5][1], //atas
														cd[5][1]); //bawah
	glPopMatrix();
	};

	if(tdinding[1]==1){
	/////////////////////////////////////////////////////////////////////////////////////////jendela samping kanan
	glPushMatrix();
		glTranslatef(48.5f,0.0f,0.0f);
		balokrumah(1.5f,10.0f,1.0f,-25.0f,20.0f,0.5f,	    cd[1][4], //depan
														cd[1][4], //belakang
														cd[1][4], //kiri
														cd[1][4], //kanan
														cd[1][4], //atas
														cd[1][4]); //bawah

		balokrumah(1.5f,10.0f,1.0f,-25.0f,-5.0f,0.5f,	    cd[1][4], //depan
														cd[1][4], //belakang
														cd[1][4], //kiri
														cd[1][4], //kanan
														cd[1][4], //atas
														cd[1][4]); //bawah

		balokrumah(1.5f,10.0f,1.0f,-25.0f,20.0f,-19.5f,	    cd[1][4], //depan
														cd[1][4], //belakang
														cd[1][4], //kiri
														cd[1][4], //kanan
														cd[1][4], //atas
														cd[1][4]); //bawah

		balokrumah(1.5f,10.0f,1.0f,-25.0f,-5.0f,-19.5f,	    cd[1][4], //depan
														cd[1][4], //belakang
														cd[1][4], //kiri
														cd[1][4], //kanan
														cd[1][4], //atas
														cd[1][4]); //bawah
		///////////////////////////////////////////
		balokrumah(1.5f,1.0f,10.0f,-25.0f,24.5f,5.0f,	    cd[1][4], //depan
														cd[1][4], //belakang
														cd[1][4], //kiri
														cd[1][4], //kanan
														cd[1][4], //atas
														cd[1][4]); //bawah

		balokrumah(1.5f,1.0f,10.0f,-25.0f,-0.5f,5.0f,	    cd[1][4], //depan
														cd[1][4], //belakang
														cd[1][4], //kiri
														cd[1][4], //kanan
														cd[1][4], //atas
														cd[1][4]); //bawah

		balokrumah(1.5f,1.0f,10.0f,-25.0f,24.5f,-15.0f,	    cd[1][4], //depan
														cd[1][4], //belakang
														cd[1][4], //kiri
														cd[1][4], //kanan
														cd[1][4], //atas
														cd[1][4]); //bawah

		balokrumah(1.5f,1.0f,10.0f,-25.0f,-0.5f,-15.0f,	    cd[1][4], //depan
														cd[1][4], //belakang
														cd[1][4], //kiri
														cd[1][4], //kanan
														cd[1][4], //atas
														cd[1][4]); //bawah
		///////////////////////////////////////////////////////////////////////
		balokrumah(0.5f,10.0f,10.0f,-24.5f,-5.0f,-15.0f,	    cd[5][1], //depan
														cd[5][1], //belakang
														cd[5][1], //kiri
														cd[5][1], //kanan
														cd[5][1], //atas
														cd[5][1]); //bawah

		balokrumah(0.5f,10.0f,10.0f,-24.5f,-5.0f,5.0f,	    cd[5][1], //depan
														cd[5][1], //belakang
														cd[5][1], //kiri
														cd[5][1], //kanan
														cd[5][1], //atas
														cd[5][1]); //bawah

		balokrumah(0.5f,10.0f,10.0f,-24.5f,20.0f,-15.0f,	    cd[5][1], //depan
														cd[5][1], //belakang
														cd[5][1], //kiri
														cd[5][1], //kanan
														cd[5][1], //atas
														cd[5][1]); //bawah

		balokrumah(0.5f,10.0f,10.0f,-24.5f,20.0f,5.0f,	    cd[5][1], //depan
														cd[5][1], //belakang
														cd[5][1], //kiri
														cd[5][1], //kanan
														cd[5][1], //atas
														cd[5][1]); //bawah
	glPopMatrix();
	};
};
void pintukiri(void){
	if(pintu==1){
	glPushMatrix();
		balokrumah(4.8f,20.0f,0.5f,-5.0f,-15.0f,14.5f,	    cd[5][3], //depan
														cd[5][3], //belakang
														cd[2][3], //kiri
														cd[2][3], //kanan
														cd[2][4], //atas
														cd[2][4]); //bawah

		balokrumah(0.5f,10.0f,0.5f,-1.5f,-10.0f,15.5f,	    cd[1][0], //depan
														cd[0][1], //belakang
														cd[0][1], //kiri
														cd[0][1], //kanan
														cd[0][1], //atas
														cd[0][1]); //bawah
	glPopMatrix();
	};
};
void pintukanan(void){
	if(pintu==1){
	glPushMatrix();
	balokrumah(4.8f,20.0f,0.5f,0.2f,-15.0f,14.5f,	    cd[5][3], //depan
													cd[5][3], //belakang
													cd[2][3], //kiri
													cd[2][3], //kanan
													cd[2][4], //atas
													cd[2][4]); //bawah

	balokrumah(0.5f,10.0f,0.5f,1.0f,-10.0f,15.5f,	    cd[1][0], //depan
													cd[0][1], //belakang
													cd[0][1], //kiri
													cd[0][1], //kanan
													cd[0][1], //atas
													cd[0][1]); //bawah
	glPopMatrix();
	};
};
void kacasegitiga(void){
	glPushMatrix();
		segitigarumah(25.0f,25.0f,20.0f,1.5f,0.0f,35.0f,15.0f,cd[0][0], //depan
															cd[0][1], //belakang
															cd[0][2], //kiri
															cd[0][3], //kanan
															cd[0][4]); //bawah
		segitigarumah(25.0f,25.0f,20.0f,1.5f,0.0f,35.0f,-33.5f,	cd[0][0], //depan
															cd[0][1], //belakang
															cd[0][2], //kiri
															cd[0][3], //kanan
															cd[0][4]); //bawah
	glPopMatrix();
};


void rumahistimewa(void){
	glPushMatrix();
	glTranslatef(45.0,-71.0,45.0);
		glPushMatrix();
		glScalef(0.1f,0.1f,0.1f);
		glRotatef(180.0,0.0,1.0,0.0);
			rumah();
			jendelarumah();
			pintukiri();
			pintukanan();
			kacasegitiga();
		glPopMatrix();
	glPopMatrix();
};
void rekursirumah(void){
	int i,j;
	float a,b;
	glPushMatrix();
	glTranslatef(ob[1].tx,ob[1].ty,ob[1].tz);
	glRotatef(ob[1].rx,	1.0,	0.0,	0.0);
	glRotatef(ob[1].ry,	0.0,	1.0,	0.0);
	glRotatef(ob[1].rz,	0.0,	0.0,	1.0);
	glScalef(ob[1].sx,ob[1].sy,ob[1].sz);
	glPushMatrix();
	for(i=0;i<12;i++){
		for(j=0;j<4;j++){
			a = (float) i*-8.0f;
			b = (float) j*-8.0f;
			glPushMatrix();
			glTranslatef(b,0.0,a);
			rumahistimewa();
			glPopMatrix();
		};
	};
	glPopMatrix();
	glPopMatrix();
};
void towern(void){
	glPushMatrix();
		glTranslatef(0.0f,-50.0f,0.0f);
		glPushMatrix();
			glRotatef(0.0,0.0,1.0,0.0);
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
			if(tjendela == 1){
				tabung(10.0f,10.0f,3.0f,0.0f,74.0f,0.0f,w[1],w[2],w[1]);//
			};
			tabung(10.0f,10.0f,1.0f,0.0f,73.0f,0.0f,w[1],w[4],w[1]);
			if(tjendela == 1){
				tabung(10.0f,10.0f,3.0f,0.0f,70.0f,0.0f,w[1],w[2],w[1]);//
			};
			tabung(10.0f,10.0f,1.0f,0.0f,69.0f,0.0f,w[1],w[4],w[1]);
			if(tjendela == 1){
				tabung(10.0f,10.0f,3.0f,0.0f,66.0f,0.0f,w[1],w[2],w[1]);
			};
			tabung(10.0f,10.0f,1.0f,0.0f,65.0f,0.0f,w[1],w[4],w[1]);
			//
			tabungtexture(3.0f,3.0f,70.0f,0.0f,-5.0f,0.0f,w[1],w[0],w[1]);
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
			glVertex3f(1.0	,0.0,	1.0+10.0);
			glVertex3f(1.0	,0.0,	-1.0+10.0);
			glVertex3f(-1.0	,0.0,	-1.0+10.0);
			glVertex3f(-1.0	,0.0,	1.0+10.0);
			glEnd();
		glPopMatrix();
};
void gembok(void){
	glPushMatrix();
		glScalef(0.1,0.1,0.1);
		baloktexture(20.0,20.0,5.0,0.0,0.0,0.0,w[11],w[11],w[12],w[12],w[11],w[11]);
		balok(2.0,15.0,2.0,8.0,20.0,0.0,w[13],w[13],w[14],w[14],w[13],w[13]);
		balok(2.0,15.0,2.0,-8.0,20.0,0.0,w[13],w[13],w[14],w[14],w[13],w[13]);
		balok(14.0,2.0,2.0,0.0,33.0,0.0,w[13],w[13],w[14],w[14],w[13],w[13]);
	glPopMatrix();

};
void pohongembok(void){
	int i,j;
	float a,b,c;
	glPushMatrix();
		glRotatef(animasirotasipohon,0.0,1.0,0.0);
		tabung(1.0f,1.0f,30.0f,0.0f,-5.0f,0.0f,w[1],w[3],w[1]);
		/*glPushMatrix();//sampel
			glTranslatef(2.0,21.0,0.0); //bawah -3 , kiri = 2
			gembok();
		glPopMatrix();*/
		
		for(i=0;i<5;i++){
			for(j=0;j<(i+1);j++){
				glPushMatrix();//kiri
					a=j*2.0;
					b=i*-3.0;
					glTranslatef(2.0+a,21.0+b,0.0);
					gembok();
				glPopMatrix();
			};
		};

		for(i=0;i<5;i++){
			for(j=0;j<(i+1);j++){
				glPushMatrix();//kanan
					a=j*-2.0;
					b=i*-3.0;
					glTranslatef(-2.0+a,21.0+b,0.0);
					gembok();
				glPopMatrix();
			};
		};

		for(i=0;i<5;i++){
			for(j=0;j<(i+1);j++){
				glPushMatrix();//depan
					a=j*-2.0;
					b=i*-3.0;
					glRotatef(90.0,0.0,1.0,0.0);
					glTranslatef(-2.0+a,21.0+b,0.0);
					gembok();
				glPopMatrix();
			};
		};
		for(i=0;i<5;i++){
			for(j=0;j<(i+1);j++){
				glPushMatrix();//depan
					a=j*-2.0;
					b=i*-3.0;
					glRotatef(-90.0,0.0,1.0,0.0);
					glTranslatef(-2.0+a,21.0+b,0.0);
					gembok();
				glPopMatrix();
			};
		};
	glPopMatrix();
};
void rekursipohon(void){
	glPushMatrix();
		glTranslatef(ob[2].tx,ob[2].ty,ob[2].tz);
		glRotatef(ob[2].rx,	1.0,	0.0,	0.0);
		glRotatef(ob[2].ry,	0.0,	1.0,	0.0);
		glRotatef(ob[2].rz,	0.0,	0.0,	1.0);
		glScalef(ob[2].sx,ob[2].sy,ob[2].sz);
		glPushMatrix();
			glScalef(0.5,0.5,0.5);
			glTranslatef(25.0,-122.0,-25.0);
			pohongembok();
		glPopMatrix();
		glPushMatrix();
			glScalef(0.5,0.5,0.5);
			glTranslatef(-25.0,-122.0,-25.0);
			pohongembok();
		glPopMatrix();
		glPushMatrix();
			glScalef(0.5,0.5,0.5);
			glTranslatef(-25.0,-122.0,25.0);
			pohongembok();
		glPopMatrix();
		glPushMatrix();
			glScalef(0.5,0.5,0.5);
			glTranslatef(25.0,-122.0,25.0);
			pohongembok();
		glPopMatrix();
	glPopMatrix();
};
void jembatan(void){
	int i;
	float z;
	glPushMatrix();
		glTranslatef(ob[3].tx,ob[3].ty,ob[3].tz);
		glRotatef(ob[3].rx,	1.0,	0.0,	0.0);
		glRotatef(ob[3].ry,	0.0,	1.0,	0.0);
		glRotatef(ob[3].rz,	0.0,	0.0,	1.0);
		glScalef(ob[3].sx,ob[3].sy,ob[3].sz);
		glPushMatrix();
			glTranslatef(0.0,-73.0,-30.0);
			for(i=0;i<11;i++){
				z = (float) i*3.0;
		
			glPushMatrix();	
				glTranslatef(9.0,6.0,-19.0);
				tabung(1.0f,1.0f,10.0f,0.0f,-5.0f,z,w[1],w[3],w[1]);
			glPopMatrix();
			glPushMatrix();	
				glTranslatef(-9.0,6.0,-19.0);
				tabung(1.0f,1.0f,10.0f,0.0f,-5.0f,z,w[1],w[3],w[1]);
			glPopMatrix();
			};
			balok(20.0f,1.0f,34.0f,0.0f,0.0f,-4.0f,w[11],w[11],w[12],w[12],w[11],w[11]);
			//balok(
		glPopMatrix();
	glPopMatrix();
};

void inisialisasi(void){
	glClearColor(0.7, 0.7, 0.7, 1.0);
	//glClearColor( 1.0,1.0,1.0,1.0);
	_textureID = loadBMP_custom("tembok.bmp");
	texturegembok = loadBMP_custom("gembok.bmp");
	glMatrixMode(GL_PROJECTION);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	conf.is_depth=1;
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// intensitas dan warna
	GLfloat qaAmbientLight[]	= {0.1, 0.1, 0.1, 0.1};
	GLfloat qaDiffuseLight[]	= {0.9, 0.9, 0.9, 1.0};
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
	GLfloat qaLightPosition[]	= {1.0, 1.0, -0.9, 0.3};
	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);

	conf.is_depth = 1;
	conf.rotasilokat[0]=0.0f;
	conf.rotasilokat[1]=0.0f;
	conf.rotasilokat[2]=0.0f;
	glMatrixMode(GL_MODELVIEW);
	glPointSize(9.0);
	glLineWidth(6.0f);
};
void tampilkan(void){
	if (conf.is_depth){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}else{
		glClear(GL_COLOR_BUFFER_BIT);
	};
	GLfloat qaBlack[] = {0.0,0.0,0.0,1.0};
	GLfloat qaGreen[] = {0.0,0.0,0.0,1.0};
	GLfloat qaWhite[] = {0.0,0.0,0.0,1.0};
	glMaterialfv(GL_FRONT, GL_AMBIENT, qaGreen);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, qaGreen);
	glMaterialfv(GL_FRONT, GL_SPECULAR,qaWhite);
	glMaterialf(GL_FRONT,GL_SHININESS, 0.0);
	
	glPushMatrix();
		glScalef(0.5f,0.5f,0.5f);
		glRotatef(180.0,0.0,1.0,0.0);
		towern();
		rekursirumah();
		rekursipohon();
		jembatan();
		//titiktengah();
		
	glPopMatrix();
	glutSwapBuffers();
};
void ukurancanvas(int lebar,int tinggi){
	if (tinggi == 0){
		tinggi = 1;
	};

	/*glMatrixMode(GL_PROJECTION);
	
	gluPerspective(50.0, lebar / tinggi, 5.0, 500.0);
	glTranslatef(0.0f, -5.0f, -150.0f);
	glMatrixMode(GL_MODELVIEW);*/
	//glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glViewport(0,0,lebar,tinggi);
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
		//cout<<"pos x = "<< lokasixyz[0]<<"; pos y = "<<lokasixyz[1]<<endl;
		tampilkan();
		
		glutPostRedisplay();
		fx = x;
		fy = y;
	}
};

int kontrol[6] = {1,0,0,0,0,0};
/*
jika
kontrol0 semua object
kontrol1 1 rumah;
kontrol2 2 pohon
kontrol3 3 jembatan
kontrol4 4 meja stasiun radio
kontrol5 5 mic radio
*/
void ubahanimasi(void){
	if(enablerotasipohon==1){
		enablerotasipohon=0;
		cout<<"disable "<<enablerotasipohon <<endl;
	}else{
		enablerotasipohon=1;
		cout<<"enable "<<enablerotasipohon <<endl;
	};

};
void toglejendela(void){
	if(tjendela==1){
		tjendela=0;		
	}else{
		tjendela=1;
	};
	cout<<tjendela<<endl;
};
void keyboard(unsigned char key, int x, int y){
	switch(key){
		//rotate
		case('w'):
		case('W'):
			if(kontrol[0] ==1){
				glRotatef(-5.0,1.0,0.0,0.0);
			}else if(kontrol[1]==1){
				ob[1].rx+=1.0;
			}else if(kontrol[2]==1){
				ob[2].rx+=1.0;
			}else if(kontrol[3]==1){
				ob[3].rx+=1.0;
			}else if(kontrol[4]==1){
			}else if(kontrol[5]==1){
			};
			break;
		case('s'):
		case('S'):
			if(kontrol[0] ==1){
				glRotatef(5.0,1.0,0.0,0.0);
			}else if(kontrol[1]==1){
				ob[1].rx-=1.0;
			}else if(kontrol[2]==1){
				ob[2].rx-=1.0;
			}else if(kontrol[3]==1){
				ob[3].rx-=1.0;
			}else if(kontrol[4]==1){
			}else if(kontrol[5]==1){
			};
			break;
		case('a'):
		case('A'):
			if(kontrol[0] ==1){
				glRotatef(-5.0,0.0,1.0,0.0);
			}else if(kontrol[1]==1){
				ob[1].ry-=1.0;
			}else if(kontrol[2]==1){
				ob[2].ry-=1.0;
			}else if(kontrol[3]==1){
				ob[3].ry-=1.0;
			}else if(kontrol[4]==1){
			}else if(kontrol[5]==1){
			};
			break;
		case('d'):
		case('D'):
			if(kontrol[0] ==1){
				glRotatef(5.0,0.0,1.0,0.0);
			}else if(kontrol[1]==1){
				ob[1].ry+=1.0;
			}else if(kontrol[2]==1){
				ob[2].ry+=1.0;
			}else if(kontrol[3]==1){
				ob[3].ry+=1.0;
			}else if(kontrol[4]==1){
			}else if(kontrol[5]==1){
			};
			break;
		case('q'):
		case('Q'):
			if(kontrol[0] ==1){
				glRotatef(-5.0,0.0,0.0,1.0);
			}else if(kontrol[1]==1){
				ob[1].rz+=1.0;
			}else if(kontrol[2]==1){
				ob[2].rz+=1.0;
			}else if(kontrol[3]==1){
				ob[3].rz+=1.0;
			}else if(kontrol[4]==1){
			}else if(kontrol[5]==1){
			};
			break;
		case('e'):
		case('E'):
			if(kontrol[0] ==1){
				glRotatef(5.0,0.0,0.0,1.0);
			}else if(kontrol[1]==1){
				ob[1].rz-=1.0;
			}else if(kontrol[2]==1){
				ob[2].rz-=1.0;
			}else if(kontrol[3]==1){
				ob[3].rz-=1.0;
			}else if(kontrol[4]==1){
			}else if(kontrol[5]==1){
			};
			break;
		//skalasi
		case('r'):
		case('R'):
			if(kontrol[0] ==1){
				glScalef(1.05,1.05,1.05);
			}else if(kontrol[1]==1){
				ob[1].sx+=0.05;
				ob[1].sy+=0.05;
				ob[1].sz+=0.05;
			}else if(kontrol[2]==1){
				ob[2].sx+=0.05;
				ob[2].sy+=0.05;
				ob[2].sz+=0.05;
			}else if(kontrol[3]==1){
				ob[3].sx+=0.05;
				ob[3].sy+=0.05;
				ob[3].sz+=0.05;
			}else if(kontrol[4]==1){
			}else if(kontrol[5]==1){
			};
			break;
		case('f'):
		case('F'):
			if(kontrol[0] ==1){
				glScalef(0.95,0.95,0.95);
			}else if(kontrol[1]==1){
				ob[1].sx-=0.05;
				ob[1].sy-=0.05;
				ob[1].sz-=0.05;
			}else if(kontrol[2]==1){
				ob[2].sx-=0.05;
				ob[2].sy-=0.05;
				ob[2].sz-=0.05;
			}else if(kontrol[3]==1){
				ob[3].sx-=0.05;
				ob[3].sy-=0.05;
				ob[3].sz-=0.05;
			}else if(kontrol[4]==1){
			}else if(kontrol[5]==1){
			};
			break;
		//translate
		case('i'):
		case('I'):
			if(kontrol[0] ==1){
				glTranslatef(+0.0,+1.0,+0.0);
			}else if(kontrol[1]==1){
				ob[1].tz+=1.0;
			}else if(kontrol[2]==1){
				ob[2].tz+=1.0;
			}else if(kontrol[3]==1){
				ob[3].tz+=1.0;
			}else if(kontrol[4]==1){
			}else if(kontrol[5]==1){
			};
			break;
		case('k'):
		case('K'):
			if(kontrol[0] ==1){
				glTranslatef(+0.0,-1.0,+0.0);
			}else if(kontrol[1]==1){
				ob[1].tz-=1.0;
			}else if(kontrol[2]==1){
				ob[2].tz-=1.0;
			}else if(kontrol[3]==1){
				ob[3].tz-=1.0;
			}else if(kontrol[4]==1){
			}else if(kontrol[5]==1){
			};
			break;
		case('j'):
		case('J'):
			if(kontrol[0] ==1){
				glTranslatef(-1.0,+0.0,+0.0);
			}else if(kontrol[1]==1){
				ob[1].tx+=1.0;
			}else if(kontrol[2]==1){
				ob[2].tx+=1.0;
			}else if(kontrol[3]==1){
				ob[3].tx+=1.0;
			}else if(kontrol[4]==1){
			}else if(kontrol[5]==1){
			};
			break;
		case('l'):
		case('L'):
			if(kontrol[0] ==1){
				glTranslatef(+1.0,+0.0,+0.0);
			}else if(kontrol[1]==1){
				ob[1].tx-=1.0;
			}else if(kontrol[2]==1){
				ob[2].tx-=1.0;
			}else if(kontrol[3]==1){
				ob[3].tx-=1.0;
			}else if(kontrol[4]==1){
			}else if(kontrol[5]==1){
			};
			break;
		case('u'):
		case('U'):
			if(kontrol[0] ==1){
				glTranslatef(+0.0,+0.0,+1.0);
			}else if(kontrol[1]==1){
				ob[1].ty+=1.0;
			}else if(kontrol[2]==1){
				ob[2].ty+=1.0;
			}else if(kontrol[3]==1){
				ob[3].ty+=1.0;
			}else if(kontrol[4]==1){
			}else if(kontrol[5]==1){
			};
			break;
		case('o'):
		case('O'):
			if(kontrol[0] ==1){
				glTranslatef(+0.0,+0.0,-1.0);
			}else if(kontrol[1]==1){
				ob[1].ty-=1.0;
			}else if(kontrol[2]==1){
				ob[2].ty-=1.0;
			}else if(kontrol[3]==1){
				ob[3].ty-=1.0;
			}else if(kontrol[4]==1){
			}else if(kontrol[5]==1){
			};
			break;
	};
	tampilkan();
};
void keyatas(unsigned char key, int x, int y){
	switch(key){
		case('z'): //memulai animasi pohon berputar
			ubahanimasi();
			
			break;
		case('x'):
			toglejendela();
			
			break;
		case('1'):
			kontrol[0]=1;
			kontrol[1]=0;
			kontrol[2]=0;
			kontrol[3]=0;
			kontrol[4]=0;
			kontrol[5]=0;
			cout << "KONTROL : SEMUA OBJEK"<<endl;
			break;
		case('2'):
			kontrol[0]=0;
			kontrol[1]=1;
			kontrol[2]=0;
			kontrol[3]=0;
			kontrol[4]=0;
			kontrol[5]=0;
			cout << "KONTROL : OBJEK RUMAH"<<endl;
			break;
		case('3'):
			kontrol[0]=0;
			kontrol[1]=0;
			kontrol[2]=1;
			kontrol[3]=0;
			kontrol[4]=0;
			kontrol[5]=0;
			cout << "KONTROL : SEMUA POHON"<<endl;
			break;
		case('4'):
			kontrol[0]=0;
			kontrol[1]=0;
			kontrol[2]=0;
			kontrol[3]=1;
			kontrol[4]=0;
			kontrol[5]=0;
			break;
		case('5'):
			kontrol[0]=0;
			kontrol[1]=0;
			kontrol[2]=0;
			kontrol[3]=0;
			kontrol[4]=1;
			kontrol[5]=0;
			break;
		case('6'):
			kontrol[0]=0;
			kontrol[1]=0;
			kontrol[2]=0;
			kontrol[3]=0;
			kontrol[4]=0;
			kontrol[5]=1;
			break;
	};
	tampilkan();
};
void waktuloop(int) {
	//glPushMatrix();
	//glPopMatrix();
	int hasil = enablerotasipohon;
	if(hasil==1){
		if(animasirotasipohon>=360.0){
			animasirotasipohon=0.0;
		};
		animasirotasipohon = animasirotasipohon +1;
	};
	glutPostRedisplay(); //redisplay pada glutDisplayFunc(tampil);
	glutTimerFunc(600/60, waktuloop, 0);

};
void initdatastruct(void){
	ob[1].rx =0.0;
	ob[1].ry= 0.0;
	ob[1].rz=0.0;
	ob[1].tx=0.0;
	ob[1].ty=0.0;
	ob[1].tz=0.0;
	ob[1].sx=1.0;
	ob[1].sy=1.0;
	ob[1].sz=1.0;
	//
	ob[2].rx =0.0;
	ob[2].ry= 0.0;
	ob[2].rz=0.0;
	ob[2].tx=0.0;
	ob[2].ty=0.0;
	ob[2].tz=0.0;
	ob[2].sx=1.0;
	ob[2].sy=1.0;
	ob[2].sz=1.0;
	//
	ob[3].rx =0.0;
	ob[3].ry= 0.0;
	ob[3].rz=0.0;
	ob[3].tx=0.0;
	ob[3].ty=0.0;
	ob[3].tz=0.0;
	ob[3].sx=1.0;
	ob[3].sy=1.0;
	ob[3].sz=1.0;
	//
	ob[4].rx =0.0;
	ob[4].ry= 0.0;
	ob[4].rz=0.0;
	ob[4].tx=0.0;
	ob[4].ty=0.0;
	ob[4].tz=0.0;
	ob[4].sx=1.0;
	ob[4].sy=1.0;
	ob[4].sz=1.0;
	//
	ob[5].rx =0.0;
	ob[5].ry= 0.0;
	ob[5].rz=0.0;
	ob[5].tx=0.0;
	ob[5].ty=0.0;
	ob[5].tz=0.0;
	ob[5].sx=1.0;
	ob[5].sy=1.0;
	ob[5].sz=1.0;
};
int main(int argc,char **argv){
	cout<<"==========================================="<<endl;
	cout<<"Panduan kontrol keyboard"<<endl;
	cout<<"angka 1 - 6 = memilih objek [semesta , rumah, pohon, jembatan, meja stasiun radio, mic radio]"<<endl;
	cout<< "wasdqeWASDQE = digunakan untuk merotasi objek yang dipilih"<<endl;
	cout<<"ijkluoIJKLUO = digunakan untuk merotasi objek yang dipilih"<<endl;
	cout<<"rfRF = melakukan skalasi terhadap objek yang dipilih"<<endl;
	cout<<"z = lakukan animasi pada pohon"<<endl;
	cout<<"x = tampilkan / hilangkan jendela tower"<<endl;
	cout<<"==========================================="<<endl;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(80, 100);
	glutCreateWindow("TUGAS RANCANG - NAMSAN TOWER [672018159 - 672018161]");
	initdatastruct();
	inisialisasi();
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glutDisplayFunc(tampilkan);
	glutReshapeFunc(ukurancanvas);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyatas);
	glutMouseFunc(mouse2);
	glutMotionFunc(gerakmouse);
	glutTimerFunc(0,waktuloop,0);
	glutMainLoop();
	
return 0;
};