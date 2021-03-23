#include "TinyDynamicLinkedList.h"

TinyLinkedList::TinyLinkedList(){
  rootNode=NULL;          // NULL until add()
  lastNode=NULL;          // NULL until add()
  lastNodeGot = rootNode; // The last node to be gotten at startup is root (even though NULL)
  listSize=0;             // So far no nodes exist/have data in the list (this includes number of children nodes)
}


// Add a node at end of list or under a grid table child node (see class def for more details)
void TinyLinkedList::add(TinyHetergeneousNode *_node){
  _node->next = NULL;   // Can't have a next yet if just being added
  _node->child = NULL;  // Can't have a child yet if just being added
  _node->parent = NULL; // Parent only references table parents, not the last node it may link too from ->next

  if(rootNode != NULL){           // If root is not NULL, list has been added to at least once, add new node to child if last was table otherwise add to next of last node
    if(lastNode->type == 2 && lastNode->gridData->currentChildCount < lastNode->gridData->maxChildCount){  // Last node added was a table, add new node as child if it can fit, 
                                                                                                           // otherwise move on to just linking to ->next (will skip next if-statement, can't be true)
      if(_node->type != 2){                       // Skip adding tables to tables (not allowed due to complexity and that there is no practical use)
        lastNode->child = _node;                  // Add first child to table
        _node->parent = lastNode;                 // Make table as new node's parent so other child nodes can link to that table as a parent
        lastNode->gridData->currentChildCount++;  // Incrase count of how many children exist under table 
      }else{
        return;                                   // Stop function execution, tables cannot be added under tables
      }
    }else if(lastNode->parent != NULL && lastNode->parent->type == 2 && lastNode->parent->gridData->currentChildCount < lastNode->parent->gridData->maxChildCount){  // Last node's parent was a table, check 
                                                                                                                                                                     // if new node can fit under last child (otherwise move to link ->next)
      if(_node->type != 2){                               // Skip adding tables tables (not allowed due to complexity and that there is no practical use)
        lastNode->child = _node;                          // Make new node a child of the last added table child node
        _node->parent = lastNode->parent;                 // Link new node parent to the last child's node parent
        lastNode->parent->gridData->currentChildCount++;  // Incrase count of how many children exist under table
      }else{
        return;                                           // Stop function execution, tables cannot be added under tables
      }
    }else{                      // If the last node didn't link to a table node, then add the new node to the last node's next
      lastNode->next = _node;   // Add new node to last node's next so has a link in tree
      _node->parent = lastNode; // Link the last node as a parent of this node
    }
  }else{                  // root is NULL, the list has not been added to yet
    rootNode = _node;     // root was NULL, make new node root (child and next links were set NULL above)
  }

  lastNode = _node;       // Make the just added node the last node now (same for case of adding node to child or next)
  listSize++;             // One node was added, increase the list size

  UpdateCachedNodeRefs(); // Update the cache of node addresses for later quick reference
}



void TinyLinkedList::TraverseListAndSendCSS(WiFiClient &_client){
  rootNode->SendNodeCSSorHTMLorJS(_client, 0);  // It all starts with the root node (false for send HTML)
}


void TinyLinkedList::TraverseListAndSendHTML(WiFiClient &_client){
  rootNode->SendNodeCSSorHTMLorJS(_client, 1);  // It all starts with the root node (true for send JS)
}


void TinyLinkedList::TraverseListAndSendJS(WiFiClient &_client){
  rootNode->SendNodeCSSorHTMLorJS(_client, 2); // It all starts with the root node (false for send HTML)
}


// Returns node using cache node ref array to dereference the address of the pointer
TinyHetergeneousNode *TinyLinkedList::GetNodeByIDFromList(int _ID){
  if(_ID < listSize){
    return (*cachedNodeRefs[_ID]);  // Return node if not out of bounds (althrough there's a chance the passed ID is corrupted)
  }
  return NULL;                      // Return NULL if ID is out of bounds of the list size
}


// Resizes and reformats cache array of node addresses for quick refernece later
void TinyLinkedList::UpdateCachedNodeRefs(){
  free(cachedNodeRefs);
  cachedNodeRefs = new TinyHetergeneousNode**[listSize];

  // The flow of increasing ID is root, child, and then next
  TinyHetergeneousNode **tempCurrent = &rootNode; // Start at the root node (always ID 0)
  int tempID = rootNode->ID;                      // Store the ID of the last node touched (NOTE: listSize and lastID are incrased at same rate just listSize is one bigger)
  cachedNodeRefs[tempID] = tempCurrent;           // Store the address of rootNode

  while(listSize-1 != tempID){                    // Check if we are at the last node yet
    if((*tempCurrent)->child != NULL){            // If child exists, go that way first
      tempCurrent = &(*tempCurrent)->child;       // Set so can index child
    }else{                                        // If not child and not a parent, go to next node on main branch and index that            
      tempCurrent = &(*tempCurrent)->next;        // Next is linked off of the child node (if it happens to be a child)
    }
    tempID = (*tempCurrent)->ID;                  // Store ID for loop
    cachedNodeRefs[tempID] = tempCurrent;         // Store address of indexed node for later quick reference
  }
}
