#include <Wire.h>       // General library for peripheral communication
#include <WiFi101.h>    // For connecting to WiFi
#include "TinyHTML.h"   // Library for building webpages quickly


// Define SerialMonitorInterface object depending on board architecture
#if defined (ARDUINO_ARCH_AVR)
#define SerialMonitorInterface Serial
#elif defined(ARDUINO_ARCH_SAMD)
#define SerialMonitorInterface SerialUSB
#endif


/*********************** EDIT THIS SECTION TO MATCH YOUR INFO *************************/
// WiFi network information
char ssid[] = "ExampleSSID";                  // Your network SSID (name)
char wifi_password[] = "VerySecurePassword";  // Your network password
IPAddress shield_ip;                          // Set by connect to WiFi function
WiFiServer web_server(80);                    // Hosting web server on port 80


// Set the page title
// Set Javascript polling rate of elements at 66 tiems a second
// Allow sending of 5 commands from client to Arduino at a time
TinyHTML HTML("TinyHTML Example Webpage", 66, 5);


// List of ID variables that will be defined in setup()
int JOYSTICK_ID1;
int SLIDER_ID1;   
int SLIDER_ID2;
int SLIDER_ID3;
int BUTTON_ID1;
int DISPLAY_VALUE_ID1;

float v = 0.0f;

void setup() {
  SerialMonitorInterface.begin(9600); // Initialize serial
  while(!SerialMonitorInterface){}    // Wait until serial monitor is opened before doing anything

  HTML.SetPageBackgroundColor("#000000");           // Set the page background to black
  HTML.AddHeaderText("TinyHTML Feature Demo");      // Add some header text
  JOYSTICK_ID1 = HTML.AddJoystick(90);              // Add a joystick element that takes up 90% of the space while keeping aspect ratio constant, and store the ID
  HTML.AddHeaderText("Slider 1");                   // Add header text for slider
  SLIDER_ID1 = HTML.AddHorizontalSlider();          // Add a horozontial slider and store the ID (by default, sliders range from -1 to 1 in steps of 0.1)
  HTML.AddGridTable(2, 2);                          // Start a grid table that has two rows and columns
  HTML.AddHeaderText("Slider 2");                   // Add header text to first table slot (top right)                           
  HTML.AddHeaderText("Slider 3");                   // Add header text to second table slot (top left in this case)
  SLIDER_ID2 = HTML.AddVerticalSlider();            // Add vertical slider to third table slot (bottom left in this case), and store its ID
  SLIDER_ID3 = HTML.AddVerticalSlider();            // Add vertical slider to fourth table slot (bottom right in this case, the table in now full), and store its ID
  BUTTON_ID1 = HTML.AddButton("Test Button");       // Add button as the last element of the page and store its ID
  HTML.AddHeaderText("Increasing float:");          // Add a header to tell user that below value increases
  DISPLAY_VALUE_ID1 = HTML.AddValueDisplay(0.01f);  // Add display value element to show a float increase every 2 seconds

  Wire.begin();               // Initialize wire library
  WiFi.setPins(8, 2, A3, -1); // Initialize Wifi hardware: SETTING PINS VERY IMPORTANT FOR TINYCIRCUITS WIFI SHIELD
  delay(100);                 // Wait 100ms for hardware to setup

  if(!connectWifi()){         // Connect WiFi, stop program if connection fails
    SerialMonitorInterface.println("WiFi could not connect - halting program!");
    while(1);
  }

  web_server.begin(); // Start web server
}


void loop() {
  HTML.HandleClient(web_server);  // Call every loop so that data sent from web browser to server (Arduino) is stored in library
  
  v = v + 0.1f;
  HTML.SetValueDisplay(DISPLAY_VALUE_ID1, v); // Send float to display value element on web broswer client (could be used for sensor data)

  // Only display information in serial monitor if a command has been received from the web broswer (i.e. an element was interacted with)
  if(HTML.IsDirty()){
    SerialMonitorInterface.print("Joystick ");
    SerialMonitorInterface.print(JOYSTICK_ID1);
    SerialMonitorInterface.print(" x,y: ");
    SerialMonitorInterface.print(HTML.GetJoystickX(JOYSTICK_ID1));
    SerialMonitorInterface.print(",");
    SerialMonitorInterface.println(HTML.GetJoystickY(JOYSTICK_ID1));

    SerialMonitorInterface.print("Slider ");
    SerialMonitorInterface.print(SLIDER_ID1);
    SerialMonitorInterface.print(": ");
    SerialMonitorInterface.println(HTML.GetSliderValue(SLIDER_ID1));

    SerialMonitorInterface.print("Slider ");
    SerialMonitorInterface.print(SLIDER_ID2);
    SerialMonitorInterface.print(": ");
    SerialMonitorInterface.println(HTML.GetSliderValue(SLIDER_ID2));

    SerialMonitorInterface.print("Slider ");
    SerialMonitorInterface.print(SLIDER_ID3);
    SerialMonitorInterface.print(": ");
    SerialMonitorInterface.println(HTML.GetSliderValue(SLIDER_ID3));

    SerialMonitorInterface.print("Button ");
    SerialMonitorInterface.print(BUTTON_ID1);
    SerialMonitorInterface.print(": ");
    SerialMonitorInterface.println(HTML.GetButtonState(BUTTON_ID1));
  }
}


int connectWifi(void) {
  // Set priority of WiFi to something less than 0 (highest priority)
  // This should allow for the WiFi shield and motors to run smoothly on RobotZero
  NVIC_DisableIRQ(EIC_IRQn);
  NVIC_ClearPendingIRQ(EIC_IRQn);
  NVIC_SetPriority(EIC_IRQn, 1);
  NVIC_EnableIRQ(EIC_IRQn);
  
  // Connect to Wifi network:
  SerialMonitorInterface.println("Connecting Wifi: ");
  SerialMonitorInterface.print("   SSID: ");
  SerialMonitorInterface.println(ssid);
  WiFi.begin(ssid, wifi_password);
  delay(100);
  if (WiFi.status() != WL_CONNECTED) {
    SerialMonitorInterface.println("   ERROR: Connection failed: Move closer to router, double check network info, or ensure shield physically connected. Halting program...");
    return 0;
  } else {
    // Success message and put WiFi in low power mode to save energy
    WiFi.maxLowPowerMode();
    SerialMonitorInterface.println("   SUCCESS: WiFi connected");

    // print your WiFi shield's IP address:
    shield_ip = WiFi.localIP();
    SerialMonitorInterface.print("   TinyShield IP Address: ");
    SerialMonitorInterface.println(shield_ip);
  }
  return 1;
}
