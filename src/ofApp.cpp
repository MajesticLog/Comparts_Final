#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofBackground(0);		// background color

	bFullscreen = 0;

	//---------------------------------------------------------- CAM SETUP ------------------------------------------------------
	myCam.setAutoDistance(false);
	myCam.setPosition(vec3(300.0, 250.0, 300.0));
	myCam.setTarget(vec3(0.0, 150.0, 0.0));
	myCam.disableMouseInput();
	

	//----------------------------------------------------------- WRITINGS ------------------------------------------------------
	minDistance = 10;
	leftMouseButtonPressed = false;
	writing = false;
	written = 0;

	//------------------------------------------------------------- MESH --------------------------------------------------------
	numVertices = int(ofRandom(100, 200));	// how many vertices 
	phiMult = ofRandom(1, 5);		// randomises the radius increment (see in mousePressed)
	numOfClicks = 0;					// how many times have we started a new word or letter? Maps phi increments (see in mousePressed)
	phi = 0;							// angle that influences the height of the vase, passed onto the vase object
	radius = int(ofRandom(35, 60));		// initial radius, passed to setup the vase and to then add each loop
	radLim = int(ofRandom(0, radius - 10));		// how much we want to be able to stray from the initial radius (see in mousePressed)
	initRadius = radius;				// stores the original radius so we can compare against it and avoid having weird proportions
	maxClicks = 0;						// uses system time and sets the limit of numOfClicks needed to reach phi = 180
	varVase = 0;			// uses system time and defines how many petals the vases will have
	time = 0;							// stores ofGetElapsedTimef()
	sv = true;							// do we save?
	userCount = 0;						

	myVase.setup(radius, numVertices);				// initialises the vase mesh with the original radius. Creates a tessellated base for 3D printing
	
	//------------------------------------------------------------- TEXT --------------------------------------------------------
	instructions.setGlobalDpi(72);

	instructions.load("verdana.ttf", 30, true, true);
	instructions.setLineHeight(30);
	instructions.setLetterSpacing(1.2);


}

//--------------------------------------------------------------
void ofApp::update(){

	
	
	maxClicks = ofMap(ofGetHours(), 0, 23, 50, 150);		// maps how fast phi reaches 180, based on the hour of the day	(0 -23)
	varVase = ofToInt(ofGetTimestampString("%I"));		// gets system time on a 12h basis (1 - 12)

	time = ofGetElapsedTimef();		// stores elapsed time

	
	// from ofBook on how to make a drawing program
	if (leftMouseButtonPressed) {
		ofPoint mousePos(ofGetMouseX(), ofGetMouseY());
		if (lastPoint.distance(mousePos) >= minDistance) {
			// a.distance(b) calculates the Euclidean distance between point a and b.  It's
			// the length of the straight line distance between the points.
			line.curveTo(mousePos);
			lastPoint = mousePos;
		}
	}


	// make the writings disappear
	for (int i = 0; i < polylines.size(); i++) {
		
		if (polylines[i].size() > 0) {
			polylines[i].getVertices().erase(polylines[i].getVertices().begin());
		}
		if (polylines[i].size() == 0) {
			if (i != 0) {
				polylines.erase(polylines.begin() + i);
			}
			else if (i == 0) {
				polylines.erase(polylines.begin());
			}
		}
	}

	
	

	// checks every 3f if we are currently writing or not
	if (time % 3 == 0) {	
		if (polylines.size() != 0) {
			writing = true;	
			counter = 0;
			sv = false;
		}
		else {		
			writing = false;
			counter++;
		
		}
	}				
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	
	// now onto the vase
	ofEnableDepthTest();
	myCam.begin();
	myVase.draw();
	myCam.end();
	ofDisableDepthTest();


	ofSetColor(255);  // White color for saved polylines

	// draw the lines and store them
	for (int i = 0; i < polylines.size(); i++) {
		ofPolyline polyline = polylines[i];
		polyline.draw();
	}

	ofSetColor(255, 100, 0);  // Orange color for active polyline
	line.draw();

	

	// if we've been idle for a certain amount of time 
	if (counter >= 300 && !sv || time >= 180) {
		// consider next to be from new person
		phiMult += ofRandom(-0.5, 0.5);
		userCount += 1;			
		counter = 0;
		ofResetElapsedTimeCounter();
		sv = true;
	}


	if (userCount > 5 || phi >= 180 ) {	// or || phi >= 180 && userCount != 0
		// save the mesh
		saveMesh();		
		// reset user count
		userCount = 0;
		
	}

	if (polylines.size() == 0 && time != 0) {
		ofSetColor(255);
		instructions.drawString("Take a pen and write something on the screen to generate", 10, 50);
		instructions.drawString(" the next vessel", ofGetWidth() / 3, 100);
	}


	cout << userCount << endl;
	cout << time << endl;
	

	
}

//--------------------------------------------------------------
void ofApp::saveMesh() {

	int marker = 0;
	int name = (ofGetSystemTimeMillis());	
	myVase.getMesh().save(ofToString(marker) + "_" + ofToString(name) + "vase.ply");
	sv = true;
	counter = 0;
	numVertices = int(ofRandom(100, 200));	// how many vertices 
	phiMult = ofRandom(1, 5);		// randomises the radius increment (see in mousePressed)
	numOfClicks = 0;					// how many times have we started a new word or letter? Maps phi increments (see in mousePressed)
	phi = 0;							// angle that influences the height of the vase, passed onto the vase object
	radius = int(ofRandom(35, 60));		// initial radius, passed to setup the vase and to then add each loop
	radLim = int(ofRandom(0, radius - 10));		// how much we want to be able to stray from the initial radius (see in mousePressed)
	initRadius = radius;				// stores the original radius so we can compare against it and avoid having weird proportions
	maxClicks = 0;						// uses system time and sets the limit of numOfClicks needed to reach phi = 180
	varVase = 0;						// uses system time and defines how many petals the vases will have
	time = 0;							// stores ofGetElapsedTimef()
	sv = true;							// do we save?

	myVase.setup(radius, numVertices);

	marker++;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
	//from windowing examples

	if (key == 'f') {

		bFullscreen = !bFullscreen;

		if (!bFullscreen) {
			ofSetFullscreen(false);
		}
		else if (bFullscreen == 1) {
			ofSetFullscreen(true);
		}
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

	//----------------------------------------------------------- WRITINGS ------------------------------------------------------

	// from Lewis Lepton's tutorial
	if (button == OF_MOUSE_BUTTON_LEFT) {
		numOfClicks++;	// increment to increase phi
		leftMouseButtonPressed = true;
		line.curveTo(x, y);  // Remember that x and y are the location of the mouse
		line.curveTo(x, y);  // Necessary duplicate for first control point
		lastPoint.set(x, y);  // Set the x and y of a ofVec2f in a single line		
	}


	//------------------------------------------------------------- MESH --------------------------------------------------------

	

	if (phi < 180) {		
		phi = ofMap(numOfClicks, 0, maxClicks, 0, 180);		// only add to phi if it hasn't reached 180
		float u = ofMap(ofGetMouseX(), 0, ofGetWidth(), -1.5, 1.5);
		float v = ofMap(ofGetMouseY(), 0, ofGetHeight(), 1.0, -1.0);
		radLim += (u + v);
		}

	
	float cl = ofClamp(sin(ofDegToRad(phi * phiMult)), -1.0, 1.0);		// clamped because I noticed sin() of a value multiplied sometimes gives weird results
	float radStep = ofMap(cl, -1.0, 1.0, initRadius - radLim, initRadius + radLim);		// for a nice smooth change of shape
	radius = radStep;		// vary the radius while we build the vase
	
	if(phi > 180) {		// if phi is at the max, stop adding to these
		phi += 0;
		radius += 0;
		numOfClicks += 0;
	}

	myVase.addLoop(phi, radius, varVase, initRadius + 10);		// add a loop to the mesh
	
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

// also from Lewis Lepton

	if (button == OF_MOUSE_BUTTON_LEFT) {
		leftMouseButtonPressed = false;
		line.curveTo(x, y); // Necessary duplicate for last control point
		polylines.push_back(line);
		line.clear();  // Erase the vertices, allows us to start a new brush stroke
	}
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
