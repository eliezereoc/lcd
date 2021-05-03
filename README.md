# lcd
Display LCD PIC, Arduino, Fresscale, NXP...

# Exemplo de uso

//
void main(void) {
    //INICIALIZA LCD
    lcd_ini(display_8x5 | _2_linhas,display_ligado | cursor_desligado | cursor_fixo); 

    //LIMPA LCD
	lcd_escreve_char('\f'); 

    //POSICIONA O CURSOR NA PRIMEIRA LINHA
	lcd_pos_xy(4,1);

    //ESCREVE MENSAGEM NO DISPLAY
	lcd_escreve_string("DISPLAY LCD");	

    //POSICIONA O CURSOR NA SEGUNDA LINHA
	lcd_pos_xy(4, 2);

    //ESCREVE MENSAGEM NO DISPLAY
	lcd_escreve_string("VERSAO: ");

    //DECODIFICA O VALOR DA VARIAVEL
	decodifica_digito(versao);

    //MOSTRA O VALOR DE CADA DIGITO DA VARIAVEL
    lcd_escreve_char(d1 + 48);//MILHAR
    lcd_escreve_char(d2 + 48);//CENTENA 
	lcd_escreve_char(d3 + 48);//DEZENA 
	lcd_escreve_char(d4 + 48);//UNIDADE

}

