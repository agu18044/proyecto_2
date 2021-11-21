// Adafruit IO Digital Output Example
// Tutorial Link: https://learn.adafruit.com/adafruit-io-basics-digital-output
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"

/************************ Example Starts Here *******************************/

// digital pin 5
#define LED_1 22
#define LED_2 23
#define LED_3 18
#define LED_4 19

// set up the 'digital' feed
AdafruitIO_Feed *feed0 = io.feed("skey");
AdafruitIO_Feed *feed1 = io.feed("wkey");
AdafruitIO_Feed *feed2 = io.feed("akey");
AdafruitIO_Feed *feed3 = io.feed("dkey");
void setup() {
  
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  
  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // set up a message handler for the 'digital' feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  feed0->onMessage(handleMessage);
  feed1->onMessage(handleMessage1);
  feed2->onMessage(handleMessage2);
  feed3->onMessage(handleMessage3);

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  feed0->get();
  feed1->get();
  feed2->get();
  feed3->get();

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

}

// this function is called whenever an 'digital' feed message
// is received from Adafruit IO. it was attached to
// the 'digital' feed in the setup() function above.
void handleMessage(AdafruitIO_Data *data) {
  
  Serial.print('\n');
  //Serial.println(data->value());

  if(data->toString() == "1"){
    Serial.println("LED VERDE ON");
    digitalWrite(LED_1, HIGH);
    }
  if(data->toString() == "0"){   //apaga el LED 
    digitalWrite(LED_1, LOW);  
    Serial.print("LED VERDE OFF");
    }   
}

void handleMessage1(AdafruitIO_Data *data) {

  Serial.print('\n');
  //Serial.println(data->value());

   if(data->toString() == "1"){      //enciende el LED 
    digitalWrite(LED_2, HIGH);
    Serial.print("LED ROJO ON");
    }
   
   if(data->toString() == "0"){   //apaga el LED 
    digitalWrite(LED_2, LOW);  
    Serial.print("LED ROJO OFF");
    }
}

void handleMessage2(AdafruitIO_Data *data) {

  Serial.print('\n');

   if(data->toString() == "1"){      //enciende el LED 
    digitalWrite(LED_4, HIGH);
    Serial.print("LED AMARILLO ON");
    }
   
   if(data->toString() == "0"){   //apaga el LED 
    digitalWrite(LED_4, LOW);  
    Serial.print("LED AMARILLO OFF");
    }
}

void handleMessage3(AdafruitIO_Data *data) {

  Serial.print('\n');

   if(data->toString() == "1"){      //enciende el LED 
    digitalWrite(LED_3, HIGH);
    Serial.print("LED AZUL ON");
    }
   
   if(data->toString() == "0"){   //apaga el LED 
    digitalWrite(LED_3, LOW);  
    Serial.print("LED AZUL OFF");
    }
}
