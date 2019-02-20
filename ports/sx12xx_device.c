/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-02-20     XiaojieFan   add port file
 */

#include "drv_spi.h"
#include "board.h"
#include "drv_gpio.h"
int sx12xx_spi_device_init()
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    return rt_hw_spi_device_attach("spi1", SX12XX_SPI_DEVICE, GPIOA, GPIO_PIN_8);
}
INIT_DEVICE_EXPORT(sx12xx_spi_device_init);
