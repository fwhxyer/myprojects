// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
#pragma once

// TODO: 在此处引用程序需要的其他头文件
#include"_ljinclude\\stdafx.h"
struct CalculateNode
{
	short level;//优先级
	/*
	0数字
	1+加
	2-减
	3*乘
	4/除以
	5^次方
	6sin
	7cos
	8tan
	9cot
	10arcsin
	11arccos
	12arctan
	13ln
	14lg
	15log
	16,
	17+正
	18-负
	19(
	20)
	*/
	static enum:short
	{
	Number=0,
	Plus=1,
	Minus=2,
	Multiply=3,
	Divide=4,
	Pow=5,
	Sin=6,
	Cos=7,
	Tan=8,
	Cot=9,
	Arcsin=10,
	Arccos=11,
	Arctan=12,
	Ln=13,
	Lg=14,
	Sqrt=15,
	Log=16,
	Dou=17,
	Positive=18,
	Negative=19,
	L=20,
	R=21
	};
	short type;

	LJ::Equation::Float256 num;
	CalculateNode():level(0),type(0),num(0){}
	CalculateNode(short t,const LJ::Equation::Float256& f):level(0),type(t),num(f)
	{
		switch(type)
		{
		case Number: level = 0;break;//number
		case Plus: level = 1;break;//+
		case Minus: level = 1;break;//-
		case Multiply: level = 2;break;//*
		case Divide: level = 2;break;// /
		case Pow: level = 3;break;//^
		case Sin: level = 4;break;//sin
		case Cos: level = 4;break;//cos
		case Tan: level = 4;break;//tan
		case Cot: level = 4;break;//cot
		case Arcsin: level = 4;break;//arcsin
		case Arccos: level = 4;break;//arccos
		case Arctan: level = 4;break;//arctan
		case Ln: level = 4;break;//ln
		case Lg: level = 4;break;//lg
		case Sqrt: level = 4;break;//sqrt
		case Log: level = 5;break;//log
		case Dou: level = 6;break;//,
		case Positive: level = 7;break;//+
		case Negative: level = 7;break;//-
		case L: level = 8;break;//(
		case R: level = 8;break;//)
		};
	}
	CalculateNode& operator=(const CalculateNode&t){LJ::Memory::Copy<sizeof(CalculateNode)>(this,&t);return *this;}
	LJ::XString ToString(int n=30)const
	{
		switch(type)
		{
		case Number: return num.ToString(n);
		case Plus: return L"+";
		case Minus: return L"-";
		case Multiply: return L"*";
		case Divide: return L"/";
		case Pow: return L"^";
		case Sin: return L"sin";
		case Cos: return L"cos";
		case Tan: return L"tan";
		case Cot: return L"cot";
		case Arcsin: return L"arcsin";
		case Arccos: return L"arccos";
		case Arctan: return L"arctan";
		case Ln: return L"ln";
		case Lg: return L"lg";
		case Log: return L"log";
		case Dou: return L",";
		case Positive: return L"+";
		case Negative: return L"-";
		case L: return L"(";
		case R: return L")";
		case Sqrt: return L"sqrt";
		}
	}
};
#include "Form1.h"
