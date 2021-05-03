#ifndef LCD_H_
#define LCD_H_


#include "main.h" 


#define LCD_2_LIN           0xC0  
#define LCD_3_LIN           0x94
#define LCD_4_LIN           0xD4

#define cursor_ligado       2
#define cursor_desligado    0
#define cursor_piscante     1
#define cursor_fixo         0
#define display_ligado      4
#define display_desligado   0
#define display_8x5         0
#define display_10x5        4
#define _2_linhas           8
#define _1_linha            0


typedef union {
    struct{   
        unsigned b0 : 1;
		unsigned b1 : 1;
		unsigned b2 : 1;
		unsigned b3 : 1;
		unsigned b4 : 1;
		unsigned b5 : 1;
		unsigned b6 : 1;
		unsigned b7 : 1;
    }bit_port_lcd;
    uint8_t byte_port_lcd;
} ubyte_port_lcd;
ubyte_port_lcd verifica_port_lcd;

void lcdEnviaNibble(char dado);
void lcdEnviaByte(char endereco, char dado );
void lcdInit(char modo1, char modo2 );
void lcdPosYx(char x, char y);
void lcdEscreveChar(char c);
void lcdEscreveString (char *c);
void lcdLigaDisplay(void);
void lcdDesligaDisplay(void);
void lcdLigaCursor(void);
void lcdDesligaCursor(void);
void lcdLigaCursorPiscante(void);
void lcdDesligaCursorPiscante(void);

 

 

 


 




#endif /* LDC_H_ */