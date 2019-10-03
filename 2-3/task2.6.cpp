#include <iostream>
#include <vector>
#include <cmath>
#include <string>
void printString(std::string printingstring) {
	std::cout<<printingstring<<std::endl;
}

//Функция для выполнения первого задания, считающая точное значение.
double findWithInverse(double y) {
	return asin(y);
}

//Функция для поиска значения ради интерполяции. 
double findValue(double x) {
	return sin(x);
}

//Многочлен лагранжа

double lagrange(std::vector<double> x, std::vector<double> y, short n, double _x) {

	double result = 0.0;

	for (short i = 0; i < n; i++) {
		double P = 1.0;
		for (short j = 0; j < n; j++) {
			if (j != i) 
				P *= (_x - x[j]) / (x[i] - x[j]);
		}
		result += P * y[i];
	}

	return result;
	// return cos(_x) - _x + 1;
}

//Следующее x для метода секущих. 
double getNextX(double x_k, double x_k_1, double fx_k, double fx_k_1) {
	double fraction = fx_k / (fx_k - fx_k_1);
	return x_k - fraction*(x_k - x_k_1);
}

//Метод секущих
double findValueOfEquation(double x_0, double x_1, double eps, const std::vector<double> x, const std::vector<double> y, short n, double y_0) {

	int iter = 0;
	double f_old = lagrange(x,y,n,x_0) - y_0;
	double f_new = lagrange(x,y,n,x_1) - y_0;
	double newx = x_1, oldx = x_0;
	do {
		// std::cout<<"oldx: "<<oldx<<"newx: "<<newx<< "fold: "<<f_old<<"f_new: "<<(fabs(f_new))<<"  "<<(fabs(f_new) < eps)<<std::endl;
		double temp = newx;
		newx = getNextX(newx, oldx, f_new, f_old);
		oldx = temp;
		f_old = f_new;
		f_new = lagrange(x,y,n,newx) - y_0;
		iter++;
		// std::cout<<"oldx: "<<oldx<<"newx: "<<newx<< "fold: "<<f_old<<"f_new: "<<(fabs(f_new))<<"  "<<(fabs(f_new) < eps)<<std::endl;
		} while ((fabs(f_new) >= eps) && iter < 20000);
		// printString("Number of Iterations");
		// std::cout<<iter<<std::endl;
	return newx;
}

int main() {
	//Вычисление точного значения:
	printString("My function is: sin(x).");
	printString("First task: ");
	printString("Enter y: ");
	double y = 0;
	std::cin>>y; //ввод значение функции 
	double expx = findWithInverse(y); //точное значение через обратную функцию
	std::cout<<"x* = "<<expx<<std::endl;

	//Надо ввести точность для метода секущих. 
	double eps = 0.0;
	printString("Enter eps: ");
	std::cin>>eps;
	//Надо ввести количество узлов
	printString("Enter quantity of knots: ");
	int quantity = 0;
	std::cin >> quantity;
	//ввод узлов 
	std::vector<double> knots, values;
	printString("Enter  knots: ");
	for (int i = 0; i < quantity; ++i)
	{
		double help;
		std::cin>>help; 
		knots.push_back(help);
		values.push_back(findValue(help));
	}

	//Надо ввести значение функции
	printString("Enter y_0: ");
	double y_0 = 0.0;
	std::cin>>y_0;

	//Подсчет х методом секущих
	std::cout<<"x_iter: "<< findValueOfEquation(-0.5, -0.6, eps, knots, values, quantity, y_0)<<std::endl;
	// std::cout<<lagrange(knots,values,quantity,-0.4);//<<"  "<<lagrange(knots,values,quantity,-0.6)<<std::endl;

	//Смена узлов и значения функции и подсчет таблички Лагранжем
	int m = quantity;
	// std::cin>>m;

	std::vector<double> x_m;

	for (int i = 0; i < m; ++i)
	{
		x_m.push_back(lagrange(values, knots, i, y_0));
		// std::cout<<x_m[i]<<std::endl;
	}
	std::cout<<"m, x_m, x_m - x_m_1, x_m - x*"<<std::endl;
	std::cout<<0<<" "<<x_m[0]<<"---"<<(x_m[0] - expx)<<std::endl;
	for (int i = 1; i < m; ++i)
	{
		std::cout<<i<<" "<<x_m[i]<<" "<<(x_m[i] - x_m[i-1])<<" "<<(x_m[i] - expx)<<std::endl;
	}
}