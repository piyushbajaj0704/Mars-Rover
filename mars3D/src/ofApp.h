#pragma once

#include "ofMain.h"
#include  "ofxAssimpModelLoader.h"


typedef enum { CamMoveForward, CamMoveBackward } CamMoveDirection;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void drawAxis();
		void initLightingAndMaterials();
		void savePicture();
		void toggleWireframeMode();
		void togglePointsDisplay();
		void setCameraTarget();
		void doPointSelection();
		void moveCamera(CamMoveDirection dir, float step);
		void rotateCamera(float step);
		void teleportCamera();

		ofEasyCam cam;
		ofxAssimpModelLoader mars;
		ofLight light;

		bool bAltKeyDown;
		bool bCtrlKeyDown;
		bool bWireframe;
		bool bDisplayPoints;
		bool bPointSelected;
		bool bMoveCameraForward;
		bool bMoveCameraBackward;
		bool bRotateCameraLeft;
		bool bRotateCameraRight;
		bool bTeleport;
		ofVec3f selectedPoint;
		ofVec3f teleportStartPoint;

		const float selectionRange = 4.0;
};
