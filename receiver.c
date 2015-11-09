/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x64 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

//	Need to check what I can remove for comments and still satasfy the 
//	license. 




//	Jacob Turcotte and Samuel Wallace
//	Receiver program
//	At this moment in time, the display works. Figuring out how to
//	make each word (Flange), (Tremolo), (Flange + Tremolo) work. 
//	Possibly display both and just highlight the ones that are present?

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>		//These two libraries are needed to make display work
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
#define CLOSED LOW
#define OPEN HIGH
Adafruit_SSD1306 display(OLED_RESET);

//The following adafruit display is to comply with licensing.
display.display();
delay(500);


// NEED TO SET PINS
int a = 13; 		// Pin for tremolo
int b =  12;		// Pin for Flange
int c = 11;			// Pin for both effects
int d = 0; 			// Relay D
int e = 0; 			// Relay E
int effect = 0;		// Effect variable
int fl = 0; 		// Flag variable


void setup()   {  

	//Begin Serial comms at default of BT device
	Serial.begin(9600);

	// Screen init
  	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x64)
  	
  
  	// Set all relay pins to outputs
	pinMode(a, OUTPUT);
 	pinMode(b, OUTPUT);
 	pinMode(c, OUTPUT);
 	pinMode(d, OUTPUT);
 	pinMode(e, OUTPUT);


	// Set all relays to open when starting out
	// The relays are active low. Set pins high to turn them off.
 	digitalWrite(a, OPEN);
 	digitalWrite(b, OPEN);
 	digitalWrite(c, OPEN);
 	digitalWrite(d, OPEN);
 	digitalWrite(e, OPEN);

  	// Clear the display
  	display.clearDisplay();

  	// Display 
  	display.setTextSize(2);			//	Sets larger font
  	display.setTextColor(WHITE);	//	Doesn't matter too much. Color decided by location
  	display.setCursor(0,16);		//	Sets cursor below yellow part of display
  	display.println("Flange");		//	Display Flange
  	display.setTextSize(2);			//	Same size as before
  	display.setTextColor(WHITE);	//	Doesn't matter too much. Color decided by location
  	display.println("Tremolo");		//	Tremolo
 	display.display();
  	delay(1000);

}
 
void loop() {
	//Possibly add an empty while loop for when no input?


 	if(Serial.available() > 0){
 		effect = Serial.read();
 		fl = 0;			
 	}

	switch (effect){
	
	// Input 0 clears effects
 		case '0': {
 			digitalWrite(a, OPEN);
 			digitalWrite(b, OPEN);
 			digitalWrite(c, OPEN);
 			digitalWrite(d, OPEN);
 			digitalWrite(e, CLOSED);

 			if(fl == 0){	
 				Serial.println("Clean");
 				fl = 1;		
 			}
 		}

 		// Input 1 sets Tremolo only
 		case '1': {
 			digitalWrite(a, CLOSED);
 			digitalWrite(b, OPEN);
 			digitalWrite(c, OPEN);
 			digitalWrite(d, CLOSED);
 			digitalWrite(e, OPEN);

 			if(fl == 0){	
 				Serial.println("Tremolo");
 				fl = 1;		
 			}
 		}

 		case '2': {
 			digitalWrite(a, OPEN);
 			digitalWrite(b, CLOSED);
 			digitalWrite(c, OPEN);
 			digitalWrite(d, OPEN);
 			digitalWrite(e, OPEN);

 			if(fl == 0){	
 				Serial.println("Flange");
 				fl = 1;		
 			}
 		}

 		case '3': {
 			digitalWrite(a, CLOSED);
 			digitalWrite(b, OPEN);
 			digitalWrite(c, CLOSED);
 			digitalWrite(d, OPEN);
 			digitalWrite(e, OPEN);

 			if(fl == 0){	
 				Serial.println("Both Effects");
 				fl = 1;		
 			}
 		}
 	
 		default: {
 			if(fl == 0){	
 				Serial.println("Invalid. Enter 0-3");
 				fl = 1;
 			}
 		}
 	}  //End switch

 }
