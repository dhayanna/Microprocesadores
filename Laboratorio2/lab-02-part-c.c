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
int estado_anterior_up = 0;
int estado_anterior_down = 0;
int led = -1;
int out[] = {0,0,0,0,0,0};
  
void loop()
{  
  if(digitalRead(PB_UP) && !estado_anterior_up && led < 5)
  {
    led++;
    estado_anterior_up = 1;
  }
  else if(digitalRead(PB_DOWN) && !estado_anterior_down && led > -1)
  {
    led--;
    estado_anterior_down = 1;
  }
  
  if(!digitalRead(PB_DOWN)) estado_anterior_down = 0;
  if(!digitalRead(PB_UP))   estado_anterior_up   = 0;
  
  switch(led){
  case -1:
    out[5]=0; out[4]=0; out[3]=0; out[2]=0; out[1]=0; out[0]=0;
    break;  
  case 0:
    out[5]=1; out[4]=0; out[3]=0; out[2]=0; out[1]=0; out[0]=0;
    break;
  case 1:
    out[5]=1; out[4]=1; out[3]=0; out[2]=0; out[1]=0; out[0]=0;
    break;
  case 2:
    out[5]=1; out[4]=1; out[3]=1; out[2]=0; out[1]=0; out[0]=0;
    break;
  case 3:
    out[5]=1; out[4]=1; out[3]=1; out[2]=1; out[1]=0; out[0]=0;
    break;
  case 4:
    out[5]=1; out[4]=1; out[3]=1; out[2]=1; out[1]=1; out[0]=0;
    break;
  case 5:
    out[5]=1; out[4]=1; out[3]=1; out[2]=1; out[1]=1; out[0]=1;
    break;
  }
  
  digitalWrite(LED0, out[0]);
  digitalWrite(LED1, out[1]);
  digitalWrite(LED2, out[2]);
  digitalWrite(LED3, out[3]);
  digitalWrite(LED4, out[4]);
  digitalWrite(LED5, out[5]);
    
}
