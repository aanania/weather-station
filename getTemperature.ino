#include <DHT.h>
#define DHTTYPE DHT11
#define DHTPIN  2

DHT dht(DHTPIN, DHTTYPE, 11); // 11 works fine for ESP8266
float humidity, temp_c;  // Values read from sensor

void gettemperature() {
  // Reading temperature for humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (it's a very slow sensor)
  humidity = dht.readHumidity();          // Read humidity (percent)
  temp_c = dht.readTemperature(false);     // Read temperature as Celsius
  
  Serial.println(humidity, DEC);
  Serial.println(temp_c, DEC);
  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temp_c)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
}

float FarToCel(float farenheit){
  return(farenheit - 32.)*5/9;
}

void setup() {
  Serial.begin(115200); 
  dht.begin();           // initialize temperature sensor
}

// the loop function runs over and over again forever
void loop() {
  gettemperature(); 
  Serial.println("Hola");
  delay(1000);                       // wait for a second
}
