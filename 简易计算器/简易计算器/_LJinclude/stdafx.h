#pragma once
//��׼ͷ�ļ���������ѡ���⽫���ӳ���������ʮKB����
//1.����֧��
#include<cstddef>//�����NULL��offsetof�Լ�������׼����size_t ��ptrdiff_t�����Ӧ�ı�׼Cͷ�ļ��������ǣ�NULL��c++��ָ�볣���Ĳ��䶨�壬��offsetof���ܽṹ���������Ͳ�����ֻ������û�г�Աָ�����͵ķǾ�̬��Ա����
#include<limits>//�ṩ���������������صĶ��塣���磺����ÿ����ֵ�������ͣ��������˿��Գ��������ֵ����Сֵ�Լ����������ֵ�λ����
#include<climits>//�ṩ���������������ص�c��ʽ���壬��Щ��Ϣ��c++��ʽ��<limits>���ṩ
#include<cfloat>//�ṩ�����������������ص�c��ʽ���壬��Щ��Ϣ��c++��ʽ��<limits>���ṩ
#include<cstdlib>//�ṩ֧�ֳ�����������ֹ�ĺ�ͺ��������ͷ�ļ��л������������������������������������������ַ���ת��Ϊ��ֵ�Ⱥ����������Ӧ�ı�׼cͷ�ļ�<stdlib.h>��ͬ��������abort(void)��Abort()���ж���Ĺ��ܣ�����Ϊ��̬���Զ������������������Ҳ�����ô��͸�atexit()�����ĺ���������������exit()�����Ķ��⹦�ܣ������ͷž�̬������ע������������atexit()ע��ĺ�����������ر����д򿪵�c�����ѿ���Ȩ���ظ���������
#include<new>//֧�ֶ�̬�ڴ����
#include<typeinfo>//֧�ֱ����������ڼ�����ͱ�ʶ
//#include<exception>//֧���쳣�������Ǵ�������п��ܷ����Ĵ����һ�ַ�ʽ��
//#include<cstdarg>//֧�ֽ��������ɱ�Ĳ����ĺ��������ڵ��ú���ʱ�����Ը����������������ȵ�������������˺�va_arg��va_end��va_start���Լ�va_list���� 
//#include<csetjmp>//Ϊc��ʽ�ķǱ�����Ծ�ṩ��������Щ������c++�����в�����
//#include<csignal>//Ϊ�жϴ����ṩc��ʽ֧��

/*
//2.�������
#include<iostream>//֧�ֱ�׼��cin ��cout ��cerr ��clog ���������������֧�ֶ��ֽ��ַ���׼��wcin�� wcout ��wcerr ��wclog
#include<iomanip>//�ṩ���ݳ�������ı�����״̬���Ӷ��ı��������ʽ
#include<ios>//����<iostream>�Ļ���
#include<istream>//Ϊ���������������������붨��ģ����
#include<ostream>//Ϊ������������������������ģ����
#include<sstream>//֧���ַ��������������
#include<fstream>//֧���ļ������������
#include<iosfwd>//Ϊ������������ṩ��ǰ������
#include<streambuf>//֧������������Ļ���
#include<cstdio>//Ϊ��׼���ṩc��ʽ���������
#include<cwchar>//֧�ֶ��ֽ��ַ���c��ʽ�������
//3.���
#include<stdexcept>//�����׼�쳣���쳣�Ǵ������ķ�ʽ
#include<cassert>//������Ժ꣬���ڼ�������ڼ������
#include<cerrno>//֧��c��ʽ�Ĵ�����Ϣ

//4.һ�㹤��
#include<ctime>//֧��ϵͳʱ�Ӻ���
#include<utility>//�������صĹ�ϵ��������򻯹�ϵ�������д�룬����������pair���ͣ���������һ��ģ�����ͣ����Դ洢һ��ֵ����Щ�����ڿ�������ط�ʹ��
#include<functional>//��������ຯ���������ͺ�֧�ֺ�������Ĺ��ܣ�����������֧��operator()()����������������������
#include<memory>//�������������ڴ�ĺ�����auto_ptrģ���ඨ���׼�ڴ������

//5.�ַ���
#include<string>//Ϊ�ַ������ṩ֧�ֺͶ��壬�������ֽ��ַ�������char��ɣ���string��Unicode�ַ�������wchar_t��ɣ�
#include<cctype>//���ֽ��ַ����
#include<cwctype>//Unicode�ַ����
#include<cstring>//Ϊ����ǿ��ֽ����к��ڴ���ṩ�������ⲻͬ�ڶ�Ӧ�ı�׼c��ͷ�ļ�������c��ʽ�ַ�����һ��c�⺯��������ֵΪconst�ͷ�const�ĺ���������ˡ�
#include <cwchar>//Ϊ����ִ��I/O��ת���ַ������ṩ�������Ų�ͬ�ڶ�Ӧ�ı�׼c��ͷ�ļ�������Unicodec��ʽ�ַ���������һ��c�⺯��������ֵΪconst�ͷ�const�ĺ���������ˡ�
#include<cstdlib>//Ϊ�Ѷ��ֽ��ַ���ת��Ϊ��ֵ���ڶ��ֽ��ַ�����Unicode�ַ���֮���ṩת������

//6.����
#include<vector>//����vector����ģ�壬����һ����С���������õ��������ͣ�����ͨ�������ȫ�����
#include<list>//����listģ�����У�����һ�����е���������������λ�ò����ɾ��Ԫ��
#include<deque>//����deque����ģ�壬֧���ڿ�ʼ�ͽ�β�ĸ�Ч�����ɾ������
#include<queue>//Ϊ���У��Ƚ���������ݽṹ��������������queue��priority_queue
#include<stack>//Ϊ��ջ������ȳ������ݽṹ��������������stack
#include<map>//map��һ�������������ͣ�������ݼ�ֵ����ֵ�����м�ֵ��Ψһ�ģ��Ұ�������洢��Multimap������map������������Ψһ��
#include<set>//set��һ�������������ͣ�����������ʽ�洢Ψһֵ��multiset������set����ֵ������Ψһ��
#include<bitset>//Ϊ�̶����ȵ�λ���ж���bitsetģ�壬�����Կ����̶����ȵĽ�����bool����

//7.������֧��
#include<iterator>//���������ṩ�����֧��

//8.һ����;���㷨
#include<algorithm>//�ṩһ������㷨�ĺ����������û������򣬺ϲ�������
#include<cstdlib>//����c��׼�⺯��bsearch() ��qsort()����������������
#include<ciso646>//�����ڴ�������and����&&

//9.��ֵ����
#include<complex>//֧�ָ����Ķ���Ͳ���������
#include<valarray>//֧����ֵʸ���Ĳ���
#include<numeric>//����ֵ�����϶���һ��һ����ѧ����������accumulate ��inner_product
#include<cmath>//����c��ѧ�⣬���л����������غ�������֧��c++Լ��
#include<cstdlib>//�ṩ�ĺ���������ȡ�����ľ���ֵ������������ȡ��������

//10.���ػ�
#include<locale>//�ṩ�ı��ػ������ַ�����������У��Լ����Һ����ڱ�ʾ
#include<clocale>//�Ա��ػ��ṩc��ʽ֧��
*/
//LJ����ļ�
#include "classes.h"
#include "Property.h"//����
#include "XBase.h"//����
#include "XTypes.h"//������
//#include "ThreadControl.h"//�߳̿���
#include "XTime.h"//ʱ����
#include "XRandom.h"//�������(���е�����XTime::Now����ʼ��)
#include "Iterator.h"//������
#include "XString.h"//�ַ�����
#include "XException.h"//�쳣��
#include "XArray.h"//������
//#include "XDelegate.h"//ί������
#include "Equation\\stdafx.h"
//#include "sound\\stdafx.h"//����ѡ��
//#include "Game\\stdafx.h"//����ѡ��
//#include "NodeList\\stdafx.h"//����ѡ��
