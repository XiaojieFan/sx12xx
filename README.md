# SX12XX

## 1、介绍

SX12XX 软件包是基于 semtech 官网 [Firmware Drivers V2.1.0](https://www.semtech.com/products/wireless-rf/lora-transceivers/sx1278#download-resources) 代码库的移植实现，目前只支持 SX1278 LoRa设备。该软件包在原代码库功能的基础上，对接 RT-Thread SPI 设备驱动框架，实现参数的配置和数据的读取。

### 1.1 目录结构

SX12XX 软件包目录结构如下所示：

```
sx12xx
├───inc                             // RT_Thread 移植头文件
├───samples                         // 示例文件
├───ports                           // 挂载设备 额外移植代码 
├───src                             // RT_Thread 移植源码文件
│   └───radio                       // semtech 官方库文件│
│   └───spi_lora_sx12xx.c           // sx12xx 包初始化 设备读写驱动实现 
│   LICENSE                         // 软件包许可证
│   README.md                       // 软件包使用说明
└───SConscript                      // RT-Thread 默认的构建脚本
```


### 1.2 许可证

SX12XX 软件包遵循 Apache-2.0 许可，详见 LICENSE 文件。

### 1.3 依赖

- RT-Thread 3.1.1+
- SPI 驱动：WIZnet 设备使用  SPI 进行数据通讯，需要系统 SPI 驱动框架支持；
- PIN 驱动：用于处理设备复位和中断引脚；

## 2、获取软件包

使用 SX12XX 软件包需要在 RT-Thread 的包管理中选中它，具体路径如下： 

```shell
RT-Thread online packages
    peripheral libraries and drivers  --->
		sx12xx: Semtech LoRa RF chip driver library --->
```
进入 sx12xx 软件包的配置菜单按自己的需求进行具体的配置
```shell
sx12xx: Semtech LoRa RF chip driver library --->
        SX12XX device type(SX1278 LSD4RF-2F717N30)  --->
        SX12XX device configure  --->
            (spi10) SPI device name
            (10)  Reset PIN number
            (103) DO0 PIN number
            (104) DO1 PIN number
            (105) DO2 PIN number
            (106) DO3 PIN number
            (107) DO4 PIN number
            (108) DO5 PIN number			
  [ ]   Enable sx12xx sample
        Version (latest)  --->
```

**SX12XX device type** ：配置支持的设备类型（目前只支持 SX1278 利尔达 LSD4RF-2F717N30 LoRa 模块 ）

**SX12XX device configure** ：配置使用设备的参数

- **SPI device name**：配置使用 SPI 的设备名称（注意需设置为**非 SPI 总线设备**）

- **Reset PIN number**：配置设备连接的复位引脚号（根据实际使用引脚号修改）

- **DO0~5 PIN number**：配置设备连接的中断引脚号（同上）

**Enable sx12xx sample**： 配置使用示例代码

**Version**：软件包版本选择

## 3、使用软件包

### 3.1 SX12XX 软件包初始化函数如下所示：

```c
int sx12xx_init（void）；
```
该函数不支持组件初始化，函数主要完成功能有，

- 设置 LoRa 调制模式 ；

- 设备配置和引脚初始化（配置 SPI 设备，配置复位和中断引脚）；

- LoRa 参数配置和初始化（RFFrequency , Power, SignalBw, SpreadingFactor,ErrorCoding 等）；

### 3.2 MSH 测试命令 

如果开启 sx12xx 软件包示例程序，就会导出 sx12xx_test 命令到控制台。设备上电初始化完成，在控制台调用测试命令，将会打印如下所示：

```shell
msh />sx12xx_test
sx12xx init succeed             ## 获取设备句柄 ，初始化Lora 成功
version code of the chip is 12  ## chip code 信息
SX1278 Lora parameters are :    ## 如下为主要 Lora 设置参数 信息 
RFFrequency is 870000000        ## 频率
RFPower is 14                   ## 发射功率
SignalBw is 9                   ## 信号带宽
SpreadingFactor is 7            ## 扩频因子
sx12xx spi check ok!            ## SPI 测试完成
```

## 4、常见问题

- SPI 设备初始化时断言问题

  ```shell
 spi sample run failed! cant't find spi12 device!
  ```

  出现上述问题，可能原因是 ENV 中配置 SX12XX 使用的 SPI 设备类型不正确，可以在添加 SX12XX 软件包之前在 FinSH 中使用 `list_device` 查看当前可用 SPI 设备名称，如果 BSP 工程中没有 SPI 设备或者只有 SPI 总线设备，需要手动在驱动中添加 SPI 设备，并正确配置 SX12XX 软件包中使用的 SPI 设备名称。


## 5、注意事项

- 获取软件包时，需要注意正确配置使用的 SPI 设备名称、复位引脚号和中断引脚号；

- 软件包目前处于 `beta` 测试阶段, 推荐在 menuconfig 选项中选择 `latest` 版本； 


## 6、联系方式 & 感谢

- 维护：XiaojieFan
- 主页：https://github.com/XiaojieFan/sx12xx