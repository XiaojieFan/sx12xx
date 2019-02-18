
from building import *

cwd     = GetCurrentDir()
src     = Glob('*.c') + Glob('*.cpp')
CPPPATH = [cwd]

group = DefineGroup('sx12xx', src, depend = [''], CPPPATH = CPPPATH)

Return('group')
