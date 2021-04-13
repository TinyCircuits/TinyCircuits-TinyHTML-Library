#include "TinyHetergeneousNode.h"


TinyHetergeneousNode::TinyHetergeneousNode(){
  
}


TinyHetergeneousNode::TinyHetergeneousNode(TinyHTMLJoystick *_joystickData, int _ID){
  joystickData = _joystickData;
  type = 0;
  ID = _ID;
}


TinyHetergeneousNode::TinyHetergeneousNode(TinyHTMLValueDisplay *_valueDisplayData, int _ID){
  valueDisplayData = _valueDisplayData;
  type = 1;
  ID = _ID;
}


TinyHetergeneousNode::TinyHetergeneousNode(TinyHTMLGridTable *_gridData, int _ID){
  gridData = _gridData;
  type = 2;
  ID = _ID;
}


TinyHetergeneousNode::TinyHetergeneousNode(TinyHTMLHeaderText *_headerTextData, int _ID){
  headerTextData = _headerTextData;
  type = 3;
  ID = _ID;
}


TinyHetergeneousNode::TinyHetergeneousNode(TinyHTMLSlider *_sliderData, int _ID){
  sliderData = _sliderData;
  type = 4;
  ID = _ID;  
}


TinyHetergeneousNode::TinyHetergeneousNode(TinyHTMLButton *_buttonData, int _ID){
  buttonData = _buttonData;
  type = 5;
  ID = _ID;
}


TinyHetergeneousNode::TinyHetergeneousNode(TinyHTMLPlaceholder *_placeholderData, int _ID){
  placeholderData = _placeholderData;
  type = 6;
  ID = _ID;
}


TinyHetergeneousNode::TinyHetergeneousNode(TinyHTMLLineBreak* _lineBreakData, int _ID){
  lineBreakData = _lineBreakData;
  type = 7;
  ID = _ID;
}


TinyHetergeneousNode::TinyHetergeneousNode(TinyHTMLImg *_imgData, int _ID){
  imgData = _imgData;
  type = 8;
  ID = _ID;
}


TinyHetergeneousNode::TinyHetergeneousNode(TinyHTMLCustom *_customData, int _ID){
  customData = _customData;
  type = 9;
  ID = _ID;
}


TinyHetergeneousNode* TinyHetergeneousNode::FindNearestNeededLinkNode(){
  if(parent != NULL && parent->type == 2){            // If parent is a table, check that there is room for a child, otherwise keep checking until another table or NULL (NULL means back at main branch)
    if(parent->gridData->currentChildCount < parent->gridData->maxChildCount){
      return parent->FindNearestChildlessChildNode(); // Return the nearest child under this parent node since confirmed that it needs a child
    }else{                                            // Parent node was full, try calling this function on that parent
      return parent->FindNearestNeededLinkNode();     // Return parent that needs a child or next link
    }
  }else if(parent == NULL){                           // If finally find NULL, add the node to the next to keep main branch going (done externally)
    return parent;
  }
}


TinyHetergeneousNode* TinyHetergeneousNode::FindNearestChildlessChildNode(){
  if(child == NULL){
    return this;
  }else{
    return child->FindNearestChildlessChildNode();
  }
}


void TinyHetergeneousNode::SendNodeCSSorHTMLorJS(WiFiClient &_client, int _css_html_js_flag){
  switch(type){
    case 0:   // Send joystick data
      if(joystickData){
        if(_css_html_js_flag == 2){
          joystickData->SendJoystickJSToClient(_client);
        }else if(_css_html_js_flag == 1){
          joystickData->SendJoystickHTMLToClient(_client);
        }
      }
    break;
    case 1:
      if(valueDisplayData){
        if(_css_html_js_flag == 2){
          
        }else if(_css_html_js_flag == 1){
          valueDisplayData->SendValueDisplayHTMLToClient(_client);
        }
      }
    break;
    case 2:
      if(gridData){
        if(_css_html_js_flag == 2){
          
        }else if(_css_html_js_flag == 1){
          gridData->SendGridTableHTMLStartToClient(_client);
        }
      }
    break;
    case 3:
      if(headerTextData){
        if(_css_html_js_flag == 2){
          
        }else if(_css_html_js_flag == 1){
          headerTextData->SendHeaderTextHTMLToClient(_client);
        }
      }
    break;
    case 4:
      if(sliderData){
        if(_css_html_js_flag == 2){
          sliderData->SendSliderJSToClient(_client);
        }else if(_css_html_js_flag == 1){
          sliderData->SendSliderHTMLToClient(_client);
        }else if(_css_html_js_flag == 0){
          sliderData->SendSliderCSSToClient(_client);
        }
      }
    break;
    case 5:
      if(buttonData){
        if(_css_html_js_flag == 2){
          buttonData->SendButtonJSToClient(_client);
        }else if(_css_html_js_flag == 1){
          buttonData->SendButtonHTMLToClient(_client);
        }else if(_css_html_js_flag == 0){
          buttonData->SendButtonCSSToClient(_client);
        }
      }
    break;
    case 6:
      if(placeholderData){
        if(_css_html_js_flag == 2){
          placeholderData->SendPlaceholderJSToClient(_client);
        }else if(_css_html_js_flag == 1){
          placeholderData->SendPlaceholderHTMLToClient(_client);
        }else if(_css_html_js_flag == 0){
          placeholderData->SendPlaceholderCSSToClient(_client);
        }
      }
    break;
    case 7:
      if(lineBreakData){
        if(_css_html_js_flag == 1){
          lineBreakData->SendLineBreakHTMLToClient(_client);
        }
      }
    break;
    case 8:
      if(imgData){
        if(_css_html_js_flag == 2){
          imgData->SendImgJSToClient(_client);
        }else if(_css_html_js_flag == 1){
          imgData->SendImgHTMLToClient(_client);
        }else if(_css_html_js_flag == 0){
          imgData->SendImgCSSToClient(_client);
        }
      }
    break;
    case 9:
      if(customData){
        if(_css_html_js_flag == 2){
          customData->SendCustomJSToClient(_client);
        }else if(_css_html_js_flag == 1){
          customData->SendCustomHTMLToClient(_client);
        }else if(_css_html_js_flag == 0){
          customData->SendCustomCSSToClient(_client);
        }
      }
    break;
  }

  // Everytime a node sends its HTML, it could be the last child of a table parent.
  // If this node's parent is a table (type 2) and its child is NULL (this node is childless)
  // then that means table sending HTML should be sent. Only send HTML if not sending JS
  if(gridData && parent && parent->type == 2 && child == NULL && _css_html_js_flag == 1){
    gridData->SendGridTableHTMLEndToClient(_client);
  }

  // Before starting on the next node, make sure the children nodes are taken care of
  // If a child node has a child, handle that first before doing the rest of these children nodes
  if(child){
    child->SendNodeCSSorHTMLorJS(_client, _css_html_js_flag);
  }

  if(next){
    next->SendNodeCSSorHTMLorJS(_client, _css_html_js_flag);
  }
}
