#ifndef _MAIN_H
#define _MAIN_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Windows.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>							// This includes our Graphics header for Image



////////////////////////////////////////////////////////////
// Globals
////////////////////////////////////////////////////////////

#define SCREEN_WIDTH 800								// We want our screen width 800 pixels
#define SCREEN_HEIGHT 600								// We want our screen height 600 pixels
#define SCREEN_DEPTH 16									// We want 16 bits per pixel

#define MAX_TEXTURES 100


// We need to define this for glTexParameteri()
#define GL_CLAMP_TO_EDGE	0x812F						// This is for our skybox textures

// This is our basic 3D point/vector class
struct CVector3
{
public:
	
	// A default constructor
	CVector3() {}

	// This is our constructor that allows us to initialize our data upon creating an instance
	CVector3(float X, float Y, float Z) 
	{ 
		x = X; y = Y; z = Z;
	}

	// Here we overload the + operator so we can add vectors together 
	CVector3 operator+(CVector3 vVector)
	{
		// Return the added vectors result.
		return CVector3(vVector.x + x, vVector.y + y, vVector.z + z);
	}

	// Here we overload the - operator so we can subtract vectors 
	CVector3 operator-(CVector3 vVector)
	{
		// Return the subtracted vectors result
		return CVector3(x - vVector.x, y - vVector.y, z - vVector.z);
	}
	
	// Here we overload the * operator so we can multiply by scalars
	CVector3 operator*(float num)
	{
		// Return the scaled vector
		return CVector3(x * num, y * num, z * num);
	}

	// Here we overload the / operator so we can divide by a scalar
	CVector3 operator/(float num)
	{
		// Return the scale vector
		return CVector3(x / num, y / num, z / num);
	}

	float x, y, z;						
};



// This loads a texture into openGL from a file (IE, "bitmap.bmp")
void CreateTexture(UINT textureArray[], LPSTR strFileName, int textureID);

void Init();

void RenderScene();

#endif 