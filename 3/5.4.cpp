#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#define o(x) round(x * pow(10,5))/pow(10,5) 

//значение функции 
double getValue(const double& x)  {
	return exp(2*x);
}

//точное значение певрой производной
double getExpFirstDerivative (const double& x) {
	return 2* exp(2*x);
}

//точное значение второй производной
double getExpSecondDerivative (const double& x) {
	return 4* exp(2*x);
}

//значение первой производной с первый порядком точности 
double getFirstDevivativeOH(const double x, const double h) {
	return (o(getValue(x)) - o(getValue(x-h)))/h;
}

//значение первой производной со вторым порядком точности 
double getFirstDerivativeOH2(const double x, const double h) {
	return ((-3)* o(getValue(x)) + 4* o(getValue(x + h)) - o(getValue(x + 2*h)))/(2*h);
}
//значение второй производной с первым порядком точности 
double getSecondDerivativeOH2(const double x, const double h) {
	return (o(getValue(x+h)) - 2*o(getValue(x)) + o(getValue(x-h)))/(pow(h, 2));
}

//значение первой производнйо с третьим порядком точности 
double getFirstDerivativeOH3(const double x, const double h) {
	return ((-11)*o(getValue(x-3*h)) +  18*o(getValue(x-2*h)) - 9*o(getValue(x-h)) + 2*o(getValue(x)))/(6*h);
}

//значение первой производнйо с четвертым порядком точности 
double getFirstDerivativeOH4(const double x, const double h) {
	return (o(getValue(x-2*h)) - 8*o(getValue(x-h)) + 8*o(getValue(x+h)) - o(getValue(x+2*h)))/(12*h);
}
int main() {
	double h = 0.0; //шаг
	int n = 0;//количтсво узлов
	double begin = 0.0;// начало отрезка 

	std::cout<<"Enter step, quantity of steps and then begin of the section :"<<std::endl;
	// std::cin>>h>>n>>begin;
	h = 0.1; n = 10;
	std::cout<<std::setfill(' ')<<std::setw(6)<<"x";
	std::cout<<std::setfill(' ')<<std::setw(12)<<"f(x)";
	std::cout<<std::setfill(' ')<<std::setw(15)<<"f(x)'";
	std::cout<<std::setfill(' ')<<std::setw(12)<<"f_'(x)";
	std::cout<<std::setfill(' ')<<std::setw(15)<<"O(h)";
	std::cout<<std::setfill(' ')<<std::setw(11)<<"f='(x)";
	std::cout<<std::setfill(' ')<<std::setw(18)<<"O(h^2)";
	std::cout<<std::setfill(' ')<<std::setw(12)<<"f(x)''";
	std::cout<<std::setfill(' ')<<std::setw(12)<<"f_(x)''";
	std::cout<<std::setfill(' ')<<std::setw(20)<<"O(h^2)";

	// std::vector<double > y_i, x_i; 
	// y_i.push_back(getValue(begin - h));
	// x_i.push_back(begin - h);
	double x = 0.0;
	std::cout<<std::endl;

	// for (int i = 0; i <= n; ++i)
	// {
	// 	x = begin + h * (i);
	// 	x_i.push_back(x);
	// 	y_i.push_back(getValue(x));
	// }

	// x_i.push_back(begin+ h *n + h);
	// x_i.push_back(begin+ h *n + 2*h);

	// y_i.push_back(getValue(begin+ h *n + h));
	// y_i.push_back(getValue(begin+ h *n + 2*h));

	//вывод производных
	for (int i = 0; i <= n; ++i)
	{
		x = begin + h * (i);

		std::cout<<std::setfill(' ')<<std::setw(6)<<x;

		// y_i.push_back(getValue(x));
		std::cout<<std::setfill(' ')<<std::setw(12)<<std::setprecision(5)<<getValue(x);

		double derivf = getExpFirstDerivative(x);
		std::cout<<std::setfill(' ')<<std::setw(15)<<std::setprecision(5)<<derivf;

		double firstderivOH = getFirstDevivativeOH(x, h);
		std::cout<<std::setfill(' ')<<std::setw(12)<<std::setprecision(5)<<firstderivOH;
		std::cout<<std::setfill(' ')<<std::setw(15)<<std::setprecision(5)<< fabs(firstderivOH - derivf);

		double firstderivOH2 = getFirstDerivativeOH2(x, h);
		std::cout<<std::setfill(' ')<<std::setw(11)<<std::setprecision(5)<<firstderivOH2;
		std::cout<<std::setfill(' ')<<std::setw(18)<<std::setprecision(5)<<fabs(firstderivOH2- derivf);

		double secderivf = getExpSecondDerivative(x);
		std::cout<<std::setfill(' ')<<std::setw(12)<<secderivf;

		double secondderiv = getSecondDerivativeOH2(x, h);
		std::cout<<std::setfill(' ')<<std::setw(12)<<std::setprecision(5)<<secondderiv;
		std::cout<<std::setfill(' ')<<std::setw(20)<<std::setprecision(5)<<fabs(secderivf - secondderiv);
		std::cout<<std::endl;
	}

	std::cout<<std::endl;
	std::cout<<std::endl;

	//вывод поиска оптимального h для первой производной с первым порядком точности
	x = 1.0;
	std::cout<<std::setfill(' ')<<std::setw(6)<<"h";

	h = 0.2;

	n = 6;

	for (int i = 0; i < n; ++i)
	{
		h = h / 2;
		std::cout<<std::setfill(' ')<<std::setw(15)<<h;
	}

	h = 0.2;
	std::cout<<std::endl;
	std::cout<<std::setfill(' ')<<std::setw(6)<<"f";

	for (int i = 0; i < n; ++i)
	{
		h = h / 2;
		std::cout<<std::setfill(' ')<<std::setw(15)<<getFirstDerivativeOH2(x, h);
	}

	h = 0.2;
	std::cout<<std::endl;
	std::cout<<std::setfill(' ')<<std::setw(6)<<"погрешн.";

	for (int i = 0; i < n; ++i)
	{
		h = h / 2;
		std::cout<<std::setfill(' ')<<std::setw(15)<<getExpFirstDerivative(x) - getFirstDerivativeOH2(x, h);
	}
	std::cout<<std::endl;

	//вывод значения первой производной с четвертым порядком точности и погрешности
	x = 1.0;
	std::cout<<std::setfill(' ')<<std::setw(6)<<"h";

	h = 0.1;

	std::cout<<std::setfill(' ')<<std::setw(15)<<h;

	std::cout<<std::endl;
	std::cout<<std::setfill(' ')<<std::setw(6)<<"f";


	std::cout<<std::setfill(' ')<<std::setw(15)<<getFirstDerivativeOH4(x, h);

	std::cout<<std::endl;
	std::cout<<std::setfill(' ')<<std::setw(6)<<"погрешн.";

	std::cout<<std::setfill(' ')<<std::setw(15)<<getExpFirstDerivative(x) - getFirstDerivativeOH4(x, h);
} 