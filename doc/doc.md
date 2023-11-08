# gcc 函数别名
# gcc 函数命名 
#    https://www.cnblogs.com/wfwenchao/articles/4140388.html 
#    <<程序员的自我修养>>

# MSVC https://learn.microsoft.com/zh-cn/cpp/build/reference/fa-fa-listing-file?view=msvc-170
#      https://learn.microsoft.com/zh-cn/cpp/build/reference/compiler-options-listed-by-category?view=msvc-170

# 栈回溯 与 ARM ehabi https://www.leadroyal.cn/p/1125/

# R_ARM_V4BX https://github.com/ARM-software/abi-aa/blob/main/aaelf32/aaelf32.rst
# _GLOBAL__sub_I https://blog.csdn.net/qq_38600065/article/details/117370846
# __dso_handle https://www.cnblogs.com/lsgxeva/p/11040993.html Where is __dso_handle defined?
#                  __dso_handle is a "guard" that is used to identify dynamic shared objects during global destruction.
#                  relative with -fno-use-cxa-atexit

# ##################################ARM##################################
# ARM 汇编指令 https://zhuanlan.zhihu.com/p/164415889
#    汇编风格
#        ARM官方的ARM汇编风格：指令一般用大写，Windows中的IDE开发环境。
#        GNU风格的ARM汇编：指令一般用小写。
#    汇编特点
#         LDR/STR架构 
#             ARM采用RISC架构，CPU本身不能直接读取内存，而需要先将内存中内容加载入CPU中通用寄存器中才能被CPU处理。
#         支持8种寻址方式
#         指令后缀 同一指令经常附带不同后缀，变成不同的指令，经常使用的后缀有：
#             B（byte）功能不变，操作长度变为8位
#             H（half word）功能不变，长度变为16位
#             S（signed）功能不变，操作数变为有符号
#             如 ldr ldrb ldrh ldrsb ldrsh
#             S（S标志）功能不变，影响CPSR标志位
#             如 mov和movs movs r0, #0
#
#
# 状态寄存器 https://blog.csdn.net/laviolette/article/details/51376751
#
# LR寄存器 https://www.cnblogs.com/qiyuexin/p/12609300.html
#          在ARM体系结构中LR的特殊用途有两种：一是用来保存子程序返回地址；
#          二是当异常发生时，LR中保存的值等于异常发生时PC的值减4（或者减2），因此在各种异常模式下可以根据LR的值返回到异常发生前的相应位置继续执行。

# FP寄存器
# SP寄存器
# PC寄存器
# 
# 加载指令 ldr 
# 存储指令 str
# 压栈指令
# 出栈指令
# 跳转指令

# 使用strip, eu-strip, objcopy等剥离与导回符号表及调试信息
# https://blog.csdn.net/nirendao/article/details/104107608
# https://zhuanlan.zhihu.com/p/609045881