#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <iomanip>

void printString(std::string printingstring) {
	std::cout<<printingstring<<std::endl;
}

//Значение косинуса
double findValue(double x) {
	return cos(x);
	// return 2* pow(x, 3) - 2* pow(x, 2) + 3*x - 1;
}

//Значение синуса
double findValueSin(double x) {
	return sin(x);
}

void printTaps(int k) {
	for (int i = 0; i < k; ++i)
	{
		std::cout<<"               ";
	}
}

//Вичисление N k-ого
double findN(double N_k_1, double t, int k ) {
	return N_k_1 * (t - k + 1)/k;
}

//Вычисление P k-ого
double findPol(std::vector<double> vN_k, std::vector<double> vd_k, int count) {
	double result = 0.0;
	for (int i = 0; i <= count; ++i)
	{
		result+= vN_k[i]*vd_k[i];
	}
	return result;
}

double makeD(double x) {
	x*=10000;
	x = nearbyint(x);
	x/=10000;
	return x;
}
int main() {

	// std::setprecision(6);
	 // std::cout.precision(6);
	 // printString("Enter a and b");

	//Вывод таблички со значениями и конечными разностями.
	 double a=0.5,b=1.5;
	 // std::cin>>a>>b;
	 printString("x    f(x)");
	 int n = (b - a)/(0.1);

	 std::vector<double> knots, values;

	 for (int i = 0; i < n+1; ++i)
	 {
	 	double x = a + i*0.1;
	 	knots.push_back(x);
	 	double y = findValue(x);
	 	values.push_back(y);
	 	std::cout<<x<<"  "<<y<<std::endl;
	 }

	 std::vector<double> d1, d2, d3, d4;

	 for (int i = 0; i < n; ++i)
	 {
	 	d1.push_back(values[i + 1] - values[i]);
	 	// std::cout<<d1[i]<<std::endl;
	 	if (i > 0 && i < n) {
	 		d2.push_back(d1[i] - d1[i - 1]);
	 		// std::cout<<d2[i]<<std::endl;
	 		if (i > 1 && i < n) {
	 			d3.push_back(d2[i - 1] - d2[i - 2]);
	 			// std::cout<<d3[i]<<std::endl;
	 			if(i > 2 && i < n) {
	 				d4.push_back(d3[i -2] - d3[i - 3]);
	 			}
	 		}
	 	}
	 }

	 // for (int i = 0; i < n; ++i)
	 // {
	 // 	std::cout<<d1[i]<<std::endl;
	 // }

	 // std::cout<<"-------"<<std::endl;

	 // for (int i = 0; i < n-1; ++i)
	 // {
	 // 	std::cout<<d2[i]<<std::endl;
	 // }

	 // std::cout<<"-------"<<std::endl;

	 //  for (int i = 0; i < n-2; ++i)
	 // {
	 // 	std::cout<<d3[i]<<std::endl;
	 // }

	 // std::cout<<"-------"<<std::endl;
	 printString(" x                 y             dy          d2y           d3y           d4y");

	 for (int i = 0; i < n + 1 + n; ++i)
	 {
	 	if (!(i%2)) {
	 		if (knots[i/2] == 1) std::cout<<"  ";
	 		// if (values[i/2] == 0.0) std::cout<<"        gg    ";
	 		std::cout<<knots[i/2]<<"               "<<values[i/2];
	 	}

	 	if (i%2) {
	 		printTaps(2);
	 		std::cout<<d1[(i-1)/2]<<" ";
	 	}

	 	if (!(i%2) && i> 1 && i < 2*n) {
 			printTaps(1);
 			std::cout<<d2[(i-2)/2]<<" ";
	 	}

	 	if ((i%2) && i> 2 && i < 2*n - 1) {
	 		printTaps(1);
	 		std::cout<<d3[(i - 3)/2]<<" ";
	 	}

	 	if (!(i%2) && i> 3 && i < 2*n - 2) {
	 		printTaps(1);
	 		std::cout<<d4[(i - 4)/2]<<" ";
	 	}
	 	std::cout<<std::endl;
	 }

	 //Сама интерполяция и оформление в табличку. 
	 printString("Table for x_1");
	 printString("k      0       1           2           3              4");
	 std::cout<<"dky_0  "<<findValue(a)<<"  "<<d1[0]<<"  "<<d2[0]<<"  "<<d3[0]<<"  "<<d4[0]<<std::endl;
	 //добавления нужных конечных разностей в массив
	 std::vector<double>  vd_k;
	 vd_k.push_back(findValue(a));
	 vd_k.push_back(d1[0]);
	 vd_k.push_back(d2[0]);
	 vd_k.push_back(d3[0]);
	 vd_k.push_back(d4[0]);

	 //Вычисление N и добавление в массив 
	 double x_1 = 0.52;
	 double N_0 = 1, N_1 = (x_1 - a)/0.1;
	 double N_2 = findN(N_1, N_1, 2), N_3 = findN(N_2, N_1, 3), N_4 = findN(N_3, N_1, 4);

	 std::vector<double> vN_k;
	 vN_k.push_back(N_0);
	 vN_k.push_back(N_1);
	 vN_k.push_back(N_2);
	 vN_k.push_back(N_3);
	 vN_k.push_back(N_4);


	 std::cout<<"N_k    "<<N_0<<"  "<<N_1<<"        "<<N_2<<"        "<<N_3<<"      "<<N_4<<std::endl;

	 std::cout<<"N_k * dk    "<<N_0 * vd_k[0]<<"  "<<N_1*d1[0]<<"        "<<N_2*d2[0]<<"        "<<N_3*d3[0]<<"      "<<N_4*d4[0]<<std::endl;

	 // double rez = 

	 std::cout<<"P_k      ";
	 std::vector<double> pol;
	 for (int i = 0; i < 5; i++) {
	 	double res = findPol(vN_k, vd_k, i);
	 	pol.push_back(res); //Вычисление значения полинома
	 	std::cout<<res<<"    ";
	 }
	 std::cout<<std::endl;
	 std::cout<<"F_k - P_k  ";
	 for (int i = 0; i < 5; ++i)
	 {
	 	std::cout<<findValue(x_1) - pol[i]<<"   ";  //Вывод погрешности
	 }
	 std::cout<<std::endl;
	 std::vector<double> M_k;
	 M_k.push_back(0);
	 M_k.push_back(findValueSin(a)); //M_1
	 M_k.push_back(findValue(a));   //M_2
	 M_k.push_back(findValueSin(a+0.2));  //M_3
	 M_k.push_back(findValue(a));  //M_4
	 M_k.push_back(findValueSin(a+0.4));  //M_5

	 std::cout<<"R_k<=   ";

	 for (int i = 0; i < 5; ++i)
	 {
	 	std::cout<< M_k[i+1]* fabs(vN_k[i+1])*pow(0.1, i+1)<<"  "; //вывод оценки погрешности 
	 }

	 std::cout<<std::endl;
}