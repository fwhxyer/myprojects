#include "stdafx.h"//ʹ��Ԥ����ͷ�ļ����Լӿ����ı����ٶȣ��ǳ��Ƽ�ʹ��
#include "NodeList.h"//NodeList�ɺ�Х��ɽ���д

//���ļ�ר��������дNodeList.h�������������еķ����ľ���ʵ��

namespace LJ
{
	namespace NodeList
	{
		void nodeList::ADDList(T t)//����½ڵ�
		{
			node *p = new node(t);
			if(nHead==NULL)//������Ϊ��ͷָ��ͽ�βָ�붼ָ���¼����ָ��
			{
				nHead = p;
				nEnd = p;
				return;
			}
			node *q =nHead;
			while(q->next)//�������һ���ڵ�
			{
				q=q->next;					
			}
			q->next=p;
			p->left=q;
			nEnd =p;
		}
		void nodeList::showList(state s)
		{
			if(!s)
			{
				node *p = nHead;
				while(p->next)
				{
					cout<<p->t<<endl;
					p=p->next;
				}
				cout<<p->t<<endl;
			}
			else
			{
				node *p = nEnd;
				while(p->left)
				{
					cout<<p->t<<endl;
					p=p->left;
				}
				cout<<p->t<<endl;
			}
		}
		void nodeList::clear()
		{
			node *p;
			while(nHead)
			{
				p = nHead->next;
				delete nHead;
				nHead=p;
			}
		}
		void nodeList::insertNode(T t,int num)
		{
			node *q = nHead;
			node *u;
			if(num<0)
				num=0;
			for(int i = 0; i < num ;i++)
			{
				q=q->next;
				if(!q->next)
				{
					ADDList(t);
					return;
				}
			}
	
			node *p = new node(t);
			u = q->left;
			if(!q->left)
			{
				nHead->left = p;
				p->next =nHead;
				nHead = p;
				return;
			}
			u->next = p;
			p->left = u;
			q->left = p;
			p->next = q;
		}

		void nodeList::upAandSet(T t,int num)
		{
			if(num<0)
				num = 0;
			node *q = nHead;
			node *u,*w;
			for(int i = 0; i < num ;i++)
			{
				if(!q->next)
				{
					ADDList(t);
					break;
				}
				q=q->next;		
			}
			node *p = new node(t);
			u=q->next;
			w=q->left;
			if(!q->left)
			{
				nHead = p;
				p->next = u;
				u->left =p;
			}
			else if(!q->next)
			{
				nEnd = p;
				p->left =w;
				w->next = p;
			}else
			{
				p->next = u;
				u->left = p;
				p->left = w;
				w->next = p;
			}
			delete q;
		}

		void nodeList::deletNode(int num)
		{
			if(num<0)
				return;
			if(!nHead)
				return;
			node * p = nHead;
			for(int i = 0; i != num ; i++)
			{
				if(!p->next)
					return;
				p = p->next;
			}
			node *q = p->left;
			node *u = p->next;
			if(!q)
			{
				nHead = u;
				u->left = NULL;
			}else if (!u)
			{
				nEnd = q;
				q->next =NULL;
			}else
			{
				q->next = u;
				u->left = q;
			}
			delete p;
		}
	}
}