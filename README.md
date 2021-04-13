# TinyCircuits TinyHTML Library

This library allows for creating simple webpages quickly with the ability to change the look or theme and can be used to control or interact with projects/robots.

This library aims to be low-latency in terms of reaction on the Arduino after interacting with the web page, which is ideal for robotics projects.

## Requirements
The [WiFi101](https://www.arduino.cc/en/Reference/WiFi101) Arduino library is needed in conjunction with any TinyCircuits processor board ([TinyZero](https://tinycircuits.com/products/tinyzero-processor), [RobotZero](https://tinycircuits.com/products/tinyzero-processor), etc) and the [Wi-Fi TinyShield](https://tinycircuits.com/products/wifi-tinyshield-atwinc1500). This library most likely works with typical Arduino boards, like the UNO, and Wi-Fi hardware that is compatible with the WiFi101 library, although it is untested.

## Example
The TinyCircuits-TinyHTML-Library.ino file is a ready to upload example and shows off the following features:
* Joystick
* Button
* Image
* Line break
* Horizontal slider
* Vertical slider
* Text
* Grid table
* Display value

In the example .ino file edit the ssid and Wi-Fi password, upload sketch to processor board, open the serial monitor, and then enter the IP displayed in the serial monitor in a web browser address bar. Ensure the Wi-Fi TinyShield is connected to the processor board. Resize browser window as needed to see more elements at a time.

## Features
The library provides the following functions for creating and organizing elements on a webpage
* ```TinyHTML(char* _pageTitle, int _JSPollingRate, int _commandBufferMaxSize)```
    - Starts the library
    - Parameters:
        - _pageTitle [string: any text, page title]
        - _JSPollingRate [int: how many times a second to attempt to send data to the server (Arduino) from elements (buttons, sliders, and joysticks)]
        - _commandBufferMaxSize [int: how many commands to send from client (web browser) to Arduino (server)]


* ```void SetPageBackgroundColor(char* _pageBackgroundColor)```
    - Sets the webpage background to a specific color
    - Parameters:
        - _pageBackgroundColor [string: color of entire page background, HTML #000000 format]


* ```int AddHeaderText(char* _text, char* _fontColor, char* _font, int _headerLevel, bool _underline)```
    - Adds HTML header element with any text
    - Parameters:
        - _text [string: any text]
        - _fontColor [string: color of text, HTML #000000 format]
        - _font [string: any text that names a standard HTML font family]
        - _headerLevel [int: HTML header level from 1 to 3, returns -1 if invalid level]
        - _underline [bool: passing true underlines the text]


* ```AddLineBreak(float _VWthickness, char* _lineColor)```
    - Adds a horizontal line break to the page
    - Parameters:
        - _VWthickness [float: how thick the line is in terms of viewport widths]
        - _lineColor [string: color of the line, HTML #000000 format]


* ```int AddJoystick(float _sizePercentage, float _joystickSizePercentage, char* _backgroundColor, char* _outlineColor, char* _joystickColor)```
    - Adds custom joystick element
    - Parameters:
        - _sizePercentage [float: how large the joystick outline/container should appear]
        - _joystickSizePercentage [float: how large the inner joystick handle should appear relative to container]
        - _backgroundColor [string: color behind joystick handle, HTML #000000 format]
        - _outlineColor [string: color of container outline, HTML #000000 format]
        - _joystickColor [string: color of joystick handle, HTML #000000 format]


* ```int AddHorizontalSlider(float _rangeMin, float _rangeMax, float _stepSize, float _widthPercentage, float _lengthPercentage, float _sliderVWSize, char* _backgroundColor, char* _outlineColor, char* _sliderHandleColor)```
    - Adds a standard horizontal HTML slider with custom CSS theming
    - Parameters:
        - _rangeMin [float: minimum value of the slider, positioned at the left of the slider]
        - _rangeMax [float: maximum value of the slider, positioned at the right of the slider]
        - _stepSize [float: how far the slider moves within the min and max range every time the user drags it]
        - _widthPercentage [float: thickness of the slider]
        - _lengthPercentage [float: width of the slider (horizontal length)]
        - _sliderVWSize [float: slider handle size in viewport widths]
        - _backgroundColor [string: color behind the slider handle]
        - _outlineColor [string: color of the slider outline]
        - _sliderHandleColor [string: color of the slider handle]


* ```int AddVerticalSlider(float _rangeMin, float _rangeMax, float _stepSize, float _widthPercentage, float _lengthPercentage, float _sliderVWSize, char* _backgroundColor, char* _outlineColor, char* _sliderHandleColor)```
    - Adds a standard vertical HTML slider with custom CSS theming
    - Parameters:
        - _rangeMin [float: minimum value of the slider, positioned at the left of the slider]
        - _rangeMax [float: maximum value of the slider, positioned at the right of the slider]
        - _stepSize [float: how far the slider moves within the min and max range every time the user drags it]
        - _widthPercentage [float: thickness of the slider]
        - _lengthPercentage [float: width of the slider (vertical length)]
        - _sliderVWSize [float: slider handle size in viewport widths]
        - _backgroundColor [string: color behind the slider handle]
        - _outlineColor [string: color of the slider outline]
        - _sliderHandleColor [string: color of the slider handle]


* ```int AddButton(char* _text, float _sizePercentage, float _fontSize, char* _buttonColor, char* _textColor, char* _outlineColor, char* _toggledColor)```
    - Adds square button with custom CSS theming
    - Parameters:
        - _text [string: the text that is displayed on the button]
        - _sizePercentage [float: size of the button relative the the page width]
        - _fontSize [float: the size of the font in viewport widths]
        - _buttonColor [string: color of button (text sits on top of this)]
        - _textColor [string: color of the text on the button]
        - _outlineColor [string: color of the button outline]
        _ _toggledColor [string: color of the button as it is being pressed by the user]
    

* ```int AddGridTable(int _rows, int _columns)```
    - Starts a table with defined number of rows and columns (fits _rows*_columns number of elements)
    - Parameters:
        - _rows [int: number of rows the table should have]
        - _columns [int: number of columns the table should have]


* ```int AddPlaceholder(float _sizeW, float _sizeH)```
    - Adds an empty placeholder element that can be used to fill spots in tables or create empty space
    - Parameters:
        - _sizeW [float: width of the empty space]
        - _sizeH [float: height of the empty space]


* ```int AddImage(char* _src, int _imageScale, bool _srcType)```
    - Adds an image from a URL or base64 encoded src (latter case uses more memory)
    - Parameters:
        - _src [string: source of the image, URL or encoded base64 image string]
        - _imageScale [float: the width of the image in percentage of page width to fill, height scales automatically]
        - _srcType [bool: pass 'true' if image from URL or pass 'false' if src is base64 encoded string]


* ```int AddCustom(char* _CSSContent, char* _HTMLContent, char* _JSContent)```
    - Provides ability to add custom CSS, HTML, and JavaScript to page. If adding custom JavaScript to send data to Arduino, need to add an identifier/commandType and catch it inside TinyHTML.cpp HandleClient() after sending the data with a commandQueue.push() in JS (see pre-built elements like TinyHTMLButton.cpp SendButtonJSToClient())
    - Parameters:
        - _CSSContent [string: custom CSS styling that gets added to page and is able to be used in custom HTML]
        - _HTMLContent [string: custom HTML that gets added to page and can be interacted with through custom JavaScript and styled with custom CSS]
        - _JSContent [string: custom JavaScript that gets added to the page and can interact with custom HTML]


* ```int AddValueDisplay(float _defaultValue, char* _font, char* _fontColor)```
    - Adds number element that displays a value sent from the Arduino (server)
    - Parameters:
        - _defaultValue [float: value to display when first added to page and no data has been received]
        - _font [string: any text that names an HTML font or font family]
        - _fontColor [string: color of value display font]


* ```int void SetValueDisplay(int _ID, float _currentValue)```
    - Sets the value of a value display to a custom value not sent by the Arduino (server)
    - Parameters: 
        - _ID [int: the ID of the display element to change]
        - _currentValue [float: the value to set the value display as]


* ```bool IsDirty()```
    - Returns true if any value in the library has changed, including value displays (following calls will return false until a value in the library changes)


* ```float GetJoystickX(int _ID)```
    - Returns the X value of a joystick when given the ID from the AddJoystick() function


* ```float GetJoystickY(int _ID)```
    - Returns the Y value of a joystick when given the ID from the AddJoystick() function


* ```float GetSliderValue(int _ID)```
    - Returns the value of a slider (vertical or horizontal) when given the ID from the AddSlider() function


* ```bool GetButtonState(int _ID)```
    - Returns if a button is pressed (true) or not (false) when given the ID from the AddButton() function


* ```void HandleClient(WiFiServer _web_server)```
    - Handles receiving and sending of data between the client (web browser) and server (Arduino). Should be called once per cycle/loop in the program


* Functions that start with "Add" return an int that is the ID of that element
* IDs can be stored and used in functions that start with "Get" to retrieve the value of the element as it is manipulated on the webpage
* The joystick element can be double clicked and then controlled using WASD on PC
* See TinyHTML.h for the default values used in the above functions

## Limitations
* Cannot remove elements during runtime
* Cannot change the look of elements during runtime
* Cannot add elements during runtime without the client (web browser) refreshing the page
* Cannot force/set the value of an element other than by manipulating the element manually (with touch, cursor, or keyboard)
* More than one client can load the page at a time but element visuals will not update/be shown on other client web browsers

## Tested web browsers
* Chrome on Windows Desktop
* Microsoft Edge on Windows Desktop
* Chrome on iPhone
* Safari on iPhone

## Help
* Leave an issue on this repository
* Contact us at info@tinycircuits.com