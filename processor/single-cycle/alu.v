module alu(preSrcA, preSrcB, ALUControl, ALUResult, Zero, Sub);
    input wire [31:0] preSrcA;
    input wire [31:0] preSrcB;
    input wire [2:0] ALUControl; 
    output reg [31:0] ALUResult;
    output wire Zero;
    input wire Sub;

    wire [31:0] condinvb;
    wire [31:0] sum; // Ya no necesitas 33 bits si no usas el carry out
    wire [31:0] SrcA, SrcB;
     
    assign SrcA = preSrcA;
    assign SrcB = preSrcB;

    // 1. Invertir bits si Sub es 1
    assign condinvb = Sub ? ~SrcB : SrcB; 
    
    // 2. LA CORRECCIÓN: Sumar el bit de Sub para completar el complemento a 2
    assign sum = SrcA + condinvb + Sub; 
    
    assign Zero = (ALUResult == 32'b0);

    always @(*) begin
        case (ALUControl[2:0])
            3'b000:  ALUResult = sum;            // add / sub
            3'b001:  ALUResult = SrcA << SrcB[4:0]; // sll (solo usa 5 bits para el shift)
            3'b010:  ALUResult = ($signed(SrcA) < $signed(SrcB)) ? 1 : 0; // slt (con signo)
            3'b011:  ALUResult = (SrcA < SrcB) ? 1 : 0;                   // sltu (sin signo)
            3'b100:  ALUResult = SrcA ^ SrcB;    // xor
            3'b101:  ALUResult = SrcA >> SrcB[4:0]; // srl
            3'b110:  ALUResult = SrcA | SrcB;    // OR bitwise (CORREGIDO)
            3'b111:  ALUResult = SrcA & SrcB;    // AND bitwise (CORREGIDO)
            default: ALUResult = sum;
        endcase
    end
endmodule
