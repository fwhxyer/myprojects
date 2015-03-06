#include "stdafx.h"
#ifdef XTYPES_
namespace LJ
{
	bool TypesCheckingObject::AppEquals(const TypesCheckingObject& t){if(t.count!=count)return false; return memcmp(pTypes,t.pTypes,count*sizeof(type_info*))==0;}
	void* TypesCheckingObject::Malloc(int c)
	{
		if(c<0)throw XException(E_INVALIDARG);
		void* p = malloc(c);
		if(p==NULL && c!=0)
		{
			Sleep(50);
			p = malloc(c);
			if(p==NULL)throw XException(E_OUTOFMEMORY);
		}
		return p;
	}
	XString TypesCheckingObject::ToString()const
	{
		if(count==0)return XString::Empty;
		XString t=XString(pTypes[0]->name()).Replace(L"class ",L"").Replace(L"struct ",L"");
		if(pCR[0]>=2)t+=L"&";
		if(pCR[0]%2!=0)t=L"const "+t;
		XString str;
		for(int i=1;i<count;++i)
		{
			str = XString(pTypes[i]->name()).Replace(L"class ",L"").Replace(L"struct ",L"");
			if(pCR[i]>=2)str+=L"&";
			if(pCR[i]%2!=0)str=L",const "+str;
			else str = L","+str;
			t= t+ str;
		}
		return t;
	}
	const type_info& TypesCheckingObject::operator[](int index)const
	{
		if(index<0)throw XException(E_INVALIDARG);
		if( index>=count)throw XException(COR_E_INDEXOUTOFRANGE);
		return *pTypes[index];
	}
	NodeOfRoot& NodeOfRoot::Root(){static NodeOfRoot t(0);return t;}

	//NodeOfRoot
	
	//��������
	NodeOfRoot::~NodeOfRoot()
	{
		if(type==0)
		{
			for(unsigned long i=0;i<nodeCount;++i)
			{
				switch(pNodeList[i]->type)
				{
				case 1:delete ((NodeOfNamespace*)pNodeList[i]);break;
				case 2:delete (NodeOfTemplate*)pNodeList[i];break;
				case 3:delete (NodeOfTemplateClass*)pNodeList[i];break;
				case 4:delete (NodeOfType*)pNodeList[i];break;
				}
			}
			delete []pNodeList;
#ifdef _DEBUG
			int i = _CrtDumpMemoryLeaks();
			assert( i == 0);
#endif
		}
	}
	//��ȡ�ýڵ�����
	XString NodeOfRoot::GetName()const
	{
		switch(type)
		{
		case 1:return ((NodeOfNamespace*)this)->name;
		case 2:return ((NodeOfTemplate*)this)->name;
		case 3:return ((NodeOfTemplateClass*)this)->pTemplate->GetName()+L"<"+((NodeOfTemplateClass*)this)->typesChecking.ToString()+L">";
		case 4:return ((NodeOfType*)this)->name;
		}
		return XString::Empty;
	}
	//��ȡ�ýڵ�ȫ�������������ռ䣩
	XString NodeOfRoot::GetFullName()const
	{
		switch(type)
		{
		case 1:if(((NodeOfNamespace*)this)->pNamespace==&Root())return GetName();
			return ((NodeOfNamespace*)this)->pNamespace->GetFullName()+L"::"+((NodeOfNamespace*)this)->name;
		case 2:if(((NodeOfTemplate*)this)->pNamespace==&Root())return GetName();
			return ((NodeOfTemplate*)this)->pNamespace->GetFullName()+L"::"+((NodeOfTemplate*)this)->name;
		case 3:return ((NodeOfTemplateClass*)this)->pTemplate->GetFullName()+L"<"+((NodeOfTemplateClass*)this)->typesChecking.ToString()+L">";
		case 4:if(((NodeOfType*)this)->pNamespace==&Root())return GetName();
			return((NodeOfType*)this)->pNamespace->GetFullName()+L"::"+((NodeOfType*)this)->name;
		}
		return XString::Empty;
	}
	//������id���ҽڵ�
	NodeOfRoot* NodeOfRoot::FindNodeByTypeInfo(const type_info& t)
	{
		switch(type)
		{
		case 3:if(((NodeOfTemplateClass*)this)->Info==t)return this;
			return NULL;
		case 4:if(((NodeOfType*)this)->Info==t)return this;
			return NULL;
		}
		for(unsigned long i=0;i<nodeCount;++i)
		{
			NodeOfRoot* p = pNodeList[i]->FindNodeByTypeInfo(t);
			if(p)return p;
		}
		return NULL;
	}
	//�жϸýڵ��Ƿ������ָ������ڵ�
	bool NodeOfRoot::IsIncludeIn(NodeOfRoot* p)const
	{
		switch(type)
		{
		case 1:if(((NodeOfNamespace*)this)->pNamespace==p)return true;
			return ((NodeOfNamespace*)this)->pNamespace->IsIncludeIn(p);
		case 2:if(((NodeOfTemplate*)this)->pNamespace==p)return true;
			return ((NodeOfTemplate*)this)->pNamespace->IsIncludeIn(p);
		case 3:return ((NodeOfTemplateClass*)this)->pTemplate->IsIncludeIn(p);
		case 4:if(((NodeOfType*)this)->pNamespace==p)return true;
			return ((NodeOfType*)this)->pNamespace->IsIncludeIn(p);
		}
		return false;
	}
	//�жϸýڵ��Ƿ����һ���ڵ�̳У���ڵ㣩
	bool NodeOfRoot::IsDerivedFrom(NodeOfRoot* p)const
	{
		if(p==NULL || type<=2 || p->type<=2)return false;
		if(type==3)
		{
			for(unsigned long i=0;i<((NodeOfTemplateClass*)this)->baseCount;++i)
			{
				if(((NodeOfTemplateClass*)this)->pBaseList[i]==p || ((NodeOfTemplateClass*)this)->pBaseList[i]->IsDerivedFrom(p))return true;
			}
			return false;
		}
		for(unsigned long i=0;i<((NodeOfType*)this)->baseCount;++i)
		{
			if(((NodeOfType*)this)->pBaseList[i]==p || ((NodeOfType*)this)->pBaseList[i]->IsDerivedFrom(p))return true;
		}
		return false;
	}
	//��������ռ�ڵ�(����Ѵ���ͬ���������ռ�ڵ��򷵻���ָ��)
	NodeOfRoot* NodeOfRoot::AddNamespace(const XString& path)
	{
		if(type>1 || path.IsNullOrEmpty())return NULL;
		if(nodeCount==0)pNodeList = new NodeOfRoot*[1];
		else
		{
			for(unsigned long i=0;i<nodeCount;++i)
				if(pNodeList[i]->type==1 && path==((NodeOfNamespace*)pNodeList[i])->name)
					return pNodeList[i];
			NodeOfRoot** p = new NodeOfRoot*[nodeCount+1];
			Memory::Copy(p,pNodeList,nodeCount*sizeof(NodeOfRoot*));
			delete[]pNodeList;
			pNodeList = p;
		}
		pNodeList[nodeCount] = new NodeOfNamespace(this);
		((NodeOfNamespace*)pNodeList[nodeCount])->name = VString::Strcpy(path.ToUnicode());
		return pNodeList[nodeCount++];
	}
	//���������ʱ���ڵ�
	NodeOfRoot*NodeOfRoot::AddUnknown(const type_info& xt)
	{
		NodeOfRoot* p= Root().AddNamespace(L"__unknow");
		static int i=0;
		return ((NodeOfNamespace*)p)->AddClassToList(XString(i++),xt);
	}
	//�Ƴ�������ʱ���ڵ�
	void NodeOfRoot::RemoveUnknown(const type_info& xt,NodeOfRoot*pn)
	{
		NodeOfRoot* px= Root().AddNamespace(L"__unknow");
		unsigned int i;
		for(i=0;i<px->nodeCount;++i)
		{
			if(((NodeOfType*)px->pNodeList[i])->Info == xt)break;
		}
		if(i>=px->nodeCount)return;
		NodeOfType* pt = (NodeOfType*)px->pNodeList[i];
		Memory::Move(px->pNodeList+i,px->pNodeList+i+1,sizeof(NodeOfRoot*)*(px->nodeCount-i-1));
		if(--px->nodeCount==0){delete []px->pNodeList;px->pNodeList=NULL;}
		for(i=0;i<pt->nodeCount;++i)//�����̳нڵ�
		{
			px = pt->pNodeList[i];
			switch(px->type)
			{
			case 3:
				{
					unsigned int j;for(j=0;j<((NodeOfTemplateClass*)px)->baseCount;++j){if(((NodeOfTemplateClass*)px)->pBaseList[j]==pt)break;}
					((NodeOfTemplateClass*)px)->pBaseList[j] = pn;
				}
				break;
			case 4:
				{
					unsigned int j;for(j=0;j<((NodeOfType*)px)->baseCount;++j){if(((NodeOfType*)px)->pBaseList[j]==pt)break;}
					((NodeOfType*)px)->pBaseList[j] = pn;
				}
				break;
			}
			switch(pn->type)
			{
			case 3:((NodeOfTemplateClass*)pn)->AddToList(px);break;
			case 4:((NodeOfType*)pn)->AddToList(px);
			}
		}
		delete pt;
	}
	//�����ڵ㣨��ͨ�࣬�޼̳У�,���� Add("LJ::XBase",Types<LJ::XBase>());
	XTypes& NodeOfRoot::Add(const XString& classPath,const XTypes& xt)
	{
		XArray<XString> strs = classPath.Split(L":",0xffffff,true);
		NodeOfRoot* p = &Root();
		for(int i=0;i+1<strs.Length;++i)
			p = p->AddNamespace(strs[i]);
		p = ((NodeOfNamespace*)p)->AddClassToList(strs[strs.Length-1],xt);
		NodeOfRoot::RemoveUnknown(xt,p);
		XTypes& x= ((NodeOfType*)p)->Info;
		x.pNode = p;
		return x;
	}
	//�����ڵ㣨��ͨ�࣬�м̳У�,���� Add("LJ::XString",Types<LJ::XString>(),typeid(LJ::XBase));
	XTypes& NodeOfRoot::Add(const XString& classPath,const XTypes& xt,const type_info& baseid)
	{
		NodeOfRoot* pid = Root().FindNodeByTypeInfo(baseid);
		if(pid==NULL)
		{
			pid = NodeOfRoot::AddUnknown(baseid);
		}
		XArray<XString> strs = classPath.Split(L":",0xffffff,true);
		NodeOfRoot* p = &Root();
		for(int i=0;i+1<strs.Length;++i)
		{
			p = p->AddNamespace(strs[i]);
		}
		NodeOfType* pt = ((NodeOfNamespace*)p)->AddClassToList(strs[strs.Length-1],xt);
		p=pt->AddToBase(pid);
		if(p->type==3)p=((NodeOfTemplateClass*)p)->AddToList(pt);
		else p = ((NodeOfType*)p)->AddToList(pt);
		NodeOfRoot::RemoveUnknown(xt,p);
		XTypes& x= ((NodeOfType*)p)->Info;
		x.pNode = p;
		return x;
	}
	//�����ڵ㣨ģ���࣬�޼̳У�,���� Add("LJ::XTypes",Types<LJ::XTypes<T>>(),TypesCheckingObject::MakeObject<T>(1));
	XTypes& NodeOfRoot::Add(const XString& classPath,const XTypes& xt,const TypesCheckingObject& tc)
	{
		XArray<XString> strs = classPath.Split(L":",0xffffff,true);
		NodeOfRoot* p = &Root();
		for(int i=0;i+1<strs.Length;++i)
			p = p->AddNamespace(strs[i]);
		p = ((NodeOfNamespace*)p)->AddTemplateToList(strs[strs.Length-1])->AddTemplateClassToList(tc,xt);
		NodeOfRoot::RemoveUnknown(xt,p);
		XTypes& x= ((NodeOfTemplateClass*)p)->Info;
		x.pNode = p;
		return x;
	}
	//�����ڵ㣨ģ���࣬�м̳У�,���� Add("LJ::XArray",Types<LJ::XArray<T>>(),TypesCheckingObject::MakeObject<T>(1),typeid(LJ::XBase));
	XTypes& NodeOfRoot::Add(const XString& classPath,const XTypes& xt,const TypesCheckingObject& tc,const type_info& baseid)
	{
		NodeOfRoot* pid = Root().FindNodeByTypeInfo(baseid);
		if(pid==NULL)
		{
			pid = NodeOfRoot::AddUnknown(baseid);
		}
		XArray<XString> strs = classPath.Split(L":",0xffffff,true);
		NodeOfRoot* p = &Root();
		for(int i=0;i+1<strs.Length;++i)
			p = p->AddNamespace(strs[i]);
		p = ((NodeOfNamespace*)p)->AddTemplateToList(strs[strs.Length-1])->AddTemplateClassToList(tc,xt);
		NodeOfRoot::RemoveUnknown(xt,p);
		pid = ((NodeOfTemplateClass*)p)->AddToBase(pid);
		if(pid->type==3)p = ((NodeOfTemplateClass*)pid)->AddToList(p);
		else p = ((NodeOfType*)pid)->AddToList(p);
		XTypes& x= ((NodeOfTemplateClass*)p)->Info;
		x.pNode = p;
		return x;
	}

	//NodeOfNamespace
	//��һ���ڵ���ӵ�ָ���б��У���������ӵ����б���
	NodeOfType* NodeOfNamespace::AddClassToList(const XString& name,const XTypes& xt)
	{
		if(nodeCount==0)pNodeList = new NodeOfRoot*[1];
		else
		{
			for(unsigned long i=0;i<nodeCount;++i)
				if(pNodeList[i]->type==4 && name==((NodeOfType*)pNodeList[i])->name)
					return (NodeOfType*&)pNodeList[i];
			NodeOfRoot** tp = new NodeOfRoot*[nodeCount+1];
			Memory::Copy(tp,pNodeList,nodeCount*sizeof(NodeOfRoot*));
			delete[]pNodeList;
			pNodeList = tp;
		}
		pNodeList[nodeCount] = new NodeOfType(this,name,xt);
		return (NodeOfType*&)pNodeList[nodeCount++];
	}
	//��һ��ģ��ڵ���ӵ������б��У���������ӵ����б���
	NodeOfTemplate* NodeOfNamespace::AddTemplateToList(const XString& name)
	{
		for(unsigned long i=0;i<nodeCount;++i)
			if(pNodeList[i]->type==2 && name==((NodeOfTemplate*)pNodeList[i])->name)
				return (NodeOfTemplate*)pNodeList[i];
		NodeOfRoot** tp = new NodeOfRoot*[nodeCount+1];
		Memory::Copy(tp,pNodeList,nodeCount*sizeof(NodeOfRoot*));
		delete[]pNodeList;
		pNodeList = tp;
		return (NodeOfTemplate*)(pNodeList[nodeCount++] = new NodeOfTemplate(this,name));
	}
	//��������
	NodeOfNamespace::~NodeOfNamespace()
	{
		for(unsigned long i=0;i<nodeCount;++i)
		{
			switch(pNodeList[i]->type)
			{
			case 1:delete (NodeOfNamespace*)pNodeList[i];break;
			case 2:delete (NodeOfTemplate*)pNodeList[i];break;
			case 3:delete (NodeOfTemplateClass*)pNodeList[i];break;
			case 4:delete (NodeOfType*)pNodeList[i];break;
			}
		}
		delete []pNodeList;
		delete []name;
	}

	//NodeOfTemplate

	NodeOfTemplate::NodeOfTemplate(NodeOfRoot* p,const XString& str):pNamespace(p),name(VString::Strcpy(str.ToUnicode())),NodeOfRoot(2){}
	//��һ��ģ��ڵ���ӵ������б��У���������ӵ����б���
	NodeOfTemplateClass* NodeOfTemplate::AddTemplateClassToList(const TypesCheckingObject&tc ,const XTypes& xt)
	{
		for(unsigned long i=0;i<nodeCount;++i)
			if(pNodeList[i]->type==3 && tc==((NodeOfTemplateClass*)pNodeList[i])->typesChecking)
				return (NodeOfTemplateClass*)pNodeList[i];
		NodeOfRoot** tp = new NodeOfRoot*[nodeCount+1];
		Memory::Copy(tp,pNodeList,nodeCount*sizeof(NodeOfRoot*));
		delete[]pNodeList;
		pNodeList = tp;
		return (NodeOfTemplateClass*)(pNodeList[nodeCount++] = new NodeOfTemplateClass(this,tc,xt));
	}
	//��������
	NodeOfTemplate::~NodeOfTemplate()
	{
		for(unsigned long i=0;i<nodeCount;++i)
		{
			switch(pNodeList[i]->type)
			{
			case 1:delete (NodeOfNamespace*)pNodeList[i];break;
			case 2:delete (NodeOfTemplate*)pNodeList[i];break;
			case 3:delete (NodeOfTemplateClass*)pNodeList[i];break;
			case 4:delete (NodeOfType*)pNodeList[i];break;
			}
		}
		delete []pNodeList;
		delete []name;
	}

	//NodeOfTemplateClass
	
	//��һ���ڵ���ӵ������б��У���������ӵ����б��������
	NodeOfRoot* NodeOfTemplateClass::AddToList(NodeOfRoot* p)
	{
		if(p==NULL)throw XException(E_INVALIDARG);
		for(unsigned long i=0;i<nodeCount;++i)
			if(pNodeList[i]==p)
				return (NodeOfRoot*)pNodeList[i];
		NodeOfRoot** tp = new NodeOfRoot*[nodeCount+1];
		Memory::Copy(tp,pNodeList,nodeCount*sizeof(NodeOfRoot*));
		delete[]pNodeList;
		pNodeList = tp;
		return (NodeOfRoot*)(pNodeList[nodeCount++] = p);
	}
	//��һ���ڵ���ӵ��̳��б��У���������ӵ����б��������
	NodeOfRoot* NodeOfTemplateClass::AddToBase(NodeOfRoot* p)
	{
		if(p==NULL)throw XException(E_INVALIDARG);
		for(unsigned long i=0;i<baseCount;++i)
			if(pBaseList[i]==p)
				return (NodeOfRoot*)pBaseList[i];
		NodeOfRoot** tp = new NodeOfRoot*[baseCount+1];
		Memory::Copy(tp,pBaseList,baseCount*sizeof(NodeOfRoot*));
		delete[]pBaseList;
		pBaseList = tp;
		return (NodeOfRoot*)(pBaseList[baseCount++] = p);
	}
	//��������
	NodeOfTemplateClass::~NodeOfTemplateClass()
	{
		delete []pNodeList;
		delete []pBaseList;
	}


	//NodeOfType
	
	//��һ���ڵ���ӵ������б��У���������ӵ����б��������
	NodeOfRoot*& NodeOfType::AddToList(NodeOfRoot* p)
	{
		if(p==NULL)throw XException(E_INVALIDARG);
		if(nodeCount==0)pNodeList = new NodeOfRoot*[1];
		else
		{
			for(unsigned long i=0;i<nodeCount;++i)
				if(pNodeList[i]==p)
					return (NodeOfRoot*&)pNodeList[i];
			NodeOfRoot** tp = new NodeOfRoot*[nodeCount+1];
			Memory::Copy(tp,pNodeList,nodeCount*sizeof(NodeOfRoot*));
			delete[]pNodeList;
			pNodeList = tp;
		}
		return (NodeOfRoot*&)(pNodeList[nodeCount++] = p);
	}
	//��һ���ڵ���ӵ��̳��б��У���������ӵ����б��������
	NodeOfRoot*& NodeOfType::AddToBase(NodeOfRoot* p)
	{
		if(p==NULL)throw XException(E_INVALIDARG);
		if(baseCount==0)pBaseList = new NodeOfRoot*[1];
		else
		{
			for(unsigned long i=0;i<baseCount;++i)
				if(pBaseList[i]==p)
					return (NodeOfRoot*&)pBaseList[i];
			NodeOfRoot** tp = new NodeOfRoot*[baseCount+1];
			Memory::Copy(tp,pBaseList,baseCount*sizeof(NodeOfRoot*));
			delete[]pBaseList;
			pBaseList = tp;
		}
		return (NodeOfRoot*&)(pBaseList[baseCount++] = p);
	}
	//ʹ�ð�������������ռ�ڵ㡢���ƺ�������Ϣ������
	NodeOfType::NodeOfType(NodeOfRoot* p,const XString&s,const XTypes& t):pNamespace(p),Info(t),name(VString::Strcpy(s.ToUnicode())),baseCount(0),pBaseList(NULL),NodeOfRoot(4){}
	//��������
	NodeOfType::~NodeOfType()
	{
		delete []pNodeList;
		delete []pBaseList;
		delete []name;
	}

	const XTypes& XTypes::CurrentType = CREATECLASSTYPE(LJ::XTypes,LJ::XBase);
	XString XTypes::GetName()const
	{
		if(pNode==NULL)const_cast<NodeOfRoot*&>(pNode) = NodeOfRoot::Root().FindNodeByTypeInfo(*this);
		if(pNode)return pNode->GetName();
#ifdef _CLR
		if((Object^)pType->gcType)
			return pType->gcType->ToString();
#endif
		return pType->pTypeInfo->name();
	}
	XTypes::XTypes(const type_info& t):pNode(NULL),pType(new ITypes(t)){}
	XTypes::XTypes(const XTypes& ct)
		:pNode(ct.pNode),pType(ct.pType->NewCopy())
	{	}
	XTypes::XTypes(ITypes*p):pType(p),pNode(NULL){}
	XTypes::~XTypes()
	{
		delete pType;
	}
	XTypes::operator const type_info&()const
	{
		return *pType->pTypeInfo;
	}
	XString XTypes::GetFullName()const
	{
		if(pNode==NULL)const_cast<NodeOfRoot*&>(pNode) = NodeOfRoot::Root().FindNodeByTypeInfo(*this);
		if(pNode)return pNode->GetFullName();
#ifdef _CLR
		if((Object^)pType->gcType)
			return pType->gcType->ToString();
#endif
		return pType->pTypeInfo->name();
	}
	XString XTypes::ToString()const
	{
		return GetFullName();
	}
	bool XTypes::IsDerivedFrom(const XTypes&c)const
	{
		if(pNode==NULL)const_cast<NodeOfRoot*&>(pNode) = NodeOfRoot::Root().FindNodeByTypeInfo(*this);
		if(c.pNode==NULL)const_cast<NodeOfRoot*&>(c.pNode) = NodeOfRoot::Root().FindNodeByTypeInfo(c);
		if(pNode==NULL || c.pNode==NULL)return false;
		return pNode->IsDerivedFrom(c.pNode);
	}
	XTypes XTypes::GetPointedType()const
	{
		ITypes* p = pType->NewPointedType();
		if(p==NULL)throw XException(L"�����Ͳ���ָ������",E_INVALIDARG);
		XTypes t(p);
		delete p;
		return t;
	}


	
}
#endif