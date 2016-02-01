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
#include <Windows.h>
#include <string>
#include <direct.h>
#include "SDL_image.h"

#endif
#if defined(__linux__)
#include <unistd.h>
#endif


#include <stdio.h>
#include <iostream>
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
void UpdateBackground()
{
	//Update
	//Update Background 1
	BG1pos_Y += (bkgdSpeed * 1)*deltaTime;
	//Set the new bkgd1 position
	bkgd1Pos.y = (int)(BG1pos_Y + 0.5f);

	//reset when off the bottom of the screen
	if (bkgd1Pos.y >= 1024)
	{
		bkgd1Pos.y = -1024;
		BG1pos_Y = bkgd1Pos.y;
	}


	//Update Background 2
	BG2pos_Y += (bkgdSpeed * 1)*deltaTime;
	//Set the new bkgd1 position
	bkgd2Pos.y = (int)(BG2pos_Y + 0.5f);

	//reset when off the bottom of the screen
	if (bkgd2Pos.y >= 1024)
	{
		bkgd2Pos.y = -1024;
		BG2pos_Y = bkgd2Pos.y;
	}
}



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
		string images_dir = currentWorkingDirectory + "/Resources/Images/";
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

	//create a SDL surface to hold the background images
	SDL_Surface *surface = SDL_LoadBMP((BKGDpath).c_str());



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
	surface = SDL_LoadBMP((images_dir + "Cursor.bmp").c_str());

	//create SDL_Texture
	SDL_Texture*cursor;
	//place surface info into the texture bkgd1;
	cursor = SDL_CreateTextureFromSurface(renderer, surface);

	//free SDL surface
	SDL_FreeSurface(surface);

	//Create the SDL_Rectangle for the texture's position and size -x,y,w,h
	SDL_Rect cursorPos, activePos;
	//set the X,T,W, and H for the Rectangle
	cursorPos.x = 0;
	cursorPos.y = 0;
	cursorPos.w = 64;
	cursorPos.h = 64;

	cursorPos.x = 10;
	cursorPos.y = 10;
	cursorPos.w = 10;
	cursorPos.h = 10;

	int cursorSpeed = 400;
	//*************************************Create Cursor -End**************************************




	//*************************************Create Menu -Start**************************************

	//string BKGDpath = ;

	//create a SDL surface to hold the background images
	surface = SDL_LoadBMP((images_dir + "Title.bmp").c_str());



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
	surface = SDL_LoadBMP((images_dir + "OneNorm.bmp").c_str());

	//create SDL_Texture
	SDL_Texture*oneN;
	//place surface info into the texture bkgd1;
	oneN = SDL_CreateTextureFromSurface(renderer, surface);

	//free SDL surface
	SDL_FreeSurface(surface);


	//create a SDL surface to hold the background images
	surface = SDL_LoadBMP((images_dir + "OneOver.bmp").c_str());

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
	surface = SDL_LoadBMP((images_dir + "TwoNorm.bmp").c_str());

	//create SDL_Texture
	SDL_Texture*twoN;
	//place surface info into the texture bkgd1;
	twoN = SDL_CreateTextureFromSurface(renderer, surface);

	//free SDL surface
	SDL_FreeSurface(surface);


	//create a SDL surface to hold the background images
	surface = SDL_LoadBMP((images_dir + "TwoOver.bmp").c_str());

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
	surface = SDL_LoadBMP((images_dir + "InstructionsNorm.bmp").c_str());

	//create SDL_Texture
	SDL_Texture*instructionsN;
	//place surface info into the texture bkgd1;
	instructionsN = SDL_CreateTextureFromSurface(renderer, surface);

	//free SDL surface
	SDL_FreeSurface(surface);


	//create a SDL surface to hold the background images
	surface = SDL_LoadBMP((images_dir + "InstructionsOver.bmp").c_str());

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
	surface = SDL_LoadBMP((images_dir + "QuitNorm.bmp").c_str());

	//create SDL_Texture
	SDL_Texture*quitN;
	//place surface info into the texture bkgd1;
	quitN = SDL_CreateTextureFromSurface(renderer, surface);

	//free SDL surface
	SDL_FreeSurface(surface);


	//create a SDL surface to hold the background images
	surface = SDL_LoadBMP((images_dir + "QuitOver.bmp").c_str());

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
	surface = SDL_LoadBMP((images_dir + "InstructText.bmp").c_str());



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
	surface = SDL_LoadBMP((images_dir + "MenuNorm.bmp").c_str());

	//create SDL_Texture
	SDL_Texture*menuN;
	//place surface info into the texture bkgd1;
	menuN = SDL_CreateTextureFromSurface(renderer, surface);
	//free SDL surface
	SDL_FreeSurface(surface);

	//create a SDL surface to hold the background images
	surface = SDL_LoadBMP((images_dir + "MenuOver.bmp").c_str());

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
	surface = SDL_LoadBMP((images_dir + "Win.bmp").c_str());



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
	surface = SDL_LoadBMP((images_dir + "PlayN.bmp").c_str());

	//create SDL_Texture
	SDL_Texture*playN;
	//place surface info into the texture bkgd1;
	playN = SDL_CreateTextureFromSurface(renderer, surface);
	//free SDL surface
	SDL_FreeSurface(surface);

	//create a SDL surface to hold the background images
	surface = SDL_LoadBMP((images_dir + "PlayO.bmp").c_str());

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
	surface = SDL_LoadBMP((images_dir + "Lose.bmp").c_str());



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
	//string CURSORpath = images_dir + "/Cursor.png";

	//surface = IMG_Load(CURSORpath.c_str());
	//SDL_Texture*cursor;
	//cursor= SDL_CreateTextureFromSurface(renderer,surface);





	int bkgdSpeed = 100;

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

		//Setup a Game Controller Variable
	SDL_GameController* gGameController = NULL;

	//Open Game Controller
	gGameController = SDL_GameControllerOpen(0);

	//Turn on Game Controller Events
	SDL_GameControllerEventState(SDL_ENABLE);

	//SDL Event to handle input
	SDL_Event event;

	//setup variables for the game states
	enum GameState {
		MENU, INSTRUCTIONS, PLAYERS1, PLAYERS2, WIN, LOSE
	};

	//setup the initial state
	GameState gameState = MENU;

	//boolean values to control movement though the states
	bool menu, instructions, players1, players2, win, lose, quit = false;

	//////////////////////////////////////////////

	// The window is open: could enter program loop here (see SDL_PollEvent())
	while (!quit) {
		switch (gameState) {
		case MENU:
		{
			menu = true;
			cout << "The Game State is Menu" << endl;
			//cout << images_dir + "Path.jpg" << endl;
			//cout << checking << endl;
			cout << "Press the A Button for Instructions" << endl;
			cout << "Press the X Button for 1 Player Game" << endl;
			cout << "Press the B Button for 2 Player Game" << endl;
			cout << "Press the Y Button to Quit the Game" << endl;
			cout << endl;
			while (menu) {

				//set up framerate for the section, or CASE
				thisTime = SDL_GetTicks();
				deltaTime = (float)(thisTime - lastTime) / 1000;
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
								menu = false;
								gameState = INSTRUCTIONS;

							}
							if (event.cbutton.button
								== SDL_CONTROLLER_BUTTON_B) {
								menu = false;
								gameState = PLAYERS2;

							}
							if (event.cbutton.button
								== SDL_CONTROLLER_BUTTON_X) {
								menu = false;
								gameState = PLAYERS1;
							}
							if (event.cbutton.button
								== SDL_CONTROLLER_BUTTON_Y) {
								menu = false;
								quit = true;
							}
						}
						break;
					}
				}
				//Start Drawing

				UpdateBackground();

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
				SDL_RenderCopy(renderer, oneN, NULL, &onePos);
				//Draw the One image
				SDL_RenderCopy(renderer, twoN, NULL, &twoPos);
				//Draw the One image
				SDL_RenderCopy(renderer, instructionsN, NULL, &instructionsPos);
				//Draw the One image
				SDL_RenderCopy(renderer, quitN, NULL, &quitPos);

				//Draw the One image
				SDL_RenderCopy(renderer, cursor, NULL, &cursorPos);

				//SDL Render present
				SDL_RenderPresent(renderer);

			}


		}
		break;//End menu

		case INSTRUCTIONS:
		{
			instructions = true;
			cout << "The Game State is Instructions" << endl;
			cout << "Press the A Button for Main Menu" << endl;
			cout << endl;
			while (instructions) {

				//set up framerate for the section, or CASE
				thisTime = SDL_GetTicks();
				deltaTime = (float)(thisTime - lastTime) / 1000;
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
								instructions = false;
								gameState = MENU;

							}
						}
						break;
					}
				}
				UpdateBackground();

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
				SDL_RenderCopy(renderer, menuN, NULL, &menuPos);

				//Draw the One image
				SDL_RenderCopy(renderer, cursor, NULL, &cursorPos);

				//SDL Render present
				SDL_RenderPresent(renderer);






			}
		}
		break;	//end instructions case
		case PLAYERS1:
		{
			players1 = true;
			cout << "The Game State is Players 1" << endl;
			cout << "Press the A Button for Win Screen" << endl;
			cout << "Press the B Button for Lose Screen" << endl;
			cout << endl;
			while (players1) {

				//set up framerate for the section, or CASE
				thisTime = SDL_GetTicks();
				deltaTime = (float)(thisTime - lastTime) / 1000;
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
								== SDL_CONTROLLER_BUTTON_A) {
								players1 = false;
								gameState = WIN;

							}
							if (event.cbutton.button
								== SDL_CONTROLLER_BUTTON_B) {
								players1 = false;
								gameState = LOSE;

							}
						}
						break;
					}
				}

				UpdateBackground();

				//Start Drawing
				//Clear SDL Renderer
				SDL_RenderClear(renderer);

				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1Pos);
				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2Pos);

				//Draw the menu image
				SDL_RenderCopy(renderer, oneN, NULL, &onePos);

				//SDL Render present
				SDL_RenderPresent(renderer);

			}
		}
		break;	//end players1 case
		case PLAYERS2:
		{
			players2 = true;
			cout << "The Game State is Players 2" << endl;
			cout << "Press the A Button for Win Screen" << endl;
			cout << "Press the B Button for Lose Screen" << endl;
			cout << endl;
			while (players2) {

				//set up framerate for the section, or CASE
				thisTime = SDL_GetTicks();
				deltaTime = (float)(thisTime - lastTime) / 1000;
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
						if (event.cdevice.which == 0) {
							if (event.cbutton.button
								== SDL_CONTROLLER_BUTTON_A) {
								players2 = false;
								gameState = WIN;

							}
							if (event.cbutton.button
								== SDL_CONTROLLER_BUTTON_B) {
								players2 = false;
								gameState = LOSE;

							}
						}
						break;
					}
				}

				UpdateBackground();

				//Start Drawing
				//Clear SDL Renderer
				SDL_RenderClear(renderer);

				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1Pos);
				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2Pos);

				//Draw the menu image
				SDL_RenderCopy(renderer, twoN, NULL, &twoPos);

				//SDL Render present
				SDL_RenderPresent(renderer);

			}
		}
		break;	//end players2 case
		case WIN:
		{
			win = true;
			cout << "The Game State is Win" << endl;
			cout << "Press the A Button for Main Menu" << endl;
			cout << "Press the B Button for Replay Game" << endl;
			cout << endl;
			while (win) {

				//set up framerate for the section, or CASE
				thisTime = SDL_GetTicks();
				deltaTime = (float)(thisTime - lastTime) / 1000;
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
								win = false;
								gameState = MENU;

							}
							if (event.cbutton.button
								== SDL_CONTROLLER_BUTTON_B) {
								win = false;
								gameState = PLAYERS1;

							}
						}
						break;
					}
				}

				UpdateBackground();

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
				SDL_RenderCopy(renderer, playN, NULL, &playPos);


				//Draw the menu image
				SDL_RenderCopy(renderer, menuN, NULL, &menuPos);

				//Draw the One image
				SDL_RenderCopy(renderer, cursor, NULL, &cursorPos);



				//SDL Render present
				SDL_RenderPresent(renderer);

			}
		}
		break;	//end win case
		case LOSE:
		{
			lose = true;
			cout << "The Game State is Lose" << endl;
			cout << "Press the A Button for Main Menu" << endl;
			cout << "Press the B Button for Replay Game" << endl;
			cout << endl;
			while (lose) {

				//set up framerate for the section, or CASE
				thisTime = SDL_GetTicks();
				deltaTime = (float)(thisTime - lastTime) / 1000;
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
								lose = false;
								gameState = MENU;

							}
							if (event.cbutton.button
								== SDL_CONTROLLER_BUTTON_B) {
								lose = false;
								gameState = PLAYERS1;

							}
						}
						break;
					}
				}

				UpdateBackground();

				//Start Drawing
				//Clear SDL Renderer
				SDL_RenderClear(renderer);

				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1Pos);
				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2Pos);

				//Draw the menu image
				SDL_RenderCopy(renderer, loseText, NULL, &loseTextPos);

				//Draw the menu image
				SDL_RenderCopy(renderer, playN, NULL, &playPos);


				//Draw the menu image
				SDL_RenderCopy(renderer, menuN, NULL, &menuPos);

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

