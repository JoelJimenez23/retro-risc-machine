module regfile (
	clk,
	we3,
	ra1,
	ra2,
	ra3,
	wd3,
	rd1,
	rd2,
);
	input wire clk;
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

	always @(posedge clk) begin
		if (we3)
			rf[ra3] <= wd3;
	end

	assign rd1 = rf[ra1];
	assign rd2 = rf[ra2];

	assign r0 = rf[0];
	assign r1 = rf[1];
	assign r2 = rf[2];
	assign r3 = rf[3];

endmodule
