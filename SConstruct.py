__author__ = 'Jiang.Xiaolong'

#编译规则定义

























#导入各目录下SConscript.py
SConscript(Glob('*/SConscript.py'), exports='env')