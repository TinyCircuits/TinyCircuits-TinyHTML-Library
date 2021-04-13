#ifndef TINYHTMLLINEBREAK_H
#define TINYHTMLLINEBREAK_H

#include <WiFi101.h>

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
