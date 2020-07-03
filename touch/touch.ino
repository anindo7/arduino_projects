//Turns the LED on when sensor is touched

#define TOUCH T0
#define LED 2

int touch_value=100;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Touch test");
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
   touch_value=touchRead(TOUCH);
   if(touch_value<50){
  	digitalWrite(LED, HIGH);
  	Serial.println(touch_value);}
   else
  	digitalWrite(LED, LOW);
   //delay(3000);
}

