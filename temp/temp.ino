//Records temperature readings of the sensor every 3s

#ifdef __cplusplus
extern "C" {
#endif
uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif

uint8_t temprature_sens_read();

void setup()
{
Serial.begin(9600);

}


void loop()
{

	Serial.print("Temperature of the sensor: ");
	Serial.println((temprature_sens_read()-32)/1.8);
	delay(3000);

}
