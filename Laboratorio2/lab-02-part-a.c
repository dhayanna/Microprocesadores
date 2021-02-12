const int PB_UP   = 2;
const int PB_DOWN = 3;
const int LED0    = 4;
const int LED1    = 5;
const int LED2    = 6;
const int LED3    = 7;
const int LED4    = 8;
const int LED5    = 9;

void setup()
{
  pinMode(LED0,  OUTPUT);
  pinMode(LED1,  OUTPUT);
  pinMode(LED2,  OUTPUT);
  pinMode(LED3,  OUTPUT);
  pinMode(LED4,  OUTPUT);
  pinMode(LED5,  OUTPUT);
  pinMode(PB_UP,  INPUT);
  pinMode(PB_DOWN,INPUT);
}

uint16_t counter = 0;
int cond = 1;

void loop()
{
  if(digitalRead(PB_DOWN))
  {
    counter --;
    cond = 0;
  }
  else
  {
    counter++;
    cond = 1;
  }

  if(counter == 64 &&  cond) counter = 0;
  if(counter == 0  && !cond) counter = 64;

  int arreglo[6] = {0,0,0,0,0,0};
  int i = 5;
  int num = counter;

  while(num!=0){
      arreglo[i] = num%2;
      num /= 2;
      i--;
  }

  digitalWrite(LED0, arreglo[5]);
  digitalWrite(LED1, arreglo[4]);
  digitalWrite(LED2, arreglo[3]);
  digitalWrite(LED3, arreglo[2]);
  digitalWrite(LED4, arreglo[1]);
  digitalWrite(LED5, arreglo[0]);

  delay(250);

}
