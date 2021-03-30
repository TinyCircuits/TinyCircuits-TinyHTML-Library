#ifndef TINYDYNAMICLINKEDLIST_H
#define TINYDYNAMICLINKEDLIST_H

#include "TinyHetergeneousNode.h"

class TinyLinkedList{     // Organizes the nodes in the list
public:

  TinyLinkedList();

  //  1: T added to end of main list if current type (i.e. type of object not the object being added to the list) is not TinyHTMLGridTable
  //  2: T added to end of child list if current type (i.e. the type of the object of which add() is being called) is TinyHTMLGridTable
  void add(TinyHetergeneousNode *_node);
  void TraverseListAndSendJS(WiFiClient &_client);     // Goes through the list and sends JavaScript code according to hierarchy
  void TraverseListAndSendHTML(WiFiClient &_client);   // Goes through the list and sends HTML according to hierarchy
  void TraverseListAndSendCSS(WiFiClient &_client);    // Goes through the list and sends CSS according to hierarchy
  TinyHetergeneousNode *GetNodeByIDFromList(int _ID);  // All elements have an ID member, this checks list so far and returns true if finds matching ID
  int listSize;                                        // Size of list update after add() & remove() (includes number of child nodes)
private:

  void UpdateCachedNodeRefs();              // Resizes and stores addresses in 1D linear array cachedNodeRefs for later quick reference use

  TinyHetergeneousNode *rootNode;           // The node that starts the main list
  TinyHetergeneousNode *lastNode;           // The last node that was inserted by add()
  TinyHetergeneousNode *lastNodeGot;        // Helps "get" method, by saving last position
  TinyHetergeneousNode ***cachedNodeRefs;   // Linear array of node addresses where indices correspond to generated node IDs (refreashed everytime a node is added)
};

#endif /* TINYDYNAMICLINKEDLIST_H */
