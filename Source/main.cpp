// Example program:
// Using SDL2 to create an application window

#if defined(__APPLE__)

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"

#endif
#if defined(__linux__)

#include "SDL2/SDL.h"

#endif
#if defined(_WIN32) || (_WIN64)

#include "SDL.h"

#endif
#include <stdio.h>
#include <iostream>
using namespace std;

//code for frame rate independence
float deltaTime = 0.0;
int thisTime = 0;
int lastTime = 0;







int main(int argc, char* argv[]) {

	SDL_Window *window;                    // Declare a pointer

	SDL_Init(SDL_INIT_EVERYTHING);              // Initialize SDL2

	// Create an application window with the following settings:
	window = SDL_CreateWindow("An SDL2 window",                  // window title
			SDL_WINDOWPOS_UNDEFINED,           // initial x position
			SDL_WINDOWPOS_UNDEFINED,           // initial y position
			640,                               // width, in pixels
			480,                               // height, in pixels
			SDL_WINDOW_OPENGL                  // flags - see below
			);


#if defined(__APPLE__)
	{
		cout << "Running on Apple" << endl;
		//get the current working directory
		string s_cwd(getcwd(NULL,0));

		//create a string linking to the mac's images folder
		string s_cwd_images = s_cwd + "/Resources/images/";
	}
#endif


	// Check that the window was successfully created
	if (window == NULL) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Renderer*renderer = NULL;

	//create renderer
	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);


	//CreateBackground
	string BKGDpath = s_cwd_images + "/face.png";

	//create a SDL surface to hold the background images
	SDL_Surface*surface = IMG_Load(BKGDpath.c_str());

	//create SDL_Texture
	SDL_Texture*bkgd1;
	//place surface info into the texture bkgd1;
	bkgd1.CreateTextureFromSurface(renderer,surface);

	//create SDL_Texture
		SDL_Texture*bkgd2:
		//place surface info into the texture bkgd1;
		bkgd2.CreateTextureFromSurface(renderer,surface);

	//free SDL surface
	//SDL_FreeSurface(surface);

	//Create the SDL_Rectangle for the texture's position and size -x,y,w,h
	SDL_Rect bkgd1Pos;
	//set the X,T,W, and H for the Rectangle
	bkgd1Pos.x = 0;
	bkgd1Pos.y = 0;
	bkgd1Pos.w = 1024;
	bkgd1Pos.h = 768;

	//Create the SDL_Rectangle for the texture's position and size -x,y,w,h
	SDL_Rect bkgd2Pos;
	//set the X,T,W, and H for the Rectangle
	bkgd2Pos.x = 0;
	bkgd2Pos.y = -768;
	bkgd2Pos.w = 1024;
	bkgd2Pos.h = 768;



	//Create the SDL_Rectangle for the texture's position and size -x,y,w,h
		SDL_Rect cursorPos;
		//set the X,T,W, and H for the Rectangle
		cursorPos.x = 0;
		cursorPos.y = 0;
		cursorPos.w = 64;
		cursorPos.h = 64;


	//set temp variables to hold movement
	float BG1pos_X = 0,BG1pos_Y = 0;

	//set temp variables to hold movement
	float BG2pos_X = 0,BG2pos_Y = -768;

	//create cursor
	string CURSORpath = s_cwd_images + "/Cursor.png";

	surface = IMG_Load(CURSORpath.c_str());
	SDL_Texture*cursor;
	cursor= SDL_CreateTextureFromSurface(renderer,surface);





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
	SDL_GameControllerEventState (SDL_ENABLE);

	//SDL Event to handle input
	SDL_Event event;

	//setup variables for the game states
	enum GameState {
		MENU, INSTRUCTIONS, PLAYERS1, PLAYERS2, WIN, LOSE
	};

	//setup the initial state
	GameState gameState = MENU;

	//boolean values to control movement though the states
	bool menu, instructions, players1, players2, win, lose, quit;

	//////////////////////////////////////////////

	// The window is open: could enter program loop here (see SDL_PollEvent())
	while (!quit) {
		switch (gameState) {
		case MENU:
		{
			menu = true;
			cout << "The Game State is Menu" << endl;
			cout << "Press the A Button for Instructions" << endl;
			cout << "Press the X Button for 1 Player Game" << endl;
			cout << "Press the B Button for 2 Player Game" << endl;
			cout << "Press the Y Button to Quit the Game" << endl;
			cout << endl;
			while (menu) {

				//set up framerate for the section, or CASE
				thisTime = SDL_GetTicks();
				deltaTime=(float)(thisTime - lastTime)/1000;
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
								gameState = PLAYERS1;

							}
							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_X) {
								menu = false;
								gameState = PLAYERS2;
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

				}
				//Start Drawing

			//Update
			//Update Background 1
			BG1pos_X += (bkgdSpeed *1)*deltaTime;
			//Set the new bkgd1 position
			bkgd1Pos.y = (int)(BG1pos_Y + 0.5f);

			//reset when off the bottom of the screen
			if(bkgd1Pos.y >= 768)
			{
				bkgd1Pos.y = -768;
				BG1pos_Y = bkgd1Pos.Y;
			}


			//Update Background 2
						BG2pos_X += (bkgdSpeed *1)*deltaTime;
						//Set the new bkgd1 position
						bkgd2Pos.y = (int)(BG2pos_Y + 0.5f);

						//reset when off the bottom of the screen
						if(bkgd2Pos.y >= 768)
						{
							bkgd2Pos.y = -768;
							BG2pos_Y = bkgd2Pos.Y;
						}

			//Start Drawing
				//Clear SDL Renderer
				SDL_RenderClear(renderer);

				//Draw the bkgd image
				SDL_RenderCopy(renderer,bkgd1,NULL,&bkgd1Pos);
				//Draw the bkgd image
				SDL_RenderCopy(renderer,bkgd2,NULL,&bkgd1Pos);
				/*
				//Draw the bkgd image
				SDL_RenderCopy(renderer,bkgd2,NULL,&bkgd1Pos);
				*/

				//SDL Render present
				SDL_RenderPresent(renderer);

				}
				break;//End menu

				case INSTRUCTIONS:
				{
				instructions = true;
				cout << "The Game State is Instructions" << endl;
				cout << "Press the A Button for Main Menu" << endl;
				cout << endl;
				while (instructions) {
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
					}
					}
					break;	//end players2 case
					case WIN:
					{
					win = true;
					cout << "The Game State is Win" << endl;
					cout << "Press the A Button for Main Menu" << endl;
					cout << "Press the B Button for Quit" << endl;
					cout << endl;
					while (win) {
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
										quit = true;

									}
								}
								break;
							}
						}
					}
					}
					break;	//end win case
					case LOSE:
					{
					lose = true;
					cout << "The Game State is Lose" << endl;
					cout << "Press the A Button for Main Menu" << endl;
					cout << "Press the B Button for Quit" << endl;
					cout << endl;
					while (lose) {
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
										quit = true;

									}
								}
								break;
							}
						}
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

