#include "Grapher.h"

void Grapher::saveSettings()
{
    xml_settings.setValue("settings:x", r.x);
    xml_settings.setValue("settings:y", r.y);
    xml_settings.setValue("settings:w", r.width);
    xml_settings.setValue("settings:h", r.height);

    xml_settings.saveFile(ofToDataPath("Grapher/"+name+".xml"));
}

void Grapher::setup(int _x, int _y, int _w, int _h)
{
    r.set(_x, _y, _w, _h);
    dx = 1.0;                 // default
    max_length_of_data = 20; // default
    setColor(ofColor::white);   // default
    max_data = -100000;            // default
    min_data = 100000;             // default
    name = "noname";          // default
    label.resize(1);
    
    font_title.load(ofToDataPath("Grapher/DIN Alternate Bold.ttf"), 18);
    font_parameter.load(ofToDataPath("Grapher/DIN Alternate Bold.ttf"), 10);
    img_expand.load(ofToDataPath("Grapher/expand.png"));
    img_move.load(ofToDataPath("Grapher/move.png"));
    
    button_save_csv.addListener(this, &Grapher::saveCSV);
    slider_bufsize.addListener(this, &Grapher::setMaxLengthOfData);
    button_clear.addListener(this, &Grapher::clear);

    // panel_size.set(100, 16);
    // panel.setup();
    // panel.setSize(panel_size.x, panel_size.y);
    // panel.setDefaultHeight(panel_size.y);
    // panel.setDefaultWidth(panel_size.x);
    // panel.setName("Options");
    
    // panel.add(slider_bufsize.setup("BufSize", 128, 32, 512));
    // panel.add(button_save_csv.setup("Save CSV"));
    // panel.add(toggle_pause.setup("Pause", false));
    // panel.add(toggle_no_draw.setup("No draw", false));
    // panel.add(button_clear.setup("Clear"));
    
    min_height = panel.getHeight()+20;
    min_width  = panel.getWidth()+100;
    
    grid = 10;
}

void Grapher::setup(string _name)
{
    setup(ofRandom(300)+200, ofRandom(200)+200, 500, 250);
    setName(_name);
}

void Grapher::setColor(ofColor _color)
{
    color.clear();
    color.push_back(_color);
    {
        color.push_back(ofColor::lightBlue);
        color.push_back(ofColor::lightPink);
        color.push_back(ofColor::lightGreen);
        color.push_back(ofColor::lightSalmon);
        color.push_back(ofColor::lightYellow);
        color.push_back(ofColor::lightSeaGreen);
        color.push_back(ofColor::lightGray);
        color.push_back(ofColor::lightGoldenRodYellow);
        color.push_back(ofColor::lightGrey);
    }
    
    c_text = _color;
    c_background = _color.getInverted();
    c_background.set(c_background.r, c_background.g, c_background.b, 160);
    
    c_fill = _color.getLerped(_color.getInverted(), 0.5);
    c_fill.set(c_fill.r, c_fill.g, c_fill.b, 160);
    
    

    slider_bufsize.setTextColor(c_text);
    slider_bufsize.setBackgroundColor(c_background);
    slider_bufsize.setFillColor(c_fill);
    
    button_save_csv.setTextColor(c_text);
    button_save_csv.setBackgroundColor(c_background);
    button_save_csv.setFillColor(c_fill);

    button_clear.setTextColor(c_text);
    button_clear.setBackgroundColor(c_background);
    button_clear.setFillColor(c_fill);
    
    toggle_pause.setTextColor(c_text);
    toggle_pause.setBackgroundColor(c_background);
    toggle_pause.setFillColor(c_fill);
    
    toggle_no_draw.setTextColor(c_text);
    toggle_no_draw.setBackgroundColor(c_background);
    toggle_no_draw.setFillColor(c_fill);
    
    panel.setTextColor(c_text);
    panel.setFillColor(c_fill);
    panel.setBackgroundColor(c_background);
    panel.setHeaderBackgroundColor(c_background);
    

}
void Grapher::saveCSV()
{
    ofFile csvfile;
    ofFileDialogResult result = ofSystemSaveDialog(name+"-"+ofGetTimestampString()+".csv", "Choose save directory");
    cout << result.getName() << endl;
    cout << result.getPath() << endl;

    csvfile.open(result.getPath(), ofFile::WriteOnly);

    int j = plotdata[0].size()-1;
    while( j >= 0 ){
        csvfile << ofToString(plotdata[0].size()-1-dx*j) << ",";
        for( int i = 0; i < plotdata.size(); i++ ){
            csvfile << ofToString(plotdata[i][j]) << ",";
        }
        csvfile << "\n";
        j--;
    }

}


void Grapher::setName(string _name)
{
    name = _name;
    if( xml_settings.loadFile(ofToDataPath("Grapher/"+name+".xml") )){
        cout << "load settings" << endl;
        r.x = xml_settings.getValue("settings:x",0);
        r.y = xml_settings.getValue("settings:y",0);
        r.width = xml_settings.getValue("settings:w",0);
        r.height = xml_settings.getValue("settings:h",0);
    }
}

int Grapher::getGrid(int _value, int _grid)
{
    int result;
    result = _grid*(_value/_grid);
    return result;
}
void Grapher::setPosition(float _x, float _y)
{
    r.x = _x;
    r.y = _y;
}

void Grapher::setSize(float _w, float _h)
{
    r.width = getGrid(_w, grid);
    r.height = _h;
}

void Grapher::setBufSize(int _bufsize)
{
    slider_bufsize = _bufsize;
}

void Grapher::setMaxLengthOfData(int &_max_length_of_data)
{
    max_length_of_data = _max_length_of_data;
}

void Grapher::setDx(float _dx)
{
    dx = _dx;
}

void Grapher::add(vector<float> _data)
{
    add(_data, OFXGRAPH_POINT_LABEL_NONE);
}

void Grapher::add(vector<float> _data, int _label)
{
    vector<float> max;
    vector<float> min;
    
    if( _data.size() > label.size() ){
        label.resize(_data.size());
    }
    
    
    if( !toggle_pause ){
        if( plotdata.size() < _data.size() ){
            plotdata.clear();
            plotdata.resize(_data.size());
            plotlabel.clear();
            plotlabel.resize(_data.size());
        }
        
        for( int i = 0; i < _data.size(); i++ ){
            plotdata[i].push_back(_data[i]);
            plotlabel[i].push_back(_label);
            while( plotdata[i].size() > max_length_of_data ){
                plotdata[i].erase(plotdata[i].begin());
                plotlabel[i].erase(plotlabel[i].begin());
            }
            max.push_back(*max_element(plotdata[i].begin(), plotdata[i].end()));
            min.push_back(*min_element(plotdata[i].begin(), plotdata[i].end()));
        }
        // Stops normalizing data.
        // max_data = *max_element(max.begin(), max.end());
        // min_data = *min_element(min.begin(), min.end());
    }
}

float Grapher::getY(float _x)
{
    return getY(_x, 0);
}
float Grapher::getY(float _x, int _number)
{
    if( plotdata.size() < _number ){
        return -1;
    }
    vector<float>v;
    for( int i = plotdata[0].size()-1; i >= 0; i--){
        v.push_back(plotdata[0][i]);
    }
    
    int index = _x/dx;
    return v[index];
    
}

ofPoint Grapher::getMaxPoint(float _x_left, float x_right)
{
    ofPoint p_result;
    int max = -10000;
    int pos;
    vector<float>v;
    for( int j = 0; j < plotdata.size(); j++ ){

        for( int i = plotdata[j].size()-1; i >= 0; i--){
            v.push_back(plotdata[j][i]);
        }
        
        for( float i = _x_left; i <= x_right; i = i + dx){
            int index = i/dx;
            if( v[index] > max ){
                max = v[index];
                pos = index;
            }
        }
    }
    p_result.set(pos*dx, max);
    return p_result;
}



void Grapher::add(float _data)
{
    add(_data, OFXGRAPH_POINT_LABEL_NONE);
}

void Grapher::add(float _data, int _label)
{
    vector<float>d;
    d.push_back(_data);
    add(d, _label);
}

void Grapher::clear()
{
    plotdata.clear();
    plotlabel.clear();
}

void Grapher::basicOperation(ofxPanel _panel)
{
        
    ofRectangle r_expand;
    r_expand.set(r.x+r.width-_panel.getWidth(),
               r.y+_panel.getHeight(),
               _panel.getWidth(),
               r.height-_panel.getHeight());
    ofRectangle r_gui;
    r_gui.set(r.x+r.width-_panel.getWidth(),
              r.y,
              _panel.getWidth(),
              _panel.getHeight());
    ofRectangle r_data;
    r_data.set(r.x, r.y,
               r.width-_panel.getWidth(),
               r.height);
    

    if( ofGetMousePressed() == true && r_data.inside(ofGetMouseX(), ofGetMouseY()) && !flg_mouse_dragged){
        flg_inside_pressed = true;
        flg_inside_r_data = true;
    }
    else if( ofGetMousePressed() == false ){
        flg_inside_pressed = false;
        flg_inside_r_data = false;
    }
    
    if( ofGetMousePressed() == true && r_expand.inside(ofGetMouseX(), ofGetMouseY()) && !flg_mouse_dragged){
        flg_inside_pressed = true;
        flg_inside_r_expand = true;
    }
    else if( ofGetMousePressed() == false ){
        flg_inside_pressed = false;
        flg_inside_r_expand = false;
    }
    
    // dragg operation
    if( flg_mouse_dragged && flg_inside_pressed == true){
        
        // Expand
        if( flg_inside_r_expand == true  ){
            r.width = r.width + ofGetMouseX()-dragged_start_point.x;
            r.height = r.height + ofGetMouseY()-dragged_start_point.y;
            if( r.height < min_height ){
                r.height = min_height;
            }
            if( r.width < min_width ){
                r.width = min_width;
            }

            
        }
        else if( flg_inside_r_gui == true ){
            
        }
        else if( flg_inside_r_data == true ){
            setPosition(r.x+ofGetMouseX()-dragged_start_point.x,
                        r.y+ofGetMouseY()-dragged_start_point.y);

        }
        dragged_start_point.set(ofGetMouseX(), ofGetMouseY());
    }

    
    
    
    if( flg_inside_r_data == true  ){
        ofSetColor(color[0]);
        img_move.draw(ofGetMouseX()-img_move.getWidth(),
                      ofGetMouseY()-img_move.getHeight());
    }
    if( flg_inside_r_expand == true ){
        ofSetColor(color[0]);
        img_expand.draw(ofGetMouseX()-img_expand.getWidth(),
                        ofGetMouseY()-img_expand.getHeight());
    }


    if( ofGetMousePressed() && flg_mouse_dragged == false ){
        flg_mouse_dragged = true;
        dragged_start_point.set(ofGetMouseX(), ofGetMouseY());
    }
    else if( !ofGetMousePressed() && flg_mouse_dragged == true ){
        flg_mouse_dragged = false;
        saveSettings();
    }

    
   
}

void Grapher::setLabel(vector<string>_label)
{
    label.clear();
    label = _label;
}
void Grapher::draw()
{

    ofNoFill();
    ofSetColor(color[0]);
    ofDrawRectangle(r);
    font_title.drawString(name, r.x, r.y);
    
    panel.setPosition(r.x+r.width-panel_size.x, r.y);
    float x = 0;
    float rate = 0.0;
    
    for( int j = 0; j < plotdata.size(); j++ ){
        if( plotdata[j].size() > 0 ){
            
            if( max_data > fabs(min_data) ){
                rate = max_data;
            }
            else{
                rate = min_data;
            }
            rate = fabs(rate);
            
            if( toggle_no_draw == false ){
                ofSetColor(color[j%10]);
                ofSetPolyMode(OF_POLY_WINDING_ODD);
                ofBeginShape();
                for( int i = plotdata[j].size()-1; i >= 0; i-- ){
                    ofVertex(r.x + x,
                             -0.8*(r.height/2)*(plotdata[j][i]/rate) + r.y + r.height/2);
                    x = x + r.width/(float)plotdata[j].size();
                    if( plotlabel[j][i] == OFXGRAPH_POINT_LABEL_MARKER ){
                        ofDrawCircle(r.x + x - 4,
                                     -0.8*(r.height/2)*(plotdata[j][i]/rate) + r.y + r.height/2 ,
                                     8);
                    }
                }

                ofEndShape();
            }
            
        }
        x = 0.0;
    }

    
    
    
    basicOperation(panel);
    
    // Show detail information
    if( r.inside(ofGetMouseX(), ofGetMouseY()) ){
        
        
        if( plotdata.size() > 0 && toggle_no_draw == false ){

            for( int j = 0; j < plotdata.size(); j++ ){
                ofSetColor(color[j%10]);
                float d = 1000.0;
                int pos = 0;
                int pos_x = 0;
                x = 0.0;
                for( int i = plotdata[j].size()-1; i >= 0; i-- ){
                    ofDrawCircle(r.x + x,
                                 -0.8*(r.height/2)*(plotdata[j][i]/rate) + r.y + r.height/2,
                                 2.0);
                    if( ofDist(ofGetMouseX(), ofGetMouseY(),
                               r.x+x,-0.8*(r.height/2)*(plotdata[j][i]/rate) + r.y + r.height/2) < d ){
                        pos = i;
                        d = ofDist(ofGetMouseX(), ofGetMouseY(),
                                   r.x+x,-0.8*(r.height/2)*(plotdata[j][i]/rate) + r.y + r.height/2);
                        pos_x = x;
                    }
                    x = x + r.width/(float)plotdata[j].size();
                }
                
                string str;
                
                // show nearest plot information
                ofDrawLine(ofGetMouseX()+10, ofGetMouseY()-12*j,
                           r.x+pos_x,-0.8*(r.height/2)*(plotdata[j][pos]/rate) + r.y + r.height/2);
                ofFill();
                ofSetColor(c_fill);
                str = label[j] + ":" +ofToString(dx*(plotdata[j].size()-pos-1))+", "+ofToString(plotdata[j][pos]);
                ofRectangle r_background = font_parameter.getStringBoundingBox(str, ofGetMouseX()+10, ofGetMouseY()-12*j);
                r_background.set(r_background.x, r_background.y, r_background.width, r_background.height);
                ofDrawRectangle(r_background);
                
                ofSetColor(color[j%10]);
                font_parameter.drawString(str, ofGetMouseX()+10, ofGetMouseY()-12*j);
                
                
                // max y
                str = ofToString(max_data);
                r_background.set(font_parameter.getStringBoundingBox(str, 0,0));
                r_background.setX(r.x+10);
                r_background.setY(r.y+r.height/2 - r_background.height/2 - 0.8*(r.height/2)*(max_data/rate));
                ofSetColor(c_fill);
                ofDrawRectangle(r_background);
                ofSetColor(color[0]);
                ofDrawLine(r_background.x-15, r_background.y+r_background.height/2,
                           r_background.x-5, r_background.y+r_background.height/2);
                font_parameter.drawString(str,
                                          r.x+10,
                                          r.y+r.height/2 + r_background.height/2 - 0.8*(r.height/2)*(max_data/rate));
                
                // min y
                str = ofToString(min_data);
                r_background.set(font_parameter.getStringBoundingBox(str, 0,0));
                r_background.setX(r.x+10);
                r_background.setY(r.y+r.height/2 - r_background.height/2 - 0.8*(r.height/2)*(min_data/rate));
                ofSetColor(c_fill);
                ofDrawRectangle(r_background);
                ofSetColor(color[0]);
                ofDrawLine(r_background.x-15, r_background.y+r_background.height/2,
                           r_background.x-5, r_background.y+r_background.height/2);
                font_parameter.drawString(str,
                                          r.x+10,
                                          r.y+r.height/2+font_parameter.getStringBoundingBox(str, 0, 0).height/2 - 0.8*(r.height/2)*(min_data/rate));
                
                
                // data size
                str = "data size["+ofToString(j)+"]: "+ ofToString(plotdata[j].size());
                ofSetColor(c_fill);
                ofDrawRectangle(font_parameter.getStringBoundingBox(
                                                                    str,
                                                                    r.x,
                                                                    r.y+r.height+j*12
                                                                    ));
                ofSetColor(color[0]);
                font_parameter.drawString(str,
                                          r.x,
                                          r.y+r.height+j*12);
            }
            
        }
        panel.draw();
        
    }
    
}



