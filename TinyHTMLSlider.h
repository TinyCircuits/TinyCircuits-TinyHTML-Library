#ifndef TINYHTMLSLIDER_H
#define TINYHTMLSLIDER_H

#include <WiFi101.h>

class TinyHTMLSlider{
public:
  TinyHTMLSlider(int _ID, float _rangeMin, float _rangeMax, float _stepSize, bool _horoORvert, float _widthPercentage, float _lengthPercentage, float _sliderVWSize, const char* _backgroundColor, const char* _outlineColor, const char* _sliderHandleColor, bool _showValue, int _vwFontSize, int _sliderElementIndex);
  void SendSliderJSToClient(WiFiClient &_client);
  void SendSliderHTMLToClient(WiFiClient &_client);
  void SendSliderCSSToClient(WiFiClient &_client);
  float value;  // The value of the slider, sent from the client
private:
  int ID;
  float rangeMin;
  float rangeMax;
  float stepSize;
  bool horoORvert;
  float widthPercentage;
  float lengthPercentage;
  float sliderVWSize;
  const char* backgroundColor;
  const char* outlineColor;
  const char* sliderHandleColor;
  int sliderElementIndex;
  bool showValue;
  float vwFontSize;
};

#endif /* TINYHTMLSLIDER_H */
