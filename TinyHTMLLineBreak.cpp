#include "TinyHTMLLineBreak.h"


TinyHTMLLineBreak::TinyHTMLLineBreak(int _ID, float _VWthickness, char* _lineColor, int _lineBreakElementIndex){
  ID = _ID;
  VWthickness = _VWthickness;
  lineColor = _lineColor;
  lineBreakElementIndex = _lineBreakElementIndex;
}


void TinyHTMLLineBreak::SendLineBreakHTMLToClient(WiFiClient &_client){
  _client.print("<hr style=border-style:solid;border-width:");
  _client.print(VWthickness);
  _client.print("vw;border-color:");
  _client.print(lineColor);
  _client.print(";background-color:");
  _client.print(lineColor);
  _client.print(">");
}
