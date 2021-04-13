#ifndef TINYHTMLCUSTOM_H
#define TINYHTMLCUSTOM_H

#include <WiFi101.h>

class TinyHTMLCustom{
public:
  TinyHTMLCustom(int _ID, char* _CSSContent, char* _HTMLContent, char* _JSContent, int _customElementIndex);
  void SendCustomJSToClient(WiFiClient &_client);
  void SendCustomHTMLToClient(WiFiClient &_client);
  void SendCustomCSSToClient(WiFiClient &_client);
private:
  int ID;
  char* CSSContent;
  char* HTMLContent;
  char* JSContent;
  int customElementIndex;
};

#endif /* TINYHTMLCUSTOM_H */
