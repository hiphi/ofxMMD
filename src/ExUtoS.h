//
//  ExUtoS.h
//  MMD
//
//  Created by 藤田 宗親 on 11/08/21.
//  Copyright 2011 ANSWR inc. All rights reserved.
//
#pragma once
#include "ofMain.h"

class ExUtoS{
	
public:
	ExUtoS();
	const char* changeStr(string str);
	void logStr(string str);
	
	GLuint img_p;
};