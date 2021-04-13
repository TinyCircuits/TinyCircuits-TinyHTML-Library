#include "TinyHTMLCustom.h"

TinyHTMLCustom::TinyHTMLCustom(int _ID, const char* _CSSContent, const char* _HTMLContent, const char* _JSContent, int _customElementIndex){
  ID = _ID;
  CSSContent = _CSSContent;
  HTMLContent = _HTMLContent;
  JSContent = _JSContent;
  customElementIndex = _customElementIndex;
}


void TinyHTMLCustom::SendCustomJSToClient(WiFiClient &_client){
  _client.print(JSContent);
}


void TinyHTMLCustom::SendCustomHTMLToClient(WiFiClient &_client){
  _client.print("<div class=container>");
  _client.print(HTMLContent);
  _client.print("</div>");
}


void TinyHTMLCustom::SendCustomCSSToClient(WiFiClient &_client){
  _client.print(CSSContent);
}
