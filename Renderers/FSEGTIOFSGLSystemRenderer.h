/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FSEGTIOFSGLSystemRenderer.h
 * Author: demensdeum
 *
 * Created on August 5, 2017, 6:45 PM
 */

#ifndef FSEGTIOFSGLSYSTEMRENDERER_H
#define FSEGTIOFSGLSYSTEMRENDERER_H

#include <FlameSteelEngineGameToolkit/IO/Renderers/FSEGTRenderer.h>

#include <FSGL/Controller/FSGLController.h>

class FSEGTIOFSGLSystem;
struct SDL_Window;

class FSEGTIOFSGLSystemRenderer: public FSEGTRenderer {
public:
    FSEGTIOFSGLSystemRenderer();
    FSEGTIOFSGLSystemRenderer(const FSEGTIOFSGLSystemRenderer& orig);
    virtual ~FSEGTIOFSGLSystemRenderer();
    
    virtual void initialize(shared_ptr<FSEGTIOSystemParams> params = nullptr);    
    
    virtual void render(shared_ptr<FSEGTGameData> gameData);
    
    virtual void objectsContextObjectAdded(shared_ptr<FSEGTObjectsContext> context, shared_ptr<Object> object);
    virtual void objectsContextObjectUpdate(shared_ptr<FSEGTObjectsContext> context, shared_ptr<Object> object);
    virtual void objectsContextAllObjectsRemoved(shared_ptr<FSEGTObjectsContext> context);
    virtual void objectsContextObjectRemoved(shared_ptr<FSEGTObjectsContext> context, shared_ptr<Object> object);

	SDL_Window *window = nullptr;
    
private:
	shared_ptr<FSGLController> controller;
    
};

#endif /* FSEGTIOFSGLSYSTEMRENDERER_H */

