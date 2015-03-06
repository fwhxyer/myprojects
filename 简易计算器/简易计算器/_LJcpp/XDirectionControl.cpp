#include "stdafx.h"
#ifdef XDIRECTIONCONTROL_
namespace LJ
{
    namespace Game
    {
        XDirectionControl::XDirectionControl()
			:CPROPERTY_GETSET_INIT(this,XDirectionControl::getkey_up,XDirectionControl::setkey_up,Up)
			CPROPERTY_GETSET_INIT(*this,XDirectionControl::getkey_down,XDirectionControl::setkey_down,Down)
			CPROPERTY_GETSET_INIT(*this,XDirectionControl::getkey_left,XDirectionControl::setkey_left,Left)
			CPROPERTY_GETSET_INIT(*this,XDirectionControl::getkey_right,XDirectionControl::setkey_right,Right)
			pressedKeysCount(0)
        {
            KeysList[0] = KeysList[1] = KeysList[2] = KeysList[3] = 0;
            KeysValue[0] = VK_UP;
            KeysValue[1] = VK_DOWN;
            KeysValue[2] = VK_LEFT;
            KeysValue[3] = VK_RIGHT;
        }//���캯��
        XDirectionControl::XDirectionControl(char key_up,char key_down,char key_left,char key_right)//���캯��
			:CPROPERTY_GETSET_INIT(this,XDirectionControl::getkey_up,XDirectionControl::setkey_up,Up)
			CPROPERTY_GETSET_INIT(*this,XDirectionControl::getkey_down,XDirectionControl::setkey_down,Down)
			CPROPERTY_GETSET_INIT(*this,XDirectionControl::getkey_left,XDirectionControl::setkey_left,Left)
			CPROPERTY_GETSET_INIT(*this,XDirectionControl::getkey_right,XDirectionControl::setkey_right,Right)
			pressedKeysCount(0)
		{
            KeysList[0] = KeysList[1] = KeysList[2] = KeysList[3] = 0;
            KeysValue[0] = VK_UP;
            KeysValue[1] = VK_DOWN;
            KeysValue[2] = VK_LEFT;
            KeysValue[3] = VK_RIGHT;
            Up = key_up;Down = key_down;Left = key_left;Right = key_right;
        }
        bool XDirectionControl::KeyDown(char keyValue)//����key�����¼�ʱ����ô˷���
        {
            ThreadWait();//�ٽ���
            KeyUp(keyValue);
            int i=0;
            while(i<4){if(keyValue==KeysValue[i])break;++i;}//Ѱ�Ұ�������
            if(i==4)return ThreadDone(),false;
            if(++pressedKeysCount>4)pressedKeysCount=4;
            for(i=0;i<4;++i)if(keyValue==KeysList[i])break;//Ѱ�����ȼ�
            if(i==4)i=3;
            while(i>=1){KeysList[i]=KeysList[i-1];--i;}//�ƶ����ȼ�
            KeysList[0] = keyValue;//�����϶�
            ThreadDone();
            return true;
        }
        bool XDirectionControl::KeyUp(char KeyValue)//����key�����¼�ʱ����ô˷���
        {
            ThreadWait();//�ٽ���
            int i = 0;
            int kc = pressedKeysCount;
            while(i<kc)
            {
                if(KeysList[i]==KeyValue)
                {
                    if(--pressedKeysCount<0)pressedKeysCount=0;
                    break;
                }
                ++i;
            }//Ѱ�Ұ������ҵ����¼���¼��1
            if(i<kc)//�ҵ�����
            {
                while(i<3){KeysList[i]=KeysList[i+1];++i;}//���ȼ��ƶ�
                KeysList[3]=KeyValue;//���ײ�
                ThreadDone();
                return true;
            }
            ThreadDone();
            return false;
        }
        char XDirectionControl::CurrentDirection()//��ǰ����
        {
            char Value=0;
            ThreadWait();
            if(pressedKeysCount)Value = KeysList[0];//��һ���ȼ��İ���ֵ
            ThreadDone();
            for(int i=0;i<4;++i)if(Value==KeysValue[i])return i;
            return -1;
        }
        void XDirectionControl::setkey_up(char keyValue)
        {
            ThreadWait();
            KeyUp(keyValue);
            for(int i=0;i<4;++i)
                if(KeysValue[i]==keyValue)
                    KeysValue[i]=0;
            KeysValue[0] = keyValue;
            ThreadDone();
        }
        void XDirectionControl::setkey_down(char keyValue)
        {
            ThreadWait();
            KeyUp(keyValue);
            for(int i=0;i<4;++i)
                if(KeysValue[i]==keyValue)
                    KeysValue[i]=0;
            KeysValue[1] = keyValue;
            ThreadDone();
        }
        void XDirectionControl::setkey_left(char keyValue)
        {
            ThreadWait();
            KeyUp(keyValue);
            for(int i=0;i<4;++i)
                if(KeysValue[i]==keyValue)
                    KeysValue[i]=0;
            KeysValue[2] = keyValue;
            ThreadDone();
        }
        void XDirectionControl::setkey_right(char keyValue)
        {
            ThreadWait();
            KeyUp(keyValue);
            for(int i=0;i<4;++i)
                if(KeysValue[i]==keyValue)
                    KeysValue[i]=0;
            KeysValue[3] = keyValue;
            ThreadDone();
        }
  		const ClassTypes& Game::XDirectionControl::CurrentType = (CREATECLASSTYPE(LJ::Game::XDirectionControl,LJ::XBase),CREATECLASSTYPE(LJ::Game::XDirectionControl,LJ::ThreadControl));
   }
}
#endif