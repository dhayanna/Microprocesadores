const int LED1 = 2;
const int PB = 4;

void setup()
{
  pinMode(LED1, OUTPUT);
  pinMode(PB, INPUT);
}

uint16_t counter1 = 0;
bool blink_led1 = false;

void loop()
{
  counter1++;
  
  if(counter1 >= 40 && !blink_led1){
    
    counter1 = 0;
    blink_led1 = true;
    
  } else if(counter1 >= 20 && blink_led1){
    
    counter1 = 0;
    blink_led1 = false;
    
  } 

  digitalWrite(LED1, blink_led1);
  delay(25);
  
}
