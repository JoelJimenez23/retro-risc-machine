#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "token.h"
#include "scanner.h"
#include "ast.h"
#include "parser.h"
#include "gencode.h"

int main(int argc, const char* argv[]){
	if (argc != 2){
		printf("Numero incorrecto de argumentos.\n");
		return 1;
	}
	FILE* fp = fopen(argv[1],"r");
	
	if(!fp){
		printf("El archivo no se pudo abrir.\n");
		return 2;
	} 
	
	int longitud;
	char *cadena = file_to_string(fp,&longitud);
	
	fclose(fp);

	if (cadena == NULL){
		printf("Error: Memory allocation failed\n");
		return 3;
	}

	
	int size = 0;
	Token *token_list = ejecutar_scanner(cadena,longitud,&size);
	
	Parser p;
	int instruction_number = 0;	
	parser_init(&p, token_list);
	Instruction* instruction_list = parser_Program(&p,&instruction_number);



	char * code = generate_code(instruction_list,instruction_number);
	for(int i = 0; i < instruction_number; i++) {
		printf("%.32s\n", &code[i*32]);
	}

	return 0;
}
