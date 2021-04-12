#define RS_PIN		12
#define	EN_PIN		11
#define	D4_PIN		5
#define	D5_PIN		4
#define	D6_PIN		3
#define	D7_PIN		2

#define RS_SET_VALUE(value)		digitalWrite(RS_PIN, value)
#define EN_SET_VALUE(value)		digitalWrite(EN_PIN, value)

// -------------------------------------------------------
//          H E L P E R   F U N C T I O N S
// -------------------------------------------------------

void pulse_enable()
{
	// Make sure enable start low (> 40nS)
   	EN_SET_VALUE(LOW);
    delayMicroseconds(1);
  
   	// Start pulse (> 450 nS)
   	EN_SET_VALUE(HIGH);
	delayMicroseconds(1);
  
  	// Stop pulse and let settle down (> 37 uS)
  	EN_SET_VALUE(LOW);
  	delayMicroseconds(100);
}

void lcd_write_4bits(uint8_t code, bool mode)
{
	// Decompose code
    bool d4 = (code >> 0) & 0x01;
    bool d5 = (code >> 1) & 0x01;
    bool d6 = (code >> 2) & 0x01;
    bool d7 = (code >> 3) & 0x01;

  	// Set RS to correct mode
  	RS_SET_VALUE(mode);
  
  	// Asume RD/WR tie to ground

  	// Set data pins
  	digitalWrite(D4_PIN, d4);
  	digitalWrite(D5_PIN, d5);
  	digitalWrite(D6_PIN, d6);
  	digitalWrite(D7_PIN, d7);
  
  	// Pulse enable signal
  	pulse_enable();  	
}

void lcd_send_data(uint8_t data)
{
  	// Send 4-bits MSB, then LSB
  	lcd_write_4bits(data >> 4, 1);
  	lcd_write_4bits(data, 1);
}

void lcd_send_command(uint8_t cmd)
{
  	// Send 4-bits MSB, then LSB
  	lcd_write_4bits(cmd >> 4, 0);
  	lcd_write_4bits(cmd, 0);
}

// -------------------------------------------------------
//        P R O T O T Y P E S   R O U T I N E S
// -------------------------------------------------------
void lcd_init();
void lcd_clear();
void lcd_set_cursor(uint8_t col, uint8_t row);
void lcd_print_char(char c);
void lcd_print_string(char* c);
void lcd_print_float(float f);
void lcd_print_unsigned(uint16_t u);


void setup()
{
  lcd_init();
}

void loop()
{
  lcd_clear();
  delay(2000);
  
  // Print Hello one char at a time
  lcd_set_cursor( 2, 0); lcd_print_char('H');
  lcd_set_cursor( 4, 0); lcd_print_char('E');
  lcd_set_cursor( 6, 0); lcd_print_char('L');
  lcd_set_cursor( 8, 0); lcd_print_char('L');
  lcd_set_cursor(10, 0); lcd_print_char('O');
  
  lcd_set_cursor( 3, 1); lcd_print_char('W');
  lcd_set_cursor( 5, 1); lcd_print_char('O');
  lcd_set_cursor( 7, 1); lcd_print_char('R');
  lcd_set_cursor( 9, 1); lcd_print_char('L');
  lcd_set_cursor(11, 1); lcd_print_char('D');
  
  delay(2000);
  
  // Testing other routines
  lcd_clear();
  lcd_set_cursor( 2, 0); 
  lcd_print_string("Testing Int:");
  lcd_set_cursor( 4, 1); 
  lcd_print_unsigned(1234);
  delay(2000);
  
  lcd_clear();
  lcd_set_cursor( 2, 0); 
  lcd_print_string("Testing Float:");
  lcd_set_cursor( 4, 1); 
  lcd_print_float(4.567);
  delay(2000);
}

// -----------------------------------------------------
//            U S E R   R O U T I N E S
// -----------------------------------------------------

void lcd_init()
{
  pinMode(RS_PIN, OUTPUT);
  pinMode(EN_PIN, OUTPUT);
  pinMode(D4_PIN, OUTPUT);
  pinMode(D5_PIN, OUTPUT);
  pinMode(D6_PIN, OUTPUT);
  pinMode(D7_PIN, OUTPUT);
  delay(450);
  
  digitalWrite(RS_PIN, LOW);
  digitalWrite(EN_PIN, LOW);
  
  lcd_send_command(0x02); 
  delay(20);
  lcd_send_command(0x01); 
  delay(20);
  lcd_send_command(0x0C);
  delay(20);
  lcd_send_command(0x14);
  delay(20);
  lcd_send_command(0x28);
  delay(20);
}

void lcd_clear()
{
  lcd_send_command(1);
}

void lcd_set_cursor(uint8_t col, uint8_t row)
{
  if (row == 1) col += 40;
  lcd_send_command(0x80 | col);
}

void lcd_print_char(char c)
{
  lcd_send_data(c);
}

void lcd_print_string(char* s)
{
  for(int i = 0; i < strlen(s); i++)
  {
    lcd_print_char(s[i]);
  }
}


void lcd_print_float(float f)
{
  int valor = f * 1000;
  int num[4];
  num[0]=valor%10;
  num[1]=valor%100-num[0];
  num[2]=valor%1000-num[1]-num[0];
  num[3]=(valor%10000-num[2]-num[1]-num[0])/1000;
  num[2]=num[2]/100;
  num[1]=num[1]/10;
  lcd_print_char(num[3] + '0');
  lcd_print_char('.');
  lcd_print_char(num[2] + '0');
  lcd_print_char(num[1] + '0');
  lcd_print_char(num[0] + '0');
}

void lcd_print_unsigned(uint16_t u)
{
  int num[4];
  num[0]=u%10;
  num[1]=u%100-num[0];
  num[2]=u%1000-num[1]-num[0];
  num[3]=(u%10000-num[2]-num[1]-num[0])/1000;
  num[2]=num[2]/100;
  num[1]=num[1]/10;
  if(u < 1000) num[3] = ' ' - '0';
  if(u < 100)  num[2] = ' ' - '0';
  if(u < 10)   num[1] = ' ' - '0';
  lcd_print_char(num[3] + '0');
  lcd_print_char(num[2] + '0');
  lcd_print_char(num[1] + '0');
  lcd_print_char(num[0] + '0');
}
