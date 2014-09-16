#include <fstream>
#include "Textures.h"

using namespace std;

/** Default constructor */
Textures::Textures()
{
}

/** Default destructor */
Textures::~Textures()
{
}

Textures* Textures::instance = NULL;

/** Return the global instance for our class */
Textures* Textures::GetInstance()
{
	if(instance == NULL)
		instance = new Textures();

	return instance;
}

/** Load all the textures from the Assets folder into our texture vector */
void Textures::LoadGLTextures()
{
	textures[0] = SOIL_load_OGL_texture
        (
        "Assets/Untitled.bmp",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

/** Return the texture vector */
GLuint* Textures::GetTextures()
{
	return textures;
}