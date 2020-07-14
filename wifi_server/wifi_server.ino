// Creates a Wifi server to upload temperature data readings

#include <SPI.h>
#include <WiFi.h>

char ssid[] = "me";  	      //  your network SSID (name)
char pass[] = "anindo4567";   // your network password
int keyIndex = 0;             // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;
WiFiServer server(80);

#ifdef __cplusplus
extern "C" {
#endif
uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif

uint8_t temprature_sens_read();

void setup() {
  Serial.begin(115200);  	// initialize serial communication
  WiFi.begin(ssid, pass);
  // attempt to connect to Wifi network:
  while (WiFi.status() != WL_CONNECTED) {
	Serial.print("Attempting to connect to Network named: ");
	Serial.println(ssid);               	// print the network name (SSID);

	// Connect to WPA/WPA2 network. Change this line if using open or WEP network:
	//status =
	// wait 1 seconds for connection:
	delay(1000);
  }
  server.begin();                       	// start the web server on port 80
  printWifiStatus();                    	// you're connected now, so print out the status
}

void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                         	// if you get a client,
	Serial.println("new client");       	// print a message out the serial port
	String currentLine = "";            	// make a String to hold incoming data from the client
	while (client.connected()) {        	// loop while the client's connected
  	if (client.available()) {         	// if there's bytes to read from the client,
    	char c = client.read();         	// read a byte, then
    	Serial.write(c);                	// print it out the serial monitor
    	if (c == '\n') {                	// if the byte is a newline character

      	// if the current line is blank, you got two newline characters in a row.
      	// that's the end of the client HTTP request, so send a response:
      	if (currentLine.length() == 0) {
        	// HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
        	// and a content-type so the client knows what's coming, then a blank line:
        	client.println("HTTP/1.1 200 OK");
        	client.println("Content-type:text/html");
        	client.println();

        	// the content of the HTTP response follows the header:
        	//client.print("Click <a href=\"/H\">here</a> turn the LED on pin 2 on<br>");
        	//client.print("Click <a href=\"/L\">here</a> turn the LED on pin 2 off<br>");
        	client.print("Temperature of the sensor: ");
        	client.print((temprature_sens_read()-32)/1.8);
        	// The HTTP response ends with another blank line:
        	client.println();
        	// break out of the while loop:
        	break;
      	} else {	// if you got a newline, then clear currentLine:
        	currentLine = "";
      	}
    	} else if (c != '\r') {  // if you got anything else but a carriage return character,
      	currentLine += c;  	// add it to the end of the currentLine
    	}

    	}
	}
	// close the connection:
	client.stop();
	Serial.println("client disonnected");
  }
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}
