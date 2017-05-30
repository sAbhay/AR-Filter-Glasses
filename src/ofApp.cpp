#include "ofApp.h"

using namespace ofxCv;

void ofApp::setup()
{
    ofDisableArbTex();
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    cam.initGrabber(1280, 720);
    
    scrollX = 0;
    
    ofBackground(0);
	tracker.setup();
    tracker.reset();
    _currentFilter = 0;
    
    _filters.push_back(new KuwaharaFilter(6));
    
    // here's a simple filter chain
    
    FilterChain * charcoal = new FilterChain(cam.getWidth(), cam.getHeight(), "Charcoal");
    charcoal->addFilter(new BilateralFilter(cam.getWidth(), cam.getHeight(), 4, 4));
    charcoal->addFilter(new GaussianBlurFilter(cam.getWidth(), cam.getHeight(), 2.f ));
    charcoal->addFilter(new DoGFilter(cam.getWidth(), cam.getHeight(), 12, 1.2, 8, 0.99, 4));
    _filters.push_back(charcoal);
    
    // Basic filter examples
    
    _filters.push_back(new HalftoneFilter(cam.getWidth(), cam.getHeight(), 0.01));
    _filters.push_back(new CrosshatchFilter(cam.getWidth(), cam.getHeight()));
    _filters.push_back(new SobelEdgeDetectionFilter(cam.getWidth(), cam.getHeight()));
    _filters.push_back(new BilateralFilter(cam.getWidth(), cam.getHeight()));
    _filters.push_back(new SketchFilter(cam.getWidth(), cam.getHeight()));
    _filters.push_back(new DilationFilter(cam.getWidth(), cam.getHeight()));
    _filters.push_back(new PerlinPixellationFilter(cam.getWidth(), cam.getHeight()));
    _filters.push_back(new XYDerivativeFilter(cam.getWidth(), cam.getHeight()));
    _filters.push_back(new ZoomBlurFilter());
    _filters.push_back(new EmbossFilter(cam.getWidth(), cam.getHeight(), 2.f));
    _filters.push_back(new SmoothToonFilter(cam.getWidth(), cam.getHeight()));
    _filters.push_back(new TiltShiftFilter(cam.getTexture()));
    _filters.push_back(new VoronoiFilter(cam.getTexture()));
    _filters.push_back(new CGAColorspaceFilter());
    _filters.push_back(new ErosionFilter(cam.getWidth(), cam.getHeight()));
    _filters.push_back(new LookupFilter(cam.getWidth(), cam.getHeight(), "img/lookup_amatorka.png"));
    _filters.push_back(new LookupFilter(cam.getWidth(), cam.getHeight(), "img/lookup_miss_etikate.png"));
    _filters.push_back(new LookupFilter(cam.getWidth(), cam.getHeight(), "img/lookup_soft_elegance_1.png"));
    _filters.push_back(new VignetteFilter());
    _filters.push_back(new PosterizeFilter(8));
    _filters.push_back(new LaplacianFilter(cam.getWidth(), cam.getHeight(), ofVec2f(1, 1)));
    _filters.push_back(new PixelateFilter(cam.getWidth(), cam.getHeight()));
    _filters.push_back(new HarrisCornerDetectionFilter(cam.getTexture()));
    _filters.push_back(new MotionDetectionFilter(cam.getTexture()));
    _filters.push_back(new LowPassFilter(cam.getWidth(), cam.getHeight(), 0.9));
    
    // blending examples
    
    ofImage wes = ofImage("img/wes.jpg");
    ChromaKeyBlendFilter * chroma = new ChromaKeyBlendFilter(ofVec3f(0.f, 1.f, 0.f), 0.4);
    chroma->setSecondTexture(wes.getTexture());
    _filters.push_back(chroma);
    
    _filters.push_back(new DisplacementFilter("img/mandel.jpg", cam.getWidth(), cam.getHeight(), 25.f));
    _filters.push_back(new PoissonBlendFilter(wes.getTexture(), cam.getWidth(), cam.getHeight(), 2.0));
    _filters.push_back(new DisplacementFilter("img/glass/3.jpg", cam.getWidth(), cam.getHeight(), 200.0));
    _filters.push_back(new DisplacementFilter("img/mesh.png", cam.getWidth(), cam.getHeight(), 100.0));
    _filters.push_back(new ExclusionBlendFilter(wes.getTexture()));
    
    
    
    // here's how you use Convolution filters
    
    Abstract3x3ConvolutionFilter * convolutionFilter1 = new Abstract3x3ConvolutionFilter(cam.getWidth(), cam.getHeight());
    convolutionFilter1->setMatrix(-1, 0, 1, -2, 0, 2, -1, 0, 1);
    _filters.push_back(convolutionFilter1);
    
    Abstract3x3ConvolutionFilter * convolutionFilter2 = new Abstract3x3ConvolutionFilter(cam.getWidth(), cam.getHeight());
    convolutionFilter2->setMatrix(4, 4, 4, 4, -32, 4, 4,  4, 4);
    _filters.push_back(convolutionFilter2);
    
    Abstract3x3ConvolutionFilter * convolutionFilter3 = new Abstract3x3ConvolutionFilter(cam.getWidth(), cam.getHeight());
    convolutionFilter3->setMatrix(1.2,  1.2, 1.2, 1.2, -9.0, 1.2, 1.2,  1.2, 1.2);
    _filters.push_back(convolutionFilter3);
    
    
    // and here's how you might daisy-chain a bunch of filters
    
    FilterChain * foggyTexturedGlassChain = new FilterChain(cam.getWidth(), cam.getHeight(), "Weird Glass");
    foggyTexturedGlassChain->addFilter(new PerlinPixellationFilter(cam.getWidth(), cam.getHeight(), 13.f));
    foggyTexturedGlassChain->addFilter(new EmbossFilter(cam.getWidth(), cam.getHeight(), 0.5));
    foggyTexturedGlassChain->addFilter(new GaussianBlurFilter(cam.getWidth(), cam.getHeight(), 3.f));
    _filters.push_back(foggyTexturedGlassChain);
    
    
    // here's another unimaginative filter chain
    
    FilterChain * watercolorChain = new FilterChain(cam.getWidth(), cam.getHeight(), "Monet");
    watercolorChain->addFilter(new KuwaharaFilter(9));
    watercolorChain->addFilter(new LookupFilter(cam.getWidth(), cam.getHeight(), "img/lookup_miss_etikate.png"));
    watercolorChain->addFilter(new BilateralFilter(cam.getWidth(), cam.getHeight()));
    watercolorChain->addFilter(new PoissonBlendFilter("img/canvas_texture.jpg", cam.getWidth(), cam.getHeight(), 2.0));
    watercolorChain->addFilter(new VignetteFilter());
    _filters.push_back(watercolorChain);
    
    
    // and here's a random gradient map for posterity
    
    vector<GradientMapColorPoint> colors;
    for (float percent=0.0; percent<=1.0; percent+= 0.1)
        colors.push_back( GradientMapColorPoint(ofRandomuf(),ofRandomuf(),ofRandomuf(),percent) );
    _filters.push_back(new GradientMapFilter(colors));
    
    b[0] = Button(ofGetWidth()/16, 2*ofGetHeight()/8, ofGetWidth()/50, "buttonImages/video.png", true, false);
    b[1] = Button(ofGetWidth()/16, 3*ofGetHeight()/8, ofGetWidth()/50, "buttonImages/camera.png", false, false);
    b[2] = Button(ofGetWidth()/16, 4.5*ofGetHeight()/8, ofGetWidth()/50, "buttonImages/filter.png", true, false);
    b[3] = Button(ofGetWidth()/16, 5.5*ofGetHeight()/8, ofGetWidth()/50, "buttonImages/facetracker.png", true, false);
    
    for(int i = 0; i < _filters.size(); i++)
    {
//        fb.push_back(SetButton(scrollX[0] + (ofGetWidth()/_filters.size()*i), ofGetHeight()/1.2, ofGetWidth()/50, to_string(i) + ".png", i, _filters[i]->getName()));

        fb.push_back(SetButton(scrollX + ofGetWidth()/40 + (ofGetWidth()*2.5/_filters.size()*i), ofGetHeight()/1.2, ofGetWidth()/50, "buttonImages/filter.png", i, _filters[i]->getName()));
    }
    
    ofLoadImage(img, "base.png");
    
    ff[0] = FaceFeature(ofxFaceTracker::FACE_OUTLINE, 0);
    ff[1] = FaceFeature(ofxFaceTracker::RIGHT_EYE, 1);
    ff[2] = FaceFeature(ofxFaceTracker::LEFT_EYE, 2);
    ff[3] = FaceFeature(ofxFaceTracker::OUTER_MOUTH, 3);
    ff[4] = FaceFeature(ofxFaceTracker::INNER_MOUTH, 4);
    ff[5] = FaceFeature(ofxFaceTracker::NOSE_BRIDGE, 5);
    ff[6] = FaceFeature(ofxFaceTracker::RIGHT_EYEBROW, 6);
    ff[7] = FaceFeature(ofxFaceTracker::LEFT_EYEBROW, 7);
    
    string names[8] = {"Face", "Left Eye", "Right Eye", "Lips", "Mouth", "Nose", "Right Eyebrow", "Left Eyebrow"};
    string images[8] = {"buttonImages/face.png", "buttonImages/eye.png", "buttonImages/eye.png", "buttonImages/lips.png", "buttonImages/mouth.png", "buttonImages/nose.png", "buttonImages/right_eyebrow.png", "buttonImages/left_eyebrow.png"};
    
    for(int i = 0; i < 8; i++)
    {
        ffb[i] = SetButton(15*ofGetWidth()/16, ofGetHeight()/8 + (i*ofGetHeight()/12), ofGetWidth()/50, images[i], i, names[i]);
        
        ffSelect[i] = false;
        
        ffButton[i] = Button(0.9*ofGetWidth(), 0.75*ofGetHeight(), ofGetWidth()/50, "buttonImages/filter.png", false, false);
    }
    
    done = Button(0.9*ofGetWidth(), 0.9*ofGetHeight(), ofGetWidth()/50, "buttonImages/done.png", false, false);
}

void ofApp::update() {
	
    cam.update();
    
    if(trackerOn)
    {
        if(cam.isFrameNew())
        {
            tracker.update(toCv(cam));
        }
    }
    
    if(!drawVideo)
    {
        filtersOn = false;
    }
    
    
    if(filtersOn || trackerOn)
    {
        if(ofGetMousePressed())
        {
            if(ofGetMouseY() <= ofGetHeight()/1.2 + ofGetWidth()/25 && ofGetMouseY() >= ofGetHeight()/1.2 - ofGetWidth()/25)
            {
                scrollX = ofGetMouseX() - ofGetPreviousMouseX();
                
                for(int i = 0; i < fb.size(); i++)
                {
                    fb.at(i).setPos(ofVec2f(fb.at(i).getPos().x + scrollX, fb.at(i).getPos().y));
                }
            }
        }
        
        if((ofGetPreviousMouseY() <= ofGetHeight()/1.2 + ofGetWidth()/25 && ofGetPreviousMouseY() >= ofGetHeight()/1.2 - ofGetWidth()/25) && (ofGetMouseY() > ofGetHeight()/1.2 + ofGetWidth()/25 || ofGetMouseY() < ofGetHeight()/1.2 - ofGetWidth()/25))
        {
            for(int i = 0; i < fb.size(); i++)
            {
                fb.at(i).resetPos();
            }
        }
    }
    
    if(picture)
    {
        for(int j = 0; j < 4; j++)
        {
            b[j].setHidden(true);
        }
        
        ofHideCursor();
    }
}

void ofApp::draw() {
    
    ofBackground(0, 0, 0);
    ofSetColor(255);
    ofPushMatrix();
    ofScale(-1, 1);
    ofTranslate(-cam.getWidth(), 0);
    
    if(filtersOn)
    {
        _filters[_currentFilter]->begin();
        cam.draw(0,0);
        _filters[_currentFilter]->end();
    }
    
    if(drawVideo && !filtersOn)
    {
        cam.draw(0, 0);
    }
    
    ofPopMatrix();
        
    if(trackerOn)
    {
//        overlay.draw(tracker);

//        tracker.draw(true);

        for(int i = 0; i < 8; i++)
        {
            ff[i].draw(tracker);
        }
    }
    
    ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
    
    if(ofGetMouseX() < ofGetWidth()/8)
    {
        for(int i = 0; i < 4; i++)
        {
            b[i].display();
        }
    }
    
    if(ofGetMouseY() > ofGetHeight()/1.5 && (filtersOn || fffSelect))
    {
        for(int i = 0; i < fb.size(); i++)
        {
            fb.at(i).display2();
        }
    }
    
    if(ofGetMouseX() >= 3*ofGetWidth()/4)
    {
        if(index != -10)
        {
            if(ffSelect[index])
            {
                console(index);
            }
        }
    }
    
    if(trackerOn && ofGetMouseX() >= 3*ofGetWidth()/4 && !consoleDrawing)
    {
        for(int i = 0; i < 8; i++)
        {
            {
                ffb[i].display();
            }
        }
    }
    
    if(picture)
    {
        takeScreenshot();
        picture = false;
    }
}

void ofApp::keyPressed(int key)
{
	if(key == 'r')
    {
		tracker.reset();
	}
}

void ofApp::mouseReleased(int x, int y, int button)
{
    for(int i = 0; i < 4; i++)
    {
        if(b[i].isPressed(x, y))
        {
            switch(i)
            {
                case 0:
                    drawVideo = !drawVideo;
                    b[0].setState(drawVideo);
                    break;
                    
                case 1:
                    picture = true;
                    break;
                    
                case 2:
                    filtersOn = !filtersOn;
                    b[2].setState(filtersOn);
                    break;
                    
                case 3:
                    trackerOn = !trackerOn;
                    b[3].setState(trackerOn);
                    break;
            }
        }
    }
    
    if(filtersOn || trackerOn)
    {
        for(int i = 0; i < fb.size(); i++)
        {
            if(fb.at(i).isPressed(x, y))
            {
                if(!fffSelect)
                {
                    _currentFilter = fb.at(i).getNumber();
                }
                else
                {
                    fffindex = fb.at(i).getNumber();
                    if(index != -10) ff[index].setFilter(_filters.at(fffindex));
                    
//                    fffSelect = false;
                }
            }
        }
    }
    
    if(trackerOn)
    {
        if(!consoleDrawing)
        {
            for(int i = 0; i < 8; i++)
            {
                if(ffb[i].isPressed(x, y))
                {
                    ffSelect[i] = true;
                    consoleDrawing = true;
                    index = i;
                }
            }
        }
        
        if(index != -10)
        {
            if(consoleDrawing)
            {
                if(ffButton[index].isPressed(x, y))
                {
                    if(ff[index].getFilter() != NULL)
                    {
                        ff[index].setFilter(NULL);
                    }
                    else
                    {
                        fffSelect = true;
                    }
                }
                
                if(done.isPressed(x, y))
                {
                    fffSelect = false;
                    
                    ffSelect[index] = false;
                    consoleDrawing = false;
                    
                    index = -10;
                }
            }
        }
    }
}

void ofApp::takeScreenshot()
{
    img.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
    img.save("screenshot.png");
    
    ofShowCursor();
    
    for(int j = 0; j < 4; j++)
    {
        b[j].setHidden(false);
    }
}

void ofApp::console(int i)
{
    ofFill();
    ofSetColor(ff[i].getColor());
    ofDrawRectangle(0.80*ofGetWidth(), 0, ofGetWidth()*0.20, ofGetHeight());
    
    ffButton[i].display();
    done.display();
    
    ofSetColor(255);
    ofDrawRectangle(0.825*ofGetWidth(), 0.05*ofGetHeight(), 0.15*ofGetWidth(), 0.075*ofGetHeight());
    
    ofSetColor(0);
    ofDrawBitmapString(ffb[index].getName(), 0.85*ofGetWidth(), 0.05*ofGetHeight() + 0.0375*ofGetHeight());
    
    ofColor c = ff[index].getColor();
    
    float colorAttributes[4] = {static_cast<float>(c.r), static_cast<float>(c.g), static_cast<float>(c.b), static_cast<float>(c.a)};
    
    for(int i = 1; i < 5; i++)
    {
        ofPoint low = ofPoint(0.80*ofGetWidth() + i*ofGetWidth()*0.20/5, ofGetHeight()/5);
        ofPoint high = ofPoint(0.80*ofGetWidth() + i*ofGetWidth()*0.20/5, ofGetHeight()/5 + (ofGetHeight()/720)*255);
    
        ofSetColor(255 - ff[index].getColor().r, 255 - ff[index].getColor().g, 255 - ff[index].getColor().b);
        ofDrawLine(low, high);
        
        ofFill();
        ofSetColor(0);
        
        ofDrawRectangle(low.x - ofGetWidth()/150, high.y - ofMap(colorAttributes[i-1], 0, 255, 0, (ofGetHeight()/720)*255), ofGetWidth()/75, ofGetHeight()/100);
        
        ofNoFill();
        ofSetColor(255);
        
        ofDrawRectangle(low.x - ofGetWidth()/150, high.y - ofMap(colorAttributes[i-1], 0, 255, 0, (ofGetHeight()/720)*255), ofGetWidth()/75, ofGetHeight()/100);

        
        if(ofGetMousePressed())
        {
            if(ofGetMouseX() >= low.x - ofGetWidth()/150 && ofGetMouseX() <= low.x + ofGetWidth()/150 && ofGetMouseY() <= 1.1*high.y && ofGetMouseY() >= 0.9*low.y)
            {
                colorAttributes[i-1] = ofMap(-ofGetMouseY() + low.y, 0, 255, 0, (ofGetHeight()/720)*255);
                
                ff[index].setColor(ofColor(colorAttributes[0], colorAttributes[1], colorAttributes[2], colorAttributes[3]));
            }
        }
    }
}
