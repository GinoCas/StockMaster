#include <iostream>
#include <conio.h>
#include <cstdio>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <string.h>
#include <windows.h>
#include <locale>
#include "Librerias\specialprint.h"
#include "Librerias\verify.h"
#include "Librerias\Login.h"

using namespace std;
void inicio();

int main(){
	SetConsoleOutputCP(CP_UTF8);
	inicio();
}

void inicio(){
	system("cls");
	cout<<"            ##                        ##                                   ##"<<endl;
	cout<<"            ##                        ##                                   ##"<<endl;
	cout<<"  #####    #####    ####     ####     ##  ##  ##  ##    ####     #####    #####    ####    ######"<<endl;
	cout<<" ##         ##     ##  ##   ##  ##    ## ##   #######      ##   ##         ##     ##  ##    ##  ##"<<endl;
	cout<<"  #####     ##     ##  ##   ##        ####    ## # ##   #####    #####     ##     ######    ##"<<endl;
	cout<<"      ##    ## ##  ##  ##   ##  ##    ## ##   ##   ##  ##  ##        ##    ## ##  ##        ##"<<endl;
	cout<<" ######      ###    ####     ####     ##  ##  ##   ##   #####   ######      ###    #####   ####"<<endl;
	escribir("[esp=100][line=_]");
	printf("\n\n¿Que desea hacer?\n");
	escribir("[esp=20]Opciones[esp=20][line=-]");
	cout<<"\nInicio de Sesión\nRegistrarse\nSalir"<<endl;
	escribir("[esp=48][line=-]");
	char carac;
	opt = 0;
	do{
		switch(opt){
			case 0:
				cursor(17, 12);
			break;	
			case 1:
				cursor(12, 13);
			break;
			case 2:
				cursor(6, 14);
			break;
		}
		printf(" <---");
		while(carac != -32 && carac != '\r'){
			carac = getch();
		}
		if(opt == 1 && carac == '\r'){
			cursor(0,20);
			cout<<"no fue hecho aun :(";
			carac = '.';
			continue;
		}
		if(carac == '\r'){
			break;
		}
		last_char = carac;
		change_option(2);
		carac = '.';
		printf("\b\b\b\b\033[K");
	}while(true);
	switch(opt){
		case 0:
			inicio_de_sesion();
		return inicio();
		case 1:
			//Registrarse
		break;
		case 2:
			exit(EXIT_SUCCESS);
	}
}
