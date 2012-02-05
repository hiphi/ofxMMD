/*
 *  ImageLoader.h
 *  3d_sample
 *
 *  Created by Munetika Hujita on 10/05/02.
 *  Copyright 2010 hiphi. All rights reserved.
 *
 */
#pragma once
#include "ofMain.h"

class ImageLoader{
	
public:
	ImageLoader();
	GLuint loadImage(string path);
	
	GLuint img_p;
};
