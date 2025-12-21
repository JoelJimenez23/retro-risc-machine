typedef enum {
	T_TYPE,
	R_TYPE,
	I_TYPE,
	S_TYPE,
	L_TYPE,
	B_TYPE,
	U_TYPE,
	J_TYPE
} Instr_Type;

typedef struct {
	char *label;
} Tag;

typedef struct {
	char *rs1;
	char *rs2;
	char *rd;
	TokenType  op;
} Rtype;

typedef struct {
	char *rs1;
	char *rd;
	char *imm;
	TokenType op;
} Itype;

typedef struct {
	char *rs1;
	char *rs2;
	char *imm;
	TokenType op;
} Stype;

typedef struct {
	char *rs1;
	char *rs2;
	char *imm;
	TokenType op;
} Ltype;

typedef struct {
	char *rs1;
	char *rs2;
	char* label;
	TokenType op;
} Btype;

typedef struct {
	char *rd;
	char *imm;
} Utype;

typedef struct {
	char *label;
} Jtype;

typedef struct {
	int i_num;
	Instr_Type i_type;
	union {
		Tag t;
		Rtype r;
		Itype i;
		Stype s;
		Ltype l;
		Btype b;
		Utype u;
		Jtype j;
	} data;
} Instruction;

Instruction new_tag(char* label,int i_num){
	Instruction inst;
	inst.i_type = T_TYPE;
	inst.i_num = i_num;
	inst.data.t.label = label;
	return inst;
}

Instruction new_r_type(TokenType op,char *rd,char *rs1,char *rs2,int i_num) {
	Instruction inst;
	inst.i_num = i_num;
	inst.i_type = R_TYPE;
	inst.data.r.op = op;
	inst.data.r.rd = rd;
	inst.data.r.rs1 = rs1;
	inst.data.r.rs2 = rs2;

	return inst;
}

Instruction new_i_type(TokenType op,char *rd,char *rs1,char *imm,int i_num) {
	Instruction inst;
	inst.i_num = i_num;
	inst.i_type = I_TYPE;
	inst.data.i.op = op;
	inst.data.i.rd = rd;
	inst.data.i.rs1 = rs1;
	inst.data.i.imm = imm;

	return inst;
}

Instruction new_s_type(TokenType op,char *rs1,char *rs2,char *imm,int i_num) {
	Instruction inst;
	inst.i_num = i_num;
	inst.i_type = S_TYPE;
	inst.data.s.op = op;
	inst.data.s.rs1 = rs1;
	inst.data.s.rs2 = rs2;
	inst.data.s.imm = imm;
	
	return inst;
}

Instruction new_l_type(TokenType op,char *rs1,char *rs2,char *imm,int i_num) {
	Instruction inst;
	inst.i_num = i_num;
	inst.i_type = L_TYPE;
	inst.data.l.op = op;
	inst.data.l.rs1 = rs1;
	inst.data.l.rs2 = rs2;
	inst.data.l.imm = imm;

	return inst;
}

Instruction new_b_type(TokenType op,char *rs1,char *rs2,char *label,int i_num) {
	Instruction inst;
	inst.i_num = i_num;
	inst.i_type = B_TYPE;
	inst.data.b.op = op;
	inst.data.b.rs1 = rs1;
	inst.data.b.rs2 = rs2;
	inst.data.b.label = label;

	return inst;
}

Instruction new_u_type(char *rd,char *imm,int i_num) {
	Instruction inst;
	inst.i_num = i_num;
	inst.i_type = U_TYPE;
	inst.data.u.rd = rd;
	inst.data.u.imm = imm;

	return inst;
}

Instruction new_j_type(char *label,int i_num) {
	Instruction inst;
	inst.i_num = i_num;
	inst.i_type = J_TYPE;
	inst.data.j.label = label;

	return inst;
}
