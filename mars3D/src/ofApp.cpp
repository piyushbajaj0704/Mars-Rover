
//--------------------------------------------------------------
//
//  CS235 - User Interface Design - Kevin M. Smith
//
//  Assignment 5 -  Mars HiRise Project - startup scene
// 
//  This is an openFrameworks 3D scene that includes an EasyCam
//  and example 3D geometry which I have reconstructed from Mars
//  HiRis photographs taken the Mars Reconnaisance Orbiter
//
//  You will use this source file (and include file) as a starting point
//  to implement assignment 5  (Parts I and II)
//
//  Please do not modify any of the keymappings.  I would like 
//  the input interface to be the same for each student's 
//  work.  Please also add your name/date below.

//  Please document/comment all of your work !
//  Have Fun !!
//
//  Student Name:   < Your Name goes Here >
//  Date: <date of last version>


#include "ofApp.h"



//--------------------------------------------------------------
// setup scene, lighting, state and load geometry
//
void ofApp::setup(){

	bWireframe = false;
	bDisplayPoints = false;
	bAltKeyDown = false;
	bCtrlKeyDown = false;
	bPointSelected = false;
	ofSetWindowShape(1024, 768);
	cam.setDistance(10);
	cam.setNearClip(.1);
	cam.setFov(65.5);   // approx equivalent to 28mm in 35mm format
	ofSetVerticalSync(true);
	cam.disableMouseInput();
	ofEnableSmoothing();
	ofEnableDepthTest();

	// setup rudimentary lighting 
	//
	initLightingAndMaterials();

	// load model (but do not scale)
	//
	mars.loadModel("mars-low-v2.obj");
	mars.setScaleNormalization(false);
}

//--------------------------------------------------------------
// incrementally update scene (animation)
//
void ofApp::update(){
	if (bMoveCameraForward && !bCtrlKeyDown) moveCamera(CamMoveForward, .05);
	else if (bMoveCameraBackward && !bCtrlKeyDown) moveCamera(CamMoveBackward, .05);

	else if (bRotateCameraLeft) rotateCamera(-1.0);   // rotate left/right
	else if (bRotateCameraRight) rotateCamera(1.0); 
	else if (bMoveCameraForward && bCtrlKeyDown) rotateCamera(-1.0);  // rotate up/down
	else if (bMoveCameraBackward && bCtrlKeyDown) rotateCamera(1.0);

	else if (bTeleport) teleportCamera();
}

//--------------------------------------------------------------
void ofApp::draw(){

//	ofBackgroundGradient(ofColor(20), ofColor(0));   // pick your own backgroujnd
	ofBackground(ofColor::black);

	cam.begin();
	ofPushMatrix();
	if (bWireframe) {                    // wireframe mode  (include axis)
		ofDisableLighting();
		ofSetColor(ofColor::slateGray);
		mars.drawWireframe();
		drawAxis();
	}
	else {
		ofEnableLighting();              // shaded mode
		mars.drawFaces();
	}

	if (bDisplayPoints) {                // display points as an option    
		glPointSize(3);
		ofSetColor(ofColor::green);
		mars.drawVertices();
	}

	// highlight selected point (draw sphere around selected point)
	//
	if (bPointSelected) {
		ofSetColor(ofColor::blue);
		ofDrawSphere(selectedPoint, .1);
	}
	
	ofPopMatrix();
	cam.end();
}

// Draw an XYZ axis in RGB at world (0,0,0) for reference.
//
void ofApp::drawAxis() { 

	ofPushMatrix();
	ofSetColor(ofColor(255, 0, 0));
	ofDrawLine(ofPoint(0, 0, 0), ofPoint(1, 0, 0));
	ofSetColor(ofColor(0, 255, 0));
	ofDrawLine(ofPoint(0, 0, 0), ofPoint(0, 1, 0));
	ofSetColor(ofColor(0, 0, 255));
	ofDrawLine(ofPoint(0, 0, 0), ofPoint(0, 0, 1));
	ofPopMatrix();
}


void ofApp::keyPressed(int key) {

	switch (key) {
	case 'C':
	case 'c':
		if (cam.getMouseInputEnabled()) cam.disableMouseInput();
		else cam.enableMouseInput();
		break;
	case 'F':
	case 'f':
		ofToggleFullscreen();
		break;
	case 'H':
	case 'h':
		break;
	case 'r':
		cam.reset();
		break;
	case 's':
		savePicture();
		break;
	case 't':
		setCameraTarget();
		break;
	case 'u':
		break;
	case 'v':
		togglePointsDisplay();
		break;
	case 'V':
		break;
	case 'w':
		toggleWireframeMode();
		break;
	case OF_KEY_ALT:
		cam.enableMouseInput();
		bAltKeyDown = true;
		break;
	case OF_KEY_CONTROL:
		bCtrlKeyDown = true;
		break;
	case OF_KEY_SHIFT:
		break;
	case OF_KEY_DEL:
		break;
	case OF_KEY_LEFT:
		bRotateCameraLeft = true;
		break;
	case OF_KEY_RIGHT:
		bRotateCameraRight = true;
		break;
	case OF_KEY_UP:
		bMoveCameraForward = true;
		break;
	case OF_KEY_DOWN:
		bMoveCameraBackward = true;
		break;
	case OF_KEY_F1:
		teleportStartPoint = cam.getPosition();
		bTeleport = true;
		break;
	}
}

void ofApp::toggleWireframeMode() {
	bWireframe = !bWireframe;
}

void ofApp::togglePointsDisplay() {
	bDisplayPoints = !bDisplayPoints;
}

void ofApp::keyReleased(int key) {
	switch (key) {

	case OF_KEY_ALT:
		cam.disableMouseInput();
		bAltKeyDown = false;
		break;
	case OF_KEY_CONTROL:
		bCtrlKeyDown = false;
		break;
	case OF_KEY_SHIFT:
		break;
	case OF_KEY_LEFT:
		bRotateCameraLeft = false;
		break;
	case OF_KEY_RIGHT:
		bRotateCameraRight = false;
		break;
	case OF_KEY_UP:
		bMoveCameraForward = false;
		break;
	case OF_KEY_DOWN:
		bMoveCameraBackward = false;
		break;
	}
}



//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

	if (bAltKeyDown == false) doPointSelection();
}

//
//  Select Target Point on Terrain
//
void ofApp::doPointSelection() {
}

// Set the camera to use the selected point as it's new target
//  
void ofApp::setCameraTarget() {
}

// Animate camera by moving it to the selected points (using update())
//
void ofApp::moveCamera(CamMoveDirection dir, float step) {
}

// Rotate Camera Left/Right
//
void ofApp::rotateCamera(float step) {
}


//  "Teleport" Camera to Selected Target
// 
void ofApp::teleportCamera() {
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
// setup basic ambient lighting in GL  (for now, enable just 1 light)
//
void ofApp::initLightingAndMaterials() {

	static float ambient[] =
	{ .5f, .5f, .5, 1.0f };
	static float diffuse[] =
	{ 1.0f, 1.0f, 1.0f, 1.0f };

	static float position[] =
	{5.0, 5.0, 5.0, 0.0 };

	static float lmodel_ambient[] =
	{ 1.0f, 1.0f, 1.0f, 1.0f };

	static float lmodel_twoside[] =
	{ GL_TRUE };


	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, position);


	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, lmodel_twoside);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
//	glEnable(GL_LIGHT1);
	glShadeModel(GL_SMOOTH);
} 

void ofApp::savePicture() {
	ofImage picture;
	picture.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
	picture.save("screenshot.png");
	cout << "picture saved" << endl;
}
