#include <iostream>
#include <vector>
#include <string.h>
#include <cmath>


using namespace std;

int opt = 0;
int opty = 0;
char last_char;

string usuario, after_text = "";

void empty_section(int xstart, int ystart, int repeat, int spaces){
	for(int i = 0; i<repeat; i++){
		cursor(xstart, ystart + i); 
		escribir("[esp=" + to_string(spaces) + "]");
	}
}

struct Producto{
	string nombre = "";
	string categoria = "";
	string persona = "";
	string descripcion = "";
	int stock = 0;
	
};
void change_option(int max_limit){
	if(last_char != -32){
		return;
	}
	last_char = getch();
	switch(last_char){
		case 72:
			opt--;
			Sleep(100);
			opt = opt < 0 ? max_limit : opt;
		break;
		case 80:
			opt++;
			opt = opt > max_limit ? 0 : opt;
			Sleep(100);
		break;
	}
}

string delet_carac_from_s(string word, char special_carac){
	string result = "";
	for(char& carac : word){
		if(carac == special_carac){
			continue;
		}
		result += carac;
	}
	return result;
}
string mayus_transform(string word){
	for(char& carac : word){
		carac = toupper(carac);
	}
	return word;
}

void change_option_two_dim(int max_x, int max_y){
	if(last_char != -32){
		return;
	}
	last_char = getch();
	switch(last_char){
		case 75:
			opty--;
			opty = opty < 0 ? max_x : opty;
			Sleep(100);
		break;
		case 77:
			opty++;
			opty = opty > max_x ? 0 : opty;
			Sleep(100);
		break;
		case 72:
			opt--;
			opt = opt < 0 ? max_y : opt;
			Sleep(100);
		break;
		case 80:
			opt++;
			opt = opt > max_y ? 0 : opt;
			Sleep(100);
		break;
	}
}

void change_option_y(int max_y){
	if(last_char != -32){
		return;
	}
	last_char = getch();
	switch(last_char){
		case 75:
			opty--;
			opty = opty < 0 ? max_y : opty;
			Sleep(100);
		break;
		case 77:
			opty++;
			opty = opty > max_y ? 0 : opty;
			Sleep(100);
		break;
	}
}

string input_text(string using_text, int char_limit, int opt_limit, char show, int x_end, int x_start, int y_start){
	char carac; //caracter escrito y todo lo escrito
	string text = using_text;
	int carac_idx = using_text.length();
	bool flechas = false;
	string last_word = "";
	vector<string> word_list; //lista de palabras
	for(int i = 0; i<text.length(); i++){
		if(text[i] != '\\' && text[i] != ' '){
			last_word += text[i];	
		}
		if(text[i] == ' '){
			word_list.push_back(last_word);
			last_word = "";
		}
	}
	cursor(x_start + carac_idx % x_end, y_start + ceil(carac_idx / x_end));
	int before = 0;
	while((carac = getch()) != '\r'){
		if(carac == '\\'){
			continue;
		}
		if(carac == ' ' && carac_idx < char_limit){
			if(carac_idx == 0){
				continue;
			}
			if((carac_idx+1) % x_end == 0 && text[carac_idx-1] == ' '){
				continue;
			}
			word_list.push_back(last_word);
			last_word = "";
		}
		if(carac == '\b'){
			if(carac_idx == 0){
				continue;
			}
			before = ceil(carac_idx / x_end);
			cout<<"\b \b";
			carac_idx--;
			cursor(x_start + carac_idx % x_end, y_start + ceil(carac_idx / x_end));
			if(text[carac_idx] == ' '){
				word_list.pop_back();
				last_word = word_list[word_list.size()];
			}else{
				last_word = last_word.substr(0, last_word.length()-1);
			}
			text = text.substr(0, text.length()-1);
			if(text[carac_idx-1] == '\\'){
				cursor(x_start, -1);
				for(int i = 0; i<last_word.length(); i++){
					cout<<" ";
					carac_idx--;
				}
				text = text.substr(0, text.length() - last_word.length() - 1);
				carac_idx -= last_word.length()+1;
				empty_section(0, y_start + 1 + ceil(carac_idx / x_end), 25-(y_start + 1 + ceil(carac_idx / x_end)), 50);
				cursor(0, y_start + ceil(carac_idx / x_end));
				cout<<after_text;
				cursor(x_start + carac_idx % x_end, y_start + ceil(carac_idx / x_end));
				cout<<last_word;
				carac_idx += last_word.length();
				continue;
			}
			if(before != ceil(carac_idx/x_end)){
				empty_section(0, y_start + 1 + ceil(carac_idx / x_end), 25-(y_start + 1 + ceil(carac_idx / x_end)), 50);
				cursor(0, y_start + ceil(carac_idx / x_end));
				cout<<after_text;
				cursor(x_start + carac_idx % x_end, y_start + ceil(carac_idx / x_end));
			}
			continue;
		}
		if(last_word.length() > 19 && (carac_idx+1) % x_end == 0){
			cout<<carac_idx;
			continue;
		}
		last_char = carac;
		change_option(opt_limit);
		if(carac == -32 && (last_char == 72 || last_char == 80)){
			break;
		}
		if(carac < 32 || carac == 127){
			continue;
		}
		if(carac_idx > char_limit-1 || carac == '\t'){
			continue;
		}
		if(carac_idx >= char_limit){
			continue;
		}
		if(carac != ' '){
			last_word += carac;
		}
		before = ceil(carac_idx / x_end);
		carac_idx++;
		if(show == '\0'){
			cout<<carac;
		}else{
			cout<<show;
		}
		cursor(x_start + carac_idx % x_end, y_start + ceil(carac_idx / x_end));
		if(carac_idx % x_end == 0){
			if(text[carac_idx-1] != ' '){
				cursor(x_start + x_end - last_word.length(), y_start + ceil(carac_idx / x_end) - 1);
				for(int i = 0; i<last_word.length(); i++){
					cout<<" ";
				}
				for(int i = 0; i<last_word.length(); i++){
					text += '\\';
				}
				carac_idx += last_word.length();
				empty_section(0, y_start + ceil(carac_idx / x_end), 25-(y_start + ceil(carac_idx / x_end)), 50);
				cursor(0, y_start + ceil(carac_idx / x_end));
				cout<<after_text;
				cursor(x_start, y_start + ceil(carac_idx / x_end));
				cout<<last_word;
				text += carac;
				continue;
			}
			if(before != ceil(carac_idx / x_end)){
				empty_section(0, y_start + ceil(carac_idx / x_end), 25-(y_start + ceil(carac_idx / x_end)), 50);
				cursor(0, y_start + ceil(carac_idx / x_end));
				cout<<after_text;
				cursor(x_start, y_start + ceil(carac_idx / x_end));
			}
		}
		text += carac;
	}
	string result;
	for(int i = 0; i<carac_idx; i++){
		result += text[i];
	}
	last_char = carac;
	return result;
}
int input_number(int num, int num_max, int opt_limit){
	char carac = getch();
	if(carac == '\b'){
        if(num > 0){
            num = num / 10;
       	}
    	return num;
    }
    last_char = carac;
    change_option(opt_limit);
	num = num > num_max ? num_max : num; 
    if(carac == -32){
		return num;
	}
    int carac_num = atoi(&carac);
    if(carac_num >= 0){
    	int before = num;
    	num = num * 10 + carac_num;
    	if(num > num_max){
    		num = before;
		}
    }
    return num;
}
void show_text_in_margin(string text, int x_start, int x_end, int y_start){
	for(int i = 0; i<text.length(); i++){
		cursor(x_start + i % x_end, y_start + ceil(i / x_end));
		cout<<text[i];
	}
}