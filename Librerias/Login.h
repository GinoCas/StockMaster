#include <iostream>
#include <string>
#include <fstream>
#include "Global.h"
#include "StockMenu"
//$include "specialprint.h"

using namespace std;

void inicio_sesion(bool create_acc){
	opt = 0;
	string user_name = "", password = "";
	bool caracteres_validos = false, error = false, done = false, mostrar_contra = false, user_exist = false;
	system("cls");
	if(create_acc){
		escribir("[esp=23]Registrarse[esp=22][line==]");	
	}else{
		escribir("[esp=20]INICIO DE SESIÓN[esp=20][line==]");	
	}
	printf("\n\nUsuario:");
	printf("\nContraseña:\n\n");
	escribir("[esp=56][line==]");
	printf("\nINGRESAR");
	printf("\nMOSTRAR CONTRASEÑA");
	printf("\nVOLVER");
	vector<user> user_list = get_users();
	do{
		char carac;
		switch(opt){
			case 0:
				cursor(9+user_name.length(), 3);
				user_name = input_text(user_name, 16, 4, '\0', 50, 9, 3);
				user_name = minus_transform(user_name);
				cursor(0, 5);
				printf("\033[K");
				if(last_char != '\r'){break;}
				if(!is_every_char_alpha(user_name) && create_acc){
					send_error("simbol");
					cursor(9+user_name.length(), 4);
					break;
				}
				if(!create_acc){ opt++; break;}
				if(!check_user(user_name, 4)){break;};
				opt++;
			break;
			case 1:
				cursor(12+password.length(), 4);
				password = !mostrar_contra ? input_text(password, 16, 4, '*', 50, 12, 4) : input_text(password, 32, 4, '\0', 50, 12, 4);
				cursor(0, 5);
				printf("\033[K");
				if(last_char != '\r'){break;}
				user_exist = false;
				if(!create_acc){
					for(int i = 0; i<user_list.size(); i++){
						if(user_name == user_list[i].name && password == user_list[i].password){
							user_exist = true;
							break;
						}
					}
					if(user_exist){
						done = true;
						break;
					}else{
						send_error("El usuario o contraseña ingresado son incorrectos.");
						break;
					}
				}else{
					for(int i = 0; i<user_list.size(); i++){
						if(user_name == user_list[i].name){
							send_error("user_exist");
							user_exist = true;	
							break;
						}
					}
					if(user_exist){
						user_exist = false;
						break;
					}
				}
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
					for(int i = 0; i<user_list.size(); i++){
						if(user_name == user_list[i].name){
							if(create_acc){
								send_error("user_exist");
								cursor(9+user_name.length(), 4);
								user_exist = true;
								break;	
							}else if(password == user_list[i].password){
								user_exist = true;
								break;
							}
						}
					}
					if(user_exist && create_acc){
						user_exist = false;
						break;
					}else if(!user_exist && !create_acc){
						send_error("El usuario o contraseña ingresado son incorrectos.");
						break;
					}
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
	string admin = password == "AdminGC" ? "1" : "0";
	if(create_acc){
		add_text_to_file("Cuentas.txt", user_name + ";" + password + ";" + admin, 0);	
	}
	menu_principal(true);
	return inicio_sesion(false);
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


