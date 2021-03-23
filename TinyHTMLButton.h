#ifndef TINYHTMLBUTTON_H
#define TINYHTMLBUTTON_H

#include <WiFi101.h>

class TinyHTMLButton{
public:
  TinyHTMLButton(int _ID, char* _text, float _sizePercentage, float _fontSize, char* _buttonColor, char* _textColor, char* _outlineColor, char* _toggledColor, int _buttonElementIndex);
  void SendButtonJSToClient(WiFiClient &_client);
  void SendButtonHTMLToClient(WiFiClient &_client);
  void SendButtonCSSToClient(WiFiClient &_client);
  bool state;  // The value of the button, sent from the client
private:
  int ID;
  char* text;
  float sizePercentage;
  float fontSize;
  char* buttonColor;
  char* textColor;
  char* outlineColor;
  char* toggledColor;
  int buttonElementIndex;
};

#endif /* TINYHTMLBUTTON_H */
