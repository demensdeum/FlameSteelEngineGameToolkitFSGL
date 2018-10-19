/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FSEGTIOFSGLSystemRenderer.cpp
 * Author: demensdeum
 * 
 * Created on August 5, 2017, 6:45 PM
 */

#include "FSEGTIOFSGLSystemRenderer.h"

#include <iostream>
#include <FlameSteelEngineGameToolkit/Utils/FSEGTUtils.h>

#include <FlameSteelEngineGameToolkitFSGL/Data/FSGTIOFSGLSystemFactory.h>

FSEGTIOFSGLSystemRenderer::FSEGTIOFSGLSystemRenderer() {
}

FSEGTIOFSGLSystemRenderer::FSEGTIOFSGLSystemRenderer(const FSEGTIOFSGLSystemRenderer& ) {
}

void FSEGTIOFSGLSystemRenderer::initialize(shared_ptr<FSEGTIOGenericSystemParams> params) {

	if (params.get() == nullptr) {
		throw logic_error("Can't initialize FSGLSystemRenderer - params initialize");
	}

    controller = make_shared<FSGLController>();
    window = controller->initialize(params);

}

void FSEGTIOFSGLSystemRenderer::render(shared_ptr<FSEGTGameData> ) {

    controller->render();

}

void FSEGTIOFSGLSystemRenderer::objectsContextObjectAdded(shared_ptr<FSEGTObjectsContext> , shared_ptr<Object> object) {

    //cout << "FSEGTIOFSGLSystemRenderer: object add - " << object->getInstanceIdentifier()->c_str() << endl;

	if (object->getClassIdentifier().get() == nullptr) {

		cout << "FSEGTIOFSGLSystemRenderer: empty name for added object - exit" << endl;

		exit(1);
	
	}

    if (FSEGTUtils::contains3D(object)) {

	auto materialLibrary = ioSystem->materialLibrary;

	if (materialLibrary.get() == nullptr) {

		throw logic_error("Material Library nullptr - stop");

	}

        auto graphicsObject = FSGTIOFSGLSystemFactory::graphicsObjectFrom(object, materialLibrary);

        controller->addObject(graphicsObject);

    } else if (object->getClassIdentifier()->compare("ui") == 0) {

    } else if (object->getClassIdentifier()->compare("camera") == 0) {

        auto position = FSEGTUtils::getObjectPosition(object);
        auto rotation = FSEGTUtils::getObjectRotation(object);

        controller->setCameraX(position->x);
        controller->setCameraY(position->y);
        controller->setCameraZ(position->z);

        controller->setCameraRotationX(rotation->x);
        controller->setCameraRotationY(rotation->y);
        controller->setCameraRotationZ(rotation->z);

    }
}

void FSEGTIOFSGLSystemRenderer::objectsContextObjectUpdate(shared_ptr<FSEGTObjectsContext> , shared_ptr<Object> object) {

    if (FSEGTUtils::contains3D(object)) {

        auto position = FSEGTUtils::getObjectPosition(object);
        auto rotation = FSEGTUtils::getObjectRotation(object);
        auto brightness = FSEGTUtils::getObjectBrightness(object);
        
        auto id = object->uuid;
        auto graphicsObject = controller->getObjectWithID(id);
        
	if (graphicsObject.get() == nullptr)
	{
		throw logic_error("graphics object - null");
	}

        graphicsObject->positionVector->x = position->x;
        graphicsObject->positionVector->y = position->y;
        graphicsObject->positionVector->z = position->z;
        
        graphicsObject->rotationVector->x = rotation->x;
        graphicsObject->rotationVector->y = rotation->y;
        graphicsObject->rotationVector->z = rotation->z;

	graphicsObject->brightness = brightness->floatNumber;

    } else if (object->getClassIdentifier()->compare("camera") == 0) {

        auto position = FSEGTUtils::getObjectPosition(object);
        auto rotation = FSEGTUtils::getObjectRotation(object);

        controller->setCameraX(position->x);
        controller->setCameraY(position->y);
        controller->setCameraZ(position->z);

        controller->setCameraRotationX(rotation->x);
        controller->setCameraRotationY(rotation->y);
        controller->setCameraRotationZ(rotation->z);

    }

}

void FSEGTIOFSGLSystemRenderer::objectsContextAllObjectsRemoved(shared_ptr<FSEGTObjectsContext> ) {

    //cout << "FSEGTIOFSGLSystemRenderer: all objects removed" << endl;

    controller->removeAllObjects();
    
}

void FSEGTIOFSGLSystemRenderer::objectsContextObjectRemoved(shared_ptr<FSEGTObjectsContext> context, shared_ptr<Object> object)
{
        auto id = object->uuid;
        auto graphicsObject = controller->getObjectWithID(id);

	controller->removeObject(graphicsObject);
}

FSEGTIOFSGLSystemRenderer::~FSEGTIOFSGLSystemRenderer() {
}