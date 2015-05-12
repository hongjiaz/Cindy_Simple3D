//created by Hongjia Zhang 

#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "Math/MathUtils.h"

#include "Utils/ofTrueTypeFontExt.h"
#include "Utils/Cameras/ofxWalkingFirstPersonCamera.h"

class ofApp : public ofBaseApp
{
	public:
		
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
        void setNormals(ofMesh &mesh);
	
		ofxFirstPersonCamera	camera;
	
		ofTrueTypeFontExt		fontSmall;
    
    ofMesh mesh;
    //hand out the mesh
    ofLight light;
    //hand out the light
    int W = 300;
    //width = 300
    int H = 300;
    //height = 300
    ofImage background;
    //put the background into
};