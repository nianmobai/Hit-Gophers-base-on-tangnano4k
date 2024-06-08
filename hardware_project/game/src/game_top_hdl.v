
module top_hdl(
    //Inputs
    input gclk,      // 27MHz
    input gresetn,    //arm核置位信号
    input key,//按键输入信号
    input [3:0]  KeyX,//键盘扫略输入的横向信号

    //Outputs
    output  led,//led灯信号，用以标志按键按下
    output sclk_out,//SPI的时钟输出
    output nss_out,//从设备使能信号
    output sda_out,//SPI输出信号
    output [3:0] KeyY,//键盘扫略输出的纵向信号
    output BLK,//屏幕
    output RES,//屏幕
    output DC//
);

wire clk_60m;

wire arm_clk = clk_60m;
wire arm_resetn = gresetn;

wire [15:0] arm_gpio_out;//gpio的输出，与LED灯的显示结合在一起
wire [15:0] arm_gpio_outen;//gpioouten的输出
reg [15:0] arm_gpio_in;//gpio的输入，与4*4键盘矩阵耦合在一起

reg [3:0] keyscan = 4'b0001;
reg [8:0] count = 8'h00;

wire valid;

//循环扫略键盘
always @(posedge gclk)
begin
if(count == 100)
begin
    count = 0;
    case(KeyY[3:0])
        4'B0001:begin
            arm_gpio_in[3:0] = KeyX[3:0];
            end
        4'B0010:begin
            arm_gpio_in[7:4] = KeyX[3:0];
            end
        4'B0100:begin
            arm_gpio_in[11:8] = KeyX[3:0];
            end
        4'B1000:begin
            arm_gpio_in[15:12] = KeyX[3:0];
            end
    endcase
        keyscan[3:0]  =  {keyscan[2:0],keyscan[3]};
end
else
begin
    count = count +1;
end
end

assign led = (arm_gpio_out[0] == 1'b1);
assign BLK = (arm_gpio_out[1] == 1'b1);//
assign RES = (arm_gpio_out[2] == 1'b1);
assign DC = (arm_gpio_out[3] == 1'b1);

//SPI port
assign sclk_out = arm_gpio_out[4];
assign nss_out = arm_gpio_out[5];
assign sda_out = arm_gpio_out[6];

assign KeyY[3:0] = keyscan[3:0];

Gowin_PLLVR pll_ut0(
    .clkout(clk_60m), //输出60Mhz的时钟频率
    .clkin(gclk) //输入27Mhz的时钟频率
);

Gowin_EMPU_Top CotexM3(
		.sys_clk(clk_60m), //input sys_clk 输入时钟信号
        .reset_n(arm_resetn), //input reset_n 输入复位信号

		.gpioin(arm_gpio_in), //input [15:0] gpioin GPIO输入
		.gpioout(arm_gpio_out), //output [15:0] gpioout GPIO输出
		.gpioouten(arm_gpio_outen) //output [15:0] gpioouten GPIO输出后

	);

endmodule   //top_hdl end