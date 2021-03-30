# TinyCircuits TinyHTML Library

This library allows for creating simple webpages quickly with the ability to change the look or theme that can be used to control or interact with projects/robots.

The WiFi101 Arduino library is needed in conjunction with any TinyCircuits processor board (TinyZero, etc) and the WiFi TinyShield.

## Example
The TinyCircuits-TinyHTML-Library.ino file is a ready to upload example and shows off the following features:
* Joystick
* Button
* Horozontial slider
* Vertical slider
* Text
* Grid table
* Display value

In the example .ino file edit the ssid and wifi_password, upload sketch to processor board, open the serial monitor, and then enter the IP displayed in the serial monitor in a web browser address bar. Ensure the WiFi TinyShield is connected to the processor board. Resize browser window as needed to see more elements at a time.

## Features
The library provides the following functions for creating and organizing elements on a webpage
* TinyHTML(char* _pageTitle, int _JSPollingRate, int _commandBufferMaxSize)
* void SetPageBackgroundColor(char* _pageBackgroundColor)
* int AddHeaderText(char* _text, char* _fontColor, char* _font, int _headerLevel, bool _underline)
* int AddJoystick(float _sizePercentage, float _joystickSizePercentage, char* _backgroundColor, char* _outlineColor, char* _joystickColor)
* int AddHorizontalSlider(float _rangeMin, float _rangeMax, float _stepSize, float _widthPercentage, float _lengthPercentage, float _sliderVWSize, char* _backgroundColor, char* _outlineColor, char* _sliderHandleColor)
* int AddVerticalSlider(float _rangeMin, float _rangeMax, float _stepSize, float _widthPercentage, float _lengthPercentage, float _sliderVWSize, char* _backgroundColor, char* _outlineColor, char* _sliderHandleColor)
* int AddButton(char* _text, float _sizePercentage, float _fontSize, char* _buttonColor, char* _textColor, char* _outlineColor, char* _toggledColor)
* int AddGridTable(int _rows, int _columns)
* int AddPlaceholder(float _sizeW, float _sizeH)
* int AddValueDisplay(float _defaultValue, char* _font, char* _fontColor)
* int void SetValueDisplay(int _ID, float _currentValue)
* bool IsDirty()
* float GetJoystickX(int _ID)
* float GetJoystickY(int _ID)
* float GetSliderValue(int _ID)
* bool GetButtonState(int _ID)
* void HandleClient(WiFiServer _web_server)

* Functions that start with "Add" return an int that is the ID of that element
* IDs can be stored and used in functions that start with "Get" to retrieve the value of the element as it is manipulated on the webpage
* The joystick element can be double clicked and then controlled using WASD on PC
* See TinyHTML.h for the default values used in the above functions

## Limitations
* Cannot remove elements during runtime
* Cannot change the look of elements during runtime
* Cannot add elements during runtime without the client (web broswer) refreashing the page
* Cannot force/set the value of an element other than by manipulating the element manually (with touch, cursor, or keyboard)
* More than one client can load the page at a time but element visuals will not update/be shown on other client web browsers
* Server (Arduino hosting the webpage) cannot send data to the client to be displayed (such as sensor data) but this is a planned feature

## Tested web browsers
* Chrome on Windows Desktop
* Microsoft Edge on Desktop
* Chrome on iPhone
* Safari on iPhone

## Help
* Leave an issue on this repository
* Contact us at info@tinycircuits.com