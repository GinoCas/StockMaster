#include <iostream>
#include <string.h>
#include <sstream>
#include "array.h"
//Libreria por: Gino Casentini 
using namespace std;

string bbcode[] = {"esp", "line"}; //Palabras Especiales

void escribir(string), do_bbcode(string, string);
string texto = "";
int char_idx = 0;

void escribir(string _texto){
	texto = _texto;
	int bbcode_state = 0, bbcode_start = 0;
	string bbcode_word = "", bbcode_value = "";
	bool reset_values = false;
	char_idx = 0;
	while(char_idx < texto.length()){
		if(reset_values){
			bbcode_state = 0;
			bbcode_start = 0;
			bbcode_word = "";
			bbcode_value = "";
			reset_values = false;
		}
		switch(texto[char_idx]){
			case '[':
				if(bbcode_state != 0){bbcode_state = 0; break;}
				bbcode_start = char_idx;
				bbcode_state = 1;
				char_idx++;
			continue;
			case ']':
				if(bbcode_state == 0){break;}
				if(!str_contiene(bbcode, bbcode_word)){
					bbcode_state = 0;
					continue;
				}
				char_idx++;
				texto = texto.substr(0, bbcode_start) + texto.substr(char_idx, texto.length());
				char_idx -= char_idx-bbcode_start;
				do_bbcode(bbcode_word, bbcode_value);
				reset_values = true;
			continue;
			case '=':
				if(bbcode_state != 1){break;}
				if(!str_contiene(bbcode, bbcode_word)){
					reset_values = true;
					char_idx -= char_idx-bbcode_start;
					continue;
				}
				bbcode_state = 2;
				char_idx++;
			continue;
		}
		switch(bbcode_state){
			case 1:
				bbcode_word += texto[char_idx];
			break;
			case 2:
				bbcode_value += texto[char_idx];
			break;
		}
		char_idx++;
	}
	cout<<texto;
}

void do_bbcode(string code, string value){
	if(code == "esp"){
		int num;
		istringstream(value)>>num;
		for(int i = 0; i<num; i++){
			texto = texto.substr(0, char_idx) + ' ' + texto.substr(char_idx, texto.length());
		}
	}
	if(code == "line"){
		int chr_inicial = -1;
		int chr_final = -1;
		for(int i = 0; i<texto.length(); i++){
			if(texto[i] != ' '){
				chr_final = i;
				if(chr_inicial == -1){
					chr_inicial = i;	
				}
			}
		}
		for(int i = 0; i<texto.length(); i++){
			char char_line;
			istringstream(value)>>char_line;
			if(i < chr_inicial){
				texto[i] = char_line;
			}
			if(i > chr_final){
				texto[i] = char_line;
			}
		}
	}
}
