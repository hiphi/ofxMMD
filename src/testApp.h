#pragma once

#include "ofMain.h"
#include "ofxBullet.h"
#include "vpvl.h"
#include "Renderer.h"
#include "Delegate.h"

class testApp : public ofBaseApp {

public:
	
	void setup();
	void update();
	void draw();

	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
	vpvl::PMDModel *model;
	vpvl::gl2::Renderer *render;
	internal::Delegate *delegate;
	
	vpvl::VMDMotion *motion;
	
	ofVbo *vbo;
	
	//////////
	btDiscreteDynamicsWorld *mWorld;
	btBroadphaseInterface *bi;
	btCollisionDispatcher *cDisp;
	btConstraintSolver *sol;
	btDefaultCollisionConfiguration *cConf;
	//////////
};