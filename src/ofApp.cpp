#include "ofApp.h"

//-----------------------------------------------------------------------------------------
//
void ofApp::setup()
//At the begining of the program, to define the basic code condition.
{
	fontSmall.loadFont("Fonts/DIN.otf", 8 );
    //put the file into
	
	// Give us a starting point for the camera
	camera.setNearClip(0.01f);
    //the carema's clip
	camera.setPosition( 0, 10, -150 );
    //set the position
    camera.lookAt( ofVec3f( 0, 0, 0));
    //put the location
	camera.setMovementMaxSpeed( 1 );
    //set the speed
    
    //+++++++++++++++++++++++++++++++++++++++++++++++++
    //Set up vertices and colors
    for (int y=0; y<H; y++) {
        for (int x=0; x<W; x++) {
        //set the size
            mesh.addVertex(
                           ofPoint( (x - W/2), (y - H/2), 0 ) );
            //set the position
            mesh.addColor( ofColor( 0, 0, 0 ) );
            //set the color
        }
    }
    //Set up triangles' indices
    for (int y=0; y<H-1; y++) {
        for (int x=0; x<W-1; x++) {
            int i1 = x + W * y;
            int i2 = x+1 + W * y;
            int i3 = x + W * (y+1);
            int i4 = x+1 + W * (y+1);
            mesh.addTriangle( i1, i2, i3 );
            mesh.addTriangle( i2, i4, i3 );
        }
    }
    
    setNormals( mesh );
    //Set normals to the surface
    //Note, setNormals is our function, which is declared
    
    //Enabling light source
    light.enable();
    //put the light into
    background.loadImage("1.jpg");
    //load the image
    
}

//-----------------------------------------------------------------------------------------
//
void ofApp::update()
//the update code
{
    float time = ofGetElapsedTimef();
    //Get time
    //Change vertices
    for (int y=0; y<H; y++) {
        for (int x=0; x<W; x++) {
            int i = x + W * y;
            //Vertex index
            ofPoint p = mesh.getVertex( i );
            
            //Get Perlin noise value
            float value = ofNoise( x * 0.05, y * 0.05, time * 0.5 )+(ofNoise( x * 1, y * 1, time * 1 )/5);
            
            //Change z-coordinate of vertex
            p.z = value * (H-y)/120 * 5;
            mesh.setVertex( i, p );
            
            //Change color of vertex
            mesh.setColor( i,
                          ofColor( value*50, value * 25, 150 ) );
                          //set the color
        }
    }
    setNormals( mesh );
    //Update the normals
    
}

//-----------------------------------------------------------------------------------------
//
void ofApp::draw()
//To work on the code.
{
    background.draw(0,0,0, 1280, 800);
    //the position of background
	//ofBackgroundGradient( ofColor(40,40,40), ofColor(0,0,0), OF_GRADIENT_CIRCULAR);
	
	ofEnableDepthTest();
    //we start and stop depth testing every loop to allow for GUI elements
	
	camera.begin();
    //start drawing to the camera view
	
		// draw a grid on the floor
//		ofSetColor( ofColor(60) ); //color of the grid
//		ofPushMatrix();
//			ofRotate(90, 0, 0, -1); //turn the YZ plane CCW to make a "floor"
//            ofDrawGridPlane( 50, 10, false); //Draws a YZ plane
//		ofPopMatrix();
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    ofPushMatrix();
    //Store the coordinate system

    ofRotate( 90, -1, 0, 0 );
    //the rotate
    ofTranslate(0, 0, -2.5);//Rotate coordinate system
    //Draw mesh
    //Here ofSetColor() does not affects the result of drawing,
    //because the mesh has its own vertices' colors
    mesh.draw();
    
    ofPopMatrix();
    //push ... pop matrix
    
    
    
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	camera.end();
    //stop drawing to the camera


	ofDisableDepthTest();
    //stop drawing to the z-buffer
    
 	ofSetColor( ofColor::white );
    //set color for the framerate text
	fontSmall.drawStringShadowed(ofToString(ofGetFrameRate(),2), ofGetWidth()-35, ofGetHeight() - 6, ofColor::whiteSmoke,
    ofColor::black );
    //draw the current framerate in the lower right hand corner with a dropshadow
}

//--------------------------------------------------------------
//Universal function which sets normals for the triangle mesh
void ofApp::setNormals( ofMesh &mesh ){
    
    //The number of the vertices
    int nV = mesh.getNumVertices();
    
    //The number of the triangles
    int nT = mesh.getNumIndices() / 3;
    
    vector<ofPoint> norm( nV ); //Array for the normals
    
    //Scan all the triangles. For each triangle add its
    //normal to norm's vectors of triangle's vertices
    for (int t=0; t<nT; t++) {
        
        //Get indices of the triangle t
        int i1 = mesh.getIndex( 3 * t );
        int i2 = mesh.getIndex( 3 * t + 1 );
        int i3 = mesh.getIndex( 3 * t + 2 );
        
        //Get vertices of the triangle
        const ofPoint &v1 = mesh.getVertex( i1 );
        const ofPoint &v2 = mesh.getVertex( i2 );
        const ofPoint &v3 = mesh.getVertex( i3 );
        
        //Compute the triangle's normal
        ofPoint dir = ( (v2 - v1).crossed( v3 - v1 ) ).normalized();
        
        //Accumulate it to norm array for i1, i2, i3
        norm[ i1 ] += dir;
        norm[ i2 ] += dir;
        norm[ i3 ] += dir;
    }
    
    //Normalize the normal's length
    for (int i=0; i<nV; i++) {
        norm[i].normalize();
    }
    
    //Set the normals to mesh
    mesh.clearNormals();
    mesh.addNormals( norm );
}

//-----------------------------------------------------------------------------------------
//
void ofApp::keyPressed(int key)
//key board input
{
	if( key == 'f' )
    //key board "f"
	{
		ofToggleFullscreen();
        //the whole screen
	}
}
