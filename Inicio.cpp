#include <iostream>
#include <conio.h>
#include <cstdio>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <string.h>
#include <windows.h>
#include <locale>
#include <ctime>
#include "Librerias\specialprint.h"
#include "Librerias\verify.h"
#include "Librerias\Login.h"

using namespace std;
void inicio();

int main(){
	SetConsoleOutputCP(CP_UTF8);
	system("chcp 65001");
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
	cout<<"\nInicio de Sesión\nRegistrarse\nCréditos\nSalir\n";
	escribir("[esp=48][line=-]");
	cursor(0,29);
	escribir("[esp=120][line=-]"); //Foot
	escribir("\n[esp=48]Gino Casentini @2023-2023");
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
				cursor(9, 14);
			break;
			case 3:
				cursor(6, 15);
			break;
		}
		printf(" <---");
		while(carac != -32 && carac != '\r'){
			carac = getch();
		}
		if(carac == '\r'){
			break;
		}
		last_char = carac;
		change_option(3);
		carac = '.';
		printf("\b\b\b\b\033[K");
	}while(true);
	switch(opt){
		case 0:
			inicio_sesion(false);
		return inicio();
		case 1:
			inicio_sesion(true);
			//Registrarse
		return inicio();
		case 2:
			empty_section(0, 10, 15, 60);
			cursor(1, 10);
			cout<<"\033[1;31m"<<"> Creador: Gino Casentini\n"<<"\033[1;32m"<<"> Colaborador: Stéfano Costa (https://github.com/Stefano1611)\n"<<"\033[1;34m"<<"> Profesor: Joel Godoy\033[0m";
			cout << "\033[1;36m" << "\n\n* Mi Github: https://github.com/GinoCas\n* Repositorio: https://github.com/GinoCas/StockMaster\n" << "\033[0m" << std::endl;
			cout<<"\nPresione una tecla para volver...";
			getch();
		return inicio();
		case 3:
			exit(EXIT_SUCCESS);
	}
}
