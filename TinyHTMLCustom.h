#ifndef TINYHTMLCUSTOM_H
#define TINYHTMLCUSTOM_H

#include <WiFi101.h>

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
