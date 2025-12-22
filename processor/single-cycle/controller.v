module controller(
	clk,
	reset,
	Funct7,
	Funct3,
	OPcode,
	PCSrc,
	ResultSrc,
	MemWrite,
	ALUControl,
	ALUSrc,
	ImmSrc,
	RegWrite,
	Up,
	Zero,
	Sub
);

	input wire clk;
	input wire reset;
	input wire [6:0] Funct7;
	input wire [2:0] Funct3;
	input wire [6:0] OPcode;
	input wire Zero;

	output wire PCSrc;
	output wire [1:0] ResultSrc;
	output wire MemWrite;
	output reg [2:0] ALUControl;
	output wire ALUSrc;
	output wire [2:0] ImmSrc;
	output wire RegWrite;
	output wire Up;
	output wire Sub;

	wire Branch;
	wire [1:0] ALUOp;
	wire Jump;
	reg [11:0] controls;

	always @(*) begin
		casex (OPcode)
			7'b0000011 : begin
				controls = 12'b100010010000; //lw
			end
			7'b0100011 : begin
				controls = 12'b000111xx0000; //sw
			end
			7'b0110011 : begin
				controls = 12'b1xxx00000100; //r-type
			end
			7'b1100011 : begin
				controls = 12'b001000xx1010; //b-type
			end
			7'b0010011 : begin
				controls = 12'b100010000100; //i-type
			end
			7'b1101111 : begin
				controls = 12'b1100x0100xx1; //j-type
			end 
			7'b0110111 : begin
				controls = 12'b101110000xx0; //u-type
			end
			default : begin
				controls = 12'bxxxxxxxxxxxx;
			end
		endcase
	end

	assign {RegWrite,ImmSrc,ALUSrc,MemWrite,ResultSrc,Branch,ALUOp,Jump} = controls;
	assign Up = (ImmSrc === 3'b011) ? 1'b1 : 1'b0; 

	always @(*) begin
		casex (ALUOp) 
			2'b00 : begin
				ALUControl = 3'b000;
			end
			2'b01 : begin
				ALUControl = 3'b001;
			end
			2'b10 : begin
				casex (Funct3)
					3'b000 : begin 
						ALUControl = 3'b000; //add & sub
					end
					3'b001 : begin //sll
						ALUControl = 3'b001;
					end
					3'b010 : begin //slt
						ALUControl = 3'b010;
					end
					3'b011 : begin //sltu
						ALUControl = 3'b011;
					end
					3'b100 : begin //xor
						ALUControl = 3'b100;
					end
					3'b101 : begin //srl
						ALUControl = 3'b101;
					end
					3'b110 : begin //or
						ALUControl = 3'b110;
					end
					3'b111 : begin //and
						ALUControl = 3'b111;
					end
					default : begin
						ALUControl = 3'b000;
					end
				endcase
			end
			default : begin
				ALUControl = 3'b000;
			end
		endcase
	end

	assign Sub = (Funct3 == 3'b000 && OPcode[5] && Funct7[5]) ? 1 : 0;
	assign PCSrc = ((Zero && Branch ) || Jump );

endmodule
