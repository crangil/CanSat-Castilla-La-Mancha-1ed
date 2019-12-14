/*
  Visualiza en monitor serie el valor de temperatura leido por un termistor
  tipo NTC en configuracion de divisor de tension con resistencia de 1 K.
  Se aplica la ecuacion de Steinhart-Hart y sus coeficientes mediante
  la pagina web indica en el comentario.
*/

int Vo, presionValor;
float R1 = 1000;              // resistencia fija del divisor de tension 
float logR2, R2, TEMPERATURA;
float presion;
float c1 = 2.229674985e-03, c2 = 1.211871252e-04, c3 = 8.713435086e-07;
// coeficientes de S-H en pagina: 
// http://www.thinksrs.com/downloads/programs/Therm%20Calc/NTCCalibrator/NTCcalculator.htm

void setup() {
Serial.begin(9600);   // inicializa comunicacion serie a 9600 bps
}

void loop() {
  Vo = analogRead(A0);      // lectura de A0
  presionValor=analogRead(A1);
  presion=((presionValor/1024.0)+0.095)/0.0009;
  R2 = R1 * (1023.0 / (float)Vo - 1.0); // conversion de tension a resistencia
  logR2 = log(R2);      // logaritmo de R2 necesario para ecuacion
  TEMPERATURA = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));   // ecuacion S-H
  TEMPERATURA = TEMPERATURA - 273.15;   // Kelvin a Centigrados (Celsius)

  Serial.print("Temperatura: ");  // imprime valor en monitor serie
  Serial.print(TEMPERATURA);
  Serial.print(" C         "); 
  Serial.print("Presion: ");  // imprime valor en monitor serie
  Serial.print(presion);
  Serial.println(" hPa"); 
  delay(500);       
}
