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
	
	
	
	
	delegate = new internal::Delegate();
	render = new vpvl::gl2::Renderer(delegate,1024,768,60);
	render->createPrograms();
	render->initializeSurface();
	render->uploadModel(model, "../../../data");
	render->setSelectedModel(model);
	render->createShadowFrameBuffers();
	render->renderModel(model);
	//render->renderModelZPlot(model);
}

//--------------------------------------------------------------
void testApp::update() {
	render->updateModel(model);
}

//--------------------------------------------------------------
void testApp::draw() {
	render->clear();
	//render->renderModelZPlot(model);
	ofPushMatrix();
	ofTranslate(100, 100);
	ofScale(100.f, 100.f);
	render->renderModel(model);
	ofPopMatrix();
    //render->renderProjectiveShadow();
   // render->renderAllModels();
   // render->renderAllAssets();
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