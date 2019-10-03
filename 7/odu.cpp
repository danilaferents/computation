#include <iostream>
#include <vector>
#include <cmath>
#include <boost/numeric/odeint.hpp>
using namespace boost::numeric::odeint;
using boost::math::constants::pi;

// Через библиотеки.
std::vector<double> y_math;
void rhs( const double x , double &dxdt , const double t )
{
    dxdt = cos(x)/(t + 1) + 0.5*x;
}

void write_cout( const double &x , const double t )
{	
	y_math.push_back(x);
    std::cout << "x: "<<t <<" y: " << x << std::endl;
}

typedef runge_kutta_dopri5< double > stepper_type;

double functionValue(double x, double y) {
	return cos(y)/(x + 1) + 0.5*y;
}	

//Улучшенный метод Эйлера
void eilerMethod(std::vector<double>& x_, int count, double h, std::vector<double>& y_h) {
	for (int i = 0; i < count; ++i)
	{
		y_h.push_back(y_h[i] + h * functionValue(x_[i] + h/2, y_h[i] + h/2*functionValue(x_[i], y_h[i])));
	}
}

//уточнение Ричардсона.
void richardson(std::vector<double>& R_m, std::vector<double> y_h, std::vector<double> y_h_2, int s, std::vector<double>& y_rev) {
	for (int i = 0; i < y_h.size(); ++i)
	{
		double res = (y_h_2[2*i] - y_h[i]) / (pow(2, s) - 1);
		R_m.push_back(res);
		y_rev.push_back(y_h_2[2*i] + R_m[i]);
	}

}
 //Метод Рунге-Кутты 4-го порядка 
void rungekutt(std::vector<double> x_h, std::vector<double>& y_RK, int count, double h) {
	for (int i = 0; i < count; ++i)
	{	
		double k1 = h * functionValue(x_h[i], y_RK[i]);
		double k2 = h * functionValue(x_h[i] + h/2, y_RK[i] + k1/2);
		double k3 = h * functionValue(x_h[i] + h/2, y_RK[i] + k2/2);
		double k4 = h * functionValue(x_h[i] + h, y_RK[i] + k3);
		double res = y_RK[i] + 1.0/6 * (k1 + 2 * k2 + 2 * k3 + k4);
		y_RK.push_back(res);
	}
}
//Метод Адамса экстраполяционных
void adamsMethod(std::vector<double> x_h, std::vector<double>& y_a, int count, double h, std::vector<double>& q) {
	// std::cout<<"JJJJJ"<<y_a[0];
	for (int i = 0; i < count; ++i)
	{
		y_a.push_back(y_a[i] + 1.0/720 * (1901 * q[i + 4] - 2774 * q[i + 3] +2616 * q[i + 2] - 1274 * q[i + 1] + 251 * q[i]));
		q.push_back(h * functionValue(x_h[i + 1], y_a[i + 1]));
	}
}

void adamsMethodIn(std::vector<double>& y_a, int count, double h, std::vector<double>& q) {
	// std::cout<<"JJJJJ"<<y_a[0];
	for (int i = 0; i < count; ++i)
	{
		y_a.push_back(y_a[i] + 1.0/720 * (251 * q[i + 4] + 646 * q[i + 3] - 264 * q[i + 2] + 106 * q[i + 1] - 19 * q[i]));
		// std::cout<<y_a[i]<<" "<<q[i + 4]<<" "<<q[i + 3]<<" "<<q[i + 2]<<" "<<q[i + 1]<<" "<<q[i]<<std::endl;
	}
}
int main() {
	std::cout<< "Enter step and line segment: "<<std::endl;
	double h = 0.0, a = 0.0, b = 0.0;
	// std::cin>>h>>a>>b;
	h = 0.05;
	a = 0;
	b = 0.5;
	int count = (b - a)/h;
	//Через библиотеки.
	std::cout<< "Exact value using libraries: "<<std::endl;
	double x = 0.0;    
    integrate_n_steps( make_controlled( 1E-12 , 1E-12 , stepper_type() ) ,
                        rhs , x , 0.0 , 0.05 ,  count, write_cout );

    //Улучшенный метод Эйлера.
    std::vector<double> y_h, y_h_2, y_rev;
    std::cout<<std::endl<<std::endl<<std::endl;
    std::cout<< "Update Eiler Method: "<<std::endl;
    y_h.push_back(0);
    y_h_2.push_back(0);

    std::vector<double> x_h, x_h_2, r_m;
    std::cout<<std::setfill(' ')<<std::setw(15)<< "h: "<<std::endl;
    //для h
    for (int i = 0; i <= count; ++i)
    {
    	x_h.push_back(a + i * h);
    }

    eilerMethod(x_h, count, h, y_h);
    for (int i = 0; i <= count; ++i)
    {
    	std::cout<<"x_h: "<<x_h[i]<<" y_h: "<<y_h[i]<<std::endl;
    }
    std::cout<<std::endl<<std::endl<<std::endl;

    //для h/2
    count = 2*(b - a)/h;
    std::cout<<std::setfill(' ')<<std::setw(15)<< "h/2: "<<std::endl;
    for (int i = 0; i <= count; ++i)
    {
    	x_h_2.push_back(a + i * h/2);
    }
    eilerMethod(x_h_2, count, h/2, y_h_2);

    for (int i = 0; i <= count; ++i)
    {
    	std::cout<<"x_h/2: "<<x_h_2[i]<<" y_h/2: "<<y_h_2[i]<<std::endl;
    }
    std::cout<<std::endl<<std::endl<<std::endl;

    //уточнение
    std::cout<<std::setfill(' ')<<std::setw(15)<< "y_rev: "<<std::endl;
    int s = 2;
    richardson(r_m, y_h, y_h_2, s, y_rev);
    for (int i = 0; i <= count/2; ++i)
    {
    	std::cout<<"y_rev: "<<y_rev[i]<<std::endl;	
    }
	std::cout<<std::endl<<std::endl<<std::endl;
	std::cout<<std::setfill(' ')<<std::setw(50)<<"Infelicity: "<<std::endl;
	std::cout<<std::setfill(' ')<<std::setw(20)<<"y_math";
	std::cout<<std::setfill(' ')<<std::setw(20)<<"y^h";
	std::cout<<std::setfill(' ')<<std::setw(20)<<"y^h/2";
	std::cout<<std::setfill(' ')<<std::setw(20)<<"y_rev";
	std::cout<<std::setfill(' ')<<std::setw(20)<<"y_rev - y_math"<<std::endl;

	for (int i = 0; i <= count/2; ++i)
	{
		std::cout<<std::setfill(' ')<<std::setw(20)<<y_math[i];
		std::cout<<std::setfill(' ')<<std::setw(20)<<y_h[i];
		std::cout<<std::setfill(' ')<<std::setw(20)<<y_h_2[2*i];
		std::cout<<std::setfill(' ')<<std::setw(20)<<y_rev[i];
		std::cout<<std::setfill(' ')<<std::setw(20)<<fabs(y_rev[i] - y_math[i])<<std::endl;
		// std::cout<<"y_math: "<<y_math[i + 4]<<" ex: "<<y_ad_in[i]<<std::endl;

	}
	std::cout<<std::endl<<std::endl<<std::endl;
    //Метод Рунге-Кутты 4-го порядка 
    std::vector<double> y_RK;
    y_RK.push_back(0);
    std::cout<< "Runge Kutte Method: "<<std::endl;
    count = (b - a)/h;
    rungekutt(x_h, y_RK, count, h);
    for (int i = 0; i <= count; ++i)
    {
    	std::cout<<"x_h: "<<x_h[i]<<" y_RK: "<<y_RK[i]<<std::endl;
    }
    std::cout<<std::endl<<std::endl<<std::endl;
    //Экстраполяционный метод Адамса
    std::cout<< "Extrapolation Adams Method: "<<std::endl;
    a = 4 * h;
	count = (b - a)/h + 1;
	std::vector<double> x_a, y_ad_ex;

	for (int i = 0; i <= count; ++i)
	{
		x_a.push_back(a + i*h);
	}

	//Вычисление k начальных точек методом Рунге-Кутты
	//k = 4
	std::vector<double> yhelp,xhelp = {0, 0.05, 0.1, 0.15,0.2},q;
	yhelp.push_back(0);
	rungekutt(xhelp,yhelp, 5,h);
	y_ad_ex.push_back(yhelp[4]);
	// std::cout<<"."<<yhelp[4]<<std::endl;
	for (int i = 0; i < 5; ++i)
	{
		q.push_back(h * functionValue(xhelp[i], yhelp[i]));
		// std::cout<<q[i]<<std::endl;
	}
	adamsMethod(x_a, y_ad_ex, count, h, q);
	for (int i = 0; i <= count; ++i)
	{
		std::cout<<"x: "<<x_a[i]<<" y_Ad_ex: "<<y_ad_ex[i]<<std::endl;
	}
    std::cout<<std::endl<<std::endl<<std::endl;

    //Интерполяционный метод Адамса
    std::cout<< "Interpolation Adams Method: "<<std::endl;
	std::vector<double> y_ad_in;


	// //Вычисление k начальных точек методом Рунге-Кутты
	std::vector<double> yhelp2,xhelp2 ,q2;
	xhelp2.push_back(0);
	xhelp2.push_back(0.05);
	xhelp2.push_back(0.1);
	xhelp2.push_back(0.15);
	for (int i = 0; i <= count; ++i)
	{
		xhelp2.push_back(a + h * i);
	}
	yhelp2.push_back(0);
	rungekutt(xhelp2,yhelp2, count + 4,h);
	y_ad_in.push_back(yhelp[4]);
	for (int i = 0; i <= count + 4; ++i)
	{
		q.push_back(h * functionValue(xhelp[i], yhelp[i]));
		// std::cout<<q[i]<<std::endl;
	}

	// for (int i = 0; i <= count + 4; ++i)
	// {
	// 	std::cout<<"x: "<<xhelp2[i]<<" y: "<<yhelp2[i]<<" q: "<<q[i]<<std::endl;;
	// }
	adamsMethodIn(y_ad_in, count, h, q);
	for (int i = 0; i <= count; ++i)
	{
		std::cout<<"x: "<<x_a[i]<<" y_Ad_in: "<<y_ad_in[i]<<std::endl;
	}
    std::cout<<std::endl<<std::endl<<std::endl;
	//погрешность
	std::cout<<"Infelicity: "<<std::endl;
	std::cout<<std::setfill(' ')<<std::setw(20)<<"y_math − y_RK";
	std::cout<<std::setfill(' ')<<std::setw(30)<<"y_math − y_Ad_ex";
	std::cout<<std::setfill(' ')<<std::setw(30)<<"y_math − y_Ad_in"<<std::endl;

	for (int i = 0; i <= count; ++i)
	{
		std::cout<<std::setfill(' ')<<std::setw(20)<<fabs(y_math[i] - y_RK[i]);
		std::cout<<std::setfill(' ')<<std::setw(25)<<fabs(y_math[i + 4] - y_ad_ex[i]);
		std::cout<<std::setfill(' ')<<std::setw(25)<<fabs(y_math[i + 4] - y_ad_in[i])<<std::endl;
		// std::cout<<"y_math: "<<y_math[i + 4]<<" ex: "<<y_ad_in[i]<<std::endl;

	}
}