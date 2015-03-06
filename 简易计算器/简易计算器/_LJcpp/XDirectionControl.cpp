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
        }//构造函数
        XDirectionControl::XDirectionControl(char key_up,char key_down,char key_left,char key_right)//构造函数
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
        bool XDirectionControl::KeyDown(char keyValue)//发生key按下事件时请调用此方法
        {
            ThreadWait();//临界区
            KeyUp(keyValue);
            int i=0;
            while(i<4){if(keyValue==KeysValue[i])break;++i;}//寻找按键方向
            if(i==4)return ThreadDone(),false;
            if(++pressedKeysCount>4)pressedKeysCount=4;
            for(i=0;i<4;++i)if(keyValue==KeysList[i])break;//寻找优先级
            if(i==4)i=3;
            while(i>=1){KeysList[i]=KeysList[i-1];--i;}//移动优先级
            KeysList[0] = keyValue;//到最上端
            ThreadDone();
            return true;
        }
        bool XDirectionControl::KeyUp(char KeyValue)//发生key弹起事件时请调用此方法
        {
            ThreadWait();//临界区
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
            }//寻找按键，找到则按下键记录减1
            if(i<kc)//找到按键
            {
                while(i<3){KeysList[i]=KeysList[i+1];++i;}//优先级移动
                KeysList[3]=KeyValue;//到底层
                ThreadDone();
                return true;
            }
            ThreadDone();
            return false;
        }
        char XDirectionControl::CurrentDirection()//当前方向
        {
            char Value=0;
            ThreadWait();
            if(pressedKeysCount)Value = KeysList[0];//第一优先级的按键值
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