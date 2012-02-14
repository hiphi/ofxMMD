#include "testApp.h"
#include "Delegate.h"

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
	//render->createShadowFrameBuffers();
	//render->renderModel(model);
	//render->renderModelZPlot(model);
	
	//ofBackground(255,255,255);
}

//--------------------------------------------------------------
void testApp::update() {
	//render->updateModel(model);
	vpvl::Scene *scene = render->scene();
	scene->updateModelView();
	scene->updateProjection();
	render->updateAllModel();
}

//--------------------------------------------------------------
void testApp::draw() {
	//static float rot=0;
	render->clear();
	//render->renderModelZPlot(model);
	
	render->renderModel(model);
	//render->renderModelEdge(model);
	//render->renderModelShadow(model);
	
    //render->renderProjectiveShadow();
    //render->renderAllModels();
    //render->renderAllAssets();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
	
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