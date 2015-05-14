//THIS CODE WAS DEVELOPED BY ANDREAS MULLER


#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    {
        fontSmall.loadFont("Fonts/DIN.otf", 8 ); //Loads the font and 
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    {
        //This colors the background
        ofBackgroundGradient( ofColor(55), ofColor(0), OF_GRADIENT_CIRCULAR );
        
        //"Turns on alpha blending (which is on by default since OF version 0.8.0). It simply wraps opengl commands that enable blending, and turn on a common blend mode." (From openframeworks.cc)
        ofEnableAlphaBlending();
        
        // This feeds values measured in pixels, the frequency value will be pretty small
        float frequency = ofMap( ofGetMouseX(),  0, ofGetWidth(),  0.0001, 0.05 );
        
        // Draw ticks at each unit edge
        int numTicks = ceil(ofGetWidth() * frequency);
        float areaCovered = numTicks;
        if( numTicks <= 5 ) { numTicks *= 10; }
        
        //for loop
        for( int i = 0; i < numTicks; i++ )
        {
            float noisePos = ofMap( i, 0, numTicks, 0, areaCovered); //Maps the position of the noise
            float screenX = noisePos * (1.0/frequency); //Tracks the X location of the screen
            ofVec2f top( screenX, 0); //Computes the top of the screen
            ofVec2f bot( screenX, ofGetHeight()); //Computes the bottome of the screen
            
            // Brighter white lines at unit edges (0,1,2) and less bright at fractionals (0.1,0.2, etc), but only if we are zoomed in enough
            if( (abs(fmodf(noisePos, 1.0)) <= 0) && areaCovered < 18 )  { ofSetColor( ofColor::white, 90 ); } else { ofSetColor( ofColor::white, 30 );  }
            
            ofLine( top, bot); //Tells the line to go inbetween the top and bottom of the of the screen
            
            ofVec2f textPos = top + ofVec2f(4,20); // Text location
            fontSmall.drawString( ofToString(noisePos), textPos.x, textPos.y ); //String of text
        }
        
        // Compute a noise position for each pixels x position, taking a frequency value into account
        float noiseMagnitude = 300; //Size of the wave
        ofMesh mesh; //creates mesh
        mesh.setMode( OF_PRIMITIVE_LINE_STRIP); //Could not find out what this does
        int res = ofGetWidth();
        for( int i = 0; i < res; i++ ) //for loop
        {
            ofVec2f pos = ofVec2f( ofMap( i, 0, res, 0, ofGetWidth() ), ofGetHeight() * 0.5f ); //Handles the position of the wave
            
            float noisePos = (pos.x * frequency); //The position of the noise equals the x position times the frequency
            float noiseValue = ofSignedNoise( noisePos ); // ofSignedNoise gives us a value -1..1
            
            ofVec2f drawPos = pos + ofVec2f(0,noiseValue * noiseMagnitude); //The is the draw position
            
            mesh.addVertex( drawPos ); //adds the vertices
        }
        
        ofSetColor( ofColor::white );//sets color to white
        mesh.draw(); //draws the mesh
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int _key)
{   //If Statement to toggle full screen
    if( _key == 'f' )
    {
        ofToggleFullscreen();
    }
}

ofTrueTypeFont fontSmall;


