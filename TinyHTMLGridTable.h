#ifndef TINYHTMLGRIDTABLE_H
#define TINYHTMLGRIDTABLE_H

#include <WiFi101.h>

class TinyHTMLGridTable{
public:
  TinyHTMLGridTable(int _rows, int _columns, int _gridElementIndex);
  void SendGridTableJSToClient(WiFiClient &_client);
  void SendGridTableHTMLStartToClient(WiFiClient &_client);
  void SendGridTableHTMLEndToClient(WiFiClient &_client);
  int maxChildCount;      // How many child elements fit under this tbale
  int currentChildCount;  // How many child elements have been added to this table so far
private:
  int rows;
  int columns;
  int gridElementIndex;
};

#endif /* TINYHTMLGRIDTABLE_H */
