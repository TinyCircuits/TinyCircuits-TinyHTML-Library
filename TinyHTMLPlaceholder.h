#ifndef TINYHTMLPLACEHOLDER_H
#define TINYHTMLPLACEHOLDER_H

#include <WiFi101.h>

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
