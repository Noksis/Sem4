#pragma once
#include <stdio.h>
#include <iostream>
double sum(double x, double y) {
	return x + y;
}

class Vector2d {

	double x, y;

public:
	Vector2d(int x_val, int y_val) {
		x = x_val;
		y = y_val;
	}
	Vector2d(double x_val, double y_val) {
		x = x_val;
		y = y_val;
	}
	Vector2d() {
		x = 0;
		y = 0;
	}
	double get_x() {
		return x;
	}
	double get_y() {
		return y;
	}
	void set_x(double value) {
		x = value;
	}
	void set_y(double value) {
		y = value;
	}

	Vector2d times(double value) {
		Vector2d new_vec;
		new_vec.set_x(this->get_x() * value);
		new_vec.set_y(this->get_y() * value);
		return new_vec;
	}

	double times(Vector2d A) {
		return x * A.get_x() + y * A.get_y();
	}

	Vector2d operator * (double N) {
		Vector2d* vec = new Vector2d(this->x * N, this->y * N);
		return *vec;
	}

	Vector2d operator + (Vector2d vec) {
		Vector2d* new_vec = new Vector2d(this->x + vec.x, this->y + vec.y);
		return *new_vec;
	}

	Vector2d operator - (Vector2d vec) {
		Vector2d* new_vec = new Vector2d(this->x - vec.x, this->y  - vec.y);
		return *new_vec;
	}

	double operator * (Vector2d vec) {
		double value = this->x * vec.x +  this->y * vec.y;
		return value;
	}



};

class Matrix {

public:

	double val[4] = { 0 };

	Matrix(int x1, int x2, int x3, int x4) {
		val[0] = x1;
		val[1] = x2;
		val[2] = x3;
		val[3] = x4;
	}

	Matrix(int x1) {
		for (int i = 0; i < 4; i++)
			val[i] = x1;
	}

	Matrix() {
	}

	Matrix operator * (Matrix A) {
		Matrix* C = new Matrix();
		C->val[0] = this->val[0] * A.val[0] + this->val[1] * A.val[2];
		C->val[1] = this->val[0] * A.val[1] + this->val[1] * A.val[3];
		C->val[2] = this->val[2] * A.val[0] + this->val[3] * A.val[2];
		C->val[3] = this->val[2] * A.val[1] + this->val[3] * A.val[3];
		return *C;
	}

	Matrix operator + (Matrix A) {
		Matrix* C = new Matrix();
		for (int i = 0; i < 4; i++) {
			C->val[i] = this->val[i] + A.val[i];
		}
		return *C;
	}

	Matrix operator - (Matrix A) {
		Matrix* C = new Matrix();
		for (int i = 0; i < 4; i++) {
			C->val[i] = this->val[i] - A.val[i];
		}
		return *C;
	}

	double det() {
		return this->val[0] * this->val[3] - this->val[1] * this->val[2];
	}

	void print() {
		for (int i = 0; i < 4; i++)
			std::cout << "\n Elm ["<< i <<"] is "<< this->val[i];
	}
};

double sum_x(Vector2d First, Vector2d Second) {
	double value = First.get_x() + Second.get_x();
	return value;
}

double sum_y(Vector2d First, Vector2d Second) {
	double value = First.get_y() + Second.get_y();
	return value;
}
