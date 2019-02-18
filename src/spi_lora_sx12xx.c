/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2019-02-25     XiaojieFan       the first version
  */
  
#include <stdint.h>
#include <rtdevice.h>

int sx12xx_spi_device_init()
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    return rt_hw_spi_device_attach("spi1","spi10",GPIOA,GPIO_PIN_18);
	
}
INIT_DEVICE_EXPORT(sx12xx_spi_device_init);