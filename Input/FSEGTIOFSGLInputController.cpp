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

#if __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/val.h>

using namespace emscripten;

#endif

#include <SDL2/SDL.h>
#include <iostream>

FSEGTIOFSGLInputController::FSEGTIOFSGLInputController() {
    
	touches = make_shared<Objects>();

    FSEGTInputController::clearKeys();
    
}

FSEGTIOFSGLInputController::FSEGTIOFSGLInputController(const FSEGTIOFSGLInputController& ) {
}

void FSEGTIOFSGLInputController::pollKey() {
    
#if __EMSCRIPTEN__

if (!pointerPollingStarted) {
		EM_ASM(

			___globalFSEGTIOFSGLJSMouseXDiff = 0;
			___globalFSEGTIOFSGLJSMouseYDiff = 0;

			{
				/*var moveCallback = function(event) {
					var x = event.movementX;
					var y = event.movementY;

					var movementString = "x: ";
					movementString += x.toString();
					movementString += " y: ";
					movementString += y.toString();

					console.log(movementString);
				}*/

				var canvas = document.getElementById("canvas");
				
				canvas.addEventListener('click', function(){

					if (document.pointerLockElement === canvas){
						//document.exitPointerLock();
					} 
					else {
						canvas.requestPointerLock();
					}

				}, false);

				document.addEventListener("mousemove", function(event) {

					if (document.pointerLockElement === canvas){

						___globalFSEGTIOFSGLJSMouseXDiff = event.movementX;
						___globalFSEGTIOFSGLJSMouseYDiff = event.movementY;

					}
					else {
						___globalFSEGTIOFSGLJSMouseXDiff = 0;
						___globalFSEGTIOFSGLJSMouseYDiff = 0;
					}

				}, false);

			}
		);

	pointerPollingStarted = true;
}

val jsMouseXdiff = val::global("___globalFSEGTIOFSGLJSMouseXDiff");
val jsMouseYdiff = val::global("___globalFSEGTIOFSGLJSMouseYDiff");

pointerXdiff = jsMouseXdiff.as<int>();
pointerYdiff = jsMouseYdiff.as<int>();

EM_ASM(
			___globalFSEGTIOFSGLJSMouseXDiff = 0;
			___globalFSEGTIOFSGLJSMouseYDiff = 0;
);

#else
    
    SDL_PumpEvents();
    
    if (window == nullptr)
    {
        throw runtime_error("window is nullptr");
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
    
    if (pointerXdiff != 0 || pointerYdiff != 0)
    {
        SDL_WarpMouseInWindow(window, windowWidth / 2, windowHeight / 2);
        SDL_GetMouseState(&mouseX, &mouseY);
        
    }
    
    if (!pointerPollingStarted)
    {
        SDL_ShowCursor(SDL_DISABLE);
        pointerPollingStarted = true;
    }
    
#endif
    
    SDL_Event event;
    
#if __EMSCRIPTEN__
    int windowWidth = 0;
    int windowHeight = 0;
#endif
    
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    while (SDL_PollEvent(&event)) {
        
        switch (event.type) {
                
		case SDL_FINGERDOWN:
		{
			float x = float(windowWidth) * event.tfinger.x;
			float y = float(windowHeight) * event.tfinger.y;

			auto touchId = event.tfinger.touchId;
			auto uuid = make_shared<string>(std::to_string(touchId));

			//cout << "fingerdown:" << *uuid << endl;

			auto touch = make_shared<FSEGTTouch>(uuid, x, y);
			touches->addObject(touch);
			break;
		}
		case SDL_FINGERMOTION:
		{
			float x = float(windowWidth) * event.tfinger.x;
			float y = float(windowHeight) * event.tfinger.y;

			auto touchId = event.tfinger.touchId;
			auto uuid = make_shared<string>(std::to_string(touchId));

			//cout << "fingermotion:" << *uuid << endl;

			auto touch = touches->objectWithInstanceIdentifier(uuid);
			auto touchCasted = static_pointer_cast<FSEGTTouch>(touch);
			touchCasted->x = x;
			touchCasted->y = y;

			break;
		}
		case SDL_FINGERUP:
		{
			auto touchId = event.tfinger.touchId;
			auto uuid = make_shared<string>(std::to_string(touchId));

			//cout << "fingerup:" << *uuid << endl;

			touches->removeObjectWithClassIdentifier(uuid);
			break;
		}
			break;

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
                        useKeyPressed = true;
                        break;
                        
                    case SDLK_RSHIFT:
                        rotateRightKeyPressed = true;
                        break;
                        
                    case SDLK_LSHIFT:
                        rotateLeftKeyPressed = true;
                        break;
                        
                    case SDLK_LEFT:
                    case SDLK_a:
                        leftKeyPressed = true;
                        
                        break;
                        
                    case SDLK_RIGHT:
                    case SDLK_d:
                        rightKeyPressed = true;
                        break;
                        
                    case SDLK_UP:
                    case SDLK_w:
                        upKeyPressed = true;
                        break;
                        
                    case SDLK_DOWN:
                    case SDLK_s:
                        downKeyPressed = true;
                        break;
                        
                    case SDLK_SPACE:
                        shootKeyPressed = true;
                        break;
                        
                    case SDLK_ESCAPE:
                        exitKeyPressed = true;
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                        
                    case SDLK_e:
                        useKeyPressed = false;
                        break;
                        
                    case SDLK_RSHIFT:
                        rotateRightKeyPressed = false;
                        break;
                        
                    case SDLK_LSHIFT:
                        rotateLeftKeyPressed = false;
                        break;
                        
                    case SDLK_LEFT:
                    case SDLK_a:
                        this->leftKeyPressed = false;
                        break;
                        
                    case SDLK_RIGHT:
                    case SDLK_d:
                        this->rightKeyPressed = false;
                        break;
                        
                    case SDLK_UP:
                    case SDLK_w:
                        this->upKeyPressed = false;
                        break;
                        
                    case SDLK_DOWN:
                    case SDLK_s:
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
