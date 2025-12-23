#include "ctype.h"
#include "string.h"

int is_white_space(char c){
	return c == ' ' || c == '\n' || c == '\r' || c == '\t'; 
}

Token nextToken(char *source,int begin,int *current_out,int end){
	Token token;
	int current = *current_out;

	while (current < end && is_white_space(source[current])) {
		current++;
	}
	
	if(current >= end){
		return fetchToken(END);
	}
	
	char c = source[current];
	int first = current;

	if(c == '-' || isdigit(c)) {
		int check_hex = (c == '-') ? current + 1 : current;

		if (check_hex + 1 < end && source[check_hex] == '0' && 
       (source[check_hex+1] == 'x' || source[check_hex+1] == 'X')) {
        
        current = check_hex + 2;
        while (current < end && isxdigit(source[current])) {
            current++;
        }
        token = fetchToken_char_ptr(NUM, source, first, current);
    } 
    else {
        if (c == '-') current++; 
        while (current < end && isdigit(source[current])) {
            current++;
        }
        token = fetchToken_char_ptr(NUM, source, first, current);
    }
  }


	else if (isalpha(c)) {
		current++;
		while (current < end && isalnum(source[current])){
			current++;
		}
		int len = current - first;
		char* lexema = (char*)malloc(sizeof(char) * (len+1));
		for (int i=first,j=0;i<current;i++,j++){
			lexema[j] = source[i];
		}
		lexema[len] = '\0';

		if(strcmp(lexema,"ADD") == 0 || strcmp(lexema,"add") == 0){token = fetchToken_char_ptr(ADD,source,first,current);}
		else if(strcmp(lexema,"SUB") == 0  || strcmp(lexema,"sub") == 0){token = fetchToken_char_ptr(SUB,source,first,current);}
		else if(strcmp(lexema,"XOR") == 0  || strcmp(lexema,"xor") == 0){token = fetchToken_char_ptr(XOR,source,first,current);}
		else if(strcmp(lexema,"OR") == 0   || strcmp(lexema,"or") == 0){token = fetchToken_char_ptr(OR,source,first,current);}
		else if(strcmp(lexema,"AND") == 0  || strcmp(lexema,"and") == 0){token = fetchToken_char_ptr(AND,source,first,current);}
		else if(strcmp(lexema,"SLL") == 0  || strcmp(lexema,"sll") == 0){token = fetchToken_char_ptr(SLL,source,first,current);}
		else if(strcmp(lexema,"SRL") == 0  || strcmp(lexema,"srl") == 0){token = fetchToken_char_ptr(SRL,source,first,current);}
		else if(strcmp(lexema,"SRA") == 0  || strcmp(lexema,"sra") == 0){token = fetchToken_char_ptr(SRA,source,first,current);}
		else if(strcmp(lexema,"SLT") == 0  || strcmp(lexema,"slt") == 0){token = fetchToken_char_ptr(SLT,source,first,current);}
		else if(strcmp(lexema,"SLTU") == 0 || strcmp(lexema,"sltu") == 0){token = fetchToken_char_ptr(SLTU,source,first,current);}
		else if(strcmp(lexema,"ADDI") == 0 || strcmp(lexema,"addi") == 0){token = fetchToken_char_ptr(ADDI,source,first,current);}
		else if(strcmp(lexema,"XORI") == 0 || strcmp(lexema,"xori") == 0){token = fetchToken_char_ptr(XORI,source,first,current);}
		else if(strcmp(lexema,"ORI") == 0  || strcmp(lexema,"ori") == 0){token = fetchToken_char_ptr(ORI,source,first,current);}
		else if(strcmp(lexema,"ANDI") == 0 || strcmp(lexema,"andi") == 0){token = fetchToken_char_ptr(ANDI,source,first,current);}
		else if(strcmp(lexema,"SLLI") == 0 || strcmp(lexema,"slli") == 0){token = fetchToken_char_ptr(SLLI,source,first,current);}
		else if(strcmp(lexema,"SRLI") == 0 || strcmp(lexema,"srli") == 0){token = fetchToken_char_ptr(SRLI,source,first,current);}
		else if(strcmp(lexema,"SRAI") == 0 || strcmp(lexema,"srai") == 0){token = fetchToken_char_ptr(SRAI,source,first,current);}
		else if(strcmp(lexema,"SLTI") == 0 || strcmp(lexema,"slti") == 0){token = fetchToken_char_ptr(SLTI,source,first,current);}
		else if(strcmp(lexema,"SLTIU") == 0||strcmp(lexema,"sltiu") == 0){token = fetchToken_char_ptr(SLTIU,source,first,current);}
		else if(strcmp(lexema,"LB") == 0   ||strcmp(lexema,"lb") == 0){token = fetchToken_char_ptr(LB,source,first,current);}
		else if(strcmp(lexema,"LH") == 0   ||strcmp(lexema,"lh") == 0){token = fetchToken_char_ptr(LH,source,first,current);}
		else if(strcmp(lexema,"LW") == 0   ||strcmp(lexema,"lw") == 0){token = fetchToken_char_ptr(LW,source,first,current);}
		else if(strcmp(lexema,"LBU") == 0  || strcmp(lexema,"lbu") == 0){token = fetchToken_char_ptr(LBU,source,first,current);}
		else if(strcmp(lexema,"LHU") == 0  || strcmp(lexema,"lhu") == 0){token = fetchToken_char_ptr(LHU,source,first,current);}
		else if(strcmp(lexema,"SB") == 0   || strcmp(lexema,"sb") == 0){token = fetchToken_char_ptr(SB,source,first,current);}
		else if(strcmp(lexema,"SH") == 0   || strcmp(lexema,"sh") == 0){token = fetchToken_char_ptr(SH,source,first,current);}
		else if(strcmp(lexema,"SW") == 0   || strcmp(lexema,"sw") == 0){token = fetchToken_char_ptr(SW,source,first,current);}
		else if(strcmp(lexema,"BEQ") == 0  || strcmp(lexema,"beq") == 0){token = fetchToken_char_ptr(BEQ,source,first,current);}
		else if(strcmp(lexema,"BNE") == 0  || strcmp(lexema,"bne") == 0){token = fetchToken_char_ptr(BNE,source,first,current);}
		else if(strcmp(lexema,"BLT") == 0  || strcmp(lexema,"blt") == 0){token = fetchToken_char_ptr(BLT,source,first,current);}
		else if(strcmp(lexema,"BGE") == 0  || strcmp(lexema,"bge") == 0){token = fetchToken_char_ptr(BGE,source,first,current);}
		else if(strcmp(lexema,"BLTU") == 0 || strcmp(lexema,"bltu") == 0){token = fetchToken_char_ptr(BLTU,source,first,current);}
		else if(strcmp(lexema,"BGEU") == 0 || strcmp(lexema,"bgeu") == 0){token = fetchToken_char_ptr(BGEU,source,first,current);}
		else if(strcmp(lexema,"LUI") == 0  || strcmp(lexema,"lui") == 0){token = fetchToken_char_ptr(LUI,source,first,current);}
		else if(strcmp(lexema,"ZERO") == 0 || strcmp(lexema,"zero") == 0){token = fetchToken_char_ptr(REG,source,first,current);}
		else if(strcmp(lexema,"RA") == 0 || strcmp(lexema,"ra") == 0){token = fetchToken_char_ptr(REG,source,first,current);}	
		else if(strcmp(lexema,"SP") == 0 || strcmp(lexema,"sp") == 0){token = fetchToken_char_ptr(REG,source,first,current);}	
		else if(strcmp(lexema,"GP") == 0 || strcmp(lexema,"gp") == 0){token = fetchToken_char_ptr(REG,source,first,current);}	
		else if(strcmp(lexema,"TP") == 0 || strcmp(lexema,"tp") == 0){token = fetchToken_char_ptr(REG,source,first,current);}	
		else if(strcmp(lexema,"T0") == 0 || strcmp(lexema,"t0") == 0){token = fetchToken_char_ptr(REG,source,first,current);}	
		else if(strcmp(lexema,"T1") == 0 || strcmp(lexema,"t1") == 0){token = fetchToken_char_ptr(REG,source,first,current);}	
		else if(strcmp(lexema,"T2") == 0 || strcmp(lexema,"t2") == 0){token = fetchToken_char_ptr(REG,source,first,current);}	
		else if(strcmp(lexema,"S0") == 0 || strcmp(lexema,"s0") == 0){token = fetchToken_char_ptr(REG,source,first,current);}	
		else if(strcmp(lexema,"FP") == 0 || strcmp(lexema,"fp") == 0){token = fetchToken_char_ptr(REG,source,first,current);}	
		else if(strcmp(lexema,"S1") == 0 || strcmp(lexema,"s1") == 0){token = fetchToken_char_ptr(REG,source,first,current);}	
		else if(strcmp(lexema,"A0") == 0 || strcmp(lexema,"a0") == 0){token = fetchToken_char_ptr(REG,source,first,current);}
		else if(strcmp(lexema,"A1") == 0 || strcmp(lexema,"a1") == 0){token = fetchToken_char_ptr(REG,source,first,current);}
		else if(strcmp(lexema,"A2") == 0 || strcmp(lexema,"a2") == 0){token = fetchToken_char_ptr(REG,source,first,current);}
		else if(strcmp(lexema,"A3") == 0 || strcmp(lexema,"a3") == 0){token = fetchToken_char_ptr(REG,source,first,current);}
		else if(strcmp(lexema,"A4") == 0 || strcmp(lexema,"a4") == 0){token = fetchToken_char_ptr(REG,source,first,current);}
		else if(strcmp(lexema,"A5") == 0 || strcmp(lexema,"a5") == 0){token = fetchToken_char_ptr(REG,source,first,current);}
		else if(strcmp(lexema,"A6") == 0 || strcmp(lexema,"a6") == 0){token = fetchToken_char_ptr(REG,source,first,current);}
		else if(strcmp(lexema,"A7") == 0 || strcmp(lexema,"a7") == 0){token = fetchToken_char_ptr(REG,source,first,current);}
		else if(strcmp(lexema,"S2") == 0 || strcmp(lexema,"s2") == 0){token = fetchToken_char_ptr(REG,source,first,current);}	
		else if(strcmp(lexema,"S3") == 0 || strcmp(lexema,"s3") == 0){token = fetchToken_char_ptr(REG,source,first,current);}	
		else if(strcmp(lexema,"S4") == 0 || strcmp(lexema,"s4") == 0){token = fetchToken_char_ptr(REG,source,first,current);}	
		else if(strcmp(lexema,"S5") == 0 || strcmp(lexema,"s5") == 0){token = fetchToken_char_ptr(REG,source,first,current);}	
		else if(strcmp(lexema,"S6") == 0 || strcmp(lexema,"s6") == 0){token = fetchToken_char_ptr(REG,source,first,current);}	
		else if(strcmp(lexema,"S7") == 0 || strcmp(lexema,"s7") == 0){token = fetchToken_char_ptr(REG,source,first,current);}	
		else if(strcmp(lexema,"S8") == 0 || strcmp(lexema,"s8") == 0){token = fetchToken_char_ptr(REG,source,first,current);}	
		else if(strcmp(lexema,"S9") == 0 || strcmp(lexema,"s9") == 0){token = fetchToken_char_ptr(REG,source,first,current);}	
		else if(strcmp(lexema,"S10") == 0 || strcmp(lexema,"s10") == 0){token = fetchToken_char_ptr(REG,source,first,current);}	
		else if(strcmp(lexema,"S11") == 0 || strcmp(lexema,"s11") == 0){token = fetchToken_char_ptr(REG,source,first,current);}	
		else if(strcmp(lexema,"T3") == 0 || strcmp(lexema,"t3") == 0){token = fetchToken_char_ptr(REG,source,first,current);}	
		else if(strcmp(lexema,"T4") == 0 || strcmp(lexema,"t4") == 0){token = fetchToken_char_ptr(REG,source,first,current);}	
		else if(strcmp(lexema,"T5") == 0 || strcmp(lexema,"t5") == 0){token = fetchToken_char_ptr(REG,source,first,current);}	
		else if(strcmp(lexema,"T6") == 0 || strcmp(lexema,"t6") == 0){token = fetchToken_char_ptr(REG,source,first,current);}	
		else if(strcmp(lexema,"J") == 0   || strcmp(lexema,"j") == 0){token = fetchToken_char_ptr(J,source,first,current);}

		else {token = fetchToken_char_ptr(ID,source,first,current);}

		free(lexema);
	}
	else if (strchr("(),:",c)) {
		current++;
		switch (c) {
			case '(':
				token = fetchToken_char_ptr(LPAREN,source,first,current);
				break;
			case ')': 	 
				token = fetchToken_char_ptr(RPAREN,source,first,current);
				break;	
			case ',':
				token = fetchToken_char_ptr(COMMA,source,first,current);
				break;
			case ':':
				token = fetchToken_char_ptr(COLON,source,first,current);
				break;
		}
	}
	else {
		current++;
	}

	*current_out = current;
	return token;
}

Token* ejecutar_scanner(char *cadena,int longitud,int *size){
	int current = 0;
	int current_out = 0;
	int capacidad = 1;
	Token token;
	Token *token_list = NULL;

	while(1){
		token = nextToken(cadena,0,&current_out,longitud);
		token_list_pushback(&token_list,token,&current,&capacidad);
		if(token.type == END){break;}
	}
	*size = current;
	return token_list;
}

