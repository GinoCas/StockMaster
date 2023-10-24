#include <iostream>
#include <string.h>
#include <ctype.h>

using namespace std;
int userchar, passchar;
bool is_every_char_alpha(string), check_user(string, int), check_pass(string, int);
void send_error(string), cursor(int, int);

void cursor(int x, int y){
	if(x == -1){
		printf("\x1b[%dA", y);
		return;
	}
	if(y == -1){
		printf("\x1b[%dG", x);
		return;
	}
	printf("\x1b[%d;%df", y, x);
}

bool is_every_char_alpha(string str){
	for(char carac : str){
		if(!isalpha(carac)){
			return false;
		}
	}
	return true;
}

bool check_login(string user, string pass, int _userchar, int _passchar){
	if(!check_user(user, _userchar)){return false;};
	if(!check_pass(pass, _passchar)){return false;}
	return true;
}

bool check_user(string user, int _userchar)
{
	userchar = _userchar;
	if(user.length() < userchar){
		send_error("userchar");
		return false;
	}
	if(!is_every_char_alpha(user)){
		send_error("simbol");
		return false;
	}
	return true;
}

bool check_pass(string pass, int _passchar){
	passchar = _passchar;
	if(pass.length() < passchar){
		send_error("passchar");
		return false;;
	}
	if(!is_every_char_alpha(pass)){
		send_error("simbol");
		return false;
	}
	return true;	
}

void send_error(string err){
	cursor(0,5);
	if(err == "simbol"){
		cout<<"\033[1;31mSimbolos, numeros y espacios no estan permitidos.\033[0m";
		return;
	}
	if(err == "pass"){
		printf("\033[1;31mContraseña incorrecta.\033[0m");
		return;
	}
	if(err == "passchar"){
		printf("\033[1;31mLa contraseña debe tener un minimo de %i caracteres.\033[0m", passchar);
		return;
	}
	if(err == "userchar"){
		cout<<"\033[1;31mEl usuario debe tener un minimo de "<<userchar<<" caracteres.\033[0m";
		return;
	}
	if(err == "user"){
		cout<<"\033[1;31mUsuario incorrecto.\033[0m";
		return;
	}
	if(err == "surpass"){
		cout<<"\033[1;31mLo ingresado supera el limite de caracteres.\033[0m";
		return;
	}
	cout<<"\033[1;31m"<<err<<"\033[0m";
}