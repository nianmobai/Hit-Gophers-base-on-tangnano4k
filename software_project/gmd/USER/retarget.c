/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2019 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file        retarget.c
 * @author      Embedded Development Team
 * @version     V1.0.0
 * @date        2019-10-1 09:00:00
 * @brief       UART printf and scanf retarget function.
 ******************************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "gw1ns4c.h"
#include <stdio.h>
#include <sys/stat.h>

__attribute__ ((used))  int _write (int fd, char *ptr, int len)
{
  size_t i;

  for (i=0; i<len; i++)
  {
    UART_SendChar(UART0,ptr[i]); // call character output function
  }

  return len;
}
