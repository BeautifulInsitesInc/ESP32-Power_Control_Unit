//#include <DallasTemperature.h> // For DS18B20 Water tempurature sensor
#include <DHT.h> // Humidity and tempurature sensor

float convertCtoF(float c){float f = c*1.8 + 32;return f;} // Convert default C into F


// ========== DHT Sensor ==============================
#define DHTTYPE DHT11   // DHT 11
DHT dht(dht_pin, DHTTYPE); // Currently pin 13

void dhtSetup(){
  dht.begin(); // initialize humidity sensor
  //dhtDelayTimer.start(dht_delay*1000); // Start the delay between readings
  //pinMode(dht_pin, INPUT_PULLUP);
  dht_timer_start = millis();

}

void getDHTReadings(){
  if(millis() >= dht_timer_start + (dht_timer_period*1000)){
    if (isnan(dht.readTemperature())){
      dht_tempC = 0;
      dht_tempF = 0;
    }
    else {
      dht_tempC = dht.readTemperature();
      dht_tempF = dht.readTemperature(true);
    }
    if (isnan(dht.readHumidity())) dht_humidity = 0;
    else dht_humidity = dht.readHumidity();
  

    // --- debugging ----
    tout("DHT Temp = C:"); tout(dht_tempC); tout("       F: "); tout(dht_tempF); tout("       Humidity = "); tout(dht_humidity); toutln("%");
    // --- end debugging ---
    dht_timer_start = millis();
  }
}
 
