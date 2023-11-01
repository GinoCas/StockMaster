#include <iostream>
#include <vector>

int get_category(string category, int stop){
	FILE * archivo;
	archivo = fopen("Computacion.txt", "rt");
	
	string current_category = "", texto = "";
	int current_line = 0, return_line = 0;
	bool found_category = false;
	char letra;
	bool end_cat = false;
	while(!feof(archivo)){
		letra = fgetc(archivo);
		if(letra == '\n' || letra == '\r' || letra == '\t'){
			if(letra == '\n'){
				current_line++;
			}
			continue;
		}
		if(letra != ' ' && letra > 31){
			return_line = current_line;
		}
		int ult_barra = current_category.rfind('/');
		switch(letra){
			case '{':
				end_cat = false;
				current_category = current_category + "/" + texto;
				found_category = current_category == category && !found_category ? true : found_category;
				if(found_category){
					if(stop == 1){
						return current_line;
					}
				}
				texto = "";
			continue;
			case '}':
				if(ult_barra != string::npos){
					found_category = current_category == category && found_category ? false : found_category;
					current_category.erase(ult_barra);
					if(end_cat){
						return current_line;
					}
					if(current_category == category && found_category){
						end_cat = true;
					}
				}
			continue;
			case '"':
				texto = "";	
			continue;
			case ';':
				texto = "";
			continue;
		}
		texto += letra;
	}
	return return_line;
}
vector<string> get_category_list(string category, bool all){
	FILE * archivo;
	archivo = fopen("Computacion.txt", "rt");
	string current_category = "", texto = "";
	vector<string> categories;
	bool on_quotes = false, found_category = false;
	char letra;
	while(!feof(archivo)){
		letra = fgetc(archivo);
		if(letra == '\n' || letra == '\r' || letra == '\t'){
			continue;
		}
		int ult_barra = current_category.rfind('/');
		switch(letra){
			case '{':
				current_category = current_category + "/" + texto;
				ult_barra = current_category.rfind('/');
				if(ult_barra != -1){
					string without_slash = current_category;
					found_category = without_slash.erase(ult_barra) == category ? true : false;
				}
				found_category = category == "" && current_category == "" ? true : found_category;
				if(found_category || all){
					if(all){
						categories.push_back(current_category);	
					}else{
						categories.push_back(texto);
					}
				}
				texto = "";
			continue;
			case '}':
				current_category.erase(ult_barra);
				texto = "";
			continue;
			case ';':
				texto = "";
			continue;
		}
		texto += letra;
	}
	return categories;
}

vector<Producto> get_products_in_category(string category){
	FILE * archivo;
	archivo = fopen("Computacion.txt", "rt");
	string current_category = "", texto = "";
	vector<Producto> products;
	Producto product;
	bool on_quotes = false, found_category = false;
	int property_count = 0;
	char letra;
	if(category == ""){
		found_category = true;
	}
	while(!feof(archivo)){
		letra = fgetc(archivo);
		int ult_barra = current_category.rfind('/');
		if(letra == '\n' || letra == '\r' || letra == '\t'){
			if(property_count > 0){
				product.categoria = current_category.substr(ult_barra+1, current_category.length());
				products.push_back(product);
				property_count = 0;	
			}
			continue;
		}
		switch(letra){
			case '{':
				current_category = current_category + "/" + texto;
				found_category = current_category == category && !found_category ? true : found_category;
				texto = "";
			continue;
			case '}':
				texto = "";
				found_category = current_category == category && found_category ? false : found_category;
				if(ult_barra != string::npos){
					current_category.erase(ult_barra);
				}
			continue;
			case '"':
				on_quotes = !on_quotes;
				if(on_quotes == true){
					texto = "";
				}
			continue;
			case ';':
				switch(property_count){
					case 0:
						product.nombre = texto;
					break;
					case 1:
						product.stock = stoi(texto);
					break;
					case 2:
						product.persona = texto;
					break;
					case 3:
						product.descripcion = texto;
					break;
				}
				if(found_category){
					property_count++;
				}
				texto = "";	
			continue;
		}
		texto += letra;
	}
	return products;
}
int find_product_in_category(Producto product){
	int current_line = 0;
	//FILE *archivo = fopen("Computacion.txt", "r");  // Reemplaza "mi_archivo.txt" con el nombre de tu archivo
	ifstream archivo("Computacion.txt");
	string line = "";
	string searching_for = '"' + product.nombre + "\";" + to_string(product.stock) + ";" + product.persona + ";\"" + product.descripcion +  "\";";
	while(getline(archivo, line)){
		if(line.find(searching_for) != string::npos){
			return current_line+1;
		}
		current_line++;
	}
    archivo.close();

    return -1;
}
void add_text_to_file(string file, string text, int line){
	ifstream archivo_lectura(file);
	string linea;
	vector<string> lineas;
	while(getline(archivo_lectura, linea)){
        lineas.push_back(linea);
    }
    archivo_lectura.close();
    
    lineas.insert(lineas.begin() + line, text);
    
    ofstream archivo_escritura(file);
    for (const auto& linea : lineas) {
        archivo_escritura << linea << endl;
    }
    archivo_escritura.close();
}
void delet_line_from_file(int deletLine){
	fstream file("Computacion.txt");
    int current_line = 1;
    string archivText = "";
    string line = "";
    int count = 0;
    while(getline(file, line)){
        if(current_line == deletLine){
        	count = line.length();
        }else{
            archivText += line + "\n";
        }
        current_line++;
    }
    if(count != 0){
    	for(int i = 0; i<count; i++){
    		archivText += " ";
		}
	}
    file.close();
    file.open("Computacion.txt");
    file<<archivText;
    return;
}
void delet_category(string category){
	int begin = get_category(category, 1);
	int end = get_category(category, 2);
	for(int i = 0; i<(end-begin)+1; i++){
		delet_line_from_file(begin+1);
	}
}
void replace_text_at_line(string text, int replaceLine){
	fstream file("Computacion.txt");
    int current_line = 1;
    string archivText = "";
    string line = "";
    int count = 0;
    while(getline(file, line)){
        if(current_line == replaceLine){
        	if(line.length() > text.length()){
        		count = line.length() - text.length();
			}
            archivText += text + "\n";
        }else{
            archivText += line + "\n";
        }
        current_line++;
    }
    if(count != 0){
    	for(int i = 0; i<count; i++){
    		archivText += " ";
		}
	}
    file.close();
    file.open("Computacion.txt");
    file<<archivText;
    return;
}

string select_category(string category, int ylimit){
	vector<string> category_list = get_category_list("", true);
	for(int i = 0; i<category_list.size(); i++){
		if(category_list[i] == category){
			opty = i;
			break;
		}
	}
	last_char = getch();
	if(ylimit != -1){
		change_option_two_dim(category_list.size()-1, ylimit);
	}else{
		change_option_y(category_list.size()-1);	
	}
	return category_list[opty];
}