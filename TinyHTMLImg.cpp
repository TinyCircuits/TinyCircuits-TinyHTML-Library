#include "TinyHTMLImg.h"

TinyHTMLImg::TinyHTMLImg(int _ID, char* _src, float _imageScale, bool _srcType, int _imgElementIndex){
  ID = _ID;
  src = _src;
  imageScale = _imageScale;
  srcType = _srcType;
  imgElementIndex = _imgElementIndex;
}


void TinyHTMLImg::SendImgJSToClient(WiFiClient &_client){
  
}


void TinyHTMLImg::SendImgHTMLToClient(WiFiClient &_client){
  _client.print("<div class=container>");
  if(srcType){
    _client.print("<img src=\"");
  }else{
    _client.print("<img src=\"data:image/png;base64, ");
  }
  _client.print(src);
  _client.print("\" alt=\"IMAGE LOADING ERROR\" width=\"");
  _client.print(imageScale);
  _client.print("%\" height=\"auto\">");
  _client.print("</div>");
}


void TinyHTMLImg::SendImgCSSToClient(WiFiClient &_client){
  
}
