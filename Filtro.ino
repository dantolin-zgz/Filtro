#define IN  A0
#define OUT 11

const float VrefADC = 5.0;
const int   NbitsADC = 2^10;
const int   NbitsDAC = 2^8;
const float VrefDAC = 5.0;
const int   fc = 100; //Hz
const int   T = 10 * fc;

float Xk;
float Yk;
float Xk_1 = 0.0;
float Yk_1 = 0.0;
int   i = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(2000000);
  pinMode(OUT, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Xk = analogRead(IN) * (VrefADC / NbitsADC);
  //Xk=2.0*sin(i*6.28/360);
  Yk = 0.4665 * Xk_1 + 0.5335 * Yk_1;
  Xk_1 = Xk;
  Yk_1 = Yk;
  delayMicroseconds((unsigned int)T);
  
  // if (i>=360){
  //   i=0;
  // }else {
  //   i+=1;
  // }
  
  Serial.print(Xk);
  Serial.print(",");
  Serial.println(Yk);
  analogWrite(OUT, (unsigned int)Yk * (NbitsDAC / VrefDAC));
}
