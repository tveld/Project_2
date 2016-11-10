// Cross Reference Generator
// Troy Veldhuizen
// proj2.c

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <string.h>

typedef enum { false, true } bool;

bool building_id;

void build_id(list_t* list, char* str, char ch, int line){

	if(isalpha(ch) || ch == '_'){

		char append[2] = {ch, '\0'};
		strcat(str, append);
		building_id = true;
	} else {
		if(building_id){
			building_id = false;
			int len = strlen(str);
			char* newString = (char*)malloc(len + 1);
			strcpy(newString, str);
			list_insert(list,line,newString);

			str[0] = '\0';
		}
	}

}



int main() {
	

	char ch;
	char str[1024];
	int line = 1;
	bool in_id = false;  // in the id
	bool in_ws = false; // in the whitespace
	bool in_long_comment = false;
	bool in_line_comment = false;
	bool in_string = false;
	
	FILE *fin;

	list_t * list = malloc(sizeof(list_t));
	
	fin = fopen("date.c", "r");

	while((ch = fgetc(fin)) != EOF){
		
	
		if(ch == '\n'){
			line++;
			if(in_line_comment){
				in_line_comment = false;
			}
		}
		else if(ch == '\"'){
			if(in_string == true){
				in_string = false;
			} else {
				in_string = true;
			}
		}
		else if(ch == '/'){
			ch = fgetc(fin);
			if(ch != EOF){
				if(ch == '/'){
					in_line_comment = true;
				} else if(ch == '*'){
					in_long_comment = true;
				} else if(!in_long_comment && !in_line_comment && !in_string){
					build_id(list,str,ch,line);
				}
			} else if(ch == EOF){
				break;
			} else if(ch == '\n'){
				line++;
			}
		} else if(ch == '*'){
			ch = fgetc(fin);
			if(ch != EOF){
				if(ch == '/'){;
					in_long_comment = false;
				} else if(!in_long_comment && !in_line_comment && !in_string){
					build_id(list,str,ch,line);
				}
			} else if(ch == EOF){
				break;
			} else if(ch == '\n'){
				line++;
			}
		} else if((!in_long_comment) && (!in_line_comment) && (!in_string)){
			build_id(list,str,ch,line);
		}

	}


	print_list(list);
	free(list);
	fclose(fin);
	return 0;

}


