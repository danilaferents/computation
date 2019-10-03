#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

//поиск значения всей функции 
double functionValue(double x) {
	return exp(x) / cbrt(x);
}

//поиск значения функции без веса
double funcValue(double x) {
	return exp(x);
}

//Формула средних треугольников  
double quadratureFormuleOfRightRectangles(double a, double b, int k) {
	double result = 0.0;
	double h = (b - a)/k;
	for (int i = 1; i <= k; ++i)
	{
		result += functionValue(a + h/2 +  (i - 1) * h);
		// std::cout<<" "<<a + h/2 +  (i - 1) * h<<" "<<functionValue(a + h/2 +  (i - 1) * h)<<std::endl;
	}
	return h * result;
}

//Точное значение интеграла 
double valueOfIntegaral() {
	//посчитал в вольфрам
	return 2.34359;
}

//Метод Гаусса
double Gauss(double a, double b) {
	double result = 0.0;
	result += functionValue((a + b + (b - a) * (1/ cbrt(3))) / 2);
	result += functionValue((a + b + (b - a) * (-1/ cbrt(3))) / 2);
	return result * (b - a)/2;
}

//Детерминант матрицы
double det(double x1, double x2, double x3, double x4) {
	return (x1 * x4) - (x3 * x2);
}

//Решение кв. уравнения 
std::pair<double, double> solvesystem(double a_1, double a_2) {
	double x_1 = (-a_1 + sqrt(pow(a_1, 2) - 4*a_2))/2;
	double x_2 = (-a_1 - sqrt(pow(a_1, 2) - 4*a_2))/2;

	return std::make_pair(x_1, x_2);
}

int main() {
	double a = 0.0, b = 0.0;
	std::cout<<"Enter line segment of integration."<<std::endl;
	// std::cin>>a>>b;
	std::cout<<"1.Exact value of integral: "<<valueOfIntegaral()<<std::endl<<std::endl<<std::endl;
	a = 0.0;
	b = 1.0;
	std::cout<<"2.Quadrature formule of right rectangles: "<<std::endl;
	double qforr = quadratureFormuleOfRightRectangles(a, b, 3);
	std::cout<<"Integral: "<<qforr<<std::endl;
	std::cout<<"Infelicity: "<< valueOfIntegaral() - qforr<<std::endl<<std::endl<<std::endl;


	double x1 = 1.0/6, x2 = 1.0/2, x3 = 5.0/6;
	std::cout<<"3.Int. formule with three knots: "<<std::endl;
	//посчитал на листике 
	double Aa_1 = 0.9, Aa_2 = 0.15, Aa_3 = 0.45;
	double Integr_3 = Aa_1 * funcValue(x1) + Aa_2 * funcValue(x2) +  Aa_3 * funcValue(x3);
	std::cout<<"Integral: "<<Integr_3<<std::endl;
	std::cout<<"Infelicity: "<<valueOfIntegaral() - Integr_3<<std::endl<<std::endl<<std::endl;


	std::cout<<"4.Gauss formule with two knots: "<<std::endl;
	double gauss = Gauss(a, b);
	std::cout<<"Integral: "<<gauss<<std::endl;
	std::cout<<"Infelicity: "<<valueOfIntegaral() - gauss<<std::endl<<std::endl<<std::endl;


	std::cout<<"5.Just Gauss formule with two knots: "<<std::endl;
	double m_0 = 3.0/2, m_1 = 3.0/5, m_2 = 3.0/8, m_3 = 3.0/11;
	std::cout<<"m_0: "<<m_0<<" m_1: "<<m_1<<" m_2: "<<m_2<<" m_3: "<<m_3<<std::endl;
	double a_1 = det(- m_2, m_0, - m_3, m_1)/ det(m_1, m_0, m_2, m_1);
	double a_2 = det(m_1, - m_2, m_2, - m_3)/ det(m_1, m_0, m_2, m_1);

	std::cout<<"a_1: "<<a_1<<" a_2: "<<a_2<<std::endl;

	std::pair<double, double> x = solvesystem(a_1, a_2);
	std::cout<<"x_1: "<<x.first<<" x_2: "<<x.second<<std::endl;

	double A_1 = (m_1 - x.second * m_0) / (x.first - x.second);
	double A_2 = (m_1 - x.first * m_0) / (x.second - x.first);

	std::cout<<"A_1: "<<A_1<<" A_2: "<<A_2<<std::endl<<std::endl<<std::endl;

	double Integr = funcValue(x.first) * A_1 + funcValue(x.second) * A_2;
	std::cout<<"Integral: "<<Integr<<std::endl; 
	std::cout<<"Infelicity: "<<valueOfIntegaral() - Integr<<std::endl;

}