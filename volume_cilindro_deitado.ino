//Carrega a biblioteca LiquidCrystal
#include <LiquidCrystal.h>
#include <Ultrasonic.h>
#include <math.h>


//Define os pinos para o trigger e echo
#define pino_trigger 6
#define pino_echo 7

//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(pino_trigger, pino_echo);
 
//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
 
void setup()
{
  //Define o número de colunas e linhas do LCD
  lcd.begin(16, 2);
  Serial.begin(9600);
  Serial.println("Lendo dados do sensor...");
}
 
void loop()
{
   //Le as informacoes do sensor, em cm e pol
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();
  float a,b,b1,b2,c,d,h;
  double r = 1.375;
  float l = 6.250;  
  double alt, aBase, volume;  
  double f1, f2; 
  
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);

  alt = ((r*2)-(cmMsec/100));

  b2=0;
  a = pow(r,2);
  b = acos (1-(alt/r));
  c = sqrt ((2*alt*r)-(alt*alt)); 
  d = (r-alt);
  

  f1 = PI/180;
  f2 = 180/PI;

  double  trigo , teste , teta = ((30*PI)/180);    
  trigo = sin((r-alt)/alt);
  teste = (r-alt)/alt;
  
  aBase = (a)*(b)-(c*d);
  volume = (aBase*l);  

  //Serial.print("equacao trigonometrica ");
  //Serial.println(trigo); 
  //Serial.print("ardumento da equacao ");
  //Serial.println(teste);
  
  
  //Exibe informacoes no serial monitor
  Serial.print("Distancia em cm: ");
  Serial.println(cmMsec);
  Serial.print("Altura relativa do Fluido: ");
  Serial.println(alt);  
  Serial.print("Termo A: ");
  Serial.println(a);
  Serial.println(b);
  Serial.print("Termo C:");
  Serial.println(c);
  Serial.print("Termo D:");
  Serial.println(d);
  Serial.print("Area da Base:");
  Serial.println(aBase);
  Serial.print("Volume:");
  Serial.println(volume);
  Serial.println("================");
  
  //Limpa a tela
  lcd.clear();
  //Posiciona o cursor na coluna 3, linha 0;
  lcd.setCursor(3, 0);
  //Envia o texto entre aspas para o LCD
  lcd.print("NIVEL=");
  lcd.print(alt);
  lcd.setCursor(3, 1);
  lcd.print("vol=");
  lcd.print(volume);
  delay(2000);   

}
