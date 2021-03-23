#ifndef TINYHTMLHEADERTEXT_H
#define TINYHTMLHEADERTEXT_H

#include <WiFi101.h>

class TinyHTMLHeaderText{
public:
  TinyHTMLHeaderText(int _ID, char* _text, char* _fontColor, char* _font, int _headerLevel, bool _underline, int _headerTextElementIndex);
  void SendHeaderTextJSToClient(WiFiClient &_client);
  void SendHeaderTextHTMLToClient(WiFiClient &_client);
private:
  int ID;
  char* text;
  char* fontColor;
  char* font;
  int headerLevel;
  bool underline;
  int headerTextElementIndex;
};

#endif /* TINYHTMLHEADERTEXT_H */
