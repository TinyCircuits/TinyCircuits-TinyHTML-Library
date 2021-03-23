#include "TinyHTMLPlaceholder.h"


TinyHTMLPlaceholder::TinyHTMLPlaceholder(int _ID, float _sizeW, float _sizeH, int _placeholderElementIndex){
  ID = _ID;
  sizeW = _sizeW;
  sizeH = _sizeH;
  placeholderElementIndex = _placeholderElementIndex;
}


void TinyHTMLPlaceholder::SendPlaceholderJSToClient(WiFiClient &_client){

}


void TinyHTMLPlaceholder::SendPlaceholderHTMLToClient(WiFiClient &_client){
  _client.print("<div style=width:");
  _client.print(sizeW);
  _client.print("vw;height:");
  _client.print(sizeH);
  _client.print("vh></div>");
}


void TinyHTMLPlaceholder::SendPlaceholderCSSToClient(WiFiClient &_client){
  
}
