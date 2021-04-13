#ifndef TINYHTMLHEADERTEXT_H
#define TINYHTMLHEADERTEXT_H

#include <WiFi101.h>

class TinyHTMLHeaderText{
public:
  TinyHTMLHeaderText(int _ID, const char* _text, const char* _fontColor, const char* _font, int _headerLevel, bool _underline, int _headerTextElementIndex);
  void SendHeaderTextJSToClient(WiFiClient &_client);
  void SendHeaderTextHTMLToClient(WiFiClient &_client);
private:
  int ID;
  const char* text;
  const char* fontColor;
  const char* font;
  int headerLevel;
  bool underline;
  int headerTextElementIndex;
};

#endif /* TINYHTMLHEADERTEXT_H */
