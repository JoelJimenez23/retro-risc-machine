module extend (
    input  wire [31:0]  Instr,  // He ajustado el rango para mayor claridad
    input  wire [2:0]   ImmSrc, // Aumentado a 3 bits para cubrir más tipos
    output reg  [31:0]  ExtImm
);

    always @(*)
        case (ImmSrc)
            // I-type: Inmediatos de 12 bits (ej. addi, lw)
            3'b000: ExtImm = {{20{Instr[31]}}, Instr[31:20]};
            
            // S-type: Inmediatos de 12 bits para stores (sw, sb)
            3'b001: ExtImm = {{20{Instr[31]}}, Instr[31:25], Instr[11:7]};
            
            // B-type: Saltos condicionales (beq, bne). 
            // El bit 0 es siempre 0. El bit 11 y 12 están movidos.
            3'b010: ExtImm = {{20{Instr[31]}}, Instr[7], Instr[30:25], Instr[11:8], 1'b0};
            
            // U-type: Cargas en la parte alta (lui, auipc)
            // Los bits 31:12 se ponen directamente, los 12 bajos en 0.
            3'b011: ExtImm = {Instr[31:12], 12'b0};
            
            // J-type: Saltos incondicionales (jal)
            // El bit 0 es siempre 0. El orden es muy específico: 20 | 10:1 | 11 | 19:12
            3'b100: ExtImm = {{12{Instr[31]}}, Instr[19:12], Instr[20], Instr[30:21], 1'b0};

            default: ExtImm = 32'h00000000;
        endcase
endmodule
