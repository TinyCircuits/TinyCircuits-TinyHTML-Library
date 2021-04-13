#ifndef TINYHTMLSENSORDISPLAY_H
#define TINYHTMLSENSORDISPLAY_H

#include <WiFi101.h>

class TinyHTMLValueDisplay{
public:
  TinyHTMLValueDisplay(int _ID, float _defaultValue, const char* _font, const char* _fontColor, int _valueDisplayElementIndex);
  void SendValueDisplayJSToClient(WiFiClient &_client);
  void SendValueDisplayHTMLToClient(WiFiClient &_client);
  void SetCurrentValue(float _currentValue);
  float GetCurrentValue();
  void SendValueToClient(WiFiClient &_client);
private:
  int ID;
  float defaultValue;
  const char* font;
  const char* fontColor;
  int valueDisplayElementIndex;

  float currentValue;  // The value of the display as set by user
  bool isDirty = false;
};

#endif /* TINYHTMLSENSORDISPLAY_H */
