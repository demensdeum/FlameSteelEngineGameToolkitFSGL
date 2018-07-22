/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FSGTIOFSGLSystemFactory.cpp
 * Author: demensdeum
 * 
 * Created on August 5, 2017, 7:28 PM
 */

#include "FSGTIOFSGLSystemFactory.h"
#include <FlameSteelEngineGameToolkit/Const/FSEGTConst.h>

#include <FSGL/Data/ResourcesLoader/FSGLResourceLoader.h>

#include <FlameSteelEngineGameToolkit/Utils/FSEGTUtils.h>
#include <FlameSteelEngineGameToolkit/Data/Components/SerializedModel/FSEGTSerializedModel.h>

#include <sstream>

FSGTIOFSGLSystemFactory::FSGTIOFSGLSystemFactory() {
}

FSGTIOFSGLSystemFactory::FSGTIOFSGLSystemFactory(const FSGTIOFSGLSystemFactory& ) {
}

shared_ptr<FSGLObject> FSGTIOFSGLSystemFactory::graphicsObjectFrom(shared_ptr<Object> object) {
    
    auto model = shared_ptr<FSGLModel>();
    
    auto modelFilePath = shared_ptr<string>();

	if (object->containsComponentWithIdentifier(make_shared<string>(FSEGTConstComponentsModel)))
	{
		modelFilePath = FSEGTUtils::getModelFilePathForObject(object);
	}

    auto serializedModel = FSEGTUtils::getSerializedModel(object);

	if (modelFilePath.get() != nullptr) {

	    stringstream stream;
    
	    stream << modelFilePath->c_str();
    
	    auto preparedModelFilePath = FSEGTUtils::platformPath(stream.str().c_str());

	    model = static_pointer_cast<FSGLModel>(FSGLResourceLoader::loadResource(preparedModelFilePath));

	}
	else if (serializedModel.get() != nullptr) {

		model = FSGLResourceLoader::deserializeModel(serializedModel);

	}
    
	if (model.get() == nullptr) {

		return shared_ptr<FSGLObject>();

	}

    auto graphicsObject = make_shared<FSGLObject>(model);
    
    auto position = FSEGTUtils::getObjectPosition(object);
    
    graphicsObject->id = object->uuid;
    
    graphicsObject->positionVector->x = position->x;
    graphicsObject->positionVector->y = position->y;
    graphicsObject->positionVector->z = position->z;
    
	auto rotation = FSEGTUtils::getObjectRotation(object);

	graphicsObject->rotationVector->x = rotation->x;
	graphicsObject->rotationVector->y = rotation->y;
	graphicsObject->rotationVector->z = rotation->z;

    auto scale = FSEGTUtils::getObjectScale(object);
    
    graphicsObject->scaleVector->x = scale->x;
    graphicsObject->scaleVector->y = scale->y;
    graphicsObject->scaleVector->z = scale->z;
    
    auto brightness = FSEGTUtils::getObjectBrightness(object);

	graphicsObject->brightness = brightness->floatNumber;

    return graphicsObject;
}

FSGTIOFSGLSystemFactory::~FSGTIOFSGLSystemFactory() {
}
