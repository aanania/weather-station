#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <InfluxDb.h>
#include <DHT.h>
#define DHTTYPE DHT11
#define DHTPIN  2
#define INFLUXDB_HOST "192.168.0.32"
const char* ssid     = "YourRouterID";
const char* password = "YourRouterPassword";

//Global variables initialization
DHT dht(DHTPIN, DHTTYPE, 11); // 11 works fine for ESP8266
float humidity, temp_c;  // Values read from sensor
Influxdb influx(INFLUXDB_HOST);

void gettemperature() {
  // Reading temperature for humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (it's a very slow sensor)
  humidity = dht.readHumidity();          // Read humidity (percent)
  temp_c = dht.readTemperature();     // Read temperature as Celsius
  
  Serial.println(humidity, DEC);
  Serial.println(temp_c, DEC);
  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temp_c)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
}

void setup() {
  Serial.begin(115200); 
  dht.begin();           // initialize temperature sensor

  // Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.print("\n\r \n\rWorking to connect");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("DHT Weather Station Logging");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  influx.setDb("test");
  Serial.println("Setup done");
}

// the loop function runs over and over again forever
void loop() {
  gettemperature();
  InfluxData row("weather");
  row.addTag("room", "plants");
  row.addTag("sensor", "one");
  row.addValue("temperature", temp_c);
  row.addValue("humidity", humidity);
  influx.write(row);
  delay(5000);                       // wait for 5 seconds
}
