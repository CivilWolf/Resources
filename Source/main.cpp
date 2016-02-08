// Example program:
// Using SDL2 to create an application window

#if defined(__APPLE__)

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#endif
#if defined(__linux__)

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#endif
#if defined(_WIN32) || (_WIN64)

#include "SDL.h"
#include <direct.h>
#include "SDL_image.h"
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

int bkgdSpeed = 100;

SDL_Rect bkgd1Pos, bkgd2Pos;

//set temp variables to hold movement
float BG1pos_X = 0, BG1pos_Y = 0;

//set temp variables to hold movement
float BG2pos_X = 0, BG2pos_Y = -1024;

//code for frame rate independence
float deltaTime = 0.0;
int thisTime = 0;
int lastTime = 0;

//move the background
void UpdateBackground(float deltaTime) {
	//Update
	//Update Background 1
	BG1pos_Y += (bkgdSpeed * 1) * deltaTime;
	//Set the new bkgd1 position
	bkgd1Pos.y = (int) (BG1pos_Y + 0.5f);

	//reset when off the bottom of the screen
	if (bkgd1Pos.y >= 1024) {
		bkgd1Pos.y = -1024;
		BG1pos_Y = bkgd1Pos.y;
	}

	//Update Background 2
	BG2pos_Y += (bkgdSpeed * 1) * deltaTime;
	//Set the new bkgd1 position
	bkgd2Pos.y = (int) (BG2pos_Y + 0.5f);

	//reset when off the bottom of the screen
	if (bkgd2Pos.y >= 1024) {
		bkgd2Pos.y = -1024;
		BG2pos_Y = bkgd2Pos.y;
	}
}
//new Joystick vars

//analog joystick dead zone
const int JOYSTICK_DEAD_ZONE = 8000;
//joystick direction vars
float xDir, yDir;
//CURSOR FLOAT VARS FOR MOVEMENT
float pos_X, pos_Y;
SDL_Rect cursorPos, activePos;
int cursorSpeed = 400;

void moveCursor(const SDL_ControllerAxisEvent event) {
	//check joystick 0 - firstplayer
	if (event.which == 0) {
		//check X axis
		if (event.axis == 0) {
			if (event.value < -JOYSTICK_DEAD_ZONE) {
				xDir = -1.0f;

			}
			else if (event.value > JOYSTICK_DEAD_ZONE) {
				xDir = 1.0f;
			}
			else {
				xDir = 0.0f;
			}
		}
		if (event.axis == 1) {
			if (event.value < -JOYSTICK_DEAD_ZONE) {
				yDir = -1.0f;

			}
			else if (event.value > JOYSTICK_DEAD_ZONE) {
				yDir = 1.0f;
			}
			else {
				yDir = 0.0f;
			}
		}
	}
}
void UpdateCursor(float deltaTime) {
	pos_X += (cursorSpeed * xDir) * deltaTime;
	pos_Y += (cursorSpeed * yDir) * deltaTime;

	//assign SDL_Rect X and Y
	cursorPos.x = (int) (pos_X + 0.5f);
	cursorPos.y = (int) (pos_Y + 0.5f);
	//update active position of cursor - collision box
	activePos.x = cursorPos.x;
	activePos.y = cursorPos.y;

	//off the screen in X
	if (cursorPos.x < 0) {
		cursorPos.x = 0;
		pos_X = cursorPos.x;

	}
	if (cursorPos.x > 1024 - cursorPos.w) {
		cursorPos.x = 1024 - cursorPos.w;
		pos_X = cursorPos.x;

	}
	//off the screen in Y
	if (cursorPos.y < 0) {
		cursorPos.y = 0;
		pos_Y = cursorPos.y;
	}
	if (cursorPos.y > 1024 - cursorPos.h) {
		cursorPos.y = 1024 - cursorPos.h;
		pos_Y = cursorPos.y;
	}
}
bool players1Over = false, players2Over = false, instructionsOver = false,
		quitOver = false, menuOver = false, playOver = false;


#include "player.h"


int main(int argc, char* argv[]) {

	SDL_Window *window;                    // Declare a pointer

	SDL_Init(SDL_INIT_EVERYTHING);              // Initialize SDL2

	// Create an application window with the following settings:
	window = SDL_CreateWindow("An SDL2 window",                  // window title
			SDL_WINDOWPOS_UNDEFINED,           // initial x position
			SDL_WINDOWPOS_UNDEFINED,           // initial y position
			1024,                               // width, in pixels
			1024,                               // height, in pixels
			SDL_WINDOW_OPENGL                  // flags - see below
			);

#if defined(__APPLE__)
	{
		cout << "Running on Apple" << endl;
		//get the current working directory
		string currentWorkingDirectory(getcwd(NULL, 0));

		//create a string linking to the mac's images folder
		string images_dir = currentWorkingDirectory + "/Resources/Images/";
	}
#endif

#if defined(__APPLE__)
	{
		cout << "Running on Linux" << endl;
		//get the current working directory
		string currentWorkingDirectory(getcwd(NULL, 0));

		//create a string linking to the mac's images folder
		string images_dir = currentWorkingDirectory + "/Resources/Images/";
	}
#endif

#if defined(_WIN32) || (_WIN64)
	{
		cout << "Running on Windows" << endl;
		//get the current working directory
		string currentWorkingDirectory(getcwd(NULL, 0));

		//create a string linking to the mac's images folder
		string images_dir = currentWorkingDirectory + "\\Resources\\Images\\";
	}
#endif

	// Check that the window was successfully created
	if (window == NULL) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		//quit = true;
		return 1;
	}

	SDL_Renderer*renderer = NULL;

	//create renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);



	string currentWorkingDirectory(getcwd(NULL, 0));
	string images_dir = currentWorkingDirectory + "/Resources/Images/";
	//CreateBackground
	string BKGDpath = images_dir + "Path.bmp";

	Player player1 =Player(renderer,0,images_dir.c_str(),250.0,500.0);
	Player player2 = Player(renderer, 1, images_dir.c_str(), 750.0, 500.0);


	//create a SDL surface to hold the background images
	SDL_Surface *surface = IMG_Load((BKGDpath).c_str());

	//create SDL_Texture
	SDL_Texture*bkgd1;
	//place surface info into the texture bkgd1;
	bkgd1 = SDL_CreateTextureFromSurface(renderer, surface);

	//create SDL_Texture
	SDL_Texture*bkgd2;
	//place surface info into the texture bkgd1;
	bkgd2 = SDL_CreateTextureFromSurface(renderer, surface);

	//free SDL surface
	SDL_FreeSurface(surface);

	//Create the SDL_Rectangle for the texture's position and size -x,y,w,h

	//set the X,T,W, and H for the Rectangle
	bkgd1Pos.x = 0;
	bkgd1Pos.y = 0;
	bkgd1Pos.w = 1024;
	bkgd1Pos.h = 1024;

	//Create the SDL_Rectangle for the texture's position and size -x,y,w,h

	//set the X,T,W, and H for the Rectangle
	bkgd2Pos.x = 0;
	bkgd2Pos.y = -768;
	bkgd2Pos.w = 1024;
	bkgd2Pos.h = 1024;

	//**************************************Create Background -End*************************************

	//*************************************Create Cursor -Start**************************************
	//create a SDL surface to hold the background images
	surface = IMG_Load((images_dir + "Cursor.bmp").c_str());

	//create SDL_Texture
	SDL_Texture*cursor;
	//place surface info into the texture bkgd1;
	cursor = SDL_CreateTextureFromSurface(renderer, surface);

	//free SDL surface
	SDL_FreeSurface(surface);

	//Create the SDL_Rectangle for the texture's position and size -x,y,w,h
	//SDL_Rect cursorPos, activePos;
	//set the X,T,W, and H for the Rectangle
	cursorPos.x = 10;
	cursorPos.y = 10;
	cursorPos.w = 64;
	cursorPos.h = 64;

	activePos.x = 10;
	activePos.y = 10;
	activePos.w = 10;
	activePos.h = 10;

	//int cursorSpeed = 400;
	//*************************************Create Cursor -End**************************************

	//*************************************Create Menu -Start**************************************

	//string BKGDpath = ;

	//create a SDL surface to hold the background images
	surface = IMG_Load((images_dir + "Title.bmp").c_str());

	//create SDL_Texture
	SDL_Texture*title;
	//place surface info into the texture bkgd1;
	title = SDL_CreateTextureFromSurface(renderer, surface);

	//free SDL surface
	SDL_FreeSurface(surface);

	//Create the SDL_Rectangle for the texture's position and size -x,y,w,h
	SDL_Rect titlePos;
	//set the X,T,W, and H for the Rectangle
	titlePos.x = 336;
	titlePos.y = 113;
	titlePos.w = 352;
	titlePos.h = 50;

	//*************************************Create Menu -End**************************************

	//*************************************Create One -Start**************************************
	//create a SDL surface to hold the background images
	surface = IMG_Load((images_dir + "OneN.bmp").c_str());

	//create SDL_Texture
	SDL_Texture*oneN;
	//place surface info into the texture bkgd1;
	oneN = SDL_CreateTextureFromSurface(renderer, surface);

	//free SDL surface
	SDL_FreeSurface(surface);

	//create a SDL surface to hold the background images
	surface = IMG_Load((images_dir + "OneO.bmp").c_str());

	//create SDL_Texture
	SDL_Texture*oneO;
	//place surface info into the texture bkgd1;
	oneO = SDL_CreateTextureFromSurface(renderer, surface);

	//free SDL surface
	SDL_FreeSurface(surface);

	//Create the SDL_Rectangle for the texture's position and size -x,y,w,h
	SDL_Rect onePos;
	//set the X,T,W, and H for the Rectangle
	onePos.x = 392;
	onePos.y = 528;
	onePos.w = 240;
	onePos.h = 50;
	//*************************************Create One -End**************************************

	//*************************************Create Two -Start**************************************
	//create a SDL surface to hold the background images
	surface = IMG_Load((images_dir + "TwoN.bmp").c_str());

	//create SDL_Texture
	SDL_Texture*twoN;
	//place surface info into the texture bkgd1;
	twoN = SDL_CreateTextureFromSurface(renderer, surface);

	//free SDL surface
	SDL_FreeSurface(surface);

	//create a SDL surface to hold the background images
	surface = IMG_Load((images_dir + "TwoO.bmp").c_str());

	//create SDL_Texture
	SDL_Texture*twoO;
	//place surface info into the texture bkgd1;
	twoO = SDL_CreateTextureFromSurface(renderer, surface);

	//free SDL surface
	SDL_FreeSurface(surface);

	//Create the SDL_Rectangle for the texture's position and size -x,y,w,h
	SDL_Rect twoPos;
	//set the X,T,W, and H for the Rectangle
	twoPos.x = 392;
	twoPos.y = 626;
	twoPos.w = 240;
	twoPos.h = 50;
	//*************************************Create Two -End**************************************
	//*************************************Create Two -Start**************************************
	//create a SDL surface to hold the background images
	surface = IMG_Load((images_dir + "InstructionsN.bmp").c_str());

	//create SDL_Texture
	SDL_Texture*instructionsN;
	//place surface info into the texture bkgd1;
	instructionsN = SDL_CreateTextureFromSurface(renderer, surface);

	//free SDL surface
	SDL_FreeSurface(surface);

	//create a SDL surface to hold the background images
	surface = IMG_Load((images_dir + "InstructionsO.bmp").c_str());

	//create SDL_Texture
	SDL_Texture*instructionsO;
	//place surface info into the texture bkgd1;
	instructionsO = SDL_CreateTextureFromSurface(renderer, surface);

	//free SDL surface
	SDL_FreeSurface(surface);

	//Create the SDL_Rectangle for the texture's position and size -x,y,w,h
	SDL_Rect instructionsPos;
	//set the X,T,W, and H for the Rectangle
	instructionsPos.x = 392;
	instructionsPos.y = 724;
	instructionsPos.w = 240;
	instructionsPos.h = 50;
	//*************************************Create Two -End**************************************
	//*************************************Create Two -Start**************************************
	//create a SDL surface to hold the background images
	surface = IMG_Load((images_dir + "QuitN.bmp").c_str());

	//create SDL_Texture
	SDL_Texture*quitN;
	//place surface info into the texture bkgd1;
	quitN = SDL_CreateTextureFromSurface(renderer, surface);

	//free SDL surface
	SDL_FreeSurface(surface);

	//create a SDL surface to hold the background images
	surface = IMG_Load((images_dir + "QuitO.bmp").c_str());

	//create SDL_Texture
	SDL_Texture*quitO;
	//place surface info into the texture bkgd1;
	quitO = SDL_CreateTextureFromSurface(renderer, surface);

	//free SDL surface
	SDL_FreeSurface(surface);

	//Create the SDL_Rectangle for the texture's position and size -x,y,w,h
	SDL_Rect quitPos;
	//set the X,T,W, and H for the Rectangle
	quitPos.x = 392;
	quitPos.y = 822;
	quitPos.w = 240;
	quitPos.h = 50;
	//*************************************Create Two -End**************************************

	//*************************************Create Instructions Menu -Start**************************************

	//string BKGDpath = ;

	//create a SDL surface to hold the background images
	surface = IMG_Load((images_dir + "InstructText.bmp").c_str());

	//create SDL_Texture
	SDL_Texture*instructText;
	//place surface info into the texture bkgd1;
	instructText = SDL_CreateTextureFromSurface(renderer, surface);

	//free SDL surface
	SDL_FreeSurface(surface);

	//Create the SDL_Rectangle for the texture's position and size -x,y,w,h
	SDL_Rect instructTextPos;
	//set the X,T,W, and H for the Rectangle
	instructTextPos.x = 187;
	instructTextPos.y = 178;
	instructTextPos.w = 650;
	instructTextPos.h = 650;

	//*************************************Create Instructions Menu -End**************************************

	//*************************************Create Instructions Menu Button -Start**************************************
	//create a SDL surface to hold the background images
	surface = IMG_Load((images_dir + "MenuN.bmp").c_str());

	//create SDL_Texture
	SDL_Texture*menuN;
	//place surface info into the texture bkgd1;
	menuN = SDL_CreateTextureFromSurface(renderer, surface);
	//free SDL surface
	SDL_FreeSurface(surface);

	//create a SDL surface to hold the background images
	surface = IMG_Load((images_dir + "MenuO.bmp").c_str());

	//create SDL_Texture
	SDL_Texture*menuO;
	//place surface info into the texture bkgd1;
	menuO = SDL_CreateTextureFromSurface(renderer, surface);
	//free SDL surface
	SDL_FreeSurface(surface);

	//Create the SDL_Rectangle for the texture's position and size -x,y,w,h
	SDL_Rect menuPos;
	//set the X,T,W, and H for the Rectangle
	menuPos.x = 56;
	menuPos.y = 903;
	menuPos.w = 240;
	menuPos.h = 50;
	//*************************************Create Instructions Menu Button-End**************************************
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//*************************************Create WIN Menu -Start**************************************

	//string BKGDpath = ;

	//create a SDL surface to hold the background images
	surface = IMG_Load((images_dir + "Win.bmp").c_str());

	//create SDL_Texture
	SDL_Texture*winText;
	//place surface info into the texture bkgd1;
	winText = SDL_CreateTextureFromSurface(renderer, surface);

	//free SDL surface
	SDL_FreeSurface(surface);

	//Create the SDL_Rectangle for the texture's position and size -x,y,w,h
	SDL_Rect winTextPos;
	//set the X,T,W, and H for the Rectangle
	/*titlePos.x = 336;
	 titlePos.y = 113;
	 titlePos.w = 352;
	 titlePos.h = 50;*/
	winTextPos.x = 336;
	winTextPos.y = 113;
	winTextPos.w = 352;
	winTextPos.h = 50;

	//*************************************Create Instructions Menu -End**************************************

	//*************************************Create play Menu Button -Start**************************************
	//create a SDL surface to hold the background images
	surface = IMG_Load((images_dir + "PlayN.bmp").c_str());

	//create SDL_Texture
	SDL_Texture*playN;
	//place surface info into the texture bkgd1;
	playN = SDL_CreateTextureFromSurface(renderer, surface);
	//free SDL surface
	SDL_FreeSurface(surface);

	//create a SDL surface to hold the background images
	surface = IMG_Load((images_dir + "PlayO.bmp").c_str());

	//create SDL_Texture
	SDL_Texture*playO;
	//place surface info into the texture bkgd1;
	playO = SDL_CreateTextureFromSurface(renderer, surface);
	//free SDL surface
	SDL_FreeSurface(surface);

	//Create the SDL_Rectangle for the texture's position and size -x,y,w,h
	SDL_Rect playPos;
	//set the X,T,W, and H for the Rectangle

	playPos.x = 688;
	playPos.y = 903;
	playPos.w = 240;
	playPos.h = 50;
	//*************************************Create Instructions Menu Button-End**************************************

	//*************************************Create WIN Menu -Start**************************************

	//string BKGDpath = ;

	//create a SDL surface to hold the background images
	surface = IMG_Load((images_dir + "Lose.bmp").c_str());

	//create SDL_Texture
	SDL_Texture*loseText;
	//place surface info into the texture bkgd1;
	loseText = SDL_CreateTextureFromSurface(renderer, surface);

	//free SDL surface
	SDL_FreeSurface(surface);

	//Create the SDL_Rectangle for the texture's position and size -x,y,w,h
	SDL_Rect loseTextPos;
	//set the X,T,W, and H for the Rectangle
	/*titlePos.x = 336;
	 titlePos.y = 113;
	 titlePos.w = 352;
	 titlePos.h = 50;*/
	loseTextPos.x = 336;
	loseTextPos.y = 113;
	loseTextPos.w = 352;
	loseTextPos.h = 50;

	//*************************************Create Instructions Menu -End**************************************

	////Create the SDL_Rectangle for the texture's position and size -x,y,w,h
	//	SDL_Rect cursorPos;
	//	//set the X,T,W, and H for the Rectangle
	//	cursorPos.x = 0;
	//	cursorPos.y = 0;
	//	cursorPos.w = 64;
	//	cursorPos.h = 64;

	////create cursor
	//string CURSORpath = images_dir + "/Cursor.bmp";

	//surface = IMG_Load(CURSORpath.c_str());
	//SDL_Texture*cursor;
	//cursor= SDL_CreateTextureFromSurface(renderer,surface);

	//int bkgdSpeed = 100;

	/*
	 //////////////////////////////////////////////
	 //The surface contained by the window
	 SDL_Surface* screenSurface = NULL;

	 //Get window surface
	 screenSurface = SDL_GetWindowSurface(window);

	 //Fill the surface white
	 SDL_FillRect(screenSurface, NULL,
	 SDL_MapRGB(screenSurface->format, 0, 42, 254));

	 //Update the surface
	 SDL_UpdateWindowSurface(window);
	 */


	SDL_GameControllerEventState(SDL_ENABLE);
	//Setup a Game Controller Variable
	SDL_GameController* gGameController0 = NULL;

	//Open Game Controller
	gGameController0 = SDL_GameControllerOpen(0);

	SDL_GameController* gGameController1 = NULL;

	//Open Game Controller
	gGameController1 = SDL_GameControllerOpen(0);
	//Turn on Game Controller Events
	

	//SDL Event to handle input
	SDL_Event event;

	//setup variables for the game states
	enum GameState {
		MENU, INSTRUCTIONS, PLAYERS1, PLAYERS2, WIN, LOSE
	};

	//setup the initial state
	GameState gameState = MENU;

	//boolean values to control movement though the states
	bool menu = false, instructions = false, players1 = false, players2 = false, win = false, lose = false, quit = false;

	//////////////////////////////////////////////

	// The window is open: could enter program loop here (see SDL_PollEvent())
	while (!quit) {
		switch (gameState) {
		case MENU: {
			menu = true;
			cout << "The Game State is Menu" << endl;
			//cout << images_dir + "Path.jpg" << endl;
			//cout << checking << endl;
			cout << endl;
			while (menu) {

				//set up framerate for the section, or CASE
				thisTime = SDL_GetTicks();
				deltaTime = (float) (thisTime - lastTime) / 1000;
				lastTime = thisTime;

				//check for input events
				if (SDL_PollEvent(&event)) {
					//check to see if the SDL Window is closed - player clicks X in the window
					if (event.type == SDL_QUIT) {
						quit = true;
						menu = false;
						break;
					}
					switch (event.type) {
					case SDL_CONTROLLERBUTTONDOWN:
						if (event.cdevice.which == 0) {
							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_A) {
								if (players1Over) {
									menu = false;
									gameState = PLAYERS1;
									players1Over = false;
								}
								if (players2Over) {
									menu = false;
									gameState = PLAYERS2;
									players2Over = false;
								}

								if (instructionsOver) {
									menu = false;
									gameState = INSTRUCTIONS;
									instructionsOver = false;
								}

								if (quitOver) {
									menu = false;
									quit = true;
									quitOver = false;
								}

							}
						}
						break;
					case SDL_CONTROLLERAXISMOTION:
						moveCursor(event.caxis);
						break;
					}
				}
				//Start Drawing

				UpdateBackground(deltaTime);

				//Update Cursor
				UpdateCursor(deltaTime);

				players1Over = SDL_HasIntersection(&activePos, &onePos);
				players2Over = SDL_HasIntersection(&activePos, &twoPos);
				instructionsOver = SDL_HasIntersection(&activePos,&instructionsPos);
				quitOver = SDL_HasIntersection(&activePos, &quitPos);

				//Start Drawing
				//Clear SDL Renderer
				SDL_RenderClear(renderer);

				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1Pos);
				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2Pos);

				//Draw the menu image
				SDL_RenderCopy(renderer, title, NULL, &titlePos);

				//Draw the One image
				if (players1Over == true) {
					SDL_RenderCopy(renderer, oneO, NULL, &onePos);
				} else {
					SDL_RenderCopy(renderer, oneN, NULL, &onePos);
				}
				//Draw the One image
				if (players2Over == true) {
					SDL_RenderCopy(renderer, twoO, NULL, &twoPos);
				} else {
					SDL_RenderCopy(renderer, twoN, NULL, &twoPos);
				}
				//Draw the One image
				if (instructionsOver) {
					SDL_RenderCopy(renderer, instructionsO, NULL,
							&instructionsPos);
				} else {
					SDL_RenderCopy(renderer, instructionsN, NULL,
							&instructionsPos);
				}
				//Draw the One image
				if (quitOver) {
				SDL_RenderCopy(renderer, quitO, NULL, &quitPos);
				}
				else
				{
					SDL_RenderCopy(renderer, quitN, NULL, &quitPos);
				}

				//Draw the One image
				SDL_RenderCopy(renderer, cursor, NULL, &cursorPos);

				//SDL Render present
				SDL_RenderPresent(renderer);

			}

		}
			break;					//End menu

		case INSTRUCTIONS: {
			instructions = true;
			cout << "The Game State is Instructions" << endl;
			cout << endl;
			while (instructions) {

				//set up framerate for the section, or CASE
				thisTime = SDL_GetTicks();
				deltaTime = (float) (thisTime - lastTime) / 1000;
				lastTime = thisTime;
				//check for input events
				if (SDL_PollEvent(&event)) {
					//check to see if the SDL Window is closed - player clicks X in the window
					if (event.type == SDL_QUIT) {
						quit = true;
						instructions = false;
						break;
					}
					switch (event.type) {
					case SDL_CONTROLLERBUTTONDOWN:
						if (event.cdevice.which == 0) {
							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_A) {
								if(menuOver)
								{
									instructions = false;
									gameState = MENU;
									menuOver = false;
								}

							}
						}
						break;
					case SDL_CONTROLLERAXISMOTION:
						moveCursor(event.caxis);
						break;
					}
				}

				menuOver = SDL_HasIntersection(&activePos,&menuPos);

				UpdateBackground(deltaTime);
				//cursor
				UpdateCursor(deltaTime);


				//Start Drawing
				//Clear SDL Renderer
				SDL_RenderClear(renderer);

				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1Pos);
				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2Pos);

				//Draw the menu image
				SDL_RenderCopy(renderer, title, NULL, &titlePos);

				//Draw the menu image
				SDL_RenderCopy(renderer, instructText, NULL, &instructTextPos);

				//Draw the menu image
				if(menuOver)
				{
				SDL_RenderCopy(renderer, menuO, NULL, &menuPos);
				}
				else
				{
					SDL_RenderCopy(renderer, menuN, NULL, &menuPos);
				}

				//Draw the One image
				SDL_RenderCopy(renderer, cursor, NULL, &cursorPos);

				//SDL Render present
				SDL_RenderPresent(renderer);

			}
		}
			break;	//end instructions case
		case PLAYERS1: {
			players1 = true;
			cout << "The Game State is Players 1" << endl;
			cout << endl;
			while (players1) {

				//set up framerate for the section, or CASE
				thisTime = SDL_GetTicks();
				deltaTime = (float) (thisTime - lastTime) / 1000;
				lastTime = thisTime;

				//check for input events
				if (SDL_PollEvent(&event)) {
					//check to see if the SDL Window is closed - player clicks X in the window
					if (event.type == SDL_QUIT) {
						quit = true;
						players1 = false;
						break;
					}
					switch (event.type) {
					case SDL_CONTROLLERBUTTONDOWN:
						if (event.cdevice.which == 0) {
							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_X) {
								players1 = false;
								gameState = WIN;

							}
							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_Y) {
								players1 = false;
								gameState = LOSE;

							}
							//send button press info to player 1
							player1.OnControllerButton(event.cbutton);

						}
						break;
					case SDL_CONTROLLERAXISMOTION:
						player1.OnControllerAxis(event.caxis);
						break;
					}
				}

				UpdateBackground(deltaTime);

				player1.Update(deltaTime);
				//Start Drawing
				//Clear SDL Renderer
				SDL_RenderClear(renderer);

				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1Pos);
				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2Pos);

				//Draw the menu image
				//SDL_RenderCopy(renderer, oneN, NULL, &onePos);

				player1.Draw(renderer);
				//SDL Render present
				SDL_RenderPresent(renderer);

			}
		}
			break;	//end players1 case
		case PLAYERS2: {
			players2 = true;
			cout << "The Game State is Players 2" << endl;
			cout << endl;
			while (players2) {

				//set up framerate for the section, or CASE
				thisTime = SDL_GetTicks();
				deltaTime = (float) (thisTime - lastTime) / 1000;
				lastTime = thisTime;

				//check for input events
				if (SDL_PollEvent(&event)) {
					//check to see if the SDL Window is closed - player clicks X in the window
					if (event.type == SDL_QUIT) {
						quit = true;
						players2 = false;
						break;
					}
					switch (event.type) {
					case SDL_CONTROLLERBUTTONDOWN:
						if (event.cdevice.which == 0|| event.cdevice.which == 1) {
							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_X) {
								players2 = false;
								gameState = WIN;

							}
							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_Y) {
								players2 = false;
								gameState = LOSE;

							}
						}

						player1.OnControllerButton(event.cbutton);
						player2.OnControllerButton(event.cbutton);
						break;
					case SDL_CONTROLLERAXISMOTION:
						player1.OnControllerAxis(event.caxis);
						player2.OnControllerAxis(event.caxis);
						break;
					}
				}

				UpdateBackground(deltaTime);
				player1.Update(deltaTime);
				player2.Update(deltaTime);

				//Start Drawing
				//Clear SDL Renderer
				SDL_RenderClear(renderer);

				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1Pos);
				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2Pos);


				player1.Draw(renderer);
				player2.Draw(renderer);

				//Draw the menu image
				//SDL_RenderCopy(renderer, twoN, NULL, &twoPos);

				//SDL Render present
				SDL_RenderPresent(renderer);

			}
		}
			break;	//end players2 case
		case WIN: {
			win = true;
			cout << "The Game State is Win" << endl;

			cout << endl;
			while (win) {

				//set up framerate for the section, or CASE
				thisTime = SDL_GetTicks();
				deltaTime = (float) (thisTime - lastTime) / 1000;
				lastTime = thisTime;

				//check for input events
				if (SDL_PollEvent(&event)) {
					//check to see if the SDL Window is closed - player clicks X in the window
					if (event.type == SDL_QUIT) {
						quit = true;
						win = false;
						break;
					}
					switch (event.type) {
					case SDL_CONTROLLERBUTTONDOWN:
						if (event.cdevice.which == 0) {
							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_A) {
								if(menuOver)
																{
																	win = false;
																	gameState = MENU;
																	menuOver = false;
																}
																if(playOver)
																{
																	win = false;
																	gameState = PLAYERS1;
																	playOver = false;
																}

							}
						}
						break;
					case SDL_CONTROLLERAXISMOTION:
						moveCursor(event.caxis);
						break;
					}
				}

				menuOver = SDL_HasIntersection(&activePos,&menuPos);

				playOver = SDL_HasIntersection(&activePos,&playPos);

				UpdateBackground(deltaTime);
				UpdateCursor(deltaTime);

				//Start Drawing
				//Clear SDL Renderer
				SDL_RenderClear(renderer);

				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1Pos);
				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2Pos);

				//Draw the menu image
				SDL_RenderCopy(renderer, winText, NULL, &winTextPos);

				//Draw the menu image
				if(playOver)
				{
					SDL_RenderCopy(renderer, playO, NULL, &playPos);
				}
				else
				{
					SDL_RenderCopy(renderer, playN, NULL, &playPos);
				}

				//Draw the menu image
				if(menuOver)
				{
					SDL_RenderCopy(renderer, menuO, NULL, &menuPos);
				}
				else
				{
					SDL_RenderCopy(renderer, menuN, NULL, &menuPos);
				}


				//Draw the One image
				SDL_RenderCopy(renderer, cursor, NULL, &cursorPos);

				//SDL Render present
				SDL_RenderPresent(renderer);

			}
		}
			break;	//end win case
		case LOSE: {
			lose = true;
			cout << "The Game State is Lose" << endl;
			cout << endl;
			while (lose) {

				//set up framerate for the section, or CASE
				thisTime = SDL_GetTicks();
				deltaTime = (float) (thisTime - lastTime) / 1000;
				lastTime = thisTime;

				//check for input events
				if (SDL_PollEvent(&event)) {
					//check to see if the SDL Window is closed - player clicks X in the window
					if (event.type == SDL_QUIT) {
						quit = true;
						lose = false;
						break;
					}
					switch (event.type) {
					case SDL_CONTROLLERBUTTONDOWN:
						if (event.cdevice.which == 0) {
							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_A) {
								if(menuOver)
								{
									lose = false;
									gameState = MENU;
									menuOver = false;
								}
								if(playOver)
								{
									lose = false;
									gameState = PLAYERS1;
									playOver = false;
								}

							}
						}
						break;
					case SDL_CONTROLLERAXISMOTION:
											moveCursor(event.caxis);
											break;
					}
				}


				menuOver = SDL_HasIntersection(&activePos,&menuPos);

				playOver = SDL_HasIntersection(&activePos,&playPos);

				UpdateBackground(deltaTime);
				UpdateCursor(deltaTime);

				//Start Drawing
				//Clear SDL Renderer
				SDL_RenderClear(renderer);

				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1Pos);
				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2Pos);

				//Draw the menu image
				SDL_RenderCopy(renderer, loseText, NULL, &loseTextPos);

				if(playOver)
				{
					SDL_RenderCopy(renderer, playO, NULL, &playPos);
				}
				else
				{
					SDL_RenderCopy(renderer, playN, NULL, &playPos);
				}

				//Draw the menu image
				if(menuOver)
				{
					SDL_RenderCopy(renderer, menuO, NULL, &menuPos);
				}
				else
				{
					SDL_RenderCopy(renderer, menuN, NULL, &menuPos);
				}

				//Draw the One image
				SDL_RenderCopy(renderer, cursor, NULL, &cursorPos);

				//SDL Render present
				SDL_RenderPresent(renderer);

			}
		}
			break;	//end win case

		}
	}

	//SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example

	// Close and destroy the window
	SDL_DestroyWindow(window);

	// Clean up
	SDL_Quit();
	return 0;
}

