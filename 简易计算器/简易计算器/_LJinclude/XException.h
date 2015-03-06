#pragma once
#define XEXCEPTION_

//�±�Խ�����
#ifndef COR_E_INDEXOUTOFRANGE
#define COR_E_INDEXOUTOFRANGE 0x80131508
#endif

namespace LJ
{
	//�쳣���ͣ��ڼ�⵽����ʱ�׳�
	class XException:public XBase
	{
	protected:
		//��������
		XString description;
		//��������
		XString errorClassName;
		//�ڲ�����
		XException* pInner;
	public:
		PROPERTY_OFFSET(XException,ErrorClassName);
		//ͨ�û��෽��
		XBaseVTypeMethods_H(XException);
		//Ĭ�Ϲ��캯��
		XException()throw();
		//���ƹ��캯��
		XException(const XException& e)throw();
		//ʹ��һ���ַ�������ʼ��
		XException(const XString& description)throw();
		//ʹ��һ���ַ����������롢��������ʼ��
		XException(const XString& description, HRESULT hr,const XString& className=XString::Empty )throw();
		//ʹ��һ���ַ����������롢�������ڲ���������ʼ��
		XException(const XString& description, HRESULT hr,const XString& className,const XException& innerException )throw();
		//ʹ��һ������������ʼ��
		XException(HRESULT hr)throw();
		virtual ~XException();
		virtual XString ToString()const;
		virtual XString GetErrorClassName() const;
		virtual XString GetDescription() const;
		virtual XException GetInnerException() const;
		static const char* GetDescription(HRESULT);
		virtual bool Equals(const XException&)const;
		union
		{
			//������
			const HRESULT HResult;
			//ֻ�����ԣ���������
			PROPERTY_GET(XString,XException,GetErrorClassName,ErrorClassName);
			//ֻ�����ԣ���������
			PROPERTY_GET(XString,XException,GetDescription,Description);
			//ֻ�����ԣ��ڲ�����
			PROPERTY_GET(XException,XException,GetInnerException,InnerException);
		};
		//�޴���
		const static XException None;
#ifdef _CLR //�й�֧��
		//���й��쳣��ʼ��
		XException(System::Exception^ e);
		//���й��쳣��ת��
		operator System::Exception^()const;
		//ʹ���йܵķ���
		System::Exception^ operator->()const;
#endif
	};
}