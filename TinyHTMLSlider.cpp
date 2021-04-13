#include "TinyHTMLSLider.h"

TinyHTMLSlider::TinyHTMLSlider(int _ID, float _rangeMin, float _rangeMax, float _stepSize, bool _horoORvert, float _widthPercentage, float _lengthPercentage, float _sliderVWSize, char* _backgroundColor, char* _outlineColor, char* _sliderHandleColor, bool _showValue, int _vwFontSize, int _sliderElementIndex){
  ID = _ID;
  rangeMin = _rangeMin;
  rangeMax = _rangeMax;
  stepSize = _stepSize;
  horoORvert = _horoORvert;
  widthPercentage = _widthPercentage;
  lengthPercentage = _lengthPercentage;
  sliderVWSize = _sliderVWSize;
  backgroundColor = _backgroundColor;
  outlineColor = _outlineColor;
  sliderHandleColor = _sliderHandleColor;
  sliderElementIndex = _sliderElementIndex;
  showValue = _showValue;
  vwFontSize = _vwFontSize;
}


void TinyHTMLSlider::SendSliderJSToClient(WiFiClient &_client){
  if(sliderElementIndex == 0){
    _client.println("      class SliderHandler{");
    _client.println("       constructor(slider_id){");
    _client.println("       let ID = slider_id;");
    _client.println("       let slider = document.getElementById(slider_id);");
    _client.println("       let current_value = 0;");
    _client.println("       let sent_count = 0;");
    _client.println("       let interval_var = -1;");
    _client.println("       let self = this;");
    _client.println("       function send(){");
    _client.println("         commandQueue.push(\"A[\" + slider_id + \",\" + current_value + \"]\");");
    _client.println("         current_value = slider.value;");
    _client.println("         sent_count++;");
    _client.println("         if(sent_count >= 5){");
    _client.println("           sent_count = 0;");
    _client.println("           clearInterval(interval_var);");
    _client.println("         }");
    _client.println("       }");
    _client.println("       function handleSliderMove(event){");
    _client.println("         if(sent_count == 0){");
    _client.println("           clearInterval(interval_var);");
    _client.println("           interval_var = setInterval(send, (1000/POLLING_RATE)/2);");
    _client.println("         }");
    _client.println("       }");
    _client.println("       slider.addEventListener('input', handleSliderMove);");
    _client.println("       }");
    _client.println("     }");

    _client.println("function UpdateSliderOutput(sliderID, value){");
    _client.println(" sliderOutputElement = document.getElementById(sliderID.toString() + \"B\");");
    _client.println(" sliderOutputElement.value = value;");
    _client.println("}");
  }

  _client.print("slider");
  _client.print(ID);
  _client.print(" = new SliderHandler(\"");
  _client.print(ID);
  _client.println("\");");  
}


void TinyHTMLSlider::SendSliderHTMLToClient(WiFiClient &_client){
  _client.print("<div>");
  if(!horoORvert){
    _client.print("<div class=rotation-wrapper-outer>");
    _client.print("<div class=rotation-wrapper-inner>");
  }
  _client.print("<div class=container>");
  _client.print("<input id=");                        // Start input HTMl tag and id
  _client.print(ID);                                  // Insert ID generated by library
  _client.print(" type=\"range\"");                   // Define that this input is a slider/range
  _client.print("min=\"");                            // Start defining the min of the slider range
  _client.print(rangeMin);                            // Insert user defined min range for slider
  _client.print("\" max=\"");                         // Start defining the max of the slider range
  _client.print(rangeMax);                            // Insert user defined max range for slider
  _client.print("\" step=\"");                        // Start defining the step size of the silder
  _client.print(stepSize);                            // Insert user defined step size for the slider
  _client.print("\" value=\"");                       // Start defining the default/starting value of the slider
  _client.print(abs(abs(rangeMax)-abs(rangeMin))/2);  // Insert the default value at middle of the min and max
  _client.print("\" class=\"slider_common");
  _client.print(" slider_unique");
  _client.print(ID);
  _client.print(" slider_webkit_unique");
  _client.print(ID);
  _client.print(" slider_moz_unique");
  _client.print(ID);
  _client.print("\"");
  if(showValue){
    _client.print(" oninput=\"UpdateSliderOutput(this.id, this.value)\"");
  }
  _client.print("></div>");
  
  if(!horoORvert){
    _client.print("</div>");
    _client.print("</div>");
  }

  if(showValue){
    _client.print("<center><output id=");
    _client.print(ID);
    _client.print("B class=");
    _client.print("slider_output_unique");
    _client.print(ID);
    _client.print(">");
    _client.print(abs(abs(rangeMax)-abs(rangeMin))/2);
    _client.println("</output>");
    _client.print("</div></center>");
  }
}


void TinyHTMLSlider::SendSliderCSSToClient(WiFiClient &_client){
  if(sliderElementIndex == 0){  // Only send common CSS styling once
    _client.println(".slider_common{");
    _client.println(" -webkit-appearance: none;");
    _client.println(" -moz-appearance: none;");
    _client.println(" appearance: none;");
    _client.println(" touch-action: manipulation;");
    _client.println(" outline: none;");
    _client.println(" display: block;");
    _client.println(" margin: 1%;");
    _client.println("}");
  }

  _client.print(".slider_unique");
  _client.print(ID);
  _client.println("{");
  _client.print(" background-color: ");
  _client.print(backgroundColor);
  _client.print(";border-style:solid;");
  _client.print(";border-width:0.65vw;");
  _client.print(";border-color:");
  _client.print(outlineColor);
  _client.println(";");
  _client.print(" width: ");
  _client.print(lengthPercentage);
  _client.println("%;");
  _client.print(" height: ");
  _client.print(widthPercentage);
  _client.println("vw;");
  if(!horoORvert){  // Vertical 
    _client.print(" transform: rotate(-90deg);");
    _client.println("-moz-transform: rotate(-90deg);");
    _client.print(" white-space: nowrap;");
    _client.print(" display: block;");
  }
  _client.println("}");

  _client.print(".slider_unique");
  _client.print(ID);
  _client.println("::-webkit-slider-thumb{");
  _client.println(" -webkit-appearance: none;");
  _client.println(" -moz-appearance: none;");
  _client.println(" appearance: none;");
  _client.println(" cursor: pointer;");
  _client.print(" background-color: ");
  _client.print(sliderHandleColor);
  _client.println(";");
  _client.print(" height: ");
  _client.print(sliderVWSize);
  _client.println("vw;");
  _client.print(" width: ");
  _client.print(sliderVWSize);
  _client.println("vw;");
  _client.println("}");

  _client.print(".slider_unique");
  _client.print(ID);
  _client.println("::-moz-range-thumb{");
  _client.println(" -webkit-appearance: none;");
  _client.println(" -moz-appearance: none;");
  _client.println(" appearance: none;");
  _client.println(" cursor: pointer;");
  _client.print(" background-color: ");
  _client.print(sliderHandleColor);
  _client.println(";");
  _client.print(" height: ");
  _client.print(sliderVWSize);
  _client.println("vw;");
  _client.print(" width: ");
  _client.print(sliderVWSize);
  _client.println("vw;");
  _client.println("}");

  _client.print(".slider_output_unique");
  _client.print(ID);
  _client.println("{");
  _client.println("color: white;");
  _client.println("position: relative;");
  _client.println("font-size:");
  _client.println("}");
}
