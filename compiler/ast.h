
typedef enum {
	INST_R,INST_I,INST_S,INST_L,INST_B,INST_U,INST_J,TAG
} InstType;


typedef struct {
	char *label;
} Tag;

typedef struct {
	char *rs1;
	char *rs2;
	char *rd;
	int op;
} Rtype;

typedef struct {
	char *rs1;
	char *rd;
	char *imm;
	int op;
} Itype;

typedef struct {
	char *rs1;
	char *rs2;
	char *imm;
	int op;
} Stype;

typedef struct {
	char *rs1;
	char *rs2;
	char *imm;
	int op;
} Ltype;

typedef struct {
	char *rs1;
	char *rs2;
	char* label;
	int op;
} Btype;

typedef struct {
	char *rd;
	char *imm;
} Utype;

typedef struct {
	char *rd;
	char *label;
	char *imm;
} Jtype;

typedef struct {
	InstType type;
	int i_num;
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

Instruction* new_tag(char* label,int pc,int i_num){
	Instruction *inst = malloc(sizeof(Instruction));
	inst->type = TAG;
	inst->i_num = i_num;

	inst->data.t.label = label;
}

Instruction* new_r_type(int op,char *rd,char *rs1,char *rs2,int i_num) {
	Instruction *inst = malloc(sizeof(Instruction));
	inst->type = INST_R;
	inst->i_num = i_num;

	inst->data.r.op = op;
	inst->data.r.rd = rd;
	inst->data.r.rs1 = rs1;
	inst->data.r.rs2 = rs2;
}

Instruction* new_i_type(int op,char *rd,char *rs1,char *imm,int i_num) {
	Instruction *inst = malloc(sizeof(Instruction));
	inst->type = INST_R;
	inst->i_num = i_num;

	inst->data.i.op = op;
	inst->data.i.rd = rd;
	inst->data.i.rs1 = rs1;
	inst->data.i.imm = imm;
}

Instruction* new_s_type(int op,char *rs1,char *rs2,char *imm,int i_num) {
	Instruction *inst = malloc(sizeof(Instruction));
	inst->type = INST_R;
	inst->i_num = i_num;

	inst->data.s.op = op;
	inst->data.s.rs1 = rs1;
	inst->data.s.rs2 = rs2;
	inst->data.s.imm = imm;
}

Instruction* new_l_type(int op,char *rs1,char *rs2,char *imm,int i_num) {
	Instruction *inst = malloc(sizeof(Instruction));
	inst->type = INST_R;
	inst->i_num = i_num;

	inst->data.l.op = op;
	inst->data.l.rs1 = rs1;
	inst->data.l.rs2 = rs2;
	inst->data.l.imm = imm;
}

Instruction* new_b_type(int op,char *rs1,char *rs2,char *label,int i_num) {
	Instruction *inst = malloc(sizeof(Instruction));
	inst->type = INST_R;
	inst->i_num = i_num;

	inst->data.b.op = op;
	inst->data.b.rs1 = rs1;
	inst->data.b.rs2 = rs2;
	inst->data.b.label = label;
}

Instruction* new_u_type(char *rd,char *imm,int i_num) {
	Instruction *inst = malloc(sizeof(Instruction));
	inst->type = INST_R;
	inst->i_num = i_num;
	
	inst->data.u.rd = rd;
	inst->data.u.imm = imm;
}

Instruction* new_j_type(char *rd,char *label,char *imm,int i_num) {
	Instruction *inst = malloc(sizeof(Instruction));
	inst->type = INST_R;
	inst->i_num = i_num;

	inst->data.j.rd = rd;
	inst->data.j.label = label;
	inst->data.j.imm = imm;
}
