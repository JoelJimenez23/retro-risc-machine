#include<stdlib.h>

typedef struct {
    Token *tokens;   
    Token *current;  
    Token *previous; 
		int i_num;
} Parser;

void parser_init(Parser *p, Token *list) {
    p->tokens = list;
    p->current = list;
    p->previous = list;
		p->i_num = 0;
}

int parser_isAtEnd(Parser *p) {
    return p->current->type == END;
}

int parser_check(Parser *p, TokenType type) {
    if (parser_isAtEnd(p)) return 0;
    return p->current->type == type;
}

int parser_advance(Parser *p) {
    if (p->current->type != END) {
        p->previous = p->current;
        p->current++; 
        return 1;
    }
    return 0;
}

int parser_match(Parser *p, TokenType type) {
    if (p->current->type == type) {
        parser_advance(p);
        return 1;
    }
    return 0;
}


void Instruction_list_pushback(Instruction **instruction_list,Instruction instr,int *longitud,int *capacidad){
	if(*instruction_list == NULL) {
		*instruction_list = (Instruction*)malloc(sizeof(Instruction) * (*capacidad));
	}
	
	if (*longitud >= *capacidad) {
		*capacidad *= 2;
		Instruction *tmp = realloc(*instruction_list,(*capacidad)*sizeof(Instruction));
		if(tmp == NULL){
			return;
		}
		*instruction_list = tmp;
	}
	(*instruction_list)[*longitud] = instr;
	(*longitud)++;

}


Instruction* parser_Program(Parser *p,int *instr_cant) {
	Instruction *instruction_list = NULL;
	Instruction instr;
	int capacidad = 4;

	while(!parser_isAtEnd(p)){
		if(parser_check(p,ID)){
			parser_match(p,ID);
			instr = new_tag(p->previous->text,*instr_cant);
			Instruction_list_pushback(&instruction_list,instr,instr_cant,&capacidad);
			parser_match(p,COLON);
		} 
		else if(parser_check(p,LUI)){
			parser_match(p,LUI);
			parser_match(p,REG);
			char *reg = p->previous->text;
			parser_match(p,COMMA);
			parser_match(p,NUM);
			char *num = p->previous->text;
			instr = new_u_type(reg,num,*instr_cant);
			Instruction_list_pushback(&instruction_list,instr,instr_cant,&capacidad);
		}
		else if (parser_match(p,ADD) || parser_match(p,SUB) || parser_match(p,XOR) || parser_match(p,OR) || parser_match(p,AND) || parser_match(p,SLL) || parser_match(p,SRL) || parser_match(p,SRA) || parser_match(p,SLT) || parser_match(p,SLTU)){
			TokenType op = p->previous->type;
			parser_match(p,REG);
			char *rd = p->previous->text;
			parser_match(p,COMMA);
			parser_match(p,REG);
			char *rs1 = p->previous->text;
			parser_match(p,COMMA);
			parser_match(p,REG);
			char *rs2 = p->previous->text;
			instr = new_r_type(op,rd,rs1,rs2,*instr_cant);
			Instruction_list_pushback(&instruction_list,instr,instr_cant,&capacidad);
		}
		else if (parser_match(p,ADDI) || parser_match(p,XORI) || parser_match(p,ORI) || parser_match(p,ANDI) || parser_match(p,SLLI) || parser_match(p,SRLI) || parser_match(p,SRAI) || parser_match(p,SLTI) || parser_match(p,SLTIU)){
			TokenType op = p->previous->type;
			parser_match(p,REG);
			char *rd = p->previous->text;
			parser_match(p,COMMA);
			parser_match(p,REG);
			char *rs1 = p->previous->text;
			parser_match(p,COMMA);
			parser_match(p,NUM);
			char *imm = p->previous->text;
			instr = new_i_type(op,rd,rs1,imm,*instr_cant);
			Instruction_list_pushback(&instruction_list,instr,instr_cant,&capacidad);
		}
		else if (parser_match(p,LB) || parser_match(p,LH) || parser_match(p,LW) || parser_match(p,LBU) || parser_match(p,LHU)){
			TokenType op = p->previous->type;
			parser_match(p,REG);
			char *rs1 = p->previous->text;
			parser_match(p,COMMA);
			parser_match(p,NUM);
			char *imm = p->previous->text;
			parser_match(p,LPAREN);
			parser_match(p,REG);
			char *rs2 = p->previous->text;
			parser_match(p,RPAREN);
			instr = new_l_type(op,rs1,rs2,imm,*instr_cant);
			Instruction_list_pushback(&instruction_list,instr,instr_cant,&capacidad);
		}	
		else if (parser_match(p,SB) || parser_match(p,SH) || parser_match(p,SW)){
			TokenType op = p->previous->type;
			parser_match(p,REG);
			char *rs1 = p->previous->text;
			parser_match(p,COMMA);
			parser_match(p,NUM);
			char *imm = p->previous->text;
			parser_match(p,LPAREN);
			parser_match(p,REG);
			char *rs2 = p->previous->text;
			parser_match(p,RPAREN);
			instr = new_s_type(op,rs1,rs2,imm,*instr_cant);
			Instruction_list_pushback(&instruction_list,instr,instr_cant,&capacidad);
		}	
		else if (parser_match(p,BEQ) || parser_match(p,BNE) || parser_match(p,BLT) || parser_match(p,BGE) || parser_match(p,BLTU) || parser_match(p,BGEU)){
			TokenType op = p->previous->type;
			parser_match(p,REG);
			char *rs1 = p->previous->text;
			parser_match(p,COMMA);
			parser_match(p,REG);
			char *rs2 = p->previous->text;
			parser_match(p,COMMA);
			parser_match(p,ID);
			char *label = p->previous->text;
			instr = new_b_type(op,rs1,rs2,label,*instr_cant);
			Instruction_list_pushback(&instruction_list,instr,instr_cant,&capacidad);
		}
		else if (parser_match(p,J)){
			parser_match(p,ID);
			instr = new_j_type(p->previous->text,*instr_cant);
			Instruction_list_pushback(&instruction_list,instr,instr_cant,&capacidad);
		}
	
	}

	return instruction_list;
}
