#include "TinyHTMLValueDisplay.h"


TinyHTMLValueDisplay::TinyHTMLValueDisplay(int _ID, float _defaultValue, const char* _font, const char* _fontColor, int _valueDisplayElementIndex){
  ID = _ID;
  defaultValue = _defaultValue;
  font = _font;
  fontColor = _fontColor;
  valueDisplayElementIndex = _valueDisplayElementIndex;
}


void TinyHTMLValueDisplay::SendValueDisplayJSToClient(WiFiClient &_client){

}


void TinyHTMLValueDisplay::SendValueDisplayHTMLToClient(WiFiClient &_client){
  _client.println("<div class=\"container\">");
  _client.print("<output id=");
  _client.print(ID);
  _client.print(" style=font-family:");
  _client.print(font);
  _client.print(";color:");
  _client.print(fontColor);
  _client.print(">");
  _client.print(defaultValue);
  _client.println("</output>");
  _client.println("</div>");
}


void TinyHTMLValueDisplay::SetCurrentValue(float _currentValue){
  currentValue = _currentValue;
  isDirty = true;
}


float TinyHTMLValueDisplay::GetCurrentValue(){
  return currentValue;
  isDirty = false;
}


void TinyHTMLValueDisplay::SendValueToClient(WiFiClient &_client){
  if(isDirty){
    _client.println(ID);
    _client.println(GetCurrentValue());
  }
}
