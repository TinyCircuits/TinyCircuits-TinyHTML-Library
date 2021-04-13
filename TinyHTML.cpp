#include "TinyHTML.h"


TinyHTML::TinyHTML(char* _pageTitle, int _JSPollingRate, int _commandBufferMaxSize){
  pageTitle = _pageTitle;
  JSPollingRate = _JSPollingRate;
  commandBufferMaxSize = _commandBufferMaxSize;
}


void TinyHTML::SetPageBackgroundColor(char* _pageBackgroundColor){
  pageBackgroundColor = _pageBackgroundColor;
}


int TinyHTML::AddHeaderText(char* _text, char* _fontColor, char* _font, int _headerLevel, bool _underline){
  if(_headerLevel < 1 || _headerLevel > 6){
    return -1;  // Failed because of passed parameter, return error -1
  }
  hierarchyList.add(new TinyHetergeneousNode(new TinyHTMLHeaderText(lastID, _text, _fontColor, _font, _headerLevel, _underline, headerTextCount), lastID));
  headerTextCount++;
  return lastID++;
}


int TinyHTML::AddLineBreak(float _VWthickness, char* _lineColor){
  hierarchyList.add(new TinyHetergeneousNode(new TinyHTMLLineBreak(lastID, _VWthickness, _lineColor, lineBreakCount), lastID));
  lineBreakCount++;
  return lastID++;  
}


int TinyHTML::AddValueDisplay(float _defaultValue, char* _font, char* _fontColor){
  hierarchyList.add(new TinyHetergeneousNode(new TinyHTMLValueDisplay(lastID, _defaultValue, _font, _fontColor, valueDisplayCount), lastID));
  valueDisplayCount++;
  return lastID++;
}

void TinyHTML::SetValueDisplay(int _ID, float _currentValue){
  hierarchyList.GetNodeByIDFromList(_ID)->valueDisplayData->SetCurrentValue(_currentValue);
}


void TinyHTML::SendAllDisplayValuesToClient(){
  for(int i = 0; i < hierarchyList.listSize; i++){
    if(hierarchyList.GetNodeByIDFromList(i)->type == 1){
      hierarchyList.GetNodeByIDFromList(i)->valueDisplayData->SendValueToClient(client);
    }
  }
}


int TinyHTML::AddJoystick(float _sizePercentage, float _joystickSizePercentage, char* _backgroundColor, char* _outlineColor, char* _joystickColor){
  hierarchyList.add(new TinyHetergeneousNode(new TinyHTMLJoystick(lastID, _sizePercentage, _joystickSizePercentage, _backgroundColor, _outlineColor, _joystickColor, joystickCount), lastID));
  joystickCount++;
  return lastID++;
}

float TinyHTML::GetJoystickX(int _ID){
  return hierarchyList.GetNodeByIDFromList(_ID)->joystickData->xPercent;
}

float TinyHTML::GetJoystickY(int _ID){
  return hierarchyList.GetNodeByIDFromList(_ID)->joystickData->yPercent;
}

void TinyHTML::SetJoystickXY(int _ID, float _x, float _y){
  TinyHetergeneousNode *node = hierarchyList.GetNodeByIDFromList(_ID);
  if(node){
    node->joystickData->xPercent = _x;
    node->joystickData->yPercent = _y;
  }
}


int TinyHTML::AddHorizontalSlider(float _rangeMin, float _rangeMax, float _stepSize, float _widthPercentage, float _lengthPercentage, float _sliderVWSize, char* _backgroundColor, char* _outlineColor, char* _sliderHandleColor, bool _showValue, int _vwFontSize){
  hierarchyList.add(new TinyHetergeneousNode(new TinyHTMLSlider(lastID, _rangeMin, _rangeMax, _stepSize, true, _widthPercentage, _lengthPercentage, _sliderVWSize, _backgroundColor, _outlineColor, _sliderHandleColor, _showValue, _vwFontSize, sliderCount), lastID));
  sliderCount++;
  return lastID++;
}

int TinyHTML::AddVerticalSlider(float _rangeMin, float _rangeMax, float _stepSize, float _widthPercentage, float _lengthPercentage, float _sliderVWSize, char* _backgroundColor, char* _outlineColor, char* _sliderHandleColor, bool _showValue, int _vwFontSize){
  hierarchyList.add(new TinyHetergeneousNode(new TinyHTMLSlider(lastID, _rangeMin, _rangeMax, _stepSize, false, _widthPercentage, _lengthPercentage, _sliderVWSize, _backgroundColor, _outlineColor, _sliderHandleColor, _showValue, _vwFontSize, sliderCount), lastID));
  sliderCount++;
  return lastID++;
}

float TinyHTML::GetSliderValue(int _ID){
  return hierarchyList.GetNodeByIDFromList(_ID)->sliderData->value;
}

void TinyHTML::SetSliderValue(int _ID, float _value){
  TinyHetergeneousNode *node = hierarchyList.GetNodeByIDFromList(_ID);
  if(node){
    node->sliderData->value = _value;
  }  
}


int TinyHTML::AddButton(char* _text, float _sizePercentage, float _fontSize, char* _buttonColor, char* _textColor, char* _outlineColor, char* _toggledColor){
  hierarchyList.add(new TinyHetergeneousNode(new TinyHTMLButton(lastID, _text, _sizePercentage, _fontSize, _buttonColor, _textColor, _outlineColor, _toggledColor, buttonCount), lastID));
  buttonCount++;
  return lastID++;
}


void TinyHTML::SetButtonState(int _ID, bool _state){
  TinyHetergeneousNode *node = hierarchyList.GetNodeByIDFromList(_ID);
  if(node){
    node->buttonData->state = _state;
  }
}


bool TinyHTML::GetButtonState(int _ID){
  return hierarchyList.GetNodeByIDFromList(_ID)->buttonData->state;
}


int TinyHTML::AddGridTable(int _rows, int _columns){
  hierarchyList.add(new TinyHetergeneousNode(new TinyHTMLGridTable(_rows, _columns, gridTableCount), lastID));
  gridTableCount++;
  return lastID++;
}


int TinyHTML::AddPlaceholder(float _sizeW, float _sizeH){
  hierarchyList.add(new TinyHetergeneousNode(new TinyHTMLPlaceholder(lastID, _sizeW, _sizeH, placeholderCount), lastID));
  placeholderCount++;
  return lastID++;
}


int TinyHTML::AddImage(char* _src, float _imageScale, bool _srcType){
  hierarchyList.add(new TinyHetergeneousNode(new TinyHTMLImg(lastID, _src, _imageScale, _srcType, imgCount), lastID));
  imgCount++;
  return lastID++;
}


int TinyHTML::AddCustom(char* _CSSContent, char* _HTMLContent, char* _JSContent){
  hierarchyList.add(new TinyHetergeneousNode(new TinyHTMLCustom(lastID, _CSSContent, _HTMLContent, _JSContent, customCount), lastID));
  customCount++;
  return lastID++;
}


bool TinyHTML::IsDirty(){
  bool state = isDirty;
  isDirty = false;
  return state;
}


void TinyHTML::SetDisplayPollRate(float _seconds){
  displayPollRate = 1000.0f * _seconds;
}


void TinyHTML::SetClient(WiFiClient _client){
  client = _client;
}


void TinyHTML::SendAllContentToClient(){
  client.println("<!DOCTYPE html>");
  client.println("<html lang=\"en\">");
  client.println("<head>");
  client.print("<title>"); client.print(pageTitle); client.println("</title>");
  client.println("<meta charset=\"utf-8\">");
  client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  client.println("</head>");

  client.println("<style>");
  client.println(".container{");
  client.println("display: flex;");
  client.println("align-items: center;");
  client.println("justify-content: center;");
  client.println("height: 100%;}");

  client.println(".rotation-wrapper-outer{");
  client.println("display: table;");
  client.println("width: 100%;");
  client.println("}");

  client.println(".rotation-wrapper-inner{");
  client.println("padding: 50% 0;");
  client.println("height: 0;");
  client.println("width: 100%;");
  client.println("}");

  hierarchyList.TraverseListAndSendCSS(client);
  client.println("</style>");
  
  client.print("<body style=\"background-color:"); client.print(pageBackgroundColor); client.println(";\">");
  hierarchyList.TraverseListAndSendHTML(client);
  client.println("</body>");

  client.println("<script>");
  client.print("var POLLING_RATE = ");          // Declare and start defining poll rate variable
  client.print(JSPollingRate);                  // Define poll rate
  client.println(";");                          // End poll rate line

  client.print("var MAX_CMD_BUFFER_SIZE = ");   // Declare and start defining max command buffer size variable
  client.print(commandBufferMaxSize);           // Define max command buffer size
  client.println(";");                          // End max command buffer size

  client.println("      var request = new XMLHttpRequest();");
  client.println("      function POSTArduino(command){");
  client.println("        nocache = \"nocache\" + Math.random() * 1000000;");
  client.println("        request.open(\"GET\", command + nocache, true);");
  client.println("        request.send(null);");
  client.println("        return false;");
  client.println("      }");
  client.println("      var commandQueue = new Array();");
  client.println("      function pollDataForServer(){");
  client.println("        var packed_commands = \"\";");
  client.println("        var i = 0;");
  client.println("        while(i < MAX_CMD_BUFFER_SIZE && typeof commandQueue[0] !== 'undefined'){");
  client.println("          packed_commands += commandQueue[0];");
  client.println("          commandQueue.splice(0, 1);");
  client.println("          i++;");
  client.println("        }");
  client.println("        if(i > 0){");
  client.println("          packed_commands += \"$\";");
  client.println("          console.log(packed_commands);");
  client.println("          POSTArduino(packed_commands);");
  client.println("        }");
  client.println("      }");
  
  client.println("      window.setInterval(function(){");
  client.println("        pollDataForServer();");
  client.println("      }, 1000/POLLING_RATE);");

  client.println("      function fetchDisplayValues(){");
  client.println("        console.log(\"Fetching Display Value Batch...\");");
  client.println("        POSTArduino(\"I[0,0]$\");");
  client.println("        request.onreadystatechange = function(){");
  client.println("          if(request.readyState == 4 && request.status == 200){");
  client.println("            if(request.responseText != null){");
  client.println("              var displayValuesAndIDS = request.responseText.split(\"\\n\");");
  client.println("              for(var i=0; i < displayValuesAndIDS.length-1; i+=2){");
  client.println("                document.getElementById(parseInt(displayValuesAndIDS[i], 10)).value = parseFloat(displayValuesAndIDS[i+1]);");
  client.println("              }");
  client.println("            }");
  client.println("          }");
  client.println("        }");
  client.println("      }");
  
  client.println("      window.setInterval(function(){");
  client.println("        fetchDisplayValues();");
  client.print("      }, "); client.print(displayPollRate); client.println(");");
  
  hierarchyList.TraverseListAndSendJS(client);  // Send the rest of the node JS to client web broswer
  client.println("</script>");
  client.println("</html>");
}


void TinyHTML::HandleClient(WiFiServer _web_server){
  client = _web_server.available();     // listen for incoming clients, always grab the next available
  
  // check that there is a client (not null)
  if(client){
    char last_char = ' ';               // The last char received from client
    char current_char = ' ';            // Current char received from client
    char command[32];                   // Save 32 bytes/chars for recevied command strings
    int chars_read_count = 0;           // Record how many chars have been received from client
    bool command_found = false;         // Flag changes true when POST request matches command format (no empty char at index 6 of POST string)
    char decodingParameters[3][4];      // Holds chars from parameters being decoded (the most parameters in a command is 3 at 5 chars max, extra for \0)
    int paramterIndex = 0;              // Index of the current parameter being decoded (paramters are sent from client as comma seperated)
    int paramterCharIndex = 0;          // The char index of the individual parameter
    char commandType = ' ';
 
    while (client.connected() && client.available()){
      current_char = client.read();
      chars_read_count++;

      if(current_char != '$'){                                                      // Unless $ is found, read chars from client web broswer GET
        if(chars_read_count == 6 && current_char != ' '){                           // If at char read 6 and not whitespace, the GET from client contains a command
          command[chars_read_count-6] = current_char;                               // Start storing chars now (the first char of a command is its ID)
          commandType = current_char;
          command_found = true;                                                     // Command found, record any further chars until a special char is found
        }else if(command_found){                                                    // If the last char satisifed format of a command, keep recording chars
          command[chars_read_count-6] = current_char;                               // Record char, then check for special chars that signify another command in the string/packet
          if(current_char == ']'){                                                  // Check the just read char to see if it is special end char
              chars_read_count = 5;                                                 // Reset char count so command buffer is filled correctly next time
              command_found = false;                                                // Reset (may not need to)
              paramterIndex = 0;                                                    // Reset
              paramterCharIndex = 0;                                                // Reset
              isDirty = true;                                                       // Set true any time a command is confirmed to be sent from client
              switch(commandType){                                                  // Check which element this command came from so data can be stored correctly
                case 'S':
                  SetJoystickXY(atoi(decodingParameters[0]), atof(decodingParameters[1]), atof(decodingParameters[2]));
                break;
                case 'A':
                  SetSliderValue(atoi(decodingParameters[0]), atof(decodingParameters[1]));
                break;
                case 'B':
                  SetButtonState(atoi(decodingParameters[0]), atoi(decodingParameters[1]));
                break;
                case 'I':   // Client is asking for display value element data, traverse list and find these elements and send dirty ones
                  SendAllDisplayValuesToClient();
                break;
                default:
                  
                break;
              }
          }else if(current_char != '['){                                            // By this point, current_char is not $, ], or now [ so decode paramters
            if(current_char != ','){                                                // if the paramter char is not a comma to seperate paramters, move on to storing for later conversion
              decodingParameters[paramterIndex][paramterCharIndex] = current_char;  // Store the parameter string char
              paramterCharIndex++;                                                  // Increase so the next time is stored after the one just stored
            }else{
              decodingParameters[paramterIndex][paramterCharIndex] = '\0';          // Instead of storing another char, since we found a comma, store ending char \0 for atoi and atof functions
              paramterIndex++;                                                      // Move on to storing the next parameter
              paramterCharIndex = 0;                                                // Make sure start at beginning of parameter string storage next time
            }
          }
        }
      }else{
        break;  // Break out of main read loop if $ was found (end of command string)
      }

      // GET request ends when last line ended and
      // current line immediately starts to end (blank)
      if(last_char == '\r' && current_char == '\n'){
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println("Connection: keep-alive"); // https://developer.mozilla.org/en-US/docs/Web/HTTP/Connection_management_in_HTTP_1.x
        client.println();
        // If no command was found at start of GET request, must mean new client, serve webpage to it
        if(!command_found){
          SendAllContentToClient();
        }
        break;  // Stop the reading while loop
      }
      last_char = current_char;
    }
    delay(1);      // Give client web browser time to receive the data
    client.stop(); // Close the connection to the client since all GET data read and read loop done
  }  
}
