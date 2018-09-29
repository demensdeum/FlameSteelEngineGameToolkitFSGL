/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FSEGTIOFSGLInputController.cpp
 * Author: demensdeum
 * 
 * Created on August 12, 2017, 8:06 PM
 */

#include "FSEGTIOFSGLInputController.h"

#include <SDL2/SDL.h>
#include <iostream>

FSEGTIOFSGLInputController::FSEGTIOFSGLInputController() {
    
    FSEGTInputController::clearKeys();
    
}

FSEGTIOFSGLInputController::FSEGTIOFSGLInputController(const FSEGTIOFSGLInputController& ) {
}

void FSEGTIOFSGLInputController::pollKey() {
    
	SDL_PumpEvents();

	if (window == nullptr)
	{
		throw logic_error("window is nullptr");
	}

	int mouseX = 0;
	int mouseY = 0;

	if (pointerPollingStarted)
	{
		SDL_GetMouseState(&mouseX, &mouseY);
	}

	int windowWidth = 0;
	int windowHeight = 0;

	SDL_GetWindowSize(window, &windowWidth, &windowHeight);

	// SDL2 bug workaround https://stackoverflow.com/questions/17762842/sdl-getmousestate-doesnt-work-to-get-initial-mouse-position
	if (mouseX > 0 && mouseY > 0)
	{
		pointerXdiff = mouseX - (windowWidth / 2);
		pointerYdiff = mouseY - (windowHeight / 2);
	}

	/*if (pointerXdiff != 0)
	{
		cout << pointerXdiff << endl;
	}*/

	if (pointerXdiff != 0 || pointerYdiff != 0)
	{
		SDL_WarpMouseInWindow(window, windowWidth / 2, windowHeight / 2);

		auto oldMouseX = mouseX;
		auto oldMouseY = mouseY;

		SDL_GetMouseState(&mouseX, &mouseY);

		//cout << oldMouseX << ";"<< mouseX << endl;

	}

	if (!pointerPollingStarted)
	{
		SDL_ShowCursor(SDL_DISABLE);
		pointerPollingStarted = true;
	}

    SDL_Event event;

    while (SDL_PollEvent(&event)) {

        switch (event.type) {

            case SDL_QUIT:
                this->exitKeyPressed = true;
                break;

            case SDL_MOUSEBUTTONUP:
                shootKeyPressed = false;
                break;

            case SDL_MOUSEBUTTONDOWN:
                shootKeyPressed = true;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {

			case SDLK_e:
				this->useKeyPressed = true;
				break;

			case SDLK_RSHIFT:
				this->rotateRightKeyPressed = true;
				break;

			case SDLK_LSHIFT:
				this->rotateLeftKeyPressed = true;
				break;

                    case SDLK_LEFT:
                        this->leftKeyPressed = true;
                        break;

                    case SDLK_RIGHT:
                        this->rightKeyPressed = true;
                        break;

                    case SDLK_UP:
                        this->upKeyPressed = true;
                        break;

                    case SDLK_DOWN:
                        this->downKeyPressed = true;
                        break;

                    case SDLK_SPACE:
                        this->shootKeyPressed = true;
                        break;

                    case SDLK_ESCAPE:
                        this->exitKeyPressed = true;
                        break;

                    default:
                        break;
                }
                break;

            case SDL_KEYUP:
                switch (event.key.keysym.sym) {

			case SDLK_e:
				this->useKeyPressed = false;
				break;

			case SDLK_RSHIFT:
				this->rotateRightKeyPressed = false;
				break;

			case SDLK_LSHIFT:
				this->rotateLeftKeyPressed = false;
				break;

                    case SDLK_LEFT:
                        this->leftKeyPressed = false;
                        break;

                    case SDLK_RIGHT:
                        this->rightKeyPressed = false;
                        break;

                    case SDLK_UP:
                        this->upKeyPressed = false;
                        break;

                    case SDLK_DOWN:
                        this->downKeyPressed = false;
                        break;

                    case SDLK_SPACE:
                        this->shootKeyPressed = false;
                        break;

                    default:
                        break;
                }
                break;
        }
    }
}

FSEGTIOFSGLInputController::~FSEGTIOFSGLInputController() {
}
