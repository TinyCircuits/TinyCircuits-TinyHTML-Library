#ifndef TINYHETERGENEOUSNODE_H
#define TINYHETERGENEOUSNODE_H

#include "TinyHTMLJoystick.h"
#include "TinyHTMLValueDisplay.h"
#include "TinyHTMLGridTable.h"
#include "TinyHTMLHeaderText.h"
#include "TinyHTMLSlider.h"
#include "TinyHTMLButton.h"
#include "TinyHTMLPlaceholder.h"

class TinyHetergeneousNode{     // A node in a list that can be one of several object types
public:
  TinyHetergeneousNode();
  TinyHetergeneousNode(TinyHTMLJoystick *_joystickData, int _ID);
  TinyHetergeneousNode(TinyHTMLValueDisplay *_valueDisplayData, int _ID);
  TinyHetergeneousNode(TinyHTMLGridTable *_gridData, int _ID);
  TinyHetergeneousNode(TinyHTMLHeaderText *_headerTextData, int _ID);
  TinyHetergeneousNode(TinyHTMLSlider *_sliderData, int _ID);
  TinyHetergeneousNode(TinyHTMLButton *_buttonData, int _ID);
  TinyHetergeneousNode(TinyHTMLPlaceholder *_placeholderData, int _ID);

  union{                        // Use one location in memory only (although union chooses the largest space)
    TinyHTMLJoystick* joystickData;
    TinyHTMLValueDisplay* valueDisplayData;
    TinyHTMLGridTable* gridData;
    TinyHTMLHeaderText* headerTextData;
    TinyHTMLSlider* sliderData;
    TinyHTMLButton *buttonData;
    TinyHTMLPlaceholder *placeholderData;
  };
  
  TinyHetergeneousNode *next;   // The next node containing a T data member (ex. int data)
  TinyHetergeneousNode *child;  // Child node allows for branching in the case of grid/table element
  TinyHetergeneousNode *parent; // It is possible that each node has a parent table node

  int type;                     // The type of data that is important to this object and was defined
  int ID;                       // The ID of this node given by the user

  TinyHetergeneousNode* FindNearestNeededLinkNode();                        // When called from/on a node, returns nearest child or next node that can link to the node this was called from/on
  void SendNodeCSSorHTMLorJS(WiFiClient &_client, int _css_html_js_flag);   // According to the type, HTML is sent to passed client reference (true for send JS, false for HTML)
  TinyHetergeneousNode* FindNearestChildlessChildNode();                    // When called from/on a node, returns nearest child node that does not have a child under it
};


#endif /* TINYHETERGENEOUSNODE_H */
