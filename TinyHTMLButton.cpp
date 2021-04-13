#include "TinyHTMLButton.h"


TinyHTMLButton::TinyHTMLButton(int _ID, const char* _text, float _sizePercentage, float _fontSize, const char* _buttonColor, const char* _textColor, const char* _outlineColor, const char* _toggledColor, int _buttonElementIndex){
  ID = _ID;
  text = _text;
  sizePercentage = _sizePercentage;
  fontSize = _fontSize;
  buttonColor = _buttonColor;
  textColor = _textColor;
  outlineColor = _outlineColor;
  toggledColor = _toggledColor;
  buttonElementIndex = _buttonElementIndex;
}


void TinyHTMLButton::SendButtonJSToClient(WiFiClient &_client){
  if(buttonElementIndex == 0){
    _client.println("      class ButtonHandler{");
    _client.println("       constructor(button_id){");
    _client.println("         this.id = button_id;");
    _client.println("         let button = document.getElementById(button_id);");
    _client.println("         this.state = 0;");
    _client.println("         let self = this;");
    _client.println("         this.number_extra_cycles_after_polling = 4;");
    _client.println("         this.number_extra_cycles_after_polling_count = 0;");
    _client.println("         function toggleButton(event){");
    _client.println("           if(self.state == 0){");
    _client.println("             self.state = 1;");
    _client.println("           } else {");
    _client.println("             self.state = 0;");
    _client.println("           }");
    _client.println("           commandQueue.push(\"B[\" + button_id + \",\" + self.state + \"]\");");
    _client.println("         }");
    _client.println("          this.ConstantActivePoll = function(){");
    _client.println("           if(this.number_extra_cycles_after_polling_count <= this.number_extra_cycles_after_polling){");
    _client.println("             commandQueue.push(\"B[\" + button_id + \",\" + self.state + \"]\");");
    _client.println("             this.number_extra_cycles_after_polling_count++;");
    _client.println("           }");
    _client.println("           if(self.state == 1){");
    _client.println("             this.number_extra_cycles_after_polling_count = 0;");
    _client.println("           }");
    _client.println("          }");
    _client.println("         button.addEventListener(\"mousedown\", toggleButton);");
    _client.println("         button.addEventListener(\"touchstart\", toggleButton);");
    _client.println("         button.addEventListener(\"mouseup\", toggleButton);");
    _client.println("         button.addEventListener(\"touchend\", toggleButton);");
    _client.println("       }");
    _client.println("     }");
  }

  _client.print("button");
  _client.print(ID);
  _client.print(" = ");
  _client.print("new ButtonHandler(\"");
  _client.print(ID);
  _client.println("\");");

  _client.println("      window.setInterval(function(){");
  _client.print("button");
  _client.print(ID);
  _client.print(".ConstantActivePoll();");
  _client.println("}, (1000/POLLING_RATE));");
}


void TinyHTMLButton::SendButtonHTMLToClient(WiFiClient &_client){
  _client.print("<div class=container>");
  _client.print("<div style=width:");
  _client.print(sizePercentage);
  _client.print("%;");
  _client.print("height:0;margin:2.5%;");
  _client.print("padding-bottom:");
  _client.print(sizePercentage);
  _client.print("%>");
  _client.print("<button id=");
  _client.print(ID);
  _client.print(" class=button");
  _client.print(ID);
  _client.print(">");
  _client.print(text);
  _client.print("</button>");
  _client.println("</div>");
  _client.println("</div>");
}


void TinyHTMLButton::SendButtonCSSToClient(WiFiClient &_client){
  _client.print(".button");
  _client.print(ID);
  _client.println("{");
  _client.print("background-color: ");    // Background color
  _client.print(buttonColor);
  _client.println(";");
  _client.print("color: ");               // Text color
  _client.print(textColor);
  _client.println(";");
  _client.print("border: 0.65vw solid ");
  _client.print(outlineColor);           // Outline color
  _client.println(";");
  _client.println("-webkit-appearance: none;");
  _client.println("-moz-appearance: none;");
  _client.println("appearance: none;");
  _client.println("width: 100%;");
  _client.println("height: 100%;");
  _client.print("font-size: ");
  _client.print(fontSize);
  _client.println("vw;");
  _client.println("display: flex;");
  _client.println("justify-content: center;");
  _client.println("align-items: center;");
  _client.println("flex-direction: column;");
  _client.print("padding: 50%;");
  _client.println("}");

  _client.print(".button");
  _client.print(ID);
  _client.println(":active{");
  _client.print("background-color: ");    // Background color
  _client.print(toggledColor);
  _client.println(";");
  _client.println("}");
}
