/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FSEGTIOFSGLSystem.h
 * Author: demensdeum
 *
 * Created on August 5, 2017, 6:25 PM
 */

#ifndef FSEGTIOFSGLSYSTEM_H
#define FSEGTIOFSGLSYSTEM_H

#include <FlameSteelEngineGameToolkit/IO/IOSystems/FSEGTIOSystem.h>
#include <memory>

class FSEGTIOFSGLSystem: public FSEGTIOSystem {
public:
    FSEGTIOFSGLSystem();
    FSEGTIOFSGLSystem(const FSEGTIOFSGLSystem& orig);
    virtual ~FSEGTIOFSGLSystem();
    
    virtual void initialize(shared_ptr<FSEGTIOSystemParams> params);
    
    virtual void objectsContextObjectAdded(shared_ptr<FSEGTObjectsContext> context, shared_ptr<Object> object);
    virtual void objectsContextObjectUpdate(shared_ptr<FSEGTObjectsContext> context, shared_ptr<Object> object);
    virtual void objectsContextAllObjectsRemoved(shared_ptr<FSEGTObjectsContext> context);    
    virtual void objectsContextObjectRemoved(shared_ptr<FSEGTObjectsContext> context, shared_ptr<Object> object);
    
private:

};

#endif /* FSEGTIOFSGLSYSTEM_H */

