// 简易计算器.cpp: 主项目文件。

#include "stdafx.h"

using namespace 简易计算器;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// 在创建任何控件之前启用 Windows XP 可视化效果
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// 创建主窗口并运行它
	Application::Run(gcnew Form1());
	return 0;
}
void 简易计算器::Form1::ReText(System::String^str,int move)
{
	int selectIndex = textBox1->SelectionStart;
	if(textBox1->SelectionLength>0)textBox1->Text = textBox1->Text->Remove(selectIndex,textBox1->SelectionLength);
	textBox1->Text = textBox1->Text->Insert(selectIndex,str);
	textBox1->SelectionStart = selectIndex+move;
}


CalculateNode 简易计算器::Form1::calculate(XArray<CalculateNode>& str)
{
	if(str.Length==0)return CalculateNode();
	//先处理括号
	int i=0;
	for(;;)
	{
		while(++i<str.Length)
		{
			if(str[i].type==CalculateNode::R)break;
		}
		if(i>=str.Length)break;//无括号
		int j=i;
		while(--j>0)
		{
			if(str[j].type==CalculateNode::L)break;
		}
		str[j] = calculate(str.SubArray(j+1,i-j-1));
		str.Remove(j+1,i-j);
		i=j;
		textBox_result->Text += L"=";
		for(int k=0;k<str.Length;++k)if(str[k].type!=CalculateNode::Log || k+1<str.Length&&str[k+1].type!=CalculateNode::Number)textBox_result->Text +=str[k].ToString((int)numericUpDown1->Value);
		textBox_result->Text +=L"\r\n";
	}
	//处理正号
	for(i =0;i<str.Length;)
	{
		if(str[i].type==CalculateNode::Positive)//正号
			str.RemoveAt(i);
		else ++i;
	}
	//处理负号
	for(i =0;i<str.Length;)
	{
		if(str[i].type==CalculateNode::Negative)
		{
			if(i+1<str.Length)
			{
				if(str[i+1].type==CalculateNode::Number)
				{
					str[i+1].num.SelfNegative();
				}
				else if(str[i+1].type==CalculateNode::Negative)str.RemoveAt(i);
			}
			str.RemoveAt(i);
		}
		else ++i;
	}
	//处理逗号
	for(i =0;i<str.Length;i++)
	{
		if(str[i].type==CalculateNode::Dou)
			return CalculateNode(0,calculate(str.SubArray(i+1,str.Length-i-1)).num.Log(calculate(str.SubArray(0,i)).num));
	}
	//处理arcsin、arctan。。。
	for(i=0;i+1<str.Length;)
	{
		if(str[i].type<=CalculateNode::Log && str[i].type>=CalculateNode::Sin)
		{
			if(str[i+1].type<=CalculateNode::Log && str[i+1].type>=CalculateNode::Sin){++i;continue;}
			switch(str[i].type)
			{
			case CalculateNode::Log: str.RemoveAt(i);break;
			case CalculateNode::Sqrt: str.RemoveAt(i);str[i].num = str[i].num.Sqrt();break;
			case CalculateNode::Lg: str.RemoveAt(i);str[i].num = str[i].num.Lg();break;
			case CalculateNode::Ln: str.RemoveAt(i);str[i].num = str[i].num.Ln();break;
			case CalculateNode::Arctan: str.RemoveAt(i);str[i].num = str[i].num.Arctan();break;
			case CalculateNode::Arccos: str.RemoveAt(i);str[i].num = str[i].num.Arccos();break;
			case CalculateNode::Arcsin: str.RemoveAt(i);str[i].num = str[i].num.Arcsin();break;
			case CalculateNode::Cot: str.RemoveAt(i);str[i].num = str[i].num.Cot();break;
			case CalculateNode::Tan: str.RemoveAt(i);str[i].num = str[i].num.Tan();break;
			case CalculateNode::Cos: str.RemoveAt(i);str[i].num = str[i].num.Cos();break;
			case CalculateNode::Sin: str.RemoveAt(i);str[i].num = str[i].num.Sin();break;
			}
			if(i>0&& str[i-1].type<=CalculateNode::Log && str[i-1].type>=CalculateNode::Sin){--i;}
		}
		else ++i;
	}
	//处理“^”
	for(i=0;i+1<str.Length;)
	{
		if(str[i].type==CalculateNode::Pow)
		{
			if(i>0)str[i-1].num = str[i-1].num.Pow(str[i+1].num);
			str.Remove(i,2);
		}
		else i++;
	}
	//处理*和/
	for(i=0;i+1<str.Length;)
	{
		if(str[i].type==CalculateNode::Multiply)
		{
			if(i>0)str[i-1].num = str[i-1].num*str[i+1].num;
			str.Remove(i,2);
		}
		else
		if(str[i].type==CalculateNode::Divide)
		{
			if(i>0)str[i-1].num = str[i-1].num/str[i+1].num;
			str.Remove(i,2);
		}
		else i++;
	}
	//处理+和-
	for(i=0;i+1<str.Length;)
	{
		if(str[i].type==CalculateNode::Plus)
		{
			if(i>0)str[i-1].num = str[i-1].num+str[i+1].num;
			str.Remove(i,2);
		}
		else
			if(str[i].type==CalculateNode::Minus)
		{
			if(i>0)str[i-1].num = str[i-1].num-str[i+1].num;
			str.Remove(i,2);
		}
		else i++;
	}
	return str[0];
}