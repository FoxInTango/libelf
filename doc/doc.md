# gcc ��������
# gcc �������� 
#    https://www.cnblogs.com/wfwenchao/articles/4140388.html 
#    <<����Ա����������>>

# MSVC https://learn.microsoft.com/zh-cn/cpp/build/reference/fa-fa-listing-file?view=msvc-170
#      https://learn.microsoft.com/zh-cn/cpp/build/reference/compiler-options-listed-by-category?view=msvc-170

# ջ���� �� ARM ehabi https://www.leadroyal.cn/p/1125/

# R_ARM_V4BX https://github.com/ARM-software/abi-aa/blob/main/aaelf32/aaelf32.rst
# _GLOBAL__sub_I https://blog.csdn.net/qq_38600065/article/details/117370846
# __dso_handle https://www.cnblogs.com/lsgxeva/p/11040993.html Where is __dso_handle defined?
#                  __dso_handle is a "guard" that is used to identify dynamic shared objects during global destruction.
#                  relative with -fno-use-cxa-atexit

# ##################################ARM##################################
# ARM ���ָ�� https://zhuanlan.zhihu.com/p/164415889
#    �����
#        ARM�ٷ���ARM�����ָ��һ���ô�д��Windows�е�IDE����������
#        GNU����ARM��ָࣺ��һ����Сд��
#    ����ص�
#         LDR/STR�ܹ� 
#             ARM����RISC�ܹ���CPU������ֱ�Ӷ�ȡ�ڴ棬����Ҫ�Ƚ��ڴ������ݼ�����CPU��ͨ�üĴ����в��ܱ�CPU����
#         ֧��8��Ѱַ��ʽ
#         ָ���׺ ͬһָ���������ͬ��׺����ɲ�ͬ��ָ�����ʹ�õĺ�׺�У�
#             B��byte�����ܲ��䣬�������ȱ�Ϊ8λ
#             H��half word�����ܲ��䣬���ȱ�Ϊ16λ
#             S��signed�����ܲ��䣬��������Ϊ�з���
#             �� ldr ldrb ldrh ldrsb ldrsh
#             S��S��־�����ܲ��䣬Ӱ��CPSR��־λ
#             �� mov��movs movs r0, #0
#
#
# ״̬�Ĵ��� https://blog.csdn.net/laviolette/article/details/51376751
#
# LR�Ĵ��� https://www.cnblogs.com/qiyuexin/p/12609300.html
#          ��ARM��ϵ�ṹ��LR��������;�����֣�һ�����������ӳ��򷵻ص�ַ��
#          ���ǵ��쳣����ʱ��LR�б����ֵ�����쳣����ʱPC��ֵ��4�����߼�2��������ڸ����쳣ģʽ�¿��Ը���LR��ֵ���ص��쳣����ǰ����Ӧλ�ü���ִ�С�

# FP�Ĵ���
# SP�Ĵ���
# PC�Ĵ���
# 
# ����ָ�� ldr 
# �洢ָ�� str
# ѹջָ��
# ��ջָ��
# ��תָ��

# ʹ��strip, eu-strip, objcopy�Ȱ����뵼�ط��ű�������Ϣ
# https://blog.csdn.net/nirendao/article/details/104107608
# https://zhuanlan.zhihu.com/p/609045881