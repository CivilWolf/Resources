#if defined(__APPLE__)

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>


#endif
#if defined(__linux__)

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2_mixer/SDL_mixer.h"

#endif
#if defined(_WIN32) || (_WIN64)

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

#endif
#if defined(__linux__)
#include <unistd.h>
#endif

#include <stdio.h>
#include <iostream>

#include <sstream>
//#include <string>
using namespace std;
#include <vector>
#include "bullet.h"

class Player{
public:
	Mix_Chunk *arrow;

	vector<Bullet> bulletList;

	string playerPath;
	int playerNum;
	SDL_Surface*surface;
	SDL_Texture*texture;
	SDL_Rect posRect;
	float xDir;
	float yDir;
	float speed;
	float pos_X,pos_Y;

	Player(SDL_Renderer*,int pNum,string filePath, string audioPath,float x,float y);

	void Update(float deltaTime);
	void Draw(SDL_Renderer*renderer);
	void OnControllerAxis(const SDL_ControllerAxisEvent event);
	void OnControllerButton(const SDL_ControllerButtonEvent event);
	~Player();
private:
	void CreateBullet();

};
