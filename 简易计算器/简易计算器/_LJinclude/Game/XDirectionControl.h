#pragma once//W意波编写
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
            int pressedKeysCount;//四个按键中，已按下数量
            char KeysList[4];//按键优先级
            char KeysValue[4];//按键值,对应上下左右键
            void setkey_up(char);char getkey_up()const{return KeysValue[0];}
            void setkey_down(char);char getkey_down()const{return KeysValue[1];}
            void setkey_left(char);char getkey_left()const{return KeysValue[2];}
            void setkey_right(char);char getkey_right()const{return KeysValue[3];}
        public:
			//当前的类型
			static const ClassTypes& CurrentType;
			//获取对象类型信息
			virtual const ClassTypes& GetClassType()const{return CurrentType;}
			//向上的按键
			PROPERTY_GETSET(char,XDirectionControl,getkey_up,setkey_up,Up);
			//向下的按键
			PROPERTY_GETSET(char,XDirectionControl,getkey_down,setkey_down,Down);
			//向左的按键
			PROPERTY_GETSET(char,XDirectionControl,getkey_left,setkey_left,Left);
			//向右的按键
			PROPERTY_GETSET(char,XDirectionControl,getkey_right,setkey_right,Right);
			//兼容属性，向上的按键
			CPROPERTY_GETSET(char,XDirectionControl,Up);
			//兼容属性，向下的按键
			CPROPERTY_GETSET(char,XDirectionControl,Down);
			//兼容属性，向左的按键
			CPROPERTY_GETSET(char,XDirectionControl,Left);
			//兼容属性，向右的按键
			CPROPERTY_GETSET(char,XDirectionControl,Right);
			//默认构造函数
            XDirectionControl();
			//构造函数
            XDirectionControl(char key_up,char key_down,char key_left,char key_right);
			//发生key按下事件时请调用此方法
            bool KeyDown(char keyValue);
			//发生key弹起事件时请调用此方法
            bool KeyUp(char KeyValue);
			//当前方向,-1代表无按键，0代表上，1代表下，2代表左，3代表右
            char CurrentDirection();
            operator char(){return CurrentDirection();}
        };
   }
}
