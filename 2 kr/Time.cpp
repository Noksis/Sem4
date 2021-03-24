#include <math.h>
#include <iostream>
#include <vector>
#include <string.h>

// 1 класс времени
class Time {

protected:
	int hour;
	int min;
	virtual void reduce();

public:
	Time();
	Time(int a, int b);

	void set_h(int A);
	void set_m(int A);

	int get_h(void);
	int get_m(void);

	friend Time operator + (Time A, Time B);
	friend Time operator - (Time A, Time B);
}; 


// Конструкторы
Time::Time() {
	hour = 0;
	min = 0;
}

Time::Time(int a, int b) {
	hour = a;
	min = b;
}


// Сокращение минут
void Time::reduce() {

	if (min >= 60) {
		min = min - 60;
		hour += 1;
	}

	else if (min < 0) {
		min = 60 + min;
		hour -= 1;
	}

};


// Гетеры и сетеры класса
void Time::set_h(int A) {
	hour = A;
}

void Time::set_m(int A) {
	min = A;
}

int Time::get_h (void) {
	return hour;
}

int Time::get_m(void) {
	return min;
}

// Дружественные операторы
Time operator+ (Time A, Time B) {
	Time C = *new(Time);
	C.hour = A.hour + B.hour;
	C.min = A.min + B.min;
	C.reduce();

	return C;
}

Time operator- (Time A, Time B) {
	Time C = *new (Time);
	C.hour = A.hour - B.hour;
	C.min = A.min - B.min;
	C.reduce();
	
	return C;
}


// 2 Класс времени
class Time2: public Time {
	int sec;
	void reduce();

public:
	Time2();
	Time2(int A, int B, int C);
	Time2(int A, int B);

	int get_s();
	void set_s(int A);

	friend Time2 operator+ (Time2 A, Time2 B);
	friend Time2 operator- (Time2 A, Time2 B);

};

// Сокращение секунд
void Time2::reduce() {

	if (sec >= 60) {
		sec = sec - 60;
		set_m(get_m() + 1); // Сделал публичный класс после написания этой части кода
	}

	else if (sec < 0) {
		sec = 60 + sec;
		set_m(get_m() - 1); // Аналогично
	}
}

// Конструкторы
Time2::Time2() {
	hour = 0;
	min = 0;
	sec = 0;
}

Time2::Time2(int A, int B, int S) {
	hour = A;
	min = B;
	sec = S;
}

Time2::Time2(int A, int B) {
	hour = A;
	min = B;
	sec = 0;
}


// Гетеры и сеттеры
int Time2::get_s() {
	return sec;
}

void Time2::set_s(int A) {
	sec = A;
}


//Дружественные операторы
Time2 operator+ (Time2 A, Time2 B) {
	Time2 C = *new (Time2);

	C.hour = A.hour + B.hour;


	C.min = A.min + B.min;
	C.Time::reduce();

	C.sec = A.sec + B.sec;
	C.reduce();


	return C;
}

Time2 operator- (Time2 A, Time2 B) {
	Time2 C = *new(Time2);

	C.hour = A.hour - B.hour;

	C.min = A.min - B.min;
	C.Time::reduce();

	C.sec = A.sec - B.sec;
	C.reduce();

	return C;
}

// Класс урока
template <typename T>
class Lesson {
	T time;

public:
	//Lesson();
	//Lesson(int H, int M, int S);
	//Lesson(int H, int M);
	//Lesson(double A);
	Lesson(T);

	T get();
	void set(T);
	
	std::vector <std::string> Names;

	// Добавить нового участника
	int Add_man(std::string A);

	// Обработать ошибку добавления
	int check_add(int A);
	
	Lesson<T> operator+ (T t1);
	Lesson<T> operator- (T t1);
};

template <typename T>
Lesson<T> Lesson<T>::operator+ (T t1) {
	Lesson<T> L0(t1 + time);
	return L0;
}

template <typename T>
Lesson<T> Lesson<T>::operator- (T t1) {
	Lesson<T> L0(t1 - time);
	return L0;
}

template <typename T>
Lesson<T>::Lesson(T t1) {
	time = t1;
}

/* (Возможно это не нужно!)
// Конструкторы для разных типов
Lesson<Time>::Lesson() {
	Time time;
}

Lesson<Time2>::Lesson() {
	Time2 time;
}

Lesson<double>::Lesson() {
	time = 0;
}


Lesson<Time>::Lesson(int A, int B) {
	Time time;

	time.set_h(A);
	time.set_m(B);
}

Lesson<Time2>::Lesson(int A, int B, int C) {
	Time2 time;

	time.set_h(A);
	time.set_m(B);
	time.set_s(C);
}

Lesson<double>::Lesson(double A) {
	time = A;
}
*/

// Геттеры и сеттеры
template <typename T>
T Lesson<T>::get() {
	return time;
}

template <typename T>
void Lesson<T>::set(T A) {
	time = A;
}

// Код ошибок: -1 - значит превышена длина имени, 0 если все в порядке
template <typename U>
int Lesson<U>::Add_man(std::string name) {
	if (name.size() > 20) {
		return -1;
	}

	Names.insert(name);
	return 0;
}

// Вызываете check_add(Add_man(name)) и обрабатывается ошибка. Иначе ошибка не обработается.
template<typename U>
int Lesson<U>::check_add (int A) {
	if (A == 0)
		std::cout << "All is okey!";
	else if (A == -1)
		std::cout << "Your string is too much!";
}



// Собственно сам мейн
int main() {
	Time2 T(10, 20, 15);
	Time2 T1(20, 50, 55);
	Lesson<Time2> L1(T);
	L1 = L1 + T1;
	std::cout << "First try: Time2" << "\n";
	std::cout << L1.get().get_h() << "\n";
	std::cout << L1.get().get_m() << "\n";
	std::cout << L1.get().get_s() << "\n";

	Time T2(15, 50);
	Time T3(12, 15);
	Lesson<Time> L2(T2);
	L2 = L2 + T2;

	std::cout << "Second try: Time" << "\n";
	std::cout << L2.get().get_h() << "\n";
	std::cout << L2.get().get_m() << "\n";

	Lesson<double> L3(115.25);
	L3 = L3 + 15.37;

	std::cout << "Last try: double time" << "\n";
	std::cout << L3.get() << "\n";





	return 0;
}
