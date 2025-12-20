typedef enum {
	ADD,
	SUB,
	XOR,
	OR,
	AND,
	SLL,
	SRL,
	SRA,
	SLT,
	SLTU,
	ADDI,
	XORI,
	ORI,
	ANDI,
	SLLI,
	SRLI,
	SRAI,
	SLTI,
	SLTIU,
	LB,
	LH,
	LW,
	LBU,
	LHU,
	SB,
	SH,
	SW,
	BEQ,
	BNE,
	BLT,
	BGE,
	BLTU,
	BGEU,
	JAL,
	JALR,
	LUI,
	COLON,
	COMMA,
	ID,
	DEC,
	HEX,
	LPAREN,
	RPAREN,
	A0,
	A1,
	A2,
	A3,
	A4,
	A5,
	A6,
	A7,
	ERR,
	END
} TokenType;


typedef struct {
	TokenType type;
char* text;
} Token;


Token fetchToken(TokenType type){
	Token tk;
	tk.type = type;
	return tk;
}

Token fetchToken_char(TokenType type,char text){
	Token tk;
	tk.type = type;
	tk.text = (char*)malloc(sizeof(char));
	*tk.text = text;
	return tk;
}

Token fetchToken_char_ptr(TokenType type,char *source,int begin,int end){
	Token tk;
	tk.type = type;
	int len = end - begin;
	tk.text = (char*)malloc(sizeof(char) * (len+1));
	for(int i = 0; i < len; i++) {
  	tk.text[i] = source[begin + i];
  }
  tk.text[len] = '\0'; 
	
	return tk;
}


void token_list_pushback(Token **token_list, Token tk, int *longitud, int *capacidad) {
    if (*token_list == NULL) {
        *token_list = (Token*)malloc(sizeof(Token) * (*capacidad));
    }

    if (*longitud >= *capacidad) {
        *capacidad *= 2;
        Token *temp = realloc(*token_list, (*capacidad) * sizeof(Token));
        if (temp == NULL) {
            return;
        }
        *token_list = temp;
    }

    (*token_list)[*longitud] = tk; 
    (*longitud)++; 
}


void print_TokenList(Token **token_list,int size){
	for (int i=0;i<size-1;i++){
		printf("TOKEN: %s | %d \n",(*token_list)[i].text,(*token_list)[i].type);	
	}
}
