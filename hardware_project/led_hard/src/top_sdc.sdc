//Copyright (C)2014-2022 GOWIN Semiconductor Corporation.
//All rights reserved.
//File Title: Timing Constraints file
//GOWIN Version: 1.9.8.07 Education
//Created Time: 2022-09-27 22:43:29
create_clock -name gclk -period 37.037 -waveform {0 18.518} [get_ports {gclk}]
