
#include <Ultrasonic.h>
#include <math.h>

//Define os pinos para o trigger e echo
#define pino_trigger 4
#define pino_echo 5

//Constantes matematicas
float a,b,c,d,alt,a_base,v;
float pi = 3.14;
float r = 1.35;
float l = 6.06;
  
//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(pino_trigger, pino_echo);

void setup()
{
  Serial.begin(9600);
  Serial.println("Lendo dados do sensor...");  
}

void loop()
{
  float cmMsec, inMsec, meMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);  

  meMsec = cmMsec/100; // medida em metros
  alt = (2*r)-meMsec;
 //Calculo da altura do fluido 
  
 a = ((pi*(pow(r,2)))/2);
 b = (pow(r,2))*(asin((r-alt)/alt));
 c = (alt-r);
 d = sqrt((r*r)-((alt-r)*(alt-r)));

 a_base = (a)-(b)+(c*d); // area da base baseado na integral

 v = a_base*l;
 //Le as informacoes do sensor, em cm e pol
 
 cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
 inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);
  
 //Exibe informacoes no serial monitor
 Serial.print("DF [cm] ");
 Serial.print(cmMsec);
 Serial.print(" - DF [m] ");
 Serial.print(meMsec);
 Serial.print(" AF [m] ");
 Serial.print(alt);
 Serial.print(" AB ");
 Serial.print(a_base);
 Serial.print(" Volume [m3]");
 Serial.println(v);
 Serial.println(a);
 Serial.println(b);
 Serial.println(c);
 Serial.println(d);
  
 delay(2000);
}
