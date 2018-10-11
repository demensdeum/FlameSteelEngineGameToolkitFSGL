/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FSEGTIOFSGLSystem.cpp
 * Author: demensdeum
 * 
 * Created on August 5, 2017, 6:25 PM
 */

#include "FSEGTIOFSGLSystem.h"

#include <iostream>
#include <SDL2/SDL_image.h>
#include <FlameSteelEngineGameToolkitFSGL/Renderers/FSEGTIOFSGLSystemRenderer.h>
#include <FlameSteelEngineGameToolkit/IO/Input/FSEGTInputController.h>
#include <FlameSteelEngineGameToolkitFSGL/Input/FSEGTIOFSGLInputController.h>
#include <FlameSteelEngineGameToolkit/IO/AudioPlayer/FSEGTAudioPlayer.h>

FSEGTIOFSGLSystem::FSEGTIOFSGLSystem() {
}

void FSEGTIOFSGLSystem::initialize(shared_ptr<FSEGTIOSystemParams> params) {
    
	cout << "FSGL Desktop Initialize" << endl;
    
	auto fsglRenderer = make_shared<FSEGTIOFSGLSystemRenderer>();

	renderer = fsglRenderer;
	renderer->ioSystem = shared_from_this();

	auto genericParams = static_pointer_cast<FSEGTIOGenericSystemParams>(params);

	fsglRenderer->initialize(genericParams);

	int flags=IMG_INIT_PNG;
	int initted=IMG_Init(flags);
	if ((initted&flags) != flags) {
		printf("IMG_Init: Failed to init required jpg and png support!\n");
		printf("IMG_Init: %s\n", IMG_GetError());
	}

	audioPlayer = make_shared<FSEGTAudioPlayer>();

    auto window = fsglRenderer->window;
    
	auto fsglInputController = make_shared<FSEGTIOFSGLInputController>();

    inputController = fsglInputController;
	fsglInputController->window = window;
}

void FSEGTIOFSGLSystem::objectsContextObjectAdded(shared_ptr<FSEGTObjectsContext> context, shared_ptr<Object> object) {

    renderer->objectsContextObjectAdded(context, object);

}

void FSEGTIOFSGLSystem::objectsContextObjectUpdate(shared_ptr<FSEGTObjectsContext> context, shared_ptr<Object> object) {
    
    renderer->objectsContextObjectUpdate(context, object);
    
}

void FSEGTIOFSGLSystem::objectsContextObjectRemoved(shared_ptr<FSEGTObjectsContext> context, shared_ptr<Object> object) {
	renderer->objectsContextObjectRemoved(context, object);
}

void FSEGTIOFSGLSystem::objectsContextAllObjectsRemoved(shared_ptr<FSEGTObjectsContext> context) {
    
    renderer->objectsContextAllObjectsRemoved(context);
}

FSEGTIOFSGLSystem::FSEGTIOFSGLSystem(const FSEGTIOFSGLSystem& ) {
}

FSEGTIOFSGLSystem::~FSEGTIOFSGLSystem() {
}