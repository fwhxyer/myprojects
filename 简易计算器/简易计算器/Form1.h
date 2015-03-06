#pragma once


namespace 简易计算器 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace LJ;//LJ类库命名空间，使用了LJ::XArray、LJ::XString两个类
	using namespace LJ::Equation;//使用了LJ::Equation::Float256类

	/// <summary>
	/// Form1 摘要
	///
	/// 警告: 如果更改此类的名称，则需要更改
	///          与此类所依赖的所有 .resx 文件关联的托管资源编译器工具的
	///          “资源文件名”属性。否则，
	///          设计器将不能与此窗体的关联
	///          本地化资源正确交互。
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: 在此处添加构造函数代码
			//
		}
		CalculateNode calculate(XArray<CalculateNode>&);
		void ReText(System::String^str,int move);
	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected: 
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox_result;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::Button^  button7;
	private: System::Windows::Forms::Button^  button8;
	private: System::Windows::Forms::Button^  button9;
	private: System::Windows::Forms::Button^  button0;
	private: System::Windows::Forms::Button^  buttonPoint;
	private: System::Windows::Forms::Button^  buttonMinus;
	private: System::Windows::Forms::Button^  buttonPlus;
	private: System::Windows::Forms::Button^  buttonMultiply;
	private: System::Windows::Forms::Button^  buttonClear;
	private: System::Windows::Forms::Button^  buttonEqual;
	private: System::Windows::Forms::Button^  buttonDivide;
	private: System::Windows::Forms::Button^  buttonCos;
	private: System::Windows::Forms::Button^  buttonCot;
	private: System::Windows::Forms::Button^  buttonLg;
	private: System::Windows::Forms::Button^  buttonArcsin;
	private: System::Windows::Forms::Button^  buttonArctan;
	private: System::Windows::Forms::Button^  buttonArccos;
	private: System::Windows::Forms::Button^  buttonLog;
	private: System::Windows::Forms::Button^  buttonLn;
	private: System::Windows::Forms::Button^  buttonTan;
	private: System::Windows::Forms::Button^  buttonSin;
	private: System::Windows::Forms::Button^  buttonBack;

	private: System::Windows::Forms::Button^  buttonPow;
	private: System::Windows::Forms::Button^  buttonPi;
	private: System::Windows::Forms::Button^  buttonE;


	private: System::Windows::Forms::Button^  M3;
	private: System::Windows::Forms::Button^  buttonM4;
	private: System::Windows::Forms::Button^  buttonExp;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown1;


	protected: 

	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox_result = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->button0 = (gcnew System::Windows::Forms::Button());
			this->buttonPoint = (gcnew System::Windows::Forms::Button());
			this->buttonMinus = (gcnew System::Windows::Forms::Button());
			this->buttonPlus = (gcnew System::Windows::Forms::Button());
			this->buttonMultiply = (gcnew System::Windows::Forms::Button());
			this->buttonClear = (gcnew System::Windows::Forms::Button());
			this->buttonEqual = (gcnew System::Windows::Forms::Button());
			this->buttonDivide = (gcnew System::Windows::Forms::Button());
			this->buttonCos = (gcnew System::Windows::Forms::Button());
			this->buttonCot = (gcnew System::Windows::Forms::Button());
			this->buttonLg = (gcnew System::Windows::Forms::Button());
			this->buttonArcsin = (gcnew System::Windows::Forms::Button());
			this->buttonArctan = (gcnew System::Windows::Forms::Button());
			this->buttonArccos = (gcnew System::Windows::Forms::Button());
			this->buttonLog = (gcnew System::Windows::Forms::Button());
			this->buttonLn = (gcnew System::Windows::Forms::Button());
			this->buttonTan = (gcnew System::Windows::Forms::Button());
			this->buttonSin = (gcnew System::Windows::Forms::Button());
			this->buttonBack = (gcnew System::Windows::Forms::Button());
			this->buttonPow = (gcnew System::Windows::Forms::Button());
			this->buttonPi = (gcnew System::Windows::Forms::Button());
			this->buttonE = (gcnew System::Windows::Forms::Button());
			this->M3 = (gcnew System::Windows::Forms::Button());
			this->buttonM4 = (gcnew System::Windows::Forms::Button());
			this->buttonExp = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(10, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(53, 12);
			this->label1->TabIndex = 0;
			this->label1->Text = L"计算式：";
			// 
			// textBox1
			// 
			this->textBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox1->HideSelection = false;
			this->textBox1->Location = System::Drawing::Point(59, 6);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(526, 39);
			this->textBox1->TabIndex = 1;
			// 
			// textBox_result
			// 
			this->textBox_result->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox_result->Location = System::Drawing::Point(12, 63);
			this->textBox_result->Multiline = true;
			this->textBox_result->Name = L"textBox_result";
			this->textBox_result->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->textBox_result->Size = System::Drawing::Size(313, 174);
			this->textBox_result->TabIndex = 2;
			this->textBox_result->WordWrap = false;
			// 
			// label2
			// 
			this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 51);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(59, 12);
			this->label2->TabIndex = 3;
			this->label2->Text = L"计算结果:";
			// 
			// button1
			// 
			this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button1->Location = System::Drawing::Point(419, 179);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(37, 26);
			this->button1->TabIndex = 4;
			this->button1->Text = L"1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// button2
			// 
			this->button2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button2->Location = System::Drawing::Point(462, 179);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(37, 26);
			this->button2->TabIndex = 4;
			this->button2->Text = L"2";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click_1);
			// 
			// button3
			// 
			this->button3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button3->Location = System::Drawing::Point(505, 179);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(37, 26);
			this->button3->TabIndex = 4;
			this->button3->Text = L"3";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// button4
			// 
			this->button4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button4->Location = System::Drawing::Point(419, 147);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(37, 26);
			this->button4->TabIndex = 4;
			this->button4->Text = L"4";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
			// 
			// button5
			// 
			this->button5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button5->Location = System::Drawing::Point(462, 147);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(37, 26);
			this->button5->TabIndex = 4;
			this->button5->Text = L"5";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &Form1::button5_Click);
			// 
			// button6
			// 
			this->button6->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button6->Location = System::Drawing::Point(505, 147);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(37, 26);
			this->button6->TabIndex = 4;
			this->button6->Text = L"6";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &Form1::button6_Click);
			// 
			// button7
			// 
			this->button7->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button7->Location = System::Drawing::Point(419, 115);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(37, 26);
			this->button7->TabIndex = 4;
			this->button7->Text = L"7";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &Form1::button7_Click);
			// 
			// button8
			// 
			this->button8->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button8->Location = System::Drawing::Point(462, 115);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(37, 26);
			this->button8->TabIndex = 4;
			this->button8->Text = L"8";
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Click += gcnew System::EventHandler(this, &Form1::button8_Click);
			// 
			// button9
			// 
			this->button9->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button9->Location = System::Drawing::Point(505, 115);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(37, 26);
			this->button9->TabIndex = 4;
			this->button9->Text = L"9";
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Click += gcnew System::EventHandler(this, &Form1::button9_Click);
			// 
			// button0
			// 
			this->button0->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button0->Location = System::Drawing::Point(419, 211);
			this->button0->Name = L"button0";
			this->button0->Size = System::Drawing::Size(37, 26);
			this->button0->TabIndex = 4;
			this->button0->Text = L"0";
			this->button0->UseVisualStyleBackColor = true;
			this->button0->Click += gcnew System::EventHandler(this, &Form1::button0_Click);
			// 
			// buttonPoint
			// 
			this->buttonPoint->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->buttonPoint->Location = System::Drawing::Point(505, 211);
			this->buttonPoint->Name = L"buttonPoint";
			this->buttonPoint->Size = System::Drawing::Size(37, 26);
			this->buttonPoint->TabIndex = 4;
			this->buttonPoint->Text = L".";
			this->buttonPoint->UseVisualStyleBackColor = true;
			this->buttonPoint->Click += gcnew System::EventHandler(this, &Form1::buttonPoint_Click);
			// 
			// buttonMinus
			// 
			this->buttonMinus->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->buttonMinus->Location = System::Drawing::Point(548, 115);
			this->buttonMinus->Name = L"buttonMinus";
			this->buttonMinus->Size = System::Drawing::Size(37, 26);
			this->buttonMinus->TabIndex = 4;
			this->buttonMinus->Text = L"-";
			this->buttonMinus->UseVisualStyleBackColor = true;
			this->buttonMinus->Click += gcnew System::EventHandler(this, &Form1::buttonMinus_Click);
			// 
			// buttonPlus
			// 
			this->buttonPlus->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->buttonPlus->Location = System::Drawing::Point(548, 83);
			this->buttonPlus->Name = L"buttonPlus";
			this->buttonPlus->Size = System::Drawing::Size(37, 26);
			this->buttonPlus->TabIndex = 4;
			this->buttonPlus->Text = L"+";
			this->buttonPlus->UseVisualStyleBackColor = true;
			this->buttonPlus->Click += gcnew System::EventHandler(this, &Form1::buttonPlus_Click);
			// 
			// buttonMultiply
			// 
			this->buttonMultiply->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->buttonMultiply->Location = System::Drawing::Point(548, 147);
			this->buttonMultiply->Name = L"buttonMultiply";
			this->buttonMultiply->Size = System::Drawing::Size(37, 26);
			this->buttonMultiply->TabIndex = 4;
			this->buttonMultiply->Text = L"*";
			this->buttonMultiply->UseVisualStyleBackColor = true;
			this->buttonMultiply->Click += gcnew System::EventHandler(this, &Form1::buttonMultiply_Click);
			// 
			// buttonClear
			// 
			this->buttonClear->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->buttonClear->Location = System::Drawing::Point(462, 83);
			this->buttonClear->Name = L"buttonClear";
			this->buttonClear->Size = System::Drawing::Size(37, 26);
			this->buttonClear->TabIndex = 4;
			this->buttonClear->Text = L"C";
			this->buttonClear->UseVisualStyleBackColor = true;
			this->buttonClear->Click += gcnew System::EventHandler(this, &Form1::buttonClear_Click);
			// 
			// buttonEqual
			// 
			this->buttonEqual->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->buttonEqual->Location = System::Drawing::Point(548, 211);
			this->buttonEqual->Name = L"buttonEqual";
			this->buttonEqual->Size = System::Drawing::Size(37, 26);
			this->buttonEqual->TabIndex = 4;
			this->buttonEqual->Text = L"=";
			this->buttonEqual->UseVisualStyleBackColor = true;
			this->buttonEqual->Click += gcnew System::EventHandler(this, &Form1::buttonEqual_Click);
			// 
			// buttonDivide
			// 
			this->buttonDivide->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->buttonDivide->Location = System::Drawing::Point(548, 179);
			this->buttonDivide->Name = L"buttonDivide";
			this->buttonDivide->Size = System::Drawing::Size(37, 26);
			this->buttonDivide->TabIndex = 4;
			this->buttonDivide->Text = L"/";
			this->buttonDivide->UseVisualStyleBackColor = true;
			this->buttonDivide->Click += gcnew System::EventHandler(this, &Form1::buttonDivide_Click);
			// 
			// buttonCos
			// 
			this->buttonCos->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->buttonCos->Location = System::Drawing::Point(376, 83);
			this->buttonCos->Name = L"buttonCos";
			this->buttonCos->Size = System::Drawing::Size(37, 26);
			this->buttonCos->TabIndex = 4;
			this->buttonCos->Text = L"Cos";
			this->buttonCos->UseVisualStyleBackColor = true;
			this->buttonCos->Click += gcnew System::EventHandler(this, &Form1::buttonCos_Click);
			// 
			// buttonCot
			// 
			this->buttonCot->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->buttonCot->Location = System::Drawing::Point(376, 115);
			this->buttonCot->Name = L"buttonCot";
			this->buttonCot->Size = System::Drawing::Size(37, 26);
			this->buttonCot->TabIndex = 4;
			this->buttonCot->Text = L"Cot";
			this->buttonCot->UseVisualStyleBackColor = true;
			this->buttonCot->Click += gcnew System::EventHandler(this, &Form1::buttonCot_Click);
			// 
			// buttonLg
			// 
			this->buttonLg->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->buttonLg->Font = (gcnew System::Drawing::Font(L"宋体", 9));
			this->buttonLg->Location = System::Drawing::Point(333, 179);
			this->buttonLg->Name = L"buttonLg";
			this->buttonLg->Size = System::Drawing::Size(37, 26);
			this->buttonLg->TabIndex = 4;
			this->buttonLg->Text = L"lg";
			this->buttonLg->UseVisualStyleBackColor = true;
			this->buttonLg->Click += gcnew System::EventHandler(this, &Form1::buttonLg_Click);
			// 
			// buttonArcsin
			// 
			this->buttonArcsin->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->buttonArcsin->Location = System::Drawing::Point(370, 147);
			this->buttonArcsin->Name = L"buttonArcsin";
			this->buttonArcsin->Size = System::Drawing::Size(49, 26);
			this->buttonArcsin->TabIndex = 4;
			this->buttonArcsin->Text = L"Arcsin";
			this->buttonArcsin->UseVisualStyleBackColor = true;
			this->buttonArcsin->Click += gcnew System::EventHandler(this, &Form1::buttonArcsin_Click);
			// 
			// buttonArctan
			// 
			this->buttonArctan->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->buttonArctan->Location = System::Drawing::Point(370, 211);
			this->buttonArctan->Name = L"buttonArctan";
			this->buttonArctan->Size = System::Drawing::Size(49, 26);
			this->buttonArctan->TabIndex = 4;
			this->buttonArctan->Text = L"Arctan";
			this->buttonArctan->UseVisualStyleBackColor = true;
			this->buttonArctan->Click += gcnew System::EventHandler(this, &Form1::buttonArctan_Click);
			// 
			// buttonArccos
			// 
			this->buttonArccos->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->buttonArccos->Location = System::Drawing::Point(370, 179);
			this->buttonArccos->Name = L"buttonArccos";
			this->buttonArccos->Size = System::Drawing::Size(49, 26);
			this->buttonArccos->TabIndex = 4;
			this->buttonArccos->Text = L"Arccos";
			this->buttonArccos->UseVisualStyleBackColor = true;
			this->buttonArccos->Click += gcnew System::EventHandler(this, &Form1::buttonArccos_Click);
			// 
			// buttonLog
			// 
			this->buttonLog->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->buttonLog->Location = System::Drawing::Point(333, 211);
			this->buttonLog->Name = L"buttonLog";
			this->buttonLog->Size = System::Drawing::Size(37, 26);
			this->buttonLog->TabIndex = 4;
			this->buttonLog->Text = L"log";
			this->buttonLog->UseVisualStyleBackColor = true;
			this->buttonLog->Click += gcnew System::EventHandler(this, &Form1::buttonLog_Click);
			// 
			// buttonLn
			// 
			this->buttonLn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->buttonLn->Location = System::Drawing::Point(333, 147);
			this->buttonLn->Name = L"buttonLn";
			this->buttonLn->Size = System::Drawing::Size(37, 26);
			this->buttonLn->TabIndex = 4;
			this->buttonLn->Text = L"ln";
			this->buttonLn->UseVisualStyleBackColor = true;
			this->buttonLn->Click += gcnew System::EventHandler(this, &Form1::buttonLn_Click);
			// 
			// buttonTan
			// 
			this->buttonTan->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->buttonTan->Location = System::Drawing::Point(333, 115);
			this->buttonTan->Name = L"buttonTan";
			this->buttonTan->Size = System::Drawing::Size(37, 26);
			this->buttonTan->TabIndex = 4;
			this->buttonTan->Text = L"Tan";
			this->buttonTan->UseVisualStyleBackColor = true;
			this->buttonTan->Click += gcnew System::EventHandler(this, &Form1::buttonTan_Click);
			// 
			// buttonSin
			// 
			this->buttonSin->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->buttonSin->Location = System::Drawing::Point(333, 83);
			this->buttonSin->Name = L"buttonSin";
			this->buttonSin->Size = System::Drawing::Size(37, 26);
			this->buttonSin->TabIndex = 4;
			this->buttonSin->Text = L"Sin";
			this->buttonSin->UseVisualStyleBackColor = true;
			this->buttonSin->Click += gcnew System::EventHandler(this, &Form1::buttonSin_Click);
			// 
			// buttonBack
			// 
			this->buttonBack->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->buttonBack->Location = System::Drawing::Point(419, 83);
			this->buttonBack->Name = L"buttonBack";
			this->buttonBack->Size = System::Drawing::Size(37, 26);
			this->buttonBack->TabIndex = 4;
			this->buttonBack->Text = L"Back";
			this->buttonBack->UseVisualStyleBackColor = true;
			this->buttonBack->Click += gcnew System::EventHandler(this, &Form1::buttonBack_Click);
			// 
			// buttonPow
			// 
			this->buttonPow->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->buttonPow->Location = System::Drawing::Point(505, 83);
			this->buttonPow->Name = L"buttonPow";
			this->buttonPow->Size = System::Drawing::Size(37, 26);
			this->buttonPow->TabIndex = 4;
			this->buttonPow->Text = L"^";
			this->buttonPow->UseVisualStyleBackColor = true;
			this->buttonPow->Click += gcnew System::EventHandler(this, &Form1::buttonPow_Click);
			// 
			// buttonPi
			// 
			this->buttonPi->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->buttonPi->Location = System::Drawing::Point(419, 51);
			this->buttonPi->Name = L"buttonPi";
			this->buttonPi->Size = System::Drawing::Size(37, 26);
			this->buttonPi->TabIndex = 4;
			this->buttonPi->Text = L"Pi";
			this->buttonPi->UseVisualStyleBackColor = true;
			this->buttonPi->Click += gcnew System::EventHandler(this, &Form1::buttonPi_Click);
			// 
			// buttonE
			// 
			this->buttonE->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->buttonE->Location = System::Drawing::Point(462, 51);
			this->buttonE->Name = L"buttonE";
			this->buttonE->Size = System::Drawing::Size(37, 26);
			this->buttonE->TabIndex = 4;
			this->buttonE->Text = L"e";
			this->buttonE->UseVisualStyleBackColor = true;
			this->buttonE->Click += gcnew System::EventHandler(this, &Form1::buttonE_Click);
			// 
			// M3
			// 
			this->M3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->M3->Location = System::Drawing::Point(505, 51);
			this->M3->Name = L"M3";
			this->M3->Size = System::Drawing::Size(37, 26);
			this->M3->TabIndex = 4;
			this->M3->Text = L"(";
			this->M3->UseVisualStyleBackColor = true;
			this->M3->Click += gcnew System::EventHandler(this, &Form1::M3_Click);
			// 
			// buttonM4
			// 
			this->buttonM4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->buttonM4->Location = System::Drawing::Point(548, 51);
			this->buttonM4->Name = L"buttonM4";
			this->buttonM4->Size = System::Drawing::Size(37, 26);
			this->buttonM4->TabIndex = 4;
			this->buttonM4->Text = L")";
			this->buttonM4->UseVisualStyleBackColor = true;
			this->buttonM4->Click += gcnew System::EventHandler(this, &Form1::buttonM4_Click);
			// 
			// buttonExp
			// 
			this->buttonExp->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->buttonExp->Location = System::Drawing::Point(462, 211);
			this->buttonExp->Name = L"buttonExp";
			this->buttonExp->Size = System::Drawing::Size(37, 26);
			this->buttonExp->TabIndex = 4;
			this->buttonExp->Text = L"10^";
			this->buttonExp->UseVisualStyleBackColor = true;
			this->buttonExp->Click += gcnew System::EventHandler(this, &Form1::buttonExp_Click);
			// 
			// label3
			// 
			this->label3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(331, 58);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(29, 12);
			this->label3->TabIndex = 5;
			this->label3->Text = L"精度";
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->numericUpDown1->Location = System::Drawing::Point(365, 56);
			this->numericUpDown1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {77, 0, 0, 0});
			this->numericUpDown1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(48, 21);
			this->numericUpDown1->TabIndex = 6;
			this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {30, 0, 0, 0});
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(597, 249);
			this->Controls->Add(this->numericUpDown1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->button0);
			this->Controls->Add(this->buttonDivide);
			this->Controls->Add(this->buttonM4);
			this->Controls->Add(this->M3);
			this->Controls->Add(this->buttonE);
			this->Controls->Add(this->buttonPi);
			this->Controls->Add(this->buttonSin);
			this->Controls->Add(this->buttonTan);
			this->Controls->Add(this->buttonLn);
			this->Controls->Add(this->buttonLog);
			this->Controls->Add(this->buttonArccos);
			this->Controls->Add(this->buttonArctan);
			this->Controls->Add(this->buttonArcsin);
			this->Controls->Add(this->buttonLg);
			this->Controls->Add(this->buttonCot);
			this->Controls->Add(this->buttonPow);
			this->Controls->Add(this->buttonBack);
			this->Controls->Add(this->buttonCos);
			this->Controls->Add(this->buttonClear);
			this->Controls->Add(this->buttonEqual);
			this->Controls->Add(this->buttonMultiply);
			this->Controls->Add(this->buttonPlus);
			this->Controls->Add(this->buttonMinus);
			this->Controls->Add(this->button9);
			this->Controls->Add(this->button8);
			this->Controls->Add(this->button7);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->buttonExp);
			this->Controls->Add(this->buttonPoint);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBox_result);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->MinimumSize = System::Drawing::Size(613, 288);
			this->Name = L"Form1";
			this->Text = L"简易计算器1.0（W意波出品）";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void buttonEqual_Click(System::Object^  sender, System::EventArgs^  e) {
				 textBox_result->Text=L"";
				 //先补充计算式中的括号
				 XString  str = textBox1->Text;
				 int leftCount = str.CountOf('(');
				 int rightCount = str.CountOf(')');
				 if(leftCount>rightCount)str=str.PadRight(str.Length+leftCount-rightCount,')');
				 else if(leftCount<rightCount)str=str.PadLeft(str.Length+rightCount-leftCount,'(');
				 textBox1->Text = str;
				// 进入分析环节，将字符串中的符号和数字加以提炼
				 XArray<CalculateNode> tmp=new VArray<CalculateNode>();
				 str = str.ToLower().Replace(L" ",L"").Replace(L"\n",L"");
				 for(int i=0;i<str.Length;)
				 {
					 switch(str[i])
					 {
					 case L'(':i++;tmp.Append(CalculateNode(CalculateNode::L,0));break;
					 case L')':i++;tmp.Append(CalculateNode(CalculateNode::R,0));break;
					 case L',':i++;tmp.Append(CalculateNode(CalculateNode::Dou,0));break;
					 case L'l':if(str[i+1]==L'o'){i+=3;tmp.Append(CalculateNode(CalculateNode::Log,0));}
							   else if(str[i+1]==L'g'){i+=2;tmp.Append(CalculateNode(CalculateNode::Lg,0));}
							   else if(str[i+1]==L'n'){i+=2;tmp.Append(CalculateNode(CalculateNode::Ln,0));}
							   break;
					 case L'a':if(str[i+3]==L't'){tmp.Append(CalculateNode(CalculateNode::Arctan,0));}
							   else if(str[i+3]==L'c'){tmp.Append(CalculateNode(CalculateNode::Arccos,0));}
							   else if(str[i+3]==L's'){tmp.Append(CalculateNode(CalculateNode::Arcsin,0));}
							   i+=6;
							   break;
					 case L't':tmp.Append(CalculateNode(CalculateNode::Tan,0));i+=3;break;
					 case L'c':if(str[i+2]==L's')tmp.Append(CalculateNode(CalculateNode::Cos,0));
							   else tmp.Append(CalculateNode(CalculateNode::Cot,0));
							   i+=3;
							 break;
					 case L's':if(str[i+1]==L'q'){i+=4;tmp.Append(CalculateNode(CalculateNode::Sqrt,0));break;}
							   i+=3;tmp.Append(CalculateNode(CalculateNode::Sin,0));break;
					 case L'^':i++;tmp.Append(CalculateNode(CalculateNode::Pow,0));break;
					 case L'/':i++;tmp.Append(CalculateNode(CalculateNode::Divide,0));break;
					 case L'*':i++;tmp.Append(CalculateNode(CalculateNode::Multiply,0));break;
					 case L'+':if(i==0 || (str[i-1]<L'0' || str[i-1]>L'9')&& str[i-1]!=L'ｅ'&& str[i-1]!=L'.' && str[i-1]!=L'π' )tmp.Append(CalculateNode(CalculateNode::Positive,0));
							   else tmp.Append(CalculateNode(CalculateNode::Plus,0));
						 i++;
						 break;
					 case L'-':if(i==0 || (str[i-1]<L'0' || str[i-1]>L'9')&& str[i-1]!=L'ｅ'&& str[i-1]!=L'.' && str[i-1]!=L'π' )tmp.Append(CalculateNode(CalculateNode::Negative,0));
							   else tmp.Append(CalculateNode(CalculateNode::Minus,0));
						 i++;
						 break;
					 case L'ｅ':i++;tmp.Append(CalculateNode(CalculateNode::Number,Float256::E));break;
					 case L'π':i++;tmp.Append(CalculateNode(CalculateNode::Number,Float256::Pi));break;
					 default:
						 if(str[i]<=L'9' && str[i]>=L'0' || str[i]==L'.')
						 {
							 int end = i;
							 for(;end<str.Length;++end)
							 {
								 if(str[end]==L'+' || str[end]==L'-')
								 {
									 if((str[end-1]<=L'9' && str[end-1]>=L'0') || str[end-1]==L'.')break;
								 }
								 else if(str[end]!=L'e' && str[end]!=L'.' && (str[end]<L'0' || str[end]>L'9'))
									 break;
							 }
							 tmp.Append(CalculateNode(CalculateNode::Number,str.Substring(i,end-i)));
							 i=end;
						 }
						 else ++i;
					 }
				 }
				 //解释如7sin3为(7*sin3)的关系：

				 for(int i=0;i+1<tmp.Length;++i)
				 {
					 if(tmp[i].type==CalculateNode::Number)
					 {
						 if(tmp[i+1].type==CalculateNode::Dou || tmp[i+1].type==CalculateNode::R ||(tmp[i+1].type<=CalculateNode::Pow&&tmp[i+1].type>=CalculateNode::Plus))
						 {
							 continue;
						 }
						 int k=0,n=0;
						 for(int j=i+1;j<tmp.Length;++j)
						 {
							 switch(tmp[j].type)
							 {
							 case CalculateNode::L:k++;break;
							 case CalculateNode::R:k--;break;
							 case CalculateNode::Number:n++;
							 }
							 if(n!=0&&k==0)
							 {
								 tmp.Insert(j+1,CalculateNode(CalculateNode::R,0));
								 break;
							 }
						 }
						 if(k>0)tmp.Append(CalculateNode(CalculateNode::R,0));
						 tmp.Insert(i+1,CalculateNode(CalculateNode::Multiply,0));
						 tmp.Insert(i,CalculateNode(CalculateNode::L,0));
					 }
				 }

				 CalculateNode t = calculate(tmp);
				 textBox_result->Text+= L"结果："+t.num.ToString((int)numericUpDown1->Value);
			 }
private: System::Void buttonPi_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 ReText("π",1);
		 }
private: System::Void buttonE_Click(System::Object^  sender, System::EventArgs^  e) {
			 ReText("ｅ",1);
		 }
private: System::Void buttonSin_Click(System::Object^  sender, System::EventArgs^  e) {
			 ReText("sin",3);
		 }
private: System::Void M3_Click(System::Object^  sender, System::EventArgs^  e) {
			 ReText("(",1);
		 }
private: System::Void buttonM4_Click(System::Object^  sender, System::EventArgs^  e) {
			 ReText(")",1);
		 }
private: System::Void buttonCos_Click(System::Object^  sender, System::EventArgs^  e) {
			 ReText("cos",3);
		 }
private: System::Void buttonBack_Click(System::Object^  sender, System::EventArgs^  e) {
			 int start = textBox1->SelectionStart;
			 if(textBox1->SelectedText && textBox1->SelectionLength>0)
			 {
				 textBox1->Text = textBox1->Text->Remove(textBox1->SelectionStart,textBox1->SelectionLength);
				 textBox1->SelectionStart = start;
				 return;
			 }
			 if(textBox1->Text!=nullptr && textBox1->SelectionStart>0)
			 {
				 textBox1->Text = textBox1->Text->Remove(textBox1->SelectionStart-1,1);
				 textBox1->SelectionStart = start-1;
			 }
		 }
private: System::Void buttonClear_Click(System::Object^  sender, System::EventArgs^  e) {
				textBox1->Text = "";
		 }
private: System::Void buttonPow_Click(System::Object^  sender, System::EventArgs^  e) {
			 ReText("^",1);
		 }
private: System::Void buttonPlus_Click(System::Object^  sender, System::EventArgs^  e) {
			 ReText("+",1);
		 }
private: System::Void buttonTan_Click(System::Object^  sender, System::EventArgs^  e) {
			 ReText("tan",3);
		 }
private: System::Void buttonCot_Click(System::Object^  sender, System::EventArgs^  e) {
			 ReText("cot",3);
		 }
private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) {
			 ReText("7",1);
		 }
private: System::Void button8_Click(System::Object^  sender, System::EventArgs^  e) {
			 ReText("8",1);
		 }
private: System::Void button9_Click(System::Object^  sender, System::EventArgs^  e) {
			 ReText("9",1);
		 }
private: System::Void buttonMinus_Click(System::Object^  sender, System::EventArgs^  e) {
			 ReText("-",1);
		 }
private: System::Void buttonLn_Click(System::Object^  sender, System::EventArgs^  e) {
			 ReText("ln",2);
		 }
private: System::Void buttonArcsin_Click(System::Object^  sender, System::EventArgs^  e) {
			 ReText("arcsin",6);
		 }
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
			 ReText("4",1);
		 }
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
			 ReText("5",1);
		 }
private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
			 ReText("6",1);
		 }
private: System::Void buttonMultiply_Click(System::Object^  sender, System::EventArgs^  e) {
			 ReText("*",1);
		 }
private: System::Void buttonLg_Click(System::Object^  sender, System::EventArgs^  e) {
			 ReText("lg",2);
		 }
private: System::Void buttonArccos_Click(System::Object^  sender, System::EventArgs^  e) {
			 ReText("arccos",6);
		 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 ReText("1",1);
		 }
private: System::Void button2_Click_1(System::Object^  sender, System::EventArgs^  e) {
			 ReText("2",1);
		 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			 ReText("3",1);
		 }
private: System::Void buttonDivide_Click(System::Object^  sender, System::EventArgs^  e) {
			 ReText("/",1);
		 }
private: System::Void buttonLog_Click(System::Object^  sender, System::EventArgs^  e) {
			 ReText("log(,)",4);
		 }
private: System::Void buttonArctan_Click(System::Object^  sender, System::EventArgs^  e) {
			 ReText("arctan",6);
		 }
private: System::Void button0_Click(System::Object^  sender, System::EventArgs^  e) {
			 ReText("0",1);
		 }
private: System::Void buttonPoint_Click(System::Object^  sender, System::EventArgs^  e) {
			 ReText(".",1);
		 }
private: System::Void buttonExp_Click(System::Object^  sender, System::EventArgs^  e) {
			 ReText("e",1);
		 }
};
}

