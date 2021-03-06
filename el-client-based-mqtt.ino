#include <ELClient.h>
#include <ELClientCmd.h>
#include <ELClientMqtt.h>

// Initialize a connection to esp-link using the normal hardware serial port both for
// SLIP and for debug messages.
ELClient esp(&Serial, &Serial);

// Initialize CMD client (for GetTime)
ELClientCmd cmd(&esp);

// Инициализация MQTT клиента
ELClientMqtt mqtt(&esp);

// Callback made from esp-link to notify of wifi status changes
// Here we just print something out for grins
void wifiCb(void* response) {
  ELClientResponse *res = (ELClientResponse*)response;
  if (res->argc() == 1) {
    uint8_t status;
    res->popArg(&status, 1);

    if(status == STATION_GOT_IP) {
      Serial.println("WIFI CONNECTED");
    } else {
      Serial.print("WIFI NOT READY: ");
      Serial.println(status);
    }
  }
}

bool connected;

// Callback when MQTT is connected
void mqttConnected(void* response) {
  Serial.println("MQTT connected!");
//  mqtt.subscribe("/esp-link/1");
   mqtt.subscribe("/hello/world/test");
   connected = true;
}

// Подпрограмма, вызываемая, когда MQTT клиент разъединяется
void mqttDisconnected(void* response) {
  Serial.println("MQTT disconnected");
  connected = false;
}

// Callback when an MQTT message arrives for one of our subscriptions
void mqttData(void* response) {
  ELClientResponse *res = (ELClientResponse *)response;

  Serial.print("Received: topic=");
  String topic = res->popString();
  Serial.println(topic);

  Serial.print("data=");
  String data = res->popString();
  Serial.println(data);
  
 int peremen = data.toInt();
 analogWrite(10,peremen);
     
  
/*     if(data == "1")
     {
     analogWrite(10,125);
       Serial.println("SIGNAL ON 10 PIN IS 2.5 VOLTS");
          mqtt.publish("/hello/world/led", "Led is on!");
          }
     else
     {
       analogWrite(10,0);
       Serial.println("SIGNAL ON 10 PIN IS 0 VOLTS.");
       mqtt.publish("/hello/world/led", "Led is off!");
       Serial.println("LED is off now!");
     }
*/
  
}

void mqttPublished(void* response) {
  Serial.println("MQTT published");
}

void setup() {
  

     
  pinMode(13, OUTPUT);
  pinMode(15, INPUT);
  pinMode(10, OUTPUT);
  Serial.begin(57600);
  Serial.println("EL-Client starting!");

  // Sync-up with esp-link, this is required at the start of any sketch and initializes the
  // callbacks to the wifi status change callback. The callback gets called with the initial
  // status right after Sync() below completes.
  esp.wifiCb.attach(wifiCb); // wifi status change callback, optional (delete if not desired)
  bool ok;
  do {
    ok = esp.Sync();      // sync up with esp-link, blocks for up to 2 seconds
    if (!ok) Serial.println("EL-Client sync failed!");
  } while(!ok);
  Serial.println("EL-Client synced!");
  
 
  // Set-up callbacks for events and initialize with es-link.
  mqtt.connectedCb.attach(mqttConnected);
  mqtt.disconnectedCb.attach(mqttDisconnected);
  mqtt.publishedCb.attach(mqttPublished);
  mqtt.dataCb.attach(mqttData);
  mqtt.setup();

  //Serial.println("ARDUINO: setup mqtt lwt");
  //mqtt.lwt("/lwt", "offline", 0, 0); //or mqtt.lwt("/lwt", "offline");

  Serial.println("EL-MQTT ready");
}

static int count;
static uint32_t last;

 
  

void loop() {
  esp.Process();

  if (connected && (millis()-last) > 4000) {
//    Serial.println("publishing");
//    char buf[12];

//    itoa(count++, buf, 10);
//    mqtt.publish("/esp-link/1", buf);

    //itoa(count+99, buf, 10);
    //mqtt.publish("/hello/world/arduino", buf);
    
                
 //   uint32_t t = cmd.GetTime();
 //   Serial.print("Time: "); Serial.println(t);
     
   
     //int temperature;
     //temperature = analogRead(15);
     //String myString = String(temperature);
   
    
    //char msgBuffer[5];           
    //float testFloat = AnalogRead(15);
    //mqtt.publish("/home/water", dtostrf(testFloat, 3, 0, msgBuffer));
    
    //char temperature[ ] = "23";
      //     Serial.println("SENSOR VALUE:"); Serial.println(temp);
      // mqtt.publish("/home/water", temperature);

    last = millis();
  }
}
