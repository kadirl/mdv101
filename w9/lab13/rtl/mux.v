module mux (
    input [15:0] in [0:8],  // 9 inputs, each 16 bits (unpacked array)
    input [3:0] sel,        // 4-bit select (since 2^3 = 8)
    output reg [15:0] out   // output
);
    always @(*) begin
        case (sel)
            4'd0: out = in[0];
            4'd1: out = in[1];
            4'd2: out = in[2];
            4'd3: out = in[3];
            4'd4: out = in[4];
            4'd5: out = in[5];
            4'd6: out = in[6];
            4'd7: out = in[7];
            4'd8: out = in[8];  // for immediate value
            default: out = 16'b0; // Optional fallback
        endcase
    end
endmodule
