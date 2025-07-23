module lsu (
    // General ports
    input  wire clk,
    input  wire reset,    // Active-low reset
    output reg  done_out, // Signal indicating the operation is complete

    // Control and Data ports
    input  wire [ 1:0] en_ls,          // Load/Store control signal
    input  wire [ 7:0] address,        // 8-bit memory address
    input  wire [15:0] data_to_store,  // Data to be sent for storing
    output reg  [15:0] data_to_load,   // Data received from loading

    // Ports for UART Interaction
    input  wire       rx_do,         // Signal indicating data received from UART
    input  wire [7:0] rx_data,       // Data byte received from UART
    input  wire       tx_done,       // Signal indicating UART transmission is done
    output reg        tx_start_out,  // Signal to start UART transmission (active low)
    output reg  [7:0] tx_data_out    // Data byte to be transmitted over UART
);
    // Init a regular active-high instead of active-low
    wire reset_n;
    assign reset_n = !reset;

    // Init an empty memory
    reg [15:0] memory[1 << 8];

    always @(posedge clk or posedge reset_n) begin
        if (reset_n) begin
            data_to_load <= 16'b0;
        end else begin
            data_to_load <= memory[address];

            if (en_ls[0]) begin
                memory[address] <= data_to_store;
            end
        end
    end

    // always @(*) begin
    //     data_to_load <= memory[address];

    //     if (en_ls[0]) begin
    //         memory[address] <= data_to_store;
    //     end
    // end

    assign done_out = en_ls[0] | en_ls[1];

    // Dump signals for WAVES=1
    initial begin
        integer i;
        for (i = 0; i < 256; i = i + 1) memory[i] = 0;

        $dumpfile("dump1.vcd");
        $dumpvars(1, lsu);
    end

endmodule
