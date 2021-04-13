#ifndef TINYHTMLIMG_H
#define TINYHTMLIMG_H

#include <WiFi101.h>

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
