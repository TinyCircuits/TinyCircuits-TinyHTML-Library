#ifndef TINYHTML_
#define TINYHTML_

#include <WiFi101.h>
#include "TinyDynamicLinkedList.h"
#include "TinyHTMLJoystick.h"
#include "TinyHTMLSlider.h"
#include "TinyHTMLValueDisplay.h"
#include "TinyHetergeneousNode.h"

#define JOYSTICK_ELEMENT_ID 0
#define SLIDER_ELEMENT_ID 1
#define SENSOR_DISPLAY_ELEMENT_ID 2
#define CUSTOM_DIV_START_ELEMENT_ID 3
#define CUSTOM_DIV_END_ELEMENT_ID 4

// Builds .html file by sending JavaScript, CSS, and HTML
// formatting to the client browser line by line.
// The main idea is to simply call one function for adding each
// preconfigured/built/template for joysticks, buttons, sensor outputs,
// etc and then have a HTML/JavaScript/CSS infused page hosted on a webserver
// by the Arduino. This is mainly for a small subset of robotics projects
// and therefore custom HTML or styling is not favoured. There are options
// to quickly change the theme/color of the elements, or the source code
// can be edited


class TinyHTML {
public:
    TinyHTML(char* _pageTitle, int _JSPollingRate, int _commandBufferMaxSize);
    void SetPageBackgroundColor(char* _pageBackgroundColor="#000000");
    int AddHeaderText(char* _text ="TEST TEXT", char* _fontColor ="#cccccc", char* _font ="Arial", int _headerLevel =2, bool _underline =true);

    int AddValueDisplay(float _defaultValue, char* _font ="Arial", char* _fontColor ="#ffffff");
    void SetValueDisplay(int _ID, float _currentValue);
    
    int AddJoystick(float _sizePercentage =85, float _joystickSizePercentage =35, char* _backgroundColor ="#333333", char* _outlineColor ="#ffffff", char* _joystickColor ="#2fa9e1");
    float GetJoystickX(int _ID);
    float GetJoystickY(int _ID);
    
    int AddHorizontalSlider(float _rangeMin =-1, float _rangeMax =1, float _stepSize =0.1f, float _widthPercentage =8, float _lengthPercentage =85, float _sliderVWSize =7, char* _backgroundColor ="#333333", char* _outlineColor ="#ffffff", char* _sliderHandleColor ="#2fa9e1");
    int AddVerticalSlider(float _rangeMin =-1, float _rangeMax =1, float _stepSize =0.1f, float _widthPercentage =8, float _lengthPercentage =85, float _sliderVWSize =7, char* _backgroundColor ="#333333", char* _outlineColor ="#ffffff", char* _sliderHandleColor ="#2fa9e1"); // CSS styling needs tweaking
    float GetSliderValue(int _ID);
    
    int AddButton(char* _text ="TEST", float _sizePercentage =25, float _fontSize =4.5, char* _buttonColor ="#2fa9e1", char* _textColor ="#ffffff", char* _outlineColor ="#ffffff", char* _toggledColor ="#eb7a34");
    bool GetButtonState(int _ID);
    
    int AddGridTable(int _rows =2, int _columns =2);             // Elements added afterwards are placed row by row until table is full
    int AddPlaceholder(float _sizeW =0.0f, float _sizeH =0.0f);  // Used to fill areas/table cells on page with empty space

    bool IsDirty(); // Returns state of library and resets isDirty to false

    void SetDisplayPollRate(float _seconds);

    void HandleClient(WiFiServer _web_server);

private:
    char* pageTitle;
    int JSPollingRate;          // The number of times a second at which commands from the client are sent here, to the server
    int commandBufferMaxSize;   // The max number of commands that are sent every polling instance
    char* pageBackgroundColor;
    int joystickCount = 0;
    int headerTextCount = 0;
    int gridTableCount = 0;
    int sensorDisplayCount = 0;
    int sliderCount = 0;
    int buttonCount = 0;
    int placeholderCount = 0;
    int valueDisplayCount = 0;

    float displayPollRate = 2000;   // Number of miliseconds between client asking for display information

    int lastID = 0;                 // ID returned by each element add function
    bool isDirty = false;           // Set true when any data received from client web browser

    void SetJoystickXY(int _ID, float _x, float _y);
    void SetSliderValue(int _ID, float _value);
    void SetButtonState(int _ID, bool _state);

    void SendAllDisplayValuesToClient();

    void SetClient(WiFiClient _client);
    void SendAllContentToClient();

    WiFiClient client;
    TinyLinkedList hierarchyList;
};

#endif /* TINYHTML_ */
