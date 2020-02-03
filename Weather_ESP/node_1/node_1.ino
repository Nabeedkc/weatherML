#include <WiFiUdp.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)
/* Connection for BME/BMP280:
 *  VIN: 3.3V 
 *  SCL: D1 of ESP
 *  SDA: D2 of ESP
 */
 
Adafruit_BME280 bme;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 19800);


String temperature, humidity, pressure, altitude, timestamp;
const char* ssid = "Redmi";
const char* password = "";

void setup()
{
  Serial.begin(115200);
  delay(100);
  bme.begin(0x76);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
  }
  Serial.print("Connected");
  timeClient.begin();

}
void loop()
{
  timeClient.update();
  timestamp= timeClient.getFormattedDate();
  temperature = String(bme.readTemperature());
  humidity = String(bme.readHumidity());
  pressure = String(bme.readPressure() / 100.0F);
  altitude = String(bme.readAltitude(SEALEVELPRESSURE_HPA));
  send_data(timestamp,temperature,humidity,pressure,altitude);
  delay(600000);

}


int send_data(String dates, String temp, String humi, String presr, String alti)
{
  String data= "timestamp="+dates+"&temperature="+temp+"&humidity="+humi;
  if(WiFi.status()== WL_CONNECTED)
  {
    HTTPClient http;
    http.begin("http://192.168.43.57/weather/Plot/weather_api.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int code = http.POST(data);
    String resp = http.getString();
    //Serial.println(code);
    //Serial.println(resp);
    http.end();
    
  }
}
