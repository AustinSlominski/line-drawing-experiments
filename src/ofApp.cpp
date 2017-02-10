#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);
    ofDisableArbTex();
    ofSetVerticalSync(true);
    
    for (int i = 0; i < NUM_LAYERS; i++) {
        layers[i].load("layer_"+ofToString(i)+".png");
    }
    
    shader_fbm.load("shaders/fbm");
    shader_layers.load("shaders/layers");
    shader_ripple.load("shaders/ripple");
    
    fbo_fbm.allocate(ofGetWidth(),ofGetHeight());
    fbo_ripple.allocate(ofGetWidth(),ofGetHeight());
    fbo_layers.allocate(ofGetWidth(),ofGetHeight());
    plane.set(ofGetWidth(),ofGetHeight());
    plane.setPosition((ofGetWidth()/2),(ofGetHeight()/2),0);
    plane_ripple.set(ofGetWidth(),ofGetWidth());
    plane_ripple.setPosition((ofGetWidth()/2),(ofGetHeight()/2),0);
    
    b_grid = true;
    
    gui_fbm.setup("FBM Noise","settings.xml",0,200);
    gui_fbm.add(noiseScaleX.set("Scale X", 5.f, .0f, 10.f));
    gui_fbm.add(noiseScaleY.set("Scale Y", 5.f, .0f, 10.f));
    gui_fbm.add(noiseIncrement1.set("Increment 1", .01f, .0f, .1f));
    gui_fbm.add(noiseIncrement2.set("Increment 2", .01f, .0f, .1f));
    gui_fbm.add(map1.set("Map Min", .0f, .0f, 1.f));
    gui_fbm.add(map2.set("Map Max", 1.f, .0f, 1.f));
    gui_fbm.add(speed.set("Speed", 0.25, .0, 1.0));
    gui_fbm.add(octaves.set("# of Octaves", 5, 1, 10));
    gui_fbm.add(bSmooth.set("Smooth", 1, 0, 1));
    gui_fbm.add(back_color.set("Background Color", ofColor(241,242,237)));
    gui_fbm.add(band_width.set("BandWidth",0.01,0.0,1.0));
}

//--------------------------------------------------------------
void ofApp::update(){
    fbo_layers.begin();
    ofClear(0,0,0,0);
    fbo_layers.end();
    
    fbo_fbm.begin();
    ofClear(0,0,0,0);
    fbo_fbm.end();
    
    fbo_ripple.begin();
    ofClear(0,0,0,0);
    fbo_ripple.end();
    
    if (ofGetFrameNum() % 100 == 0) {
        shader_fbm.load("shaders/fbm");
        shader_layers.load("shaders/layers");
        shader_ripple.load("shaders/ripple");
    }

    float shader_time = ofGetElapsedTimef()*speed;
    
//    fbo_fbm.begin();
//    shader_fbm.begin();
//    shader_fbm.setUniform1i("octaves", octaves);
//    shader_fbm.setUniform1i("b2D3D", 0);
//    shader_fbm.setUniform1f("time", shader_time);
//    shader_fbm.setUniform2f("scale", noiseScaleX, noiseScaleY);
//    shader_fbm.setUniform2f("map", map1, map2);
//    shader_fbm.setUniform1i("bSmooth", bSmooth);
//    plane.draw();
//    shader_fbm.end();
//    fbo_fbm.end();
    
    fbo_ripple.begin();
    shader_ripple.begin();
    shader_ripple.setUniform1f("time", ofGetElapsedTimef());
    shader_ripple.setUniform1f("speed", speed);
    shader_ripple.setUniform1f("band_width",band_width);
    plane_ripple.draw();
    shader_ripple.end();
    fbo_ripple.end();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetBackgroundColor(back_color);
    
//    fbo_layers.draw(0,0);
//
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    ofEnableAntiAliasing();
    for (int i = 0; i < NUM_LAYERS; i++) {
        shader_layers.begin();
        shader_layers.setUniformTexture("tex0", layers[i].getTexture(), 0);
        shader_layers.setUniformTexture("alpha_mask", fbo_ripple.getTexture(), 1);
        shader_layers.setUniform2f("range", (1.0/NUM_LAYERS)*i,((1.0/NUM_LAYERS)*i)+(1.0/NUM_LAYERS));
        plane.draw();
        shader_layers.end();
    }
    ofDisableAntiAliasing();
    ofDisableAlphaBlending();
    ofDisableSmoothing();
    
//    if(b_grid){
//        drawDebug();
//    }
    
//    fbo_ripple.draw(0,0);
    
    syphon.publishScreen();
    
    ofDrawBitmapString(ofToString(ofGetFrameRate()),10,10);
    
    gui_fbm.draw();
}

//--------------------------------------------------------------
void ofApp::drawDebug(){
    for (int i = 0; i < NUM_LAYERS; i++) {
        int grid_width = ofGetWidth()/NUM_LAYERS;
        layers[i].draw(grid_width*i,0,grid_width,(grid_width/layers[i].getWidth())*layers[i].getHeight());
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
