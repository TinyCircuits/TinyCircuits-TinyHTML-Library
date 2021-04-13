#ifndef TINYHTMLIMG_H
#define TINYHTMLIMG_H

#if defined(ARDUINO_ESP32S2_DEV)
  #include <WiFi.h>    // For connecting to WiFi on ESP32 devices
#else
  #include <WiFi101.h>    // For connecting to WiFi on typical Arduino devices
#endif

class TinyHTMLImg{
public:
  TinyHTMLImg(int _ID, const char* _src, float _imageScale, bool _srcType, int _imgElementIndex);
  void SendImgJSToClient(WiFiClient &_client);
  void SendImgHTMLToClient(WiFiClient &_client);
  void SendImgCSSToClient(WiFiClient &_client);
private:
  int ID;
  const char* src;
  float imageScale;
  bool srcType; // true for URL, false for encoded base 64
  int imgElementIndex;
};

#endif /* TINYHTMLIMG_H */
