/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-02-25     XiaojieFan     the first version
 */

#ifndef __SPI_LORA_SX12XX_H_
#define __SPI_LORA_SX12XX_H_

#include <rtthread.h>
#include <stdbool.h>


/*!
 * DIO state read functions mapping
 */
//#define DIO0                                        SX1276ReadDio0()
//#define DIO1                                        SX1276ReadDio1()
//#define DIO2                                        SX1276ReadDio2()
//#define DIO3                                        SX1276ReadDio3()
//#define DIO4                                        SX1276ReadDio4()
//#define DIO5                                        SX1276ReadDio5()

/*!
 * \brief Gets the SX1272 DIO0 hardware pin status
 *
 * \retval status Current hardware pin status [1, 0]
 */
uint8_t SX1276ReadDio0(void);

/*!
 * \brief Gets the SX1272 DIO1 hardware pin status
 *
 * \retval status Current hardware pin status [1, 0]
 */
uint8_t SX1276ReadDio1(void);

/*!
 * \brief Gets the SX1272 DIO2 hardware pin status
 *
 * \retval status Current hardware pin status [1, 0]
 */
uint8_t SX1276ReadDio2(void);

/*!
 * \brief Gets the SX1272 DIO3 hardware pin status
 *
 * \retval status Current hardware pin status [1, 0]
 */
uint8_t SX1276ReadDio3(void);

/*!
 * \brief Gets the SX1272 DIO4 hardware pin status
 *
 * \retval status Current hardware pin status [1, 0]
 */
uint8_t SX1276ReadDio4(void);

/*!
 * \brief Gets the SX1272 DIO5 hardware pin status
 *
 * \retval status Current hardware pin status [1, 0]
 */
uint8_t SX1276ReadDio5(void);

struct rt_spi_device *sx12xx_init(const char *dev_name,  rt_uint8_t param);
void SX1276Write(uint8_t addr, uint8_t data);
void SX1276Read(uint8_t addr, uint8_t *data);
void SX1276WriteBuffer(uint8_t addr, uint8_t *buffer, uint8_t size);
void SX1276ReadBuffer(uint8_t addr, uint8_t *buffer, uint8_t size);
void SX1276WriteFifo(uint8_t *buffer, uint8_t size);
void SX1276ReadFifo(uint8_t *buffer, uint8_t size);
void SX1276SetReset(uint8_t state);
uint8_t SX1276_Spi_Check(void);
void sx12xx_deinit(struct rt_spi_device *dev);
#endif