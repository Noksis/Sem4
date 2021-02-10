#include "Vector2d.h"

int main() {
	// Создаем векторы
	Vector2d* First_Vec = new Vector2d;
	Vector2d* Second_Vec = new Vector2d(5,5);
	First_Vec->set_x(10);
	First_Vec->set_y(15);
	
	//Выводим векторы
	std::cout << "First vec: X = " << First_Vec->get_x() << " Y = " << First_Vec->get_y() << " \n" ;
	std::cout << "Second vec: X = " << Second_Vec->get_x() << " Y = " << Second_Vec->get_y() << " \n" ;

	//Return сумму
	std::cout <<"\n"<< "Summarize x coordinate " << sum_x(*First_Vec, *Second_Vec) << "\n";
	std::cout << "Summarize y coordinate " << sum_y(*First_Vec, *Second_Vec) << "\n";

	//Return скалярное произведение
	std::cout <<"\n"<< "Scalar mult " << First_Vec->times(*Second_Vec) << "\n";

	//Return скалярное произведение
	std::cout << "\n" << "Scalar mult * " << *First_Vec * (*Second_Vec) << "\n";

	//Умножает на 5 и выводит свои значения
	First_Vec = &First_Vec->times(5);
	std::cout <<"\n" << "Mult to 5 first vec, coord x " << First_Vec->get_x() << "\n";
	std::cout << "Mult to 5 first vec, coord y " << First_Vec->get_y() << "\n";

	//Умножает на 5 и выводит свои значения
	*First_Vec = *First_Vec * 5;
	std::cout << "\n" << "Mult to 5 first vec, coord x " << First_Vec->get_x() << "\n";
	std::cout << "Mult to 5 first vec, coord y " << First_Vec->get_y() << "\n";

	Vector2d new_vec = *First_Vec + *Second_Vec;

	//Выводим новый векторы
	std::cout << "New vec: X = " << new_vec.get_x() << " Y = " << new_vec.get_y() << " \n";
	
	//Матрицы
	Matrix A(1, 2, 3, 4);
	Matrix B(1);
	Matrix C = A + B;
	std::cout << "Determ matrix (1,2,3,4) is" << A.det() << "\n";

	std::cout << "\n \n Sum matrix:";
	C.print();

	std::cout << "\n \n Multing matrix:";
	C = A * A;
	C.print();
	return 0;
}
