#include "stdafx.h"//使用预编译头文件可以加快程序的编译速度，非常推荐使用
#include "NodeList.h"//NodeList由呼啸的山风编写

//该文件专门用来编写NodeList.h里面声明的类中的方法的具体实现

namespace LJ
{
	namespace NodeList
	{
		void nodeList::ADDList(T t)//添加新节点
		{
			node *p = new node(t);
			if(nHead==NULL)//当链表为空头指针和结尾指针都指向新加入的指针
			{
				nHead = p;
				nEnd = p;
				return;
			}
			node *q =nHead;
			while(q->next)//链表最后一个节点
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