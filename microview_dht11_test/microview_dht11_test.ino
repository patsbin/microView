#include <DHT.h>
#include <MicroView.h>

#define DHTPIN 2     
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

MicroViewWidget *Temperature, *Humidity;
void setup()
{
  Serial.begin(9600);
  Serial.println("DHTxx test!");

  dht.begin();
  
  uView.begin();
  uView.clear(PAGE);
  Temperature= new MicroViewGauge(15,30,0,100);
  Humidity= new MicroViewGauge(48,30,0,100);
  
}

void loop()
{
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature();

   // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  else {
    Temperature->setValue(t); // give a value to widget
    Humidity->setValue(h);
    uView.setCursor(0,0);
    uView.print("  t    h %");
    uView.circle(21,1,1);
    uView.display(); // display current page buffer
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
}

