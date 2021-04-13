#include "TinyHTMLHeaderText.h"


TinyHTMLHeaderText::TinyHTMLHeaderText(int _ID, const char* _text, const char* _fontColor, const char* _font, int _headerLevel, bool _underline, int _headerTextElementIndex){
  ID = _ID;
  text = _text;
  fontColor = _fontColor;
  font = _font;
  headerLevel = _headerLevel;
  underline = _underline;
  headerTextElementIndex = _headerTextElementIndex;
}


void TinyHTMLHeaderText::SendHeaderTextJSToClient(WiFiClient &_client){
  
}


void TinyHTMLHeaderText::SendHeaderTextHTMLToClient(WiFiClient &_client){
  // Output example: <center><h1 id="0" style="font-family:Arial;text-decoration:underline;text-underline-position:under;color:#FFFFFF">HEADER TEXT</h1></center>

  _client.print("<center>");              // Insert starting center tag user defined it as true
  _client.print("<h");                    // Start HTML header tag
  _client.print(headerLevel);             // Insert header user defined header level (1~3)
  _client.print(" id=");                  // Start element ID
  _client.print(ID);                      // Insert user defined element ID
  _client.print(" style=font-family:");   // Start HTML in-line CSS style and custom font
  _client.print(font);                    // Insert user defined header font
  if(underline){                          // Insert styling for underline if user defined underline parameter as true
    _client.print(";text-decoration:underline;text-underline-position:under");
  }
  _client.print(";color:");               // Start font color
  _client.print(fontColor);               // Insert user defined font color
  _client.print(";font-size:5vw");        // Font size 
  _client.print(">");                     // End HTML in-line CSS styling
  _client.print(text);                    // Insert header text
  _client.print("</h");                   // Start end of header element/end header tag
  _client.print(headerLevel);             // Insert header user defined header level (1~3)
  _client.println(">");                   // Finish header element and tag
  _client.print("</center>");             // Insert ending center tag user defined it as true
}
