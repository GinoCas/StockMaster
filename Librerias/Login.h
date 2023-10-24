#include <iostream>
#include <string>
#include <fstream>
#include "Global.h"
#include "StockMenu"
//$include "specialprint.h"

using namespace std;

void inicio_de_sesion(){
	opt = 0;
	string user_name = "", password = "";
	bool caracteres_validos = false, error = false, done = false, mostrar_contra = false;
	system("cls");
	escribir("[esp=20]INICIO DE SESIÓN[esp=20][line==]");
	printf("\n\nUsuario:");
	printf("\nContraseña:\n\n");
	escribir("[esp=56][line==]");
	printf("\nINGRESAR");
	printf("\nMOSTRAR CONTRASEÑA");
	printf("\nVOLVER");
	do{
		char carac;
		switch(opt){
			case 0:
				cursor(9+user_name.length(), 3);
				user_name = input_text(user_name, 16, 4, '\0', 50, 9, 3);
				cursor(0, 5);
				printf("\033[K");
				if(last_char != '\r'){break;}
				if(!is_every_char_alpha(user_name)){
					send_error("simbol");
					cursor(9+user_name.length(), 4);
					break;
				}
				if(!check_user(user_name, 4)){break;};
				opt++;
			break;
			case 1:
				cursor(12+password.length(), 4);
				password = !mostrar_contra ? input_text(password, 16, 4, '*', 50, 12, 4) : input_text(password, 32, 4, '\0', 50, 12, 4);
				cursor(0, 5);
				printf("\033[K");
				if(last_char != '\r'){break;}
				if(is_every_char_alpha(password)){
					if(!check_login(user_name, password, 4, 6)){break;}
					done = true;
					continue;
				}
				send_error("simbol");
				cursor(9+user_name.length(), 4);
			break;
			case 2:
				cursor(9, 7);
				printf(" <---");
				last_char = getch();
				change_option(4);
				if(last_char == '\r'){
					if(!check_login(user_name, password, 4, 6)){break;}
					done = true;
					break;
				}
				printf("\b\b\b\b\033[K");
			break;
			case 3:
				cursor(19, 8);
				printf(" <---");
				last_char = getch();
				change_option(4);
				printf("\b\b\b\b\033[K");
				if(last_char != '\r'){break;}
				cursor(12, 4);
				if(!mostrar_contra){
					mostrar_contra = true;
					cout<<password;	
				}else{
					mostrar_contra = false;
					escribir(("[esp=" + to_string(password.length()) + "][line=*]"));
				}
			break;
			case 4:
				cursor(7, 9);
				printf(" <---");
				last_char = getch();
				change_option(4);
				if(last_char == '\r'){
					done = true;
					return;
				}
				printf("\b\b\b\b\033[K");
			break;
		}
		
	}while(!done);
	system("cls");
	opt = 0;
	usuario = user_name;
	if(usuario == ""){
		usuario = "Unknow";
	}
	menu_principal(true);
	return inicio_de_sesion();
	/*vector<string> productos = get_products_of_group("/hardware");
	for(int i = 0; i<productos.size(); i++){
		cout<<"Producto:"<<productos[i]<<" Stock:"<<productos[i+1]<<endl;
		i += 1;
	}*/
	//int line = get_group("/hardware/Placas de video", true);
	//cout<<endl<<"Agrega un producto "<<endl;
	//string produc;
	//cin>>produc;
	//add_text_to_file("Computacion.txt", '"' + produc + "\";1", line+1);
}
/*void stock_menu(){
	escribir("\n[esp=40][line=_]");
}*/

