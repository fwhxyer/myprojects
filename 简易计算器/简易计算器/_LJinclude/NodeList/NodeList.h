#pragma once//防止重复包含。该文件专门用来写类、结构体等的声明
#include <iostream>//nodeList类由呼啸的山风编写


namespace LJ//LJ类库的东西都放到LJ命名空间里
{
	//由于比较容易重名，都放到NodeList命名空间里
	namespace NodeList
	{
		//NodeList命名空间中自动使用std命名空间
		using namespace std;
		enum state
		{
			UP,
			DOWN
		};

		typedef int T;

		//链表节点结构
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
			//尾部添加节点
			void ADDList(T t);
			//输出链表节点UP升序DOWN降序
			void showList(state s = UP);
			//释放节点空间
			void clear();
			//指定位置添加节点第一个位置为0
			void insertNode(T t ,int num = 0);	
			//修改指定位置节点的值
			void upAandSet(T t , int num);
			//删除指定位置的节点
			void deletNode(int num);
		};
	}
}