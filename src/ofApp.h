#pragma once

#include "ofMain.h"
#include "Vase.h"

using namespace glm;


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void saveMesh();

		float radius;
		int numVertices;
		float initRadius;
		float phiMult;
		float radLim;
		float phi;
		float adR;
		int varVase;
		Vase myVase;
		float stp;
		vec3 scale;
		bool sv;
		int check;

		bool bFullscreen;


		int gridX, gridY;

		float counter;
		int written;
		float speed;
		int frame;
		bool writing;
		int numOfClicks;
		int maxClicks;
		int userCount;
		int countMax;
		
		ofTrueTypeFont instructions;

		ofPolyline line;
		bool leftMouseButtonPressed;
		ofVec2f lastPoint;
		float minDistance;
		vector <ofPolyline> polylines;

		int time;

		ofEasyCam myCam;


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
		
};
