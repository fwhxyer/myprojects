#ifndef XEQUATIONEXCEPTION_
#define XEQUATIONEXCEPTION_
namespace LJ
{
	namespace Equation
	{
		struct EquationError
		{
			static enum Float256:signed char
			{
				PlusExpOverflow = -2,
				MinusExpOverflow = -3,
				MultiplyExpOverflow = -4,
				DivideExpOverflow = -5,
				Divide0 = -6,
				ModDivide0 = -7,
				ExpEOverflow = -8,
				Exp2Overflow = -9,
				Arcsin = -10,
				Arccos = -11,
				Tan = -12,
				Cot = -13,
				LnLessOrEqual0 = -14,
				SqrtLessThan0 = -15,
				PowLessThan0 = -16,
				Pow00 = -17
			};
		};
		class XEquationException:public LJ::XException
		{
		public:
		};
	}
}
#endif