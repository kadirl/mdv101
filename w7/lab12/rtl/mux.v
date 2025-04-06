module mux (
    input [15:0] in [0:7],  // 8 inputs, each 16 bits (unpacked array)
    input [2:0] sel,        // 3-bit select (since 2^3 = 8)
    output reg [15:0] out   // output
);
    always @(*) begin
        case (sel)
            3'd0: out = in[0];
            3'd1: out = in[1];
            3'd2: out = in[2];
            3'd3: out = in[3];
            3'd4: out = in[4];
            3'd5: out = in[5];
            3'd6: out = in[6];
            3'd7: out = in[7];
            default: out = 16'b0; // Optional fallback
        endcase
    end
endmodule
