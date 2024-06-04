/***************************************************************
 * Copyright(C), 2010-2022, WeChat:MCU149.
 * ModuleName : top_hdl.v 
 * Date       : 2022年9月27日
 * Time       : 20:19:39
 * Author     : WeChat:MCU149
 * Function   : gw1nsr-4c led driver demo
 * Version    : v1.0
 *      Version | Modify
 *      ----------------------------------
 *       v1.0    .....
 ***************************************************************/

module top_hdl(
    //Inputs
    input gclk,      // 27MHz
    input gresetn,    
    input key,
    input uart_rxd,

    //Outputs
    output uart_txd,
    output led
);

wire clk_60m;

wire arm_clk = clk_60m;
wire arm_resetn = gresetn;

wire arm_uart0_rxd = uart_rxd;
wire arm_uart0_txd;
wire [15:0] arm_gpio_in;
wire [15:0] arm_gpio_out;
wire [15:0] arm_gpio_outen;

assign uart_txd = arm_uart0_txd;
assign led = (arm_gpio_out[15:0] == 16'haaaa);
assign arm_gpio_in[15:0] = {16{key}};

Gowin_PLLVR pll_ut0(
    .clkout(clk_60m), //output clkout
    .clkin(gclk) //input clkin
);

Gowin_EMPU_Top arm_cortex_m3_core(
    //Inputs
    .sys_clk(arm_clk),
    .reset_n(arm_resetn),
    .uart0_rxd(arm_uart0_rxd), 
    .gpioin(arm_gpio_in[15:0]),

    //Outputs
    .uart0_txd(arm_uart0_txd),
    .gpioout(arm_gpio_out[15:0]),
    .gpioouten(arm_gpio_outen[15:0])
);

endmodule   //top_hdl end

