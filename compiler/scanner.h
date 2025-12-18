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

	if(isdigit(c)) {
		current++;
		while (current < end && isdigit(source[current])) {
			current++;
		}
		token = fetchToken_char_ptr(NUM,source,first,current);
	}
	else if (isalpha(c)) {
		current++;
		while (current < end && isalnum(source[current])){
			current++;
		}
		char* lexema = (char*)malloc(sizeof(char) * (current-first));
		for (int i=first,j=0;i<current;i++,j++){
			lexema[j] = source[i];
		}

		if(strcmp(lexema,"ADD") == 0){token = fetchToken_char_ptr(ADD,source,first,current);}
		else if(strcmp(lexema,"SUB") == 0){token = fetchToken_char_ptr(SUB,source,first,current);}
		else if(strcmp(lexema,"XOR") == 0){token = fetchToken_char_ptr(XOR,source,first,current);}
		else if(strcmp(lexema,"OR") == 0){token = fetchToken_char_ptr(OR,source,first,current);}
		else if(strcmp(lexema,"AND") == 0){token = fetchToken_char_ptr(AND,source,first,current);}
		else if(strcmp(lexema,"SLL") == 0){token = fetchToken_char_ptr(SLL,source,first,current);}
		else if(strcmp(lexema,"SRL") == 0){token = fetchToken_char_ptr(SRL,source,first,current);}
		else if(strcmp(lexema,"SRA") == 0){token = fetchToken_char_ptr(SRA,source,first,current);}
		else if(strcmp(lexema,"SLT") == 0){token = fetchToken_char_ptr(SLT,source,first,current);}
		else if(strcmp(lexema,"SLTU") == 0){token = fetchToken_char_ptr(SLTU,source,first,current);}
		else if(strcmp(lexema,"ADDI") == 0){token = fetchToken_char_ptr(ADDI,source,first,current);}
		else if(strcmp(lexema,"XORI") == 0){token = fetchToken_char_ptr(XORI,source,first,current);}
		else if(strcmp(lexema,"ORI") == 0){token = fetchToken_char_ptr(ORI,source,first,current);}
		else if(strcmp(lexema,"ANDI") == 0){token = fetchToken_char_ptr(ANDI,source,first,current);}
		else if(strcmp(lexema,"SLLI") == 0){token = fetchToken_char_ptr(SLLI,source,first,current);}
		else if(strcmp(lexema,"SRLI") == 0){token = fetchToken_char_ptr(SRLI,source,first,current);}
		else if(strcmp(lexema,"SRAI") == 0){token = fetchToken_char_ptr(SRAI,source,first,current);}
		else if(strcmp(lexema,"SLTI") == 0){token = fetchToken_char_ptr(SLTI,source,first,current);}
		else if(strcmp(lexema,"SLTIU") == 0){token = fetchToken_char_ptr(SLTIU,source,first,current);}
		else if(strcmp(lexema,"LB") == 0){token = fetchToken_char_ptr(LB,source,first,current);}
		else if(strcmp(lexema,"LH") == 0){token = fetchToken_char_ptr(LH,source,first,current);}
		else if(strcmp(lexema,"LW") == 0){token = fetchToken_char_ptr(LW,source,first,current);}
		else if(strcmp(lexema,"LBU") == 0){token = fetchToken_char_ptr(LBU,source,first,current);}
		else if(strcmp(lexema,"LHU") == 0){token = fetchToken_char_ptr(LHU,source,first,current);}
		else if(strcmp(lexema,"SB") == 0){token = fetchToken_char_ptr(SB,source,first,current);}
		else if(strcmp(lexema,"SH") == 0){token = fetchToken_char_ptr(SH,source,first,current);}
		else if(strcmp(lexema,"SW") == 0){token = fetchToken_char_ptr(SW,source,first,current);}
		else if(strcmp(lexema,"BEQ") == 0){token = fetchToken_char_ptr(BEQ,source,first,current);}
		else if(strcmp(lexema,"BNE") == 0){token = fetchToken_char_ptr(BNE,source,first,current);}
		else if(strcmp(lexema,"BLT") == 0){token = fetchToken_char_ptr(BLT,source,first,current);}
		else if(strcmp(lexema,"BGE") == 0){token = fetchToken_char_ptr(BGE,source,first,current);}
		else if(strcmp(lexema,"BLTU") == 0){token = fetchToken_char_ptr(BLTU,source,first,current);}
		else if(strcmp(lexema,"BGEU") == 0){token = fetchToken_char_ptr(BGEU,source,first,current);}
		else if(strcmp(lexema,"JAL") == 0){token = fetchToken_char_ptr(JAL,source,first,current);}
		else if(strcmp(lexema,"JALR") == 0){token = fetchToken_char_ptr(JALR,source,first,current);}
		else if(strcmp(lexema,"LUI") == 0){token = fetchToken_char_ptr(LUI,source,first,current);}
		else if(strcmp(lexema,"A0") == 0){token = fetchToken_char_ptr(A0,source,first,current);}
		else if(strcmp(lexema,"A1") == 0){token = fetchToken_char_ptr(A1,source,first,current);}
		else if(strcmp(lexema,"A2") == 0){token = fetchToken_char_ptr(A2,source,first,current);}
		else if(strcmp(lexema,"A3") == 0){token = fetchToken_char_ptr(A3,source,first,current);}
		else if(strcmp(lexema,"A4") == 0){token = fetchToken_char_ptr(A4,source,first,current);}
		else if(strcmp(lexema,"A5") == 0){token = fetchToken_char_ptr(A5,source,first,current);}
		else if(strcmp(lexema,"A6") == 0){token = fetchToken_char_ptr(A6,source,first,current);}
		else if(strcmp(lexema,"A7") == 0){token = fetchToken_char_ptr(A7,source,first,current);}
		
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
