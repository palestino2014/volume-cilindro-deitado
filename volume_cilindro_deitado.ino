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

  //variaveis da equacao
  float a,b,c,d;
  //raio em metros
  double r = 1.375;
  //comprimento em metros
  float l = 6.250;
  // altura relativa do fluido, area da base, volume  
  double alt, aBase, volume; 
  float v[10];
  
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);

  // altura relativa do fluido e conversao para metros
  alt = ((r*2)-(cmMsec/100)); 

  //termos da equacao que calcula o volume
  a = pow(r,2);
  b = acos (1-(alt/r));
  c = sqrt ((2*alt*r)-(alt*alt)); 
  d = (r-alt);

  // area da base
  aBase = ((a*b)-(c*d));
  //volume 
  volume = (aBase*l);    
  
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

  // laço for para calibrar a leitura do volume - media de 10 medidas

  for (int i=0 ; i<= 10 ; i++){
    v[i]= volume;
    delay (500); 
    }

    float vFinal;
    vFinal = (v[0]+v[1]+v[2]+v[3]+v[4]+v[5]+v[6]+v[7]+v[8]+v[9])/10;
  
  //Limpa a tela
  lcd.clear();
  //Posiciona o cursor na coluna 3, linha 0;
  lcd.setCursor(0, 0);
  //Envia o texto entre aspas para o LCD
  lcd.print("Nivel =");
  lcd.print(alt);
  lcd.print(" m ");
  lcd.setCursor(0, 1);
  lcd.print("VOL = ");
  lcd.print(vFinal);
  lcd.print(" m3 ");
  delay(1000);   

}
