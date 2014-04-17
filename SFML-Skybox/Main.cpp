#include "Main.h"										// This includes our header file
#include "Camera.h"										// This includes our camera class header

CCamera g_Camera;										// This is our global camera object

#define BACK_ID		0									// The texture ID for the back side of the cube
#define FRONT_ID	1									// The texture ID for the front side of the cube
#define BOTTOM_ID	2									// The texture ID for the bottom side of the cube
#define TOP_ID		3									// The texture ID for the top side of the cube
#define LEFT_ID		4									// The texture ID for the left side of the cube
#define RIGHT_ID	5									// The texture ID for the right side of the cube

UINT g_Texture[MAX_TEXTURES] = {0};						// This holds the texture info, referenced by an ID

#define SPEED	0.03f									// This is how fast our camera moves

void CreateSkyBox(float x, float y, float z, float width, float height, float length)
{

	// Bind the BACK texture of the sky map to the BACK side of the cube
	glBindTexture(GL_TEXTURE_2D, g_Texture[BACK_ID]);

	// Since we want the sky box to be centered around X, Y, and Z for ease,
	// we do a little math to accomplish this.  We just change the X, Y and Z
	// to perform this task.  If we just minus half the width, height and length
	// from x, y and z it will give us the desired result.  Now when we create the
	// box it will center it around (x, y, z)

	// This centers the sky box around (x, y, z)
	x = x - width  / 2;
	y = y - height / 2;
	z = z - length / 2;

		// Start drawing the side as a QUAD
	glBegin(GL_QUADS);		
		
		// Assign the texture coordinates and vertices for the BACK Side
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y,			z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,			y + height, z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,			y,			z);
		
	glEnd();

	// Bind the FRONT texture of the sky map to the FRONT side of the box
	glBindTexture(GL_TEXTURE_2D, g_Texture[FRONT_ID]);

	// Start drawing the side as a QUAD
	glBegin(GL_QUADS);	
	
		// Assign the texture coordinates and vertices for the FRONT Side
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,			y,			z + length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,			y + height, z + length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,			z + length);
	glEnd();

	// Bind the BOTTOM texture of the sky map to the BOTTOM side of the box
	glBindTexture(GL_TEXTURE_2D, g_Texture[BOTTOM_ID]);

	// Start drawing the side as a QUAD
	glBegin(GL_QUADS);		
	
		// Assign the texture coordinates and vertices for the BOTTOM Side
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,			y,			z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,			y,			z + length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y,			z + length); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,			z);
	glEnd();

	// Bind the TOP texture of the sky map to the TOP side of the box
	glBindTexture(GL_TEXTURE_2D, g_Texture[TOP_ID]);
	
	// Start drawing the side as a QUAD
	glBegin(GL_QUADS);		
		
		// Assign the texture coordinates and vertices for the TOP Side
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z + length); 
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,			y + height,	z + length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,			y + height,	z);
		
	glEnd();

	// Bind the LEFT texture of the sky map to the LEFT side of the box
	glBindTexture(GL_TEXTURE_2D, g_Texture[LEFT_ID]);
	
	// Start drawing the side as a QUAD
	glBegin(GL_QUADS);		
		
		// Assign the texture coordinates and vertices for the LEFT Side
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,			y + height,	z);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,			y + height,	z + length); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,			y,			z + length);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,			y,			z);		
		
	glEnd();

	// Bind the RIGHT texture of the sky map to the RIGHT side of the box
	glBindTexture(GL_TEXTURE_2D, g_Texture[RIGHT_ID]);

	// Start drawing the side as a QUAD
	glBegin(GL_QUADS);		

		// Assign the texture coordinates and vertices for the RIGHT Side
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,			z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y,			z + length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height,	z + length); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height,	z);
	glEnd();
}



void Init()
{
		
	// Below we read in the 6 texture maps used for the sky box.
	// The ID's are important, so don't mix them up.  There is a
	// texture for every side of the box.

	CreateTexture(g_Texture, "Back.bmp",	BACK_ID		);
	CreateTexture(g_Texture, "Front.bmp",	FRONT_ID	);
	CreateTexture(g_Texture, "Bottom.bmp",	BOTTOM_ID	);
	CreateTexture(g_Texture, "Top.bmp",		TOP_ID		);
	CreateTexture(g_Texture, "Left.bmp",	LEFT_ID		);
	CreateTexture(g_Texture, "Right.bmp",	RIGHT_ID	);

	// Give our camera a decent starting point in the world
	g_Camera.PositionCamera( 0, 0, 0,	0, 0, 1,	0, 1, 0);
}

int main()
{

////////////////////////////////////////////////////////////
/// Initialize functions
////////////////////////////////////////////////////////////
    // Create the main window
    sf::Window App(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_DEPTH), "SFML Skybox");

	Init();


////////////////////////////////////////////////////////////
/// Main Loop
////////////////////////////////////////////////////////////

    while (App.IsOpened())
    {
        // Process events
        sf::Event Event;
        while (App.GetEvent(Event))
        {
            // Close window : exit
            if (Event.Type == sf::Event::Closed)
                App.Close();

            // Escape key : exit
            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
                App.Close();

            // Resize event : adjust viewport
            if (Event.Type == sf::Event::Resized)
                glViewport(0, 0, Event.Size.Width, Event.Size.Height);
        }

        // Set the active window before using OpenGL commands
        // It's useless here because active window is always the same,
        // but don't forget it if you use multiple windows or controls
        App.SetActive();

		g_Camera.Update();							// Update the camera data

		RenderScene();								// Update the screen every frame (Not good in a game)


////////////////////////////////////////////////////////////
/// Post redisplay
////////////////////////////////////////////////////////////

        // Finally, display rendered frame on screen
        App.Display();
    }

    return EXIT_SUCCESS;
}

void RenderScene() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	glLoadIdentity();									// Reset The matrix
	
	g_Camera.Look();									// Give OpenGL our camera position

	// Here we create our sky box.  It will be centered around (0, 0, 0) with
	// a width of 400, height of 200 and length of 400. 
	
	CreateSkyBox(0, 0, 0, 400, 200, 400);				// Draw the sky box centered at (0, 0, 0)

}