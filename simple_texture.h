#ifndef _SIMPLE_TEXTURE_H_
#define _SIMPLE_TEXTURE_H_

typedef unsigned int GLuint;

struct bitmap;

bitmap* load_bmp(const char* filename);
bitmap* create_bitmap(int w, int h, void* data, void* free);
void destroy_bitmap(bitmap* img);
GLuint CreateTexture(bitmap* img);
GLuint CreateTextureFromBMP(const char* filename);
void DestroyTexture(GLuint tex);

#endif //_SIMPLE_TEXTURE_H_
