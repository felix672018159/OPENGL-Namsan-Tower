#pragma once
#include <stdio.h>
#include <iostream>
#include <gl/glut.h>
using namespace std;
GLuint loadBMP_custom(const char* imagepath){
	unsigned char header[54];
	unsigned char dataPos;
	unsigned int width,height;
	unsigned int imageSize;
	unsigned char* data;
	
	FILE* file;
	fopen_s(&file, imagepath, "rb");
	if(!file){printf("gambar tidak dapat dibuka !\n"); return 0;};

	if(fread(header,1 ,54, file)!=54){
		printf("bukan merupakan file BMP\n");
		fclose(file);
		return 0;
	};

	if(header[0] != 'B' || header[1] != 'M'){
		printf("bukan merupakan bmp file yang benar");
		fclose(file);
		return 0;
	};	

	if (*(int*)&(header[0x1E]) != 0){printf("bukan merupakan bmp file yang benar"); return 0;};
	if (*(int*)&(header[0x1C]) != 24){printf("bukan merupakan bmp file yang benar"); return 0;};
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int *)&(header[0x12]);
	height = *(int *)&(header[0x16]);
	if (imageSize == 0) imageSize = width * height * 3;
	if (dataPos == 0) dataPos = 54;

	

	data = new unsigned char[imageSize];
	fread(data, 1, imageSize,file);
	fclose(file);

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,GL_RGB,GL_UNSIGNED_BYTE, data);
	delete[] data;
	return textureID;
};