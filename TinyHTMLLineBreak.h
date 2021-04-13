#ifndef TINYHTMLLINEBREAK_H
#define TINYHTMLLINEBREAK_H

#if defined(ARDUINO_ESP32S2_DEV)
  #include <WiFi.h>    // For connecting to WiFi on ESP32 devices
#else
  #include <WiFi101.h>    // For connecting to WiFi on typical Arduino devices
#endif

class TinyHTMLLineBreak{
public:
  TinyHTMLLineBreak(int _ID, float _VWthickness, const char* _lineColor, int _lineBreakElementIndex);
  void SendLineBreakHTMLToClient(WiFiClient &_client);
private:
  int ID;
  float VWthickness;
  const char* lineColor;
  int lineBreakElementIndex;
};

#endif /* TINYHTMLLINEBREAK_H */
