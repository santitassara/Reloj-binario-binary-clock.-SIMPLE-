// 24Hs Reloj Binario con segundero Arduino ATMEGA328p.  Arduino 24h Binary Clock with Seconds. (17 LEDs total)


 

// pins 2 - 13  son los tipicos pins pwm. / are the regular digital pwm pins.
int ledPinsSec[] = {0, 0, 0, 0, 0, 0};
int ledPinsMin[] = {8, 9, 10, 11, 12, 13};

// pins 14 - 20 son los pins analogicos. / are the analog pins.   0 - 5  son usados como pins pwm digitales. / used as digital pwm pins  
int ledPinsHr[] = {14, 15, 16, 17, 18, 19};

//Seteo de tiempo de inicio / set Start time here
int countS = 0;   // Seconds
int countM = 59;  // Minutes
int countH = 23;  // Hours


int buzz = 5;


int pulsador_minutos = 7;
int pulsador_horas = 6;

int estado_minutos = 0;
int estado_horas = 0;

int estado_buzz = 0;

byte countSec;
byte countMin;
byte countHr;
#define nBitsSec sizeof(ledPinsSec)/sizeof(ledPinsSec[0])
#define nBitsMin sizeof(ledPinsMin)/sizeof(ledPinsMin[0])
#define nBitsHr sizeof(ledPinsHr)/sizeof(ledPinsHr[0])





void setup(void)
{

Serial.begin(9600);
pinMode(pulsador_minutos, INPUT);
pinMode(pulsador_horas, INPUT);
pinMode(buzz, OUTPUT);



  for (byte i = 0; i < nBitsSec; i++) {
    pinMode(ledPinsSec[i], OUTPUT);
  }

  for (byte i = 0; i < nBitsMin; i++) {
    pinMode(ledPinsMin[i], OUTPUT);
  }

  for (byte i = 0; i < nBitsHr; i++) {
    pinMode(ledPinsHr[i], OUTPUT);
  }
}

// ----- Main Routine -------------------------------------------------

void loop(void)
{
  
//minutos = digitalRead(pulsador_minutos);
estado_horas = digitalRead(pulsador_horas);
estado_minutos = digitalRead(pulsador_minutos);
estado_buzz = digitalRead(buzz);

if ((estado_minutos == HIGH) && (estado_horas == HIGH ))  {

        countH = 0;
        countM = 0;
        countS = 0;
}
 

  
//Serial.println(estado_minutos);
Serial.println(countM);
if ((estado_minutos  == HIGH) && (estado_horas == LOW))
 
{ 
  countM  ++ ;
  countS = 0;
  estado_minutos = 0;

     if (countM > 59)
    {
      countM = 0;
      countH = (countH + 1);
      tone(buzz, 1000);
      delay(50);
      noTone(buzz);
      delay(50);
      tone(buzz, 1100);
      delay(50);
      noTone(buzz);
      delay(50);
      tone(buzz, 1200);
      delay(50);
      noTone(buzz);

      
      
      if (countH > 23)
      {
        countH = 0;
        countM = 0;
        countS = 0;
      }
    }
}
Serial.println(estado_horas);
Serial.println(countH);

if ((estado_horas  == HIGH) && (estado_minutos == LOW))
 
{ 
 countH  ++ ;
  //countM = 0;
  estado_horas = 0;
   if (countH > 23)
      {
        countH = 0;
        countM = 0;
        countS = 0;
      }

}
  

  
  countS = (countS + 1);
  if (countS > 59)
  {
    countS = 0;
    countM = (countM + 1);
    
    if (countM > 59)
    {
      countM = 0;
      countH = (countH + 1);
        tone(buzz, 1000);
      delay(50);
      noTone(buzz);
      delay(50);
      tone(buzz, 1100);
      delay(50);
      noTone(buzz);
      delay(50);
      tone(buzz, 1200);
      delay(50);
      noTone(buzz);
      
      if (countH > 23)
      {
        countH = 0;
        countM = 0;
        countS = 0;
      }
    }
  }

  dispBinarySec(countS);
  dispBinaryMin(countM);
  dispBinaryHr(countH);




  delay(1000);   // 1000 milisegundos = aproximado 1 segundo de delay / milliseconds = approx. 1 second delay
  // AJUSTABLE PARA MAS RAPIDO O LENTO FUNCIONAMIENTO DEL RELOJ EN MILISEGUNDOS. / ADJUST for fast or slow running clock here, in milliseconds.


  
}

// ----- Subroutines ---------------------------------------------------

void dispBinarySec(byte nSec)
{
  for (byte i = 0; i < nBitsSec; i++) {
    digitalWrite(ledPinsSec[i], nSec & 1);
    nSec /= 2;
  }
}

void dispBinaryMin(byte nMin)
{
  for (byte i = 0; i < nBitsMin; i++) {
    digitalWrite(ledPinsMin[i], nMin & 1);
    nMin /= 2;
  }
}

void dispBinaryHr(byte nHr)
{
  for (byte i = 0; i < nBitsHr; i++) {
    digitalWrite(ledPinsHr[i], nHr & 1);
    nHr /= 2;
  }
}
