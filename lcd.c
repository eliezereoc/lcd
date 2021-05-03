#include "lcd.h"

 
static char modo_lcd2;	
extern uint8_t d0, d1, d2, d3, d4;  

void decodificaDigito (uint32_t num){
	d0 = num/10000; 
	num = num%10000;
	d1 = num/1000;  
	num = num%1000; 
	d2 = num/100;   
	num = num%100;   
	d3 = num/10;    
	d4 = num%10;
}

void lcdEnviaNibble(char dado){	
    verifica_port_lcd.byte_port_lcd = dado;
	D4_LCD_LAT = verifica_port_lcd.bit_port_lcd.b0;
	D5_LCD_LAT = verifica_port_lcd.bit_port_lcd.b1;
	D6_LCD_LAT = verifica_port_lcd.bit_port_lcd.b2;
	D7_LCD_LAT = verifica_port_lcd.bit_port_lcd.b3;
	EN_LCD_LAT = ON;
	EN_LCD_LAT = 0;
}

void lcdEnviaByte(char endereco, char dado ){  
	RS_LCD_LAT = 0;	
	RS_LCD_LAT = endereco;	
	__delay_ms(2);		
	EN_LCD_LAT = 0;	
	lcdEnviaNibble(dado >> 4);	
	lcdEnviaNibble(dado & 0x0f);
}

void lcdInit(char modo1, char modo2 ){
	char conta; 	
	D4_LCD_LAT = 0;
	D5_LCD_LAT = 0;
	D6_LCD_LAT = 0;
	D7_LCD_LAT = 0;
	RS_LCD_LAT = 0;
	EN_LCD_LAT = 0;
	__delay_ms(5);
	for(conta = 1; conta <= 3; ++conta){
		lcdEnviaNibble(3); 
		__delay_ms(3); 
	}
	lcdEnviaNibble(2);
	lcdEnviaByte(0,0x20 | modo1);
	lcdEnviaByte(0,0x08 | modo2);
	modo_lcd2 = 0x08 | modo2;
	lcdEnviaByte(0,1);
	lcdEnviaByte(0,6);
}

void lcdPosYx(char y, char x){       
    char endereco;
    if(y == 1) endereco = 0x80  + (x - 1);
    else if(y == 2) endereco = LCD_2_LIN + (x - 1);   
         else if(y == 3) endereco = LCD_3_LIN  + (x - 1);   
              else if(y == 4) endereco = LCD_4_LIN  + (x - 1);   
    lcdEnviaByte(0,0x80|endereco);
}

void lcdEscreveChar(char c){
   switch (c){
        case '\f':lcdEnviaByte(0,1);break;					        
        case '\n': lcdPosYx(1,2);break;	  				   
        case '\r': lcdEnviaByte(0,4);break;  				      
          default: lcdEnviaByte(1,c);
   }   
}

void lcdEscreveString (char *c){
	while (*c){
		lcdEscreveChar(*c);
		c++;
	}
}

void lcdLigaDisplay(void){
	modo_lcd2 |= 4;
	lcdEnviaByte (0,modo_lcd2);
}

void lcdDesligaDisplay(void){
	modo_lcd2 &= 0b11111011;
	lcdEnviaByte (0,modo_lcd2);
}

void lcdLigaCursor(void){
	modo_lcd2 |= 2;
	lcdEnviaByte (0,modo_lcd2);
}

void lcdDesligaCursor(void){
	modo_lcd2 &= 0b11111101;
	lcdEnviaByte (0,modo_lcd2);
}

void lcdLigaCursorPiscante(void){
	modo_lcd2 |= 1;
	lcdEnviaByte (0,modo_lcd2);
}

//DESLIGA CURSOR EM MODO PISCANTE
void lcdDesligaCursorPiscante(void){
	modo_lcd2 &= 0b11111110;
	lcdEnviaByte (0,modo_lcd2);
}


void inicializaLcd(void){	
    lcdInit(display_8x5 | _2_linhas,display_ligado | cursor_desligado | cursor_fixo); 
	lcdEscreveChar('\f');	
}