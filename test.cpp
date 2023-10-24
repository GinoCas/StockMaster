/*string input_paragraph(){
	string text = "";
	char carac;
	vector<string> word_list;
	string last_word = "";
	int carac_idx = 0;
	while((carac = getch()) != '\r'){
		if(carac == ' '){
			word_list.push_back(last_word);
			last_word = "";
		}
		if(carac == '\b'){
			if(carac_idx == 0){
				continue;
			}
			cout<<"\b \b";
			carac_idx--;
			if(text[carac_idx] == ' '){
				word_list.pop_back();
				last_word = word_list[word_list.size()];
			}else{
				last_word = last_word.substr(0, last_word.length() - 1);	
			}
			cursor(0,20);
			cout<<last_word;
			text = text.substr(0, text.length()-1);
			cursor(15 + carac_idx % 44, 7 + ceil(carac_idx / 44));
			if(text[carac_idx-1] == '_'){
				cursor(15, -1);
				for(int i = 0; i<last_word.length(); i++){
					cout<<" ";
					carac_idx--;
				}
				text = text.substr(0, text.length() - last_word.length() - 1);
				carac_idx -= last_word.length()+1;
				cursor(15 + carac_idx % 44, 7 + ceil(carac_idx / 44));
				cout<<last_word;
				carac_idx += last_word.length();
			}
			continue;
		}
		if(carac != ' '){
			last_word += carac;	
		}
		carac_idx++;
		cout<<carac;
		cursor(15 + carac_idx % 44, 7 + ceil(carac_idx / 44));
		if(carac_idx % 44 == 0){
			if(text[carac_idx-1] != ' ' && last_word.length() < 20){
				cursor(15 + 44 - last_word.length(), 7 + ceil(carac_idx / 44) - 1);
				for(int i = 0; i<last_word.length(); i++){
					cout<<" ";
				}
				cursor(15 + carac_idx % 44, 7 + ceil(carac_idx / 44));
				for(int i = 0; i<last_word.length(); i++){
					text += "_";
				}
				carac_idx += last_word.length();
				cout<<last_word;
			}
		}
		text += carac;
	}
	return text;
}*/