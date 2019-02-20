/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-02-20     XiaojieFan     the first version
 */

#include <rtthread.h>
#include "spi_lora_sx12xx.h"
#include "drv_spi.h"
#include "radio.h"

/* Default configuration, please change according to the actual situation, support  spi device name */
#define SX12XX_DEVICE_NAME  "spi10"
#define BUFFER_SIZE                                 9 // Define the payload size here

extern tRadioDriver *Radio;
static struct rt_spi_device *spi_dev_sx1278 = RT_NULL;
const uint8_t PingMsg[] = "PING";
const uint8_t PongMsg[] = "PONG";
/* Test function */
static int sx12xx_test(int argc, char *argv[])
{
   
    char name[RT_NAME_MAX];
    if (argc == 2)
    {
        rt_strncpy(name, argv[1], RT_NAME_MAX);
    }
    else
    {
        rt_strncpy(name, SX12XX_DEVICE_NAME, RT_NAME_MAX);
    }
    if (spi_dev_sx1278 == RT_NULL)
    {
        spi_dev_sx1278 = sx12xx_init(name, RT_NULL);
        if (spi_dev_sx1278 == RT_NULL)
        {
            rt_kprintf("sx12xx init failed\n");
            return -1;
        }
    }
    rt_kprintf("sx12xx init succeed\n");

    if (0x91 != SX1276_Spi_Check())
    {
        rt_kprintf("sx12xx spi check failed!\n!");
    }
    else
    {
        rt_kprintf("sx12xx spi check ok!\n");
    }
    return 0;
}
MSH_CMD_EXPORT(sx12xx_test, lora chip sx12xx test function);
