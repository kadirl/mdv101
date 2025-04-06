module alu(
    input   wire        carry_in,
    input   wire [15:0] in_a,
    input   wire [15:0] in_b,
    input   wire [3:0]  select,
    input   wire        mode,

    output  wire        carry_out,
    output  wire        compare,
    output  wire [15:0] alu_out
);  
    wire [15:0] arithmetic_out, logic_out;
    wire compare_out;

    // Instantiate arithmetic_unit
    arithmetic_unit AU (
        .carry_in(carry_in),
        .in_a(in_a),
        .in_b(in_b),
        .select(select),
        .ar_out(arithmetic_out),
        .carry_out(carry_out),
        .comp_out(compare_out)
    );

    // Instantiate logic_unit
    logic_unit LU (
        .in_a(in_a),
        .in_b(in_b),
        .select(select),
        .log_out(logic_out)
    );

    // Default compare to 0 if not applicable
    assign compare = compare_out | 1'b0;

    // Select output based on mode using 2-to-1 MUX
    assign alu_out = mode ? logic_out : arithmetic_out;

endmodule


module arithmetic_unit(
    input   wire        carry_in,
    input   wire [15:0] in_a,
    input   wire [15:0] in_b,
    input   wire [3:0]  select,

    output  reg  [15:0] ar_out,
    output  reg        carry_out,
    output  wire [0:0]  comp_out
);
    // always output comp_out
    assign comp_out = (in_a == in_b);

    // pre-wire most common subparts
    wire [15:0] ab      = in_a & in_b;
    wire [15:0] anotb   = in_a & ~in_b;
    wire [15:0] aorb    = in_a | in_b;
    wire [15:0] aornotb = in_a | ~in_b;

    // MUX for ar_out
    always @(*) begin
        // assign carry_out to 0 by default
      	carry_out = 1'b0;
      
        case (select)
            // cases without carry output
            4'd0:   {carry_out, ar_out} = carry_in + in_a;                  // A
            4'd1:   {carry_out, ar_out} = carry_in + (in_a | in_b);           // A + B
            4'd2:   {carry_out, ar_out} = carry_in + (in_a | ~in_b);          // A + B'
            4'd3:   {carry_out, ar_out} = carry_in + {16{1'b1}};          // -1 in 2's complement
            4'd4:   {carry_out, ar_out} = carry_in + (in_a | anotb);          // A + AB'
            4'd5:   {carry_out, ar_out} = carry_in + (aorb | anotb); // (A + B) + AB'
            
            // cases with carry output
            4'd6:   {carry_out, ar_out} = carry_in + (in_a - in_b - 1);    // A minus B minus 1
            4'd7:   {carry_out, ar_out} = carry_in + (anotb - 1);          // AB' minus 1
            4'd8:   {carry_out, ar_out} = carry_in + (in_a + ab);             // A plus AB
            4'd9:   {carry_out, ar_out} = carry_in + (in_a + in_b);           // A plus B
            4'd10:  {carry_out, ar_out} = carry_in + (aornotb + ab);          // (A + B') plus AB
            4'd11:  {carry_out, ar_out} = carry_in + (ab - 1);             // AB minus 1
            4'd12:  {carry_out, ar_out} = carry_in + (in_a + in_a);           // A plus A
            4'd13:  {carry_out, ar_out} = carry_in + (aorb + in_a);           // (A + B) plus A
            4'd14:  {carry_out, ar_out} = carry_in + (aornotb + in_a);        // (A + B') plus A
            4'd15:  {carry_out, ar_out} = carry_in + (in_a - 1);           // A minus 1

            default: {carry_out, ar_out} = {1'b0, 16'b0}; 
        endcase
    end
endmodule


module logic_unit(
    input   wire [15:0] in_a,
    input   wire [15:0] in_b,
    input   wire [3:0]  select,

    output  reg  [15:0] log_out
);
        always @(*) begin
        case (select)
            4'd0:   log_out = ~in_a;            // A'
            4'd1:   log_out = ~(in_a | in_b);   // (A + B)'
            4'd2:   log_out = ~in_a & in_b;     // A'B
            4'd3:   log_out = 16'b0;            // 0
            4'd4:   log_out = ~(in_a & in_b);   // (AB)'
            4'd5:   log_out = ~in_b;            // B'
            4'd6:   log_out = in_a ^ in_b;      // A XOR B
            4'd7:   log_out = in_a & ~in_b;     // AB'
            4'd8:   log_out = ~in_a | in_b;     // A' + B
            4'd9:   log_out = ~(in_a ^ in_b);   // (A XOR B)'
            4'd10:  log_out = in_b;             // B
            4'd11:  log_out = in_a & in_b;      // AB
            4'd12:  log_out = 16'b1;            // 1
            4'd13:  log_out = in_a | ~in_b ;    // A + B'
            4'd14:  log_out = in_a | in_b ;     // A + B
            4'd15:  log_out = in_a  ;           // A
            default:    log_out = 16'b0;        // 0 by default
        endcase
    end

endmodule
