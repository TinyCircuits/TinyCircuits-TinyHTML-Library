#ifndef TINYHTMLCUSTOM_H
#define TINYHTMLCUSTOM_H

#if defined(ARDUINO_ESP32S2_DEV)
  #include <WiFi.h>    // For connecting to WiFi on ESP32 devices
#else
  #include <WiFi101.h>    // For connecting to WiFi on typical Arduino devices
#endif

class TinyHTMLCustom{
public:
  TinyHTMLCustom(int _ID, const char* _CSSContent, const char* _HTMLContent, const char* _JSContent, int _customElementIndex);
  void SendCustomJSToClient(WiFiClient &_client);
  void SendCustomHTMLToClient(WiFiClient &_client);
  void SendCustomCSSToClient(WiFiClient &_client);
private:
  int ID;
  const char* CSSContent;
  const char* HTMLContent;
  const char* JSContent;
  int customElementIndex;
};

#endif /* TINYHTMLCUSTOM_H */
