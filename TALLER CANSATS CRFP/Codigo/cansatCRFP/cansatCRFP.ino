/* Programa básico para el Taller CANSAT CLM 2019
 * Lee datos de presión atmosférica, temperatura y altitud barométrica de un BMP180,
 * lee latitud, longitud y altitud de un GPS Neo6M
 * y los envía a la estación de tierra via radio (APC220)
 * con una frecuencia de 1s.
 * César Rangil 
 * 12/12/2019
 */


#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>    //Librería del BMP180

SoftwareSerial radio(6, 7); // RX, TX   Radio APC220 
SoftwareSerial ss(4, 3);    // RX, TX   Recepción GPS Neo6M

Adafruit_BMP085 bmp;        // BMP180
TinyGPSPlus gps;            // GPS Neo6M

void setup() {
  Serial.begin(9600);
  radio.begin(9600);
  ss.begin(9600);
  radio.println("Comienza la transmisión via radio");
  if (!bmp.begin()) {
    radio.println("No se encuentra el sensor BMP180, comprueba la conexión!");
    Serial.println("No se encuentra el sensor BMP180, comprueba la conexión!");
  }
}

void loop() { // run over and over
    Serial.println(bmp.readTemperature());  // manda la temperatura al puerto serie por debugging
    
    /****** Comienza la transmisión por radio ******/
    radio.print(bmp.readTemperature());     // temperatura en ºC 
    radio.print(",\t");
    radio.print(bmp.readPressure()/100.0,2);    // Presión en hPa 
    radio.print(",\t ");
    radio.print(bmp.readAltitude(102110));  // Altitud barométrica en m 
    radio.print(",\t");
    radio.print(gps.location.lat(),6);      // Latitud GPS
    radio.print(",\t");
    radio.print(gps.location.lng(),6);      // Longitud GPS
    radio.print(",\t");
    radio.println(gps.altitude.meters());   // Altitud GPS
    /****** Fin de transimisón por radio ******/
    
    smartDelay(500);
}

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}
