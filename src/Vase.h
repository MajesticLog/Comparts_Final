#pragma once

#include "ofMain.h"

using namespace glm;


class Vase : public ofBaseApp{

	public:
		void setup(float rad, int numV);
		void update();
		void draw();
		void addLoop(float p, float rd, float st, int rdMax);
		ofMesh getMesh();

		int radius;
		int numVertices;
		ofPolyline base;
		float phi;
		float step;

		ofPolyline vase;
		ofMesh vaseM;
		ofTessellator tessie;

		vec3 pos;	//Start from center of coordinate
		vec3 axeX;	//Set initial coordinate system
		vec3 axeY;
		vec3 axeZ;

		bool pair;

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
