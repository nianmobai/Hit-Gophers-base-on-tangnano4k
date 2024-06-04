`timescale 1ns/1ps

module top_hdl_tb;

localparam PERIOD = 10;      //ns

reg clk;
reg rst_n;
reg key;

always #(PERIOD/2) clk <= !clk;

initial begin
    //$display("testbench: %s", top_hdl_tb);

    rst_n = 0;
    clk = 0;
    key = 0;

    #(PERIOD*100)
    rst_n = 1;
    #(PERIOD*1000)
    key = 1;
    #(PERIOD*1000)
    key = 0;
    #(PERIOD*1000)
    $stop(0);
end

top_hdl top_hdl_ut0(
    //Inputs
    .gclk(clk),      // 27MHz
    .gresetn(rst_n),    
    .key(key),

    //Outputs
    .led()
);

endmodule   //top_hdl_tb end