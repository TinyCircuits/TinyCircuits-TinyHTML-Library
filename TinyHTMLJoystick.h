#ifndef TINYHTMLJOYSTICK_H
#define TINYHTMLJOYSTICK_H

#include <WiFi101.h>

class TinyHTMLJoystick{
public:
  TinyHTMLJoystick(int _ID, float _sizePercentage, float _joystickSizePercentage, const char* _backgroundColor, const char* _outlineColor, const char* _joystickColor, int _joystickElementIndex);
  void SendJoystickJSToClient(WiFiClient &_client);
  void SendJoystickHTMLToClient(WiFiClient &_client);

  float xPercent; // The joystick x-axis in % received from client
  float yPercent; // The joystick y-axis in % received from client
private:
  int ID;
  float sizePercentage;
  float joystickSizePercentage;
  const char* backgroundColor;
  const char* outlineColor;
  const char* joystickColor;
  int joystickElementIndex;
};

#endif /* TINYHTMLJOYSTICK_H */
