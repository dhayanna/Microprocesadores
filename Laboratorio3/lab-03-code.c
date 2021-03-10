#define ANALOG_INPUT A0
#define PB 16
#define VER_VOLTAJE 0
#define VER_RESISTENCIA 1
#define VER_ADC 2
#define V_REF 5.0

#define SEGMENT_A 2
#define SEGMENT_B 3
#define SEGMENT_C 4
#define SEGMENT_D 5
#define SEGMENT_E 6
#define SEGMENT_F 7
#define SEGMENT_G 8
#define SEGMENT_DP 9
#define DIGIT_0 13
#define DIGIT_1 12
#define DIGIT_2 11
#define DIGIT_3 10
#define REFRESH_DELAY 1

uint8_t segment_pings[8] = {
  SEGMENT_A,
  SEGMENT_B,
  SEGMENT_C,
  SEGMENT_D,
  SEGMENT_E,
  SEGMENT_F,
  SEGMENT_G,
  SEGMENT_DP
};

uint8_t digit_cathodes[4] = {
  DIGIT_0,
  DIGIT_1,
  DIGIT_2,
  DIGIT_3
};

void ssd_output_code(uint8_t num, uint8_t digit) {
  uint8_t code;
  switch (num) {
  case 0:
    code = 0x3F;
    break;
  case 1:
    code = 0x06;
    break;
  case 2:
    code = 0x5B;
    break;
  case 3:
    code = 0x4F;
    break;
  case 4:
    code = 0x66;
    break;
  case 5:
    code = 0x6D;
    break;
  case 6:
    code = 0x7D;
    break;
  case 7:
    code = 0x07;
    break;
  case 8:
    code = 0x7F;
    break;
  case 9:
    code = 0x6F;
    break;  
  case 10: // 0.
    code = 0xBF;
    break;
  case 11: // 1.
    code = 0x86;
    break;
  case 12: // 2.
    code = 0xDB;
    break;
  case 13: // 3.
    code = 0xCF;
    break;
  case 14: // 4.
    code = 0xE6;
    break;
  case 15: // 5.
    code = 0xED;
    break;
  case 16: // 6.
    code = 0xFD;
    break;
  case 17: // 7.
    code = 0x87;
    break;
  case 18: // 8.
    code = 0xFF;
    break;
  case 19: // 9.
    code = 0xEF;
    break;
  default:
    code = 0x80;
    break;
  }

  bool segments[8];
  segments[0] = (code & (1 << 0)) != 0;
  segments[1] = (code & (1 << 1)) != 0;
  segments[2] = (code & (1 << 2)) != 0;
  segments[3] = (code & (1 << 3)) != 0;
  segments[4] = (code & (1 << 4)) != 0;
  segments[5] = (code & (1 << 5)) != 0;
  segments[6] = (code & (1 << 6)) != 0;
  segments[7] = (code & (1 << 7)) != 0;

  bool digits[4];
  digits[0] = digits[1] = digits[2] = digits[3] = HIGH;
  digits[digit] = LOW;
   
  digitalWrite(DIGIT_0, HIGH);
  digitalWrite(DIGIT_1, HIGH);
  digitalWrite(DIGIT_2, HIGH);
  digitalWrite(DIGIT_3, HIGH);
  
  digitalWrite(SEGMENT_A, segments[0]);
  digitalWrite(SEGMENT_B, segments[1]);
  digitalWrite(SEGMENT_C, segments[2]);
  digitalWrite(SEGMENT_D, segments[3]);
  digitalWrite(SEGMENT_E, segments[4]);
  digitalWrite(SEGMENT_F, segments[5]);
  digitalWrite(SEGMENT_G, segments[6]);
  digitalWrite(SEGMENT_DP, segments[7]);

  digitalWrite(DIGIT_0, digits[0]);
  digitalWrite(DIGIT_1, digits[1]);
  digitalWrite(DIGIT_2, digits[2]);
  digitalWrite(DIGIT_3, digits[3]);
}

void setup() {
  pinMode(SEGMENT_A, OUTPUT);
  pinMode(SEGMENT_B, OUTPUT);
  pinMode(SEGMENT_C, OUTPUT);
  pinMode(SEGMENT_D, OUTPUT);
  pinMode(SEGMENT_E, OUTPUT);
  pinMode(SEGMENT_F, OUTPUT);
  pinMode(SEGMENT_G, OUTPUT);
  pinMode(SEGMENT_DP, OUTPUT);

  pinMode(DIGIT_0, OUTPUT);
  pinMode(DIGIT_1, OUTPUT);
  pinMode(DIGIT_2, OUTPUT);
  pinMode(DIGIT_3, OUTPUT);

  Serial.begin(9600);
  pinMode(PB, INPUT);
}

int display = 0;
int modo = VER_VOLTAJE;
int bloqueo = 0;
int cont = 0;
int temporizador = 0;
uint16_t sensor_read = 0;
int aux;

void loop() {
  
  if (analogRead(PB) && !bloqueo) {
    modo += 1;
    if (modo == 3) modo = 0;
    bloqueo = 1;
  }
  if (!digitalRead(PB)) bloqueo = 0;

  temporizador = millis();
  if(temporizador >= aux)
  {
    sensor_read = analogRead(ANALOG_INPUT);
    aux += 1000;
  }
  
  float voltaje, resistencia;

  if (modo == VER_VOLTAJE)
  {
    voltaje = (V_REF * sensor_read) / 1024.0;
    Serial.println(voltaje, 3);
  }
  else if (modo == VER_RESISTENCIA)
  {
    resistencia = sensor_read * (-5.0 / 512) + 10;
    Serial.println(resistencia, 3);
  }
  else Serial.println(sensor_read);

  if (modo == VER_ADC)
  {
  cont = 0;
  int num[4];
  num[0]=sensor_read%10;
  num[1]=sensor_read%100-num[0];
  num[2]=sensor_read%1000-num[1]-num[0];
  num[3]=(sensor_read%10000-num[2]-num[1]-num[0])/1000;
  num[2]=num[2]/100;
  num[1]=num[1]/10;
  ssd_output_code(num[display], display);
  display += 1;
  if(display == 1 && sensor_read < 10) display = 0;
  else if(display == 2 && sensor_read < 100) display = 0;
  else if(display == 3 && sensor_read < 1000) display = 0;
  else if(display == 4) display = 0;
  }
  
  else if (modo == VER_VOLTAJE)
  {
  int v = voltaje *= 1000;
  int num[4];
  num[0]=v%10;
  num[1]=v%100-num[0];
  num[2]=v%1000-num[1]-num[0];
  num[3]=(v%10000-num[2]-num[1]-num[0])/1000;
  num[2]=num[2]/100;
  num[1]=num[1]/10;
  if(display == 3) ssd_output_code(num[display] + 10, display);
  else ssd_output_code(num[display], display);
  display += 1;
  if(display == 4) display = 0;
  }
  
  else
  {
  int r = resistencia * 1000;
  int num[4];
  num[0]=r%10;
  num[1]=r%100-num[0];
  num[2]=r%1000-num[1]-num[0];
  num[3]=(r%10000-num[2]-num[1]-num[0])/1000;
  num[2]=num[2]/100;
  num[1]=num[1]/10;
  if(display == 3) ssd_output_code(num[display] + 10, display);
  else ssd_output_code(num[display], display);
  display += 1;
  if(display == 4) display = 0;
  }
  
  delay(1);
}
