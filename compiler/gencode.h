#include "stdlib.h"
#include "string.h"

typedef struct {
	char* label;
	int pc;
} label_info;

void label_info_pushback(label_info **lblst,char **lb,int pc,int* longitud,int *capacidad){
	if(*lblst == NULL){*lblst = (label_info*)malloc(sizeof(label_info)*(*capacidad));}

  if (*longitud >= *capacidad) {
     *capacidad *= 2;
     label_info *temp = realloc(*lblst, (*capacidad) * sizeof(label_info));
     if (temp == NULL) {return;}
     *lblst = temp;
    }
		label_info li;
		li.label = *lb;
		li.pc = pc*4;
    (*lblst)[*longitud] = li; 
    (*longitud)++; 
}

int get_label_pc(label_info* lblst, int size, char* target_label) {
    for (int i = 0; i < size; i++) {
        if (strcmp(lblst[i].label, target_label) == 0) {
            return lblst[i].pc;
        }
    }
    return 0; // Etiqueta no encontrada
}

char* num_to_binary(char* input, int size) {
    long number = strtol(input, NULL, 0);
    char* binary_str = (char*)malloc(size + 1);
    if (binary_str == NULL) return NULL;

    for (int i = size - 1; i >= 0; i--) {
        binary_str[i] = (number & 1) ? '1' : '0';
        number >>= 1;
    }
    binary_str[size] = '\0'; 

    return binary_str;
}

char* reg_to_binary(char* input) {
	
	if(strcmp(input,"a0") == 0 ){ return "00000"; }
	if(strcmp(input,"a1") == 0 ){ return "00001"; }
	if(strcmp(input,"a2") == 0 ){ return "00010"; }
	if(strcmp(input,"a3") == 0 ){ return "00011"; }
	if(strcmp(input,"a4") == 0 ){ return "00100"; }
	if(strcmp(input,"a5") == 0 ){ return "00101"; }
	if(strcmp(input,"a6") == 0 ){ return "00110"; }

	return "00000";
}

char* slice_bin(char* src, int start, int end) {
    int len = end - start;
    if (len <= 0) return NULL;

    // Reservamos espacio para el fragmento + el terminador nulo
    char* fragmento = (char*)malloc(len + 1);
    if (fragmento == NULL) return NULL;

    // Copiamos la sección de la memoria
    memcpy(fragmento, &src[start], len);
    
    // Agregamos el terminador para que sprintf no explote
    fragmento[len] = '\0';

    return fragmento;
}

char* generate_code(Instruction *il,int in){
	char* program = (char*)malloc((32 * in + 1) * sizeof(char));
	memset(program, 0, 32 * in + 1); // Limpiar todo con nulos
																	 
	int lblst_size = 0;
	int lblst_cap = 4;
	label_info *lblst = NULL;
	
	for (int i = 0; i < in; i++) {
		if (il[i].i_type == T_TYPE) {
			label_info_pushback(&lblst, &il[i].data.t.label, il[i].i_num, &lblst_size, &lblst_cap);
		}
	}

	int curr_instr = 0;

	for (int i=0;i<in;i++){
		char* current_ptr = &program[32 * curr_instr];

		if(il[i].i_type == R_TYPE ) {
			const char* rs2 = reg_to_binary(il[i].data.r.rs2);
			const char* rs1 = reg_to_binary(il[i].data.r.rs1);
			const char* rd  = reg_to_binary(il[i].data.r.rd);

			if(il[i].data.r.op == ADD) sprintf(current_ptr , "0000000%s%s000%s0110011",rs2,rs1,rd );		
			else if((*(il+i)).data.r.op == SUB) sprintf(current_ptr , "0100000%s%s000%s0110011",rs2,rs1,rd);		
			else if((*(il+i)).data.r.op == XOR) sprintf(current_ptr , "0000000%s%s100%s0110011",rs2,rs1,rd);		
			else if((*(il+i)).data.r.op == OR)  sprintf(current_ptr , "0000000%s%s110%s0110011",rs2,rs1,rd);		
			else if((*(il+i)).data.r.op == AND) sprintf(current_ptr , "0000000%s%s111%s0110011",rs2,rs1,rd);		
			else if((*(il+i)).data.r.op == SLL) sprintf(current_ptr , "0000000%s%s001%s0110011",rs2,rs1,rd);		
			else if((*(il+i)).data.r.op == SRL)	sprintf(current_ptr, "0000000%s%s101%s0110011",rs2,rs1,rd);		
			else if((*(il+i)).data.r.op == SRA)	sprintf(current_ptr, "0100000%s%s101%s0110011",rs2,rs1,rd);				
			else if((*(il+i)).data.r.op == SLT) sprintf(current_ptr , "0000000%s%s010%s0110011",rs2,rs1,rd);				
			else if((*(il+i)).data.r.op == SLTU) sprintf(current_ptr, "0000000%s%s011%s0110011",rs2,rs1,rd);		
			curr_instr++;
		}
		else if(il[i].i_type == I_TYPE ) {
			const char* imm = num_to_binary(il[i].data.i.imm,12);
			const char* rs1 = reg_to_binary(il[i].data.i.rs1);
			const char* rd  = reg_to_binary(il[i].data.i.rd);

			if(il[i].data.i.op == ADDI) sprintf(current_ptr , "%s%s000%s0010011",imm,rs1,rd );		
			else if((*(il+i)).data.i.op == XORI) sprintf(current_ptr , "%s%s100%s0010011",imm,rs1,rd);		
			else if((*(il+i)).data.i.op == ORI)	sprintf(current_ptr , "%s%s110%s0010011",imm,rs1,rd);		
			else if((*(il+i)).data.i.op == ANDI) sprintf(current_ptr , "%s%s111%s0010011",imm,rs1,rd);		
			else if((*(il+i)).data.i.op == SLLI) sprintf(current_ptr , "%s%s001%s0010011",imm,rs1,rd);		
			else if((*(il+i)).data.i.op == SRLI) sprintf(current_ptr, "%s%s101%s0010011",imm,rs1,rd);		
			else if((*(il+i)).data.i.op == SRAI) sprintf(current_ptr, "%s%s101%s0010011",imm,rs1,rd);				
			else if((*(il+i)).data.i.op == SLTI) sprintf(current_ptr , "%s%s010%s0010011",imm,rs1,rd);				
			else if((*(il+i)).data.i.op == SLTIU) sprintf(current_ptr, "%s%s011%s0010011",imm,rs1,rd);		
			curr_instr++;
		}

		else if(il[i].i_type == L_TYPE ) {
			const char* imm = num_to_binary(il[i].data.l.imm,12);
			const char* rs1 = reg_to_binary(il[i].data.l.rs1);
			const char* rs2  = reg_to_binary(il[i].data.l.rs2);

			if((*(il+i)).data.l.op == LB) sprintf(current_ptr, "%s%s000%s0000011",imm,rs1,rs2); 				
			else if((*(il+i)).data.l.op == LH) sprintf(current_ptr , "%s%s001%s0000011",imm,rs1,rs2);				
			else if((*(il+i)).data.l.op == LW) sprintf(current_ptr, "%s%s010%s0000011",imm,rs1,rs2);		
			else if((*(il+i)).data.l.op == LBU) sprintf(current_ptr , "%s%s100%s0000011",imm,rs1,rs2);				
			else if((*(il+i)).data.l.op == LHU) sprintf(current_ptr, "%s%s101%s0000011",imm,rs1,rs2);		
			curr_instr++;
		}

		else if(il[i].i_type == S_TYPE ) {
			char* imm = num_to_binary(il[i].data.s.imm, 12);
			char* imm_11_5 = slice_bin(imm, 0, 7);  // Bits 11 al 5
			char* imm_4_0  = slice_bin(imm, 7, 12); // Bits 4 al 0
			const char* rs2 = reg_to_binary(il[i].data.s.rs2);
			const char* rs1 = reg_to_binary(il[i].data.s.rs1);

			if(il[i].data.s.op == SB)      sprintf(current_ptr, "%s%s%s000%s0100011", imm_11_5, rs2, rs1, imm_4_0);
			else if(il[i].data.s.op == SH) sprintf(current_ptr, "%s%s%s001%s0100011", imm_11_5, rs2, rs1, imm_4_0);
			else if(il[i].data.s.op == SW) sprintf(current_ptr, "%s%s%s010%s0100011", imm_11_5, rs2, rs1, imm_4_0);

			free(imm); free(imm_11_5); free(imm_4_0);
			curr_instr++;
		}
		

		else if (il[i].i_type == B_TYPE) {
			int pc_destino = get_label_pc(lblst, lblst_size, il[i].data.b.label);
			int pc_actual = il[i].i_num * 4;
			int offset = pc_destino - pc_actual;

			char offset_str[20];
			sprintf(offset_str, "%d", offset);
			char* imm = num_to_binary(offset_str, 13);

			char* b_12   = slice_bin(imm, 0, 1);
			char* b_11   = slice_bin(imm, 1, 2);
			char* b_10_5 = slice_bin(imm, 2, 8);
			char* b_4_1  = slice_bin(imm, 8, 12);
			const char* rs2 = reg_to_binary(il[i].data.b.rs2);
			const char* rs1 = reg_to_binary(il[i].data.b.rs1);

			const char* funct3 = "000";
			if(il[i].data.b.op == BEQ) funct3 = "000";
			else if(il[i].data.b.op == BNE) funct3 = "001";
			else if(il[i].data.b.op == BLT) funct3 = "100";
			else if(il[i].data.b.op == BGE) funct3 = "101";
			else if(il[i].data.b.op == BLTU) funct3 = "110";
			else if(il[i].data.b.op == BGEU) funct3 = "111";

			sprintf(current_ptr, "%s%s%s%s%s%s%s1100011", b_12, b_10_5, rs2, rs1, funct3, b_4_1, b_11);

			free(imm); free(b_12); free(b_11); free(b_10_5); free(b_4_1);
			curr_instr++;
		}

		else if (il[i].i_type == J_TYPE) {
			int pc_destino = get_label_pc(lblst, lblst_size, il[i].data.j.label);
			int pc_actual = il[i].i_num * 4;
			int offset = pc_destino - pc_actual;

			char offset_str[20];
			sprintf(offset_str, "%d", offset);
			char* imm = num_to_binary(offset_str, 21);

			char* j_20    = slice_bin(imm, 0, 1);   // bit 20
			char* j_10_1  = slice_bin(imm, 10, 20); // bits 10:1
			char* j_11    = slice_bin(imm, 9, 10);  // bit 11
			char* j_19_12 = slice_bin(imm, 1, 9);   // bits 19:12
			//const char* rd = reg_to_binary(il[i].data.j.rd);
			const char* rd = "00000";

			// IMPORTANTE: Agregamos el rd que faltaba en tu sprintf
			sprintf(current_ptr, "%s%s%s%s%s1101111", j_20, j_10_1, j_11, j_19_12, rd);

			free(imm); free(j_20); free(j_10_1); free(j_11); free(j_19_12);
			curr_instr++;
		}
		else if (il[i].i_type == T_TYPE) {

		}
		else if(il[i].i_type == U_TYPE ) {
			const char* rd = reg_to_binary(il[i].data.u.rd);
			char* imm = num_to_binary(il[i].data.u.imm, 20); // 20 bits superiores
			sprintf(current_ptr, "%s%s0110111", imm, rd);
			free(imm);
			curr_instr++;
		}
		else {
			printf("QUEFUE?\n");
		}
	}

	free(lblst);
	return program;
}
