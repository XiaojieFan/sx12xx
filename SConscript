from building import *
Import('rtconfig')

src   = []
cwd     = GetCurrentDir()

# add sx12xx src files.
if GetDepend('PKG_USING_SX12XX'):
    src += Glob('src/spi_lora_sx12xx.c')
    src += Glob('ports/*.c')
if GetDepend('SX12XX_USING_SX1278'):
	src += Glob('src/radio/sx1276*.c')
	src += Glob('src/radiO/radio.c')
if GetDepend('PKG_USING_SX12XX_SAMPLE'):
    src += Glob('samples/sx12xx_sample.c')

# add sx12xx include path.
path  = [cwd + '/inc']
path += ['src/radio']
group = DefineGroup('sx12xx', src, depend = ['PKG_USING_SX12XX'], CPPPATH = path)

Return('group')
