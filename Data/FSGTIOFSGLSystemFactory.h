/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FSGTIOFSGLSystemFactory.h
 * Author: demensdeum
 *
 * Created on August 5, 2017, 7:28 PM
 */

#ifndef FSGTIOFSGLSYSTEMFACTORY_H
#define FSGTIOFSGLSYSTEMFACTORY_H

#include <memory>

#include <FSGL/Data/Object/FSGLObject.h>

#include <FlameSteelCore/Object.h>

using namespace std;
using namespace FlameSteelCore;

class FSGTIOFSGLSystemFactory {
public:
    FSGTIOFSGLSystemFactory();
    FSGTIOFSGLSystemFactory(const FSGTIOFSGLSystemFactory& orig);
    virtual ~FSGTIOFSGLSystemFactory();
    
    static shared_ptr<FSGLObject> graphicsObjectFrom(shared_ptr<Object> object, shared_ptr<MaterialLibrary> materialLibrary);
    
private:

};

#endif /* FSGTIOFSGLSYSTEMFACTORY_H */

