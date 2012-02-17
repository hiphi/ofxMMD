#include "testApp.h"
#include "Delegate.h"
#include "Common.h"

#define BYTESRD 1024

GLfloat white[] = { 1.0, 1.0, 1.0, 1.00 };

//--------------------------------------------------------------
void testApp::setup() {
	
	//char readFile[] = "../../../data/hm_m.pmd";
	char readFile[] = "../../../data/Lat式ミクVer2.3_Normal.pmd";
	
	FILE *fp = fopen(readFile,"rb");
	
	uint8_t *buf,*nbuf;
    size_t s,p=0;
	
    buf=(uint8_t *)malloc(BYTESRD);
    if(!buf) return;
    while((s=fread(buf+p,1,BYTESRD,fp))==BYTESRD) {
        s=0;
        p+=BYTESRD;
        nbuf=(uint8_t *)realloc(buf,p+BYTESRD);
        if(!nbuf) break;
        buf=nbuf;
    }
	
    size_t f_size = p+s;
	
	
	
	model = new vpvl::PMDModel();
	
	bool flg = model->load(buf,f_size);
	
	if(flg == true){
		printf("load file ture!!\n");
	}else{
		printf("load file false...\n");
	}
	
	
	
	/////////
	const int MAX_OBJECT_NUMBER = 20000;
	cConf = new btDefaultCollisionConfiguration();
	cDisp = new btCollisionDispatcher(cConf);
	bi = new btAxisSweep3(btVector3(-10000,-10000,-10000), btVector3(10000,10000,10000), MAX_OBJECT_NUMBER);
	sol = new btSequentialImpulseConstraintSolver();
	mWorld = new btDiscreteDynamicsWorld(cDisp, bi, sol, cConf);
	mWorld->setGravity(btVector3(0,-10,0));
	//////////
	
	
	
	delegate = new internal::Delegate();
	render = new vpvl::gl2::Renderer(delegate,1024,768,60);
	render->createPrograms();
	render->createShadowFrameBuffers();
	vpvl::Scene *scene = render->scene();
	render->scene()->setWorld(mWorld);
	render->initializeSurface();
	render->uploadModel(model, "../../../data");
	//render->setSelectedModel(model);
	render->renderModel(model);
	render->renderModelZPlot(model);
	
	ofBackground(255,255,255);
	
	//glEnable(GL_DEPTH_TEST);
}

//--------------------------------------------------------------
void testApp::update() {
	static btScalar t= 0;
	btScalar dt = 1/60.f;
	//mWorld->stepSimulation(t / 1000000.f);
	
	model->updateImmediate();
	
	render->updateModel(model);
	vpvl::Scene *scene = render->scene();
	scene->updateModelView();
	scene->updateProjection();
	scene->advanceMotion(0.1f);
	render->updateAllModel();
	
	t += dt;
}

//--------------------------------------------------------------
void testApp::draw() {
	
	render->clear();
	
	render->renderModelZPlot(model);
	//render->renderModelEdge(model);
	render->renderModel(model);
	render->renderModelShadow(model);
	
    //render->renderProjectiveShadow();
    //render->renderAllModels();
    //render->renderAllAssets();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
	
	static float posX=0.0f;
	static float posZ=0.0f;

	if(key == 356){
		posX += 0.25;
	}else if(key == 358){
		posX -= 0.25;
	}else if(key == 359){
		posZ += 0.25;
	}else if(key == 357){
		posZ -= 0.25;
	}
	model->setPositionOffset(btVector3(posX,0.0f,posZ));
}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y) {
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h) {
	
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg) {
	
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo) { 
	
}