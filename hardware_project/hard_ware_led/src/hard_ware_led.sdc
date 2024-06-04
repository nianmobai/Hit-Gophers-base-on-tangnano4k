//Copyright (C)2014-2024 GOWIN Semiconductor Corporation.
//All rights reserved.
//File Title: Timing Constraints file
//GOWIN Version: 1.9.9 Beta-4 Education
//Created Time: 2024-05-02 22:12:21
create_clock -name gclk -period 37.037 -waveform {0 18.518} [get_ports {gclk}]
