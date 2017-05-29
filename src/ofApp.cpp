#include "ofApp.h"

using namespace ofxCv;

void ofApp::setup()
{
    ofDisableArbTex();
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    cam.initGrabber(1280, 720);
    
    for(int i = 0; i < 2; i++)
    {
        scrollX[i] = 0;
    }
    
    ofBackground(0);
	tracker.setup();
    tracker.reset();
    _currentFilter = 0;
    
    vector<string> s;
    s.push_back("overlayImages/eyes/simple.png");
    
    overlay = FaceOverlay();
    
    // here's a simple filter chain
    
    FilterChain * charcoal = new FilterChain(cam.getWidth(), cam.getHeight(), "Charcoal");
    charcoal->addFilter(new BilateralFilter(cam.getWidth(), cam.getHeight(), 4, 4));
    charcoal->addFilter(new GaussianBlurFilter(cam.getWidth(), cam.getHeight(), 2.f ));
    charcoal->addFilter(new DoGFilter(cam.getWidth(), cam.getHeight(), 12, 1.2, 8, 0.99, 4));
    _filters.push_back(charcoal);
    
    // Basic filter examples
    
    _filters.push_back(new HalftoneFilter(cam.getWidth(), cam.getHeight(), 0.01));
    _filters.push_back(new CrosshatchFilter(cam.getWidth(), cam.getHeight()));
    _filters.push_back(new KuwaharaFilter(6));
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
    b[2] = Button(ofGetWidth()/16, 5*ofGetHeight()/8, ofGetWidth()/50, "buttonImages/filter.png", true, false);
    b[3] = Button(ofGetWidth()/16, 6*ofGetHeight()/8, ofGetWidth()/50, "buttonImages/facetracker.png", true, false);
    
    for(int i = 0; i < _filters.size(); i++)
    {
//        fb.push_back(SetButton(scrollX[0] + (ofGetWidth()/_filters.size()*i), ofGetHeight()/1.2, ofGetWidth()/50, to_string(i) + ".png", i, _filters[i]->getName()));

        fb.push_back(SetButton(scrollX[0] + ofGetWidth()/40 + (ofGetWidth()*2.5/_filters.size()*i), ofGetHeight()/1.2, ofGetWidth()/50, "buttonImages/filter.png", i, _filters[i]->getName()));
    }
    
    ofLoadImage(img, "base.png");
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
    
    
    if(filtersOn)
    {
        if(ofGetMousePressed())
        {
            if(ofGetMouseY() <= ofGetHeight()/1.2 + ofGetWidth()/25 && ofGetMouseY() >= ofGetHeight()/1.2 - ofGetWidth()/25)
            {
                scrollX[0] = ofGetMouseX() - ofGetPreviousMouseX();
                
                for(int i = 0; i < fb.size(); i++)
                {
                    fb.at(i).setPos(ofVec2f(fb.at(i).getPos().x + scrollX[0], fb.at(i).getPos().y));
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
        overlay.draw(tracker);
//        tracker.draw(true);
    }
    
    ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
    
    for(int i = 0; i < 4; i++)
    {
        if(ofGetMouseX() < ofGetWidth()/8)
        {
            b[i].display();
        }
    }
    
    for(int i = 0; i < fb.size(); i++)
    {
        if(ofGetMouseY() > ofGetHeight()/1.5 && filtersOn)
        {
            fb.at(i).display2();
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
	if(key == 'r') {
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
    
    if(filtersOn)
    {
        for(int i = 0; i < fb.size(); i++)
        {
            if(fb.at(i).isPressed(x, y))
            {
                _currentFilter = fb.at(i).getNumber();
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
