/***************************************************************
 * Copyright(C), 2010-2022, WeChat:MCU149
 * ModuleName : top_hdl.v 
 * Date       : 2022年9月27日
 * Time       : 20:19:39
 * Author     : WeChat:MCU149
 * Function   : gw1nsr-4c led driver demo
 * Version    : v1.0
 *      Version | Modify
 *      ----------------------------------
 *       v1.0    first version
 ***************************************************************/

module top_hdl(
    //Inputs
    input gclk,      // 27MHz
    input gresetn,    
    input key,

    //Outputs
    output reg led
);

//1.parameter

//2.localparam
localparam KEY_PRESS   = 1'b0;      //定义本地寄存器变量，表示按键1是否摁下的状态
                                                        //闪烁速度控制功能
localparam KEY_RELEASE = !KEY_PRESS;    //按键1的状态
localparam LED_ON      = 1'b1;          //LED灯开启
localparam LED_OFF     = !LED_ON;   //LED关闭

localparam LED_PERIOD1 = 27_000_000 / 2 ;      //500ms=27_000_000/2
localparam LED_PERIOD2 = 27_000_000 / 10;      //100ms=27_000_000/10

//3.reg
reg [31:0] cnt;

//4.wire 
wire [31:0] CNT_MAX = (key == KEY_PRESS) ? LED_PERIOD2 : LED_PERIOD1;

//5.assign

//6.always
always @ (posedge gclk) begin
    if(!gresetn) 
    begin
        cnt <= 'd0;
    end

    else begin
        if(cnt >= CNT_MAX)
            cnt <= 'd0;
        else 
            cnt <= cnt + 'd1;
    end
end

always @ (posedge gclk) begin
    if(!gresetn) 
        led <= LED_OFF;
    else if(cnt == CNT_MAX)
        led <= !led;
        // led <= (led == LED_OFF) ? LED_ON : LED_OFF;
end

//7.instance

endmodule   //top_hdl end
