#include "TinyHTMLGridTable.h"


TinyHTMLGridTable::TinyHTMLGridTable(int _rows, int _columns, int _gridElementIndex){
  rows = _rows;
  columns = _columns;
  maxChildCount = rows * columns;
  currentChildCount = 0;
  gridElementIndex = _gridElementIndex;
}


void TinyHTMLGridTable::SendGridTableHTMLStartToClient(WiFiClient &_client){
  _client.print("<div style=display:grid;grid-template-columns:repeat(");  // Make div display elements in grid
  _client.print(columns);
  _client.print(",");
  _client.print(100.0f/columns);
  _client.print("%);padding:0px;align-content:center>");
}


void TinyHTMLGridTable::SendGridTableHTMLEndToClient(WiFiClient &_client){
  _client.println("</div>");
}
