#pragma once//W�Ⲩ��д
#define XDIRECTIONCONTROL_
namespace LJ
{
    namespace Game
    {
        class XDirectionControl:public LJ::XThreadControl,public LJ::XBase
        {
			PROPERTY_OFFSET(XDirectionControl,Up);
			PROPERTY_OFFSET(XDirectionControl,Down);
			PROPERTY_OFFSET(XDirectionControl,Left);
			PROPERTY_OFFSET(XDirectionControl,Right);
            int pressedKeysCount;//�ĸ������У��Ѱ�������
            char KeysList[4];//�������ȼ�
            char KeysValue[4];//����ֵ,��Ӧ�������Ҽ�
            void setkey_up(char);char getkey_up()const{return KeysValue[0];}
            void setkey_down(char);char getkey_down()const{return KeysValue[1];}
            void setkey_left(char);char getkey_left()const{return KeysValue[2];}
            void setkey_right(char);char getkey_right()const{return KeysValue[3];}
        public:
			//��ǰ������
			static const ClassTypes& CurrentType;
			//��ȡ����������Ϣ
			virtual const ClassTypes& GetClassType()const{return CurrentType;}
			//���ϵİ���
			PROPERTY_GETSET(char,XDirectionControl,getkey_up,setkey_up,Up);
			//���µİ���
			PROPERTY_GETSET(char,XDirectionControl,getkey_down,setkey_down,Down);
			//����İ���
			PROPERTY_GETSET(char,XDirectionControl,getkey_left,setkey_left,Left);
			//���ҵİ���
			PROPERTY_GETSET(char,XDirectionControl,getkey_right,setkey_right,Right);
			//�������ԣ����ϵİ���
			CPROPERTY_GETSET(char,XDirectionControl,Up);
			//�������ԣ����µİ���
			CPROPERTY_GETSET(char,XDirectionControl,Down);
			//�������ԣ�����İ���
			CPROPERTY_GETSET(char,XDirectionControl,Left);
			//�������ԣ����ҵİ���
			CPROPERTY_GETSET(char,XDirectionControl,Right);
			//Ĭ�Ϲ��캯��
            XDirectionControl();
			//���캯��
            XDirectionControl(char key_up,char key_down,char key_left,char key_right);
			//����key�����¼�ʱ����ô˷���
            bool KeyDown(char keyValue);
			//����key�����¼�ʱ����ô˷���
            bool KeyUp(char KeyValue);
			//��ǰ����,-1�����ް�����0�����ϣ�1�����£�2������3������
            char CurrentDirection();
            operator char(){return CurrentDirection();}
        };
   }
}
