#ifndef TINYHTMLBUTTON_H
#define TINYHTMLBUTTON_H

#if defined(ARDUINO_ESP32S2_DEV)
  #include <WiFi.h>    // For connecting to WiFi on ESP32 devices
#else
  #include <WiFi101.h>    // For connecting to WiFi on typical Arduino devices
#endif

class TinyHTMLButton{
public:
  TinyHTMLButton(int _ID, const char* _text, float _sizePercentage, float _fontSize, const char* _buttonColor, const char* _textColor, const char* _outlineColor, const char* _toggledColor, int _buttonElementIndex);
  void SendButtonJSToClient(WiFiClient &_client);
  void SendButtonHTMLToClient(WiFiClient &_client);
  void SendButtonCSSToClient(WiFiClient &_client);
  bool state;  // The value of the button, sent from the client
private:
  int ID;
  const char* text;
  float sizePercentage;
  float fontSize;
  const char* buttonColor;
  const char* textColor;
  const char* outlineColor;
  const char* toggledColor;
  int buttonElementIndex;
};

#endif /* TINYHTMLBUTTON_H */
