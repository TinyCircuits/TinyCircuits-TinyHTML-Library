#ifndef TINYHTMLPLACEHOLDER_H
#define TINYHTMLPLACEHOLDER_H

#if defined(ARDUINO_ESP32S2_DEV)
  #include <WiFi.h>    // For connecting to WiFi on ESP32 devices
#else
  #include <WiFi101.h>    // For connecting to WiFi on typical Arduino devices
#endif

class TinyHTMLPlaceholder{
public:
  TinyHTMLPlaceholder(int _ID, float _sizeW, float _sizeH, int _placeholderElementIndex);
  void SendPlaceholderJSToClient(WiFiClient &_client);
  void SendPlaceholderHTMLToClient(WiFiClient &_client);
  void SendPlaceholderCSSToClient(WiFiClient &_client);
private:
  int ID;
  float sizeW;
  float sizeH;
  int placeholderElementIndex;
};

#endif /* TINYHTMLPLACEHOLDER_H */
