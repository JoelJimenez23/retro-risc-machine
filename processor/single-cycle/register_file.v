module regfile (
	clk,
	reset,
	we3,
	ra1,
	ra2,
	ra3,
	wd3,
	rd1,
	rd2,
);
	input wire clk;
	input wire reset;
	input wire we3;
	input wire [4:0] ra1;
	input wire [4:0] ra2;
	input wire [4:0] ra3;
	input wire [31:0] wd3;
	output wire [31:0] rd1;
	output wire [31:0] rd2;

	reg [31:0] rf [31:0];

	wire [31:0] r0;
	wire [31:0] r1;
	wire [31:0] r2;
	wire [31:0] r3;
	wire [31:0] r4;
	wire [31:0] r5;
	wire [31:0] r6;
	wire [31:0] r7;
	wire [31:0] r8;
	wire [31:0] r9;
	wire [31:0] r10;
	wire [31:0] r11;
	wire [31:0] r12;
	wire [31:0] r13;
	wire [31:0] r14;
	wire [31:0] r15;
	wire [31:0] r16;
	wire [31:0] r17;
	wire [31:0] r18;
	wire [31:0] r19;
	wire [31:0] r20;
	wire [31:0] r21;
	wire [31:0] r22;
	wire [31:0] r23;
	wire [31:0] r24;
	wire [31:0] r25;
	wire [31:0] r26;
	wire [31:0] r27;
	wire [31:0] r28;
	wire [31:0] r29;
	wire [31:0] r30;
	wire [31:0] r31;
	wire [31:0] r32;

	always @(posedge clk) begin
		rf[0] <= 0;
		if (we3)
			rf[ra3] <= wd3;
	end

	integer i;
	always @(posedge reset) begin
		if (reset) begin
			for (i = 0;i < 32 ; i = i + 1) begin
				if(i==8 | i == 2)
					rf[i] <= 32'h00000040;
				else
					rf[i] <= 0;
			end
		end 
	end

	assign rd1 = rf[ra1];
	assign rd2 = rf[ra2];

	assign r0 = rf[0];
	assign r1 = rf[1];
	assign r2 = rf[2];
	assign r3 = rf[3];
	assign r4 = rf[4];
	assign r5 = rf[5];
	assign r6 = rf[6];
	assign r7 = rf[7];
	assign r8 = rf[8];
	assign r9 = rf[9];
	assign r10 = rf[10];
	assign r11 = rf[11];
	assign r12 = rf[12];
	assign r13 = rf[13];
	assign r14 = rf[14];
	assign r15 = rf[15];
	assign r16 = rf[16];
	assign r17 = rf[17];
	assign r18 = rf[18];
	assign r19 = rf[19];
	assign r20 = rf[20];
	assign r21 = rf[21];
	assign r22 = rf[22];
	assign r23 = rf[23];
	assign r24 = rf[24];
	assign r25 = rf[25];
	assign r26 = rf[26];
	assign r27 = rf[27];
	assign r28 = rf[28];
	assign r29 = rf[29];
	assign r30 = rf[30];
	assign r31 = rf[31];




endmodule
