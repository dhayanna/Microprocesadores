const int LED2 = 3;
const int PB = 4;

void setup()
{
  pinMode(LED2, OUTPUT);
  pinMode(PB, INPUT);
}

uint16_t counter2 = 0;
bool blink_led2 = false;

void loop()
{
  counter2++;
  
  
  int pb_val = digitalRead(4);
  
  
  if(!pb_val){
    
    if(counter2 >= 160){
      counter2 = 0;
      blink_led2 = !blink_led2;
    }
        
  } else {
    
    if(counter2 >= 30 && !blink_led2){
      counter2 = 0;
      blink_led2 = true;
    } else if (counter2 >= 10 && blink_led2){
      counter2 = 0;
      blink_led2 = false;
    }
    
  }
  
  digitalWrite(LED2, blink_led2);
  delay(25);
  
}
