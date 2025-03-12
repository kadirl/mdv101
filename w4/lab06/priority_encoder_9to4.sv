module priority_encoder_9to4 (
  input wire in8,  
  input wire in7,  
  input wire in6,
  input wire in5, 
  input wire in4,
  input wire in3,
  input wire in2, 
  input wire in1,
  input wire in0,

  output reg [3:0] out  // 4-bit output
);
  // create a vector of all inputs
  wire [8:0] input_vec;
  assign input_vec[8:0] = {in8, in7, in6, in5, in4, in3, in2, in1, in0};

always @(*) begin
  casez (input_vec)
    9'bzzzzzzzz1: out = 'd1;
    9'bzzzzzzz10: out = 'd2;
    9'bzzzzzz100: out = 'd3;
    9'bzzzzz1000: out = 'd4;
    9'bzzzz10000: out = 'd5;
    9'bzzz100000: out = 'd6;
    9'bzz1000000: out = 'd7;
    9'bz10000000: out = 'd8;
    9'b100000000: out = 'd9;
    default: out = 'd0;
  endcase
end

endmodule