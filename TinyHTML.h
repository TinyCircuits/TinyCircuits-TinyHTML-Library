#ifndef TINYHTML_H
#define TINYHTML_H

#if defined(ARDUINO_ESP32S2_DEV)
  #include <WiFi.h>    // For connecting to WiFi on ESP32 devices
#else
  #include <WiFi101.h>    // For connecting to WiFi on typical Arduino devices
#endif

#include "TinyDynamicLinkedList.h"
#include "TinyHTMLJoystick.h"
#include "TinyHTMLSlider.h"
#include "TinyHTMLValueDisplay.h"
#include "TinyHetergeneousNode.h"


// Builds .html file by sending JavaScript, CSS, and HTML
// formatting to the client browser line by line.
// The main idea is to simply call one function for adding each
// preconfigured/built/template for joysticks, buttons, sensor outputs,
// etc and then have a HTML/JavaScript/CSS infused page hosted on a webserver
// by the Arduino. This is mainly for a small subset of robotics projects
// and therefore custom HTML or styling is not favoured. There are options
// to quickly change the theme/color of the elements, otherwise, the source code
// can be edited


class TinyHTML {
public:
    TinyHTML(const char* _pageTitle, int _JSPollingRate, int _commandBufferMaxSize);
    void SetPageBackgroundColor(const char* _pageBackgroundColor="#000000");
    int AddHeaderText(const char* _text ="TEST TEXT", const char* _fontColor ="#cccccc", const char* _font ="Arial", int _headerLevel =2, bool _underline =true);

    int AddLineBreak(float _VWthickness =0.5f, const char* _lineColor ="#cccccc");

    int AddValueDisplay(float _defaultValue =2000, const char* _font ="Arial", const char* _fontColor ="#cccccc");
    void SetValueDisplay(int _ID, float _currentValue);
    
    int AddJoystick(float _sizePercentage =85, float _joystickSizePercentage =35, const char* _backgroundColor ="#333333", const char* _outlineColor ="#cccccc", const char* _joystickColor ="#2fa9e1");
    float GetJoystickX(int _ID);
    float GetJoystickY(int _ID);
    
    int AddHorizontalSlider(float _rangeMin =-1, float _rangeMax =1, float _stepSize =0.1f, float _widthPercentage =8, float _lengthPercentage =85, float _sliderVWSize =7, const char* _backgroundColor ="#333333", const char* _outlineColor ="#cccccc", const char* _sliderHandleColor ="#2fa9e1", bool _showValue =true, int _vwFontSize =10);
    int AddVerticalSlider(float _rangeMin =-1, float _rangeMax =1, float _stepSize =0.1f, float _widthPercentage =8, float _lengthPercentage =85, float _sliderVWSize =7, const char* _backgroundColor ="#333333", const char* _outlineColor ="#cccccc", const char* _sliderHandleColor ="#2fa9e1", bool _showValue =true, int _vwFontSize =10); // CSS styling needs tweaking
    float GetSliderValue(int _ID);
    
    int AddButton(const char* _text ="TEST", float _sizePercentage =25, float _fontSize =4.5, const char* _buttonColor ="#2fa9e1", const char* _textColor ="#cccccc", const char* _outlineColor ="#cccccc", const char* _toggledColor ="#eb7a34");
    bool GetButtonState(int _ID);
    
    int AddGridTable(int _rows =2, int _columns =2);             // Elements added afterwards are placed row by row until table is full
    int AddPlaceholder(float _sizeW =0.0f, float _sizeH =0.0f);  // Used to fill areas/table cells on page with empty space

    int AddImage(const char* _src ="https://cdn.shopify.com/s/files/1/1125/2198/files/TC_tinycircuits_logo_c0d46ca4-da2c-4e81-a88d-6780fae6b443_170x.png?v=1569438547", float _imageScale =50.0f, bool _srcType =true); // true for URL, false for base64 encoded

    int AddCustom(const char* _CSSContent ="", const char* _HTMLContent ="", const char* _JSContent ="");
    bool IsDirty(); // Returns state of library (returns true after any any element state has changed) and resets to returning false after being called

    void SetDisplayPollRate(float _seconds);

    void HandleClient();
    void StartPage();

private:
    const char* pageTitle;
    int JSPollingRate;          // The number of times a second at which commands from the client are sent here, to the server
    int commandBufferMaxSize;   // The max number of commands that are sent every polling instance
    const char* pageBackgroundColor = "#000000";
    int joystickCount = 0;
    int headerTextCount = 0;
    int gridTableCount = 0;
    int sensorDisplayCount = 0;
    int sliderCount = 0;
    int buttonCount = 0;
    int placeholderCount = 0;
    int valueDisplayCount = 0;
    int lineBreakCount = 0;
    int imgCount = 0;
    int customCount = 0;

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
    WiFiServer webServer;
    TinyLinkedList hierarchyList;
};

#endif /* TINYHTML_H */
