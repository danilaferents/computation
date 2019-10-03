#include <iostream>
#include <vector>
#include <cmath>

using matrix = std::vector<std::vector<double> >;
using coefficients = std::pair<double,double>; 

double findDeterminant(matrix _matrix) {
	return _matrix[0][0]*_matrix[1][1] - _matrix[0][1] * _matrix[1][0];
}

matrix getMinor(matrix _matrix) {

	std::vector<std::vector<double> > _minormatrix(2, std::vector<double>(2, 0));

	for (int i = 0; i < _matrix.size(); ++i)
		for (int j = 0; j < _matrix.size(); ++j)

		 	_minormatrix[(i + 1) % 2][(j + 1) % 2] = _matrix [i][j];
	return _minormatrix;
}

void printMatrix(matrix _matrix) {
	std::cout<<std::endl;
	for (int i = 0; i < _matrix.size(); i++) {
		for (int j = 0; j < _matrix.size(); j++) {
			std::cout<<_matrix[i][j]<<" ";
		}
		std::cout<<std::endl;
	}
}

matrix getMatrixAdditions(matrix _matrix) {

	_matrix = getMinor(_matrix);

	for (int i = 0; i < _matrix.size(); i++) {
		for (int j = 0; j < _matrix.size(); j++) {
			_matrix[i][j] = pow(-1, i+j) * _matrix[i][j];
		}
	}
	return _matrix;
}	

matrix transponateMatrix(matrix _matrix) {
	double temp =_matrix [0][1];
	_matrix[0][1] = _matrix [1][0];
	_matrix[1][0] = temp;

	return _matrix;
}

matrix getInverse(matrix _matrix) {
	_matrix = getMatrixAdditions(_matrix);
	_matrix = transponateMatrix(_matrix);
	double determ = findDeterminant(_matrix);
	if (determ == 0) return _matrix;
	for (int i = 0; i < _matrix.size(); i++) {
		for (int j = 0; j < _matrix.size(); j++) {
			_matrix[i][j] /= determ;
		}
	}

	return _matrix;

}

coefficients solveSystem(matrix _matrix, coefficients b) {
	double x1 = (b.first - ((b.second * _matrix[0][1])/(_matrix[1][1])))/(_matrix[0][0] - ((_matrix[1][0] * _matrix [0][1])/(_matrix[1][1])));
	double x2 = (b.first - _matrix[0][0] * x1)/ _matrix[0][1];
	return std::make_pair(x1, x2);
}

double findNormOfMatrix(matrix _matrix) {
	double norm = 0;

	for (int i = 0; i < _matrix.size(); ++i)
	{
		double suminarow = 0;
		for (int j=0; j < _matrix.size(); j++) {
			suminarow += std::fabs(_matrix[i][j]);
		}
		if (norm < suminarow) norm = suminarow;
		suminarow = 0;
	}
	return norm;
}

//Max of sum in each row 
double findCond(matrix _matrix) {
	double normofmatrix = findNormOfMatrix(_matrix);
	_matrix = getInverse(_matrix);

	double normofsecondmatrix = findNormOfMatrix(_matrix);

	return normofsecondmatrix * normofmatrix;
}	

//Max of coefficients
double findNormofvector(coefficients _vector){
	return std::max(std::fabs(_vector.first), std::fabs(_vector.second));
}

double findInfelicity(coefficients x1, coefficients x2) {
	return findNormofvector(std::make_pair(x2.first - x1.first, x2.second - x1.second))/findNormofvector(x1);
}

int main() {
	int sizeofmatrix = 2;
	std::cout<<"Size of matrix is:"<<sizeofmatrix<<std::endl;
	std::cout<<"Enter matrix please: "<<std::endl;

	std::vector<std::vector<double> > _matrix(sizeofmatrix, std::vector<double>(sizeofmatrix, 0));

	std::cout<<"Matrix:"<<std::endl;
	for (int i = 0; i < sizeofmatrix; i++) {
		for (int j = 0; j < sizeofmatrix; j++) {
			double input;
			std::cin>> input;
			_matrix[i][j] = input;
			// std::cout<<_matrix[i][j]<<" ";
		}
		std::cout<<std::endl;
	}


	std::cout<<"Determinant: "<<findDeterminant(_matrix)<<std::endl;

	coefficients b;
	std::cout<<"Enter first coefficients please: "<<std::endl;
	std::cin>>b.first>>b.second;

	coefficients solution= solveSystem(_matrix, b);

	std::cout<<"Solution of the first system: "<<std::endl<<"x1: "<<solution.first <<std::endl<<"x2: "<<solution.second<<std::endl;

	std::cout<<"Enter second coefficients: "<<std::endl;
	coefficients _b;
	std::cin>>_b.first>>_b.second;

	coefficients solution2 = solveSystem(_matrix, _b);

	std::cout<<"Solution of the second system: "<<std::endl<<"x1: "<<solution2.first <<std::endl<<"x2: "<<solution2.second<<std::endl;

	std::cout<<"Inverse matrix"<<std::endl;
	auto inversematrix = getInverse(_matrix);
	printMatrix(inversematrix);

	double cond = findCond(_matrix);

	std::cout<<"Cond: "<<cond<<std::endl;

	std::cout<<"Infelicity: "<<findInfelicity(solution, solution2)<<std::endl;

	std::cout<<"Mark <= " <<cond * (findNormofvector(std::make_pair(_b.first - b.first, _b.second - b.second)) / findNormofvector(b))<<std::endl;

}

