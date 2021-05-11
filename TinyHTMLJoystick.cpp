#include "TinyHTMLJoystick.h"


TinyHTMLJoystick::TinyHTMLJoystick(int _ID, float _sizePercentage, float _joystickSizePercentage, const char* _backgroundColor, const char* _outlineColor, const char* _joystickColor, int _joystickElementIndex){
  ID = _ID;
  sizePercentage = _sizePercentage;
  joystickSizePercentage = _joystickSizePercentage;
  backgroundColor = _backgroundColor;
  outlineColor = _outlineColor;
  joystickColor = _joystickColor;
  joystickElementIndex = _joystickElementIndex;
}


void TinyHTMLJoystick::SendJoystickJSToClient(WiFiClient &_client){
  if(joystickElementIndex == 0){  // Only send main part of JS joystick class once
    _client.println("      class JoystickController{");
    _client.println("       constructor(joystick_id){");
    _client.println("       this.id = joystick_id;");
    _client.println("       let joystick_container = document.getElementById(joystick_id + \"C\");");
    _client.println("       let joystick = document.getElementById(joystick_id);");
    _client.println("       this.drag_start = null;");
    _client.println("       this.touch_id = null;");
    _client.println("       this.joystick_active = false;");
    _client.println("       this.current_pos_percent = {x: 0, y: 0};");
    _client.println("       this.number_extra_cycles_after_polling = 4;");
    _client.println("       this.number_extra_cycles_after_polling_count = 0;");
    _client.println("       this.backgroundColor;");
    _client.println("       this.last_tap_time = 0;");
    _client.println("       this.double_tapped = 0;");
    _client.println("       let self = this;");
    _client.println("       function handleDown(event){");
    _client.println("         var now_tap_time = new Date().getTime();");
    _client.println("         var timesince_taps = now_tap_time - self.last_tap_time;");
    _client.println("         if((timesince_taps < 300) && (timesince_taps > 0)){");
    _client.println("           if(self.double_tapped == 0){");
    _client.println("             self.double_tapped = 1;");
    _client.println("             self.backgroundColor = joystick.style.backgroundColor;");
    _client.println("             joystick.style.backgroundColor  = \"green\";");
    _client.println("           }else{");
    _client.println("             self.double_tapped = 0;");
    _client.println("             joystick.style.backgroundColor  = self.backgroundColor;");
    _client.println("             self.joystick_active = 0;");
    _client.println("           }");
    _client.println("         }");
    _client.println("         self.joystick_active = true;");
    _client.println("           joystick.style.transition = '0s';");
    _client.println("           event.preventDefault();");
    _client.println("         if (event.changedTouches){");
    _client.println("           self.drag_start = {x: event.changedTouches[0].clientX, y: event.changedTouches[0].clientY};");
    _client.println("           } else {");
    _client.println("           self.drag_start = {x: event.clientX, y: event.clientY};");
    _client.println("           }");
    _client.println("         if (event.changedTouches){");
    _client.println("           self.touch_id = event.changedTouches[0].identifier;");
    _client.println("         }");
    _client.println("         self.last_tap_time = new Date().getTime();");
    _client.println("       }");
    _client.println("       function handleMove(event){");
    _client.println("         if ( !self.joystick_active ){");
    _client.println("           return;");
    _client.println("         }");
    _client.println("         let touch_move_id = null;");
    _client.println("         if (event.changedTouches){");
    _client.println("           for (let i = 0; i < event.changedTouches.length; i++){");
    _client.println("           if (self.touch_id == event.changedTouches[i].identifier){");
    _client.println("             touch_move_id = i;");
    _client.println("             event.clientX = event.changedTouches[i].clientX;");
    _client.println("             event.clientY = event.changedTouches[i].clientY;");
    _client.println("           }");
    _client.println("           }");
    _client.println("           if (touch_move_id == null){");
    _client.println("             return;");
    _client.println("           }");
    _client.println("         }");
    _client.println("         const joystick_radius = joystick.getBoundingClientRect().width/2;");
    _client.println("         const joystick_container_radius = joystick_container.getBoundingClientRect().width/2;");
    _client.println("         const max_distance = joystick_container_radius - joystick_radius;");
    _client.println("         const x_diff = event.clientX - self.drag_start.x;");
    _client.println("         const y_diff = event.clientY - self.drag_start.y;");
    _client.println("         const angle = Math.atan2(y_diff, x_diff);");
    _client.println("         const distance = Math.min(max_distance, Math.hypot(x_diff, y_diff));");
    _client.println("         const x_pos = distance * Math.cos(angle);");
    _client.println("         const y_pos = distance * Math.sin(angle);");
    _client.println("         joystick.style.transform = `translate3d(${x_pos}px, ${y_pos}px, 0px)`;");
    _client.println("         const x_percent = parseFloat((x_pos / max_distance).toFixed(2));");
    _client.println("         const y_percent = parseFloat((y_pos / max_distance).toFixed(2));");
    _client.println("         self.current_pos_percent = {x: x_percent, y: y_percent};");
    _client.println("         }");
    _client.println("       function handleUp(event){");
    _client.println("         if ( !self.joystick_active ) return;");
    _client.println("         // if this is a touch event, make sure it is the right one");
    _client.println("         if (event.changedTouches && self.touch_id != event.changedTouches[0].identifier) return;");
    _client.println("         // transition the joystick position back to center");
    _client.println("         joystick.style.transition = '.1s';");
    _client.println("         joystick.style.transform = `translate3d(0px, 0px, 0px)`;");
    _client.println("         // reset everything");
    _client.println("         self.current_pos_percent = { x: 0, y: 0 };");
    _client.println("         self.touch_id = null;");
    _client.println("         self.joystick_active = false;");
    _client.println("       }");
    _client.println("        this.ConstantActivePoll = function(){");
    _client.println("         if(self.joystick_active){");
    _client.println("           this.number_extra_cycles_after_polling_count = 0;");
    _client.println("         }");
    _client.println("         if(this.number_extra_cycles_after_polling_count <= this.number_extra_cycles_after_polling){");
    _client.println("           commandQueue.push(\"S[\" + joystick_id + \",\" + self.current_pos_percent.x + \",\" + self.current_pos_percent.y + \"]\");");
    _client.println("           this.number_extra_cycles_after_polling_count++;");
    _client.println("         }");
    _client.println("        }");
    _client.println("       var keys = [];");
    _client.println("       window.addEventListener(\"keydown\",");
    _client.println("         function(e){");
    _client.println("           if(self.double_tapped == 1){");
    _client.println("             keys[e.key] = true;");
    _client.println("           }");
    _client.println("         },");
    _client.println("       false);");
    _client.println("       window.addEventListener('keyup',");
    _client.println("         function(e){");
    _client.println("           if(self.double_tapped == 1){");
    _client.println("             keys[e.key] = false;");
    _client.println("             joystick.style.transition = '.1s';");
    _client.println("             joystick.style.transform = `translate3d(0px, 0px, 0px)`;");
    _client.println("             self.current_pos_percent = { x: 0, y: 0 };");
    _client.println("             self.touch_id = null;");
    _client.println("             self.joystick_active = false;");
    _client.println("             joystick.blur();");
    _client.println("             joystick_container.blur();");
    _client.println("             joystick_container.focus();");
    _client.println("           }");
    _client.println("         },");
    _client.println("       false);");
    _client.println("       function handleKeyPress(event){");
    _client.println("         event.preventDefault();");
    _client.println("         if(self.double_tapped == 1){");
    _client.println("           if(keys[\"w\"] && keys[\"a\"]){");
    _client.println("             self.current_pos_percent = {x: -0.75, y: -0.75};");
    _client.println("           }else if(keys[\"w\"] && keys[\"d\"]){");
    _client.println("             self.current_pos_percent = {x: 0.75, y: -0.75};");
    _client.println("           }else if(keys[\"s\"] && keys[\"a\"]){");
    _client.println("             self.current_pos_percent = {x: -0.75, y: 0.75};");
    _client.println("           }else if(keys[\"s\"] && keys[\"d\"]){");
    _client.println("             self.current_pos_percent = {x: 0.75, y: 0.75};");
    _client.println("           }else if(keys[\"w\"]){");
    _client.println("             self.current_pos_percent = {x: 0, y: -1.0};");
    _client.println("           }else if(keys[\"s\"]){");
    _client.println("             self.current_pos_percent = {x: 0, y: 1.0};");
    _client.println("           }else if(keys[\"a\"]){");
    _client.println("             self.current_pos_percent = {x: -1.0, y: 0};");
    _client.println("           }else if(keys[\"d\"]){");
    _client.println("             self.current_pos_percent = {x: 1.00, y: 0};");
    _client.println("           }");
    _client.println("           self.joystick_active = 1;");
    _client.println("           const joystick_radius = joystick.getBoundingClientRect().width/2;");
    _client.println("           const joystick_container_radius = joystick_container.getBoundingClientRect().width/2;");
    _client.println("           const max_distance = joystick_container_radius - joystick_radius;");
    _client.println("           const angle = Math.atan2(self.current_pos_percent.y, self.current_pos_percent.x);");
    _client.println("           const temp_pos = {x: max_distance*Math.cos(angle), y: max_distance*Math.sin(angle)};");
    _client.println("           joystick.style.transform = `translate3d(${temp_pos.x}px, ${temp_pos.y}px, 0px)`;");
    _client.println("         }");
    _client.println("       }");
    _client.println("       document.addEventListener(\"keypress\", handleKeyPress, true);");
    _client.println("       joystick_container.addEventListener('mousedown', handleDown);");
    _client.println("       joystick_container.addEventListener('touchstart', handleDown);");
    _client.println("       document.addEventListener('mousemove', handleMove, {passive: false});");
    _client.println("       document.addEventListener('touchmove', handleMove, {passive: false});");
    _client.println("       document.addEventListener('mouseup', handleUp);");
    _client.println("       document.addEventListener('touchend', handleUp);");
    _client.println("       }");
    _client.println("     }");
  }

  // Make a JS joystick instance for each joystick
  _client.print("joystick");
  _client.print(ID);
  _client.print(" = new JoystickController(\"");
  _client.print(ID);
  _client.println("\");");

  _client.println("window.setInterval(function(){");
  _client.print("joystick");
  _client.print(ID);
  _client.print(".ConstantActivePoll();");
  _client.println("}, (1000/POLLING_RATE)/2);");
}


void TinyHTMLJoystick::SendJoystickHTMLToClient(WiFiClient &_client){
  _client.print("<div class=container>");
  _client.print("<div id=");                        // Start div tag and id for joystick container
  _client.print(ID);                                // Insert user defined element ID for joystick container
  _client.print("C style=background-color:");       // Add ID modifier and start style and user defined background/outline color
  _client.print(backgroundColor);                   // Insert user defined background/outline color
  _client.print(";border-style:solid;");            // Start joystick border parameters
  _client.print(";border-width:0.65vw;");           // Start joystick border parameters
  _client.print(";border-color:");                  // Start joystick border parameters
  _client.print(outlineColor);                      // Insert the user defined joystick border/outline color
  _client.print(";width:");                         // Start user defined width style parameter
  _client.print(sizePercentage);                    // Insert user defined width size percentage
  _client.print("%;height:0;padding-bottom:");      // End width percentage, make height 0, start user defined bottom padding
  _client.print(sizePercentage);                    // Insert user defined bottom padding (this together with width scale aspect ratio as uniform)
  
  // End padding size percentage, and trial and error style paramters to make joystick stay centered
  _client.print("%;border-radius:50%;display:flex;align-items:center;justify-content:center;overflow:hidden;touch-action:none;>");

  _client.print("<div id=");                        // Start div tag and id for joystick
  _client.print(ID);                                // Insert user defined element ID for joystick
  _client.print(" style=background-color:");        // Start style and user defined background/outline color fro joystick
  _client.print(joystickColor);                     // Insert user defined joystick color
  _client.print(";width:");                         // Start user defined width style parameter
  _client.print(joystickSizePercentage);            // Insert user defined width size percentage for joystick
  _client.print("%;height:0;padding-bottom:");      // End width percentage, make height 0, start user defined bottom padding
  _client.print(joystickSizePercentage);            // Insert user defined bottom padding (this together with width scale aspect ratio as uniform) for joystick

  // End padding size percentage, and trial and error style paramters to make joystick stay centered
  _client.print("%;border-radius:50%;margin-top:100%;touch-action:none;user-select:none;>");
  _client.print("</div>");                          // End joystick container div for joystick
  
  _client.print("</div>");                          // End joystick container div for joystick container
  _client.print("</div>");
}
