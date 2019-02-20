/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2019-02-20     XiaojieFan       the first version
  */

#include "drv_spi.h"
#include "board.h"
#include "drv_gpio.h"
#include <rtthread.h>
#include "spi_lora_sx12xx.h"
#include "sx1276-Hal.h"
#include "sx1276-Lora.h"
#include "sx1276-LoraMisc.h"
#include "radio.h"

static struct rt_spi_device *spi_bus_dev;
tRadioDriver *Radio = NULL;

struct rt_spi_device *sx12xx_init(const char *dev_name, rt_uint8_t param)
{
    RT_ASSERT(dev_name);
    spi_bus_dev = (struct rt_spi_device *)rt_device_find(dev_name);
    if (!spi_bus_dev)
    {
        rt_kprintf("spi sample run failed! cant't find %s device!\n", dev_name);
        return RT_NULL;
    }
    /* config spi */
    {
        struct rt_spi_configuration cfg;
        cfg.data_width = 8;
        cfg.mode = RT_SPI_MODE_0 | RT_SPI_MSB; /* SPI Compatible: Mode 0. */
        cfg.max_hz = 10 * 1000000;             /* max 10M */
        rt_spi_configure(spi_bus_dev, &cfg);
    }
		Radio = RadioDriverInit();
    Radio->Init();	
    return spi_bus_dev;
}

/**
 * This function releases memory
 *
 * @param dev the pointer of device driver structure
 */
void sx12xx_deinit(struct rt_spi_device *dev)
{
    RT_ASSERT(dev);
    rt_spi_release_bus(dev);
}
void SX1276InitIo(void)
{
    rt_pin_mode(SX12XX_DO0_PIN, PIN_MODE_INPUT);
    rt_pin_mode(SX12XX_DO1_PIN, PIN_MODE_INPUT);
    rt_pin_mode(SX12XX_DO2_PIN, PIN_MODE_INPUT);
}
inline uint8_t SX1276ReadDio0(void)
{
    return rt_pin_read(SX12XX_DO0_PIN);
}

inline uint8_t SX1276ReadDio1(void)
{
    return rt_pin_read(SX12XX_DO1_PIN);
}

inline uint8_t SX1276ReadDio2(void)
{
    return rt_pin_read(SX12XX_DO2_PIN);
}

inline uint8_t SX1276ReadDio3(void)
{
    return rt_pin_read(SX12XX_DO3_PIN);
}
inline uint8_t SX1276ReadDio4(void)
{
    return rt_pin_read(SX12XX_DO4_PIN);
}
inline uint8_t SX1276ReadDio5(void)
{
    return rt_pin_read(SX12XX_DO5_PIN);
}
inline void SX1276WriteRxTx(uint8_t txEnable)
{
    if (txEnable != 0)
    {

    }
    else
    {

    }
}

void SX1276SetReset(uint8_t state)
{
    if (state == RADIO_RESET_ON)
    {
        rt_pin_mode(SX12XX_RST_PIN, PIN_MODE_OUTPUT);
        rt_pin_write(SX12XX_RST_PIN, PIN_LOW);
    }
    else
    {
        rt_pin_mode(SX12XX_RST_PIN, PIN_MODE_INPUT);

    }
}
void SX1276Write(uint8_t addr, uint8_t data)
{
    SX1276WriteBuffer(addr, &data, 1);
}

void SX1276Read(uint8_t addr, uint8_t *data)
{
    SX1276ReadBuffer(addr, data, 1);
}

void SX1276WriteBuffer(uint8_t addr, uint8_t *buffer, uint8_t size)
{
    struct rt_spi_message msg1, msg2;
    uint8_t    data = (addr | 0x80);
    msg1.send_buf   = &data;
    msg1.recv_buf   = RT_NULL;
    msg1.length     = 1;
    msg1.cs_take    = 1;
    msg1.cs_release = 0;
    msg1.next       = &msg2;

    msg2.send_buf   = buffer;
    msg2.recv_buf   = RT_NULL;
    msg2.length     = size;
    msg2.cs_take    = 0;
    msg2.cs_release = 1;
    msg2.next       = RT_NULL;
    rt_spi_transfer_message(spi_bus_dev, &msg1);
}

void SX1276ReadBuffer(uint8_t addr, uint8_t *buffer, uint8_t size)
{

    struct rt_spi_message msg1, msg2;
    uint8_t    data = (addr & 0x7F);
    msg1.send_buf   = &data;
    msg1.recv_buf   = RT_NULL;
    msg1.length     = 1;
    msg1.cs_take    = 1;
    msg1.cs_release = 0;
    msg1.next       = &msg2;

    msg2.send_buf   = RT_NULL;
    msg2.recv_buf   = buffer;
    msg2.length     = size;
    msg2.cs_take    = 0;
    msg2.cs_release = 1;
    msg2.next       = RT_NULL;
    rt_spi_transfer_message(spi_bus_dev, &msg1);
}

void SX1276WriteFifo(uint8_t *buffer, uint8_t size)
{
    SX1276WriteBuffer(0, buffer, size);
}

void SX1276ReadFifo(uint8_t *buffer, uint8_t size)
{
    SX1276ReadBuffer(0, buffer, size);
}
uint8_t SX1276_Spi_Check(void)
{
    uint8_t test = 0;
	  tLoRaSettings settings;
	  SX1276Read(REG_LR_VERSION,&test);
	  rt_kprintf("version code of the chip is %x\n",test);
	  settings.RFFrequency = SX1276LoRaGetRFFrequency();
	  rt_kprintf("SX1278 Lora parameters are :\nRFFrequency is %d\n",settings.RFFrequency);
	  settings.Power = SX1276LoRaGetRFPower();
	  rt_kprintf("RFPower is %d\n",settings.Power);
		settings.SignalBw = SX1276LoRaGetSignalBandwidth();	  
	  rt_kprintf("SignalBw is %d\n",settings.SignalBw);
	  settings.SpreadingFactor = SX1276LoRaGetSpreadingFactor();
	  rt_kprintf("SpreadingFactor is %d\n",settings.SpreadingFactor);
    /*SPI 验证*/
    SX1276Write(REG_LR_HOPPERIOD, 0x91); //选一个用不到的寄存器来做验证
    SX1276Read(REG_LR_HOPPERIOD, &test);
    if (test != 0x91)
    {
        return -1;
    }		
    return test;
}
