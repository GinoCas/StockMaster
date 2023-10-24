#include <iostream>
#include <vector>

int get_category(string category, bool stop_on_category){
	FILE * archivo;
	archivo = fopen("Computacion.txt", "rt");
	
	string current_category = "", texto = "";
	int current_line = 0;
	bool on_quotes = false, found_category = false;
	char letra;
	
	while(!feof(archivo)){
		letra = fgetc(archivo);
		if(letra == '\n' || letra == '\r' || letra == '\t'){
			if(letra == '\n'){
				current_line++;
			}
			continue;
		}
		int ult_barra = current_category.rfind('/');
		switch(letra){
			case '{':
				current_category = current_category + "/" + texto;
				found_category = current_category == category && !found_category ? true : found_category;
				if(found_category){
					if(stop_on_category){
						return current_line;
					}
				}
				texto = "";
			continue;
			case '}':
				if(ult_barra != string::npos){
					if(found_category){
					}
					found_category = current_category == category && found_category ? false : found_category;
					current_category.erase(ult_barra);
				}
			continue;
			case '"':
				on_quotes = !on_quotes;
				if(!on_quotes && found_category){
				}
				texto = "";	
			continue;
			case ';':
				if(!on_quotes){
					continue;
				}
			break;
		}
		texto += letra;
	}
	return current_line;
}
vector<string> get_category_list(string category){
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
				if(found_category){
					categories.push_back(texto);
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

string cut_text(string text, int limit)
{
	if(text.length() < 13){
		return text;
	}
	string resultado = "";
	int word_length = 0;
	for(int i = 0; i<text.length(); i++){
		if(text[i] == ' '){
			word_length = 0;
			if(i > 0 && text[i-1] == ' '){
				continue;
			}
		}
		if(resultado.length() >= limit){
			if(word_length <= 1){
				resultado = resultado.substr(0, resultado.length() - word_length - 2);
			}
			if(text.length() - resultado.length() > 3){
				resultado += "...";
			}
			break;
		}
		word_length++;
		resultado += text[i];
	}
	return resultado;
}