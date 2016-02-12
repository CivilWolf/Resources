// Example program:
// Using SDL2 to create an application window

#if defined(__APPLE__)

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "SDL2_mixer/SDL_mixer.h"

#endif
#if defined(__linux__)

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

#endif
#if defined(_WIN32) || (_WIN64)

#include "SDL.h"
#include <direct.h>
#include "SDL_image.h"
#include "SDL_mixer.h"
#define getcwd _getcwd

#endif
#if defined(__linux__)
#include <unistd.h>
#endif

#include <stdio.h>
#include <iostream>
//#include "player.h"
//#include <string>
using namespace std;
#include <stdlib.h>
class Enemy
{
public:
	bool active;
	SDL_Texture*texture;
	SDL_Rect posRect;
	float xDir,yDir;
	float speed;
	float pos_X,pos_Y;
	float angle;
	SDL_Point center;

	Enemy(SDL_Renderer*renderer,string filePath);
	void Update(float deltaTime);
	void Draw(SDL_Renderer*renderer);
	void Reset();
	~Enemy();
};
