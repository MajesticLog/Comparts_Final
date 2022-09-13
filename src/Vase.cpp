#include "Vase.h"

//--------------------------------------------------------------
void Vase::setup(float rad, int numV){

	// clear the memory to start all fresh
	vase.clear();

	// get values from the ofApp to setup a base disk and ensure a better print
	radius = rad;
	numVertices = numV;
	int petals = ofToInt(ofGetTimestampString("%I"));
	
	// Z axis (well, Y) for the rotation 
	axeY = vec3(0, 1, 0);

	// taken from Andy Lomas example code 
	for (int i = 0; i < numVertices; i++) {
		float theta = ofDegToRad(ofMap(i, 0, numVertices, 360, 0.0));
		vec3 pos = radius * vec3(cos(petals * theta) / petals + cos(theta), phi, sin(petals *theta) / petals + sin(theta));
		vase.addVertex(pos);
		vase.close();
	}

	// tessellate the ofPolyline: get triangle mesh from the line, add it to our vase mesh
	tessie.tessellateToMesh(vase, OF_POLY_WINDING_POSITIVE, vaseM, false);

	// display as triangle strip
	vaseM.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);

	// extra-store the vertices because I'm too anxious to remove this line for some reason
	vaseM.addVertices(vase.getVertices());

	if (ofToInt(ofGetTimestampString("%M")) % 2 == 0) {
		pair == true;
	}
	else {
		pair == false;
	}
	
	
}

//--------------------------------------------------------------
void Vase::update(){
	
}

//--------------------------------------------------------------
void Vase::draw(){
	
	// in case we want to see the mesh being drawn
	ofSetColor(255);
	vase.draw();
	//vaseM.drawWireframe();
	ofSetColor(0);
	vaseM.draw();		
	

}
//--------------------------------------------------------------
void Vase::addLoop(float p, float rd, float st, int rdMax) {

	float angle;

	// rotate angle based on phi
	if (pair == true) {
		angle = sin(ofDegToRad(p)) * 2;
	}
	else {
		angle = - sin(ofDegToRad(p)) * 2;
	}

	
	
	

	//Add vertices
	for (int i = 0; i < numVertices; i++) {	
		float theta = ofDegToRad(ofMap(i, 0, numVertices, 360.0, 0.0));	
		float phi = ofDegToRad(p);
		pos = rd * vec3(cos(st * theta) / st + cos(theta), phi/rd*rdMax , sin(st * theta) / st + sin(theta));		 // now this is a bit odd, but scaling the radius also makes the mesh move. We divide that axis by the general radius and remultiply it by a stable one

		// now apply the rotation 
		vec3 pos2 = rotate(pos, angle, axeY);

		// add vertices to polyline as a way to quickly check what's up
		vase.addVertex(pos2);
		// add vertices to the vase mesh
		vaseM.addVertex(pos2);		
		
	}
	
	

	// adapted from the Mastering openFrameworks book

	//Add the triangles
	int base = vaseM.getNumVertices() - 2 * numVertices;
	if (base >= 0) {	//Check if it is not the first step
				//and we really need to add the triangles
		for (int i = 0; i < numVertices; i++) {
			int a = base + i;
			int b = base + (i + 1) % numVertices;
			int c = numVertices + a;
			int d = numVertices + b;
			vaseM.addTriangle(a, b, d); //Clock-wise
			vaseM.addTriangle(a, d, c);
		}
	
}
	
}

//--------------------------------------------------------------
ofMesh Vase::getMesh() {
	return vaseM;
}

//--------------------------------------------------------------
void Vase::keyPressed(int key){

}

//--------------------------------------------------------------
void Vase::keyReleased(int key){

}

//--------------------------------------------------------------
void Vase::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void Vase::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void Vase::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void Vase::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void Vase::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void Vase::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void Vase::windowResized(int w, int h){

}

//--------------------------------------------------------------
void Vase::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void Vase::dragEvent(ofDragInfo dragInfo){

}
