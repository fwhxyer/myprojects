#pragma once//��ֹ�ظ����������ļ�ר������д�ࡢ�ṹ��ȵ�����
#include <iostream>//nodeList���ɺ�Х��ɽ���д


namespace LJ//LJ���Ķ������ŵ�LJ�����ռ���
{
	//���ڱȽ��������������ŵ�NodeList�����ռ���
	namespace NodeList
	{
		//NodeList�����ռ����Զ�ʹ��std�����ռ�
		using namespace std;
		enum state
		{
			UP,
			DOWN
		};

		typedef int T;

		//����ڵ�ṹ
		struct node
		{
			T t;
			node *left,*next;
			node(T t1 = 0):t(t1),left(0),next(0)
			{
			
			}
		};

		class  nodeList
		{
		public:
			nodeList():nHead(0),nEnd(0){}
			~nodeList()
			{
				clear();
			}
			node *nHead;
			node *nEnd;
			//β����ӽڵ�
			void ADDList(T t);
			//�������ڵ�UP����DOWN����
			void showList(state s = UP);
			//�ͷŽڵ�ռ�
			void clear();
			//ָ��λ����ӽڵ��һ��λ��Ϊ0
			void insertNode(T t ,int num = 0);	
			//�޸�ָ��λ�ýڵ��ֵ
			void upAandSet(T t , int num);
			//ɾ��ָ��λ�õĽڵ�
			void deletNode(int num);
		};
	}
}