#include <iostream>


using namespace std;


namespace first1
{
	class a
	{
	public:
		void printSize() {
			cout << sizeof(*this) << " byte" << endl;
		}
		
	protected:
		int data;

	};

	class b1 :public a
	{};
	class b2 :public a
	{};
	class b3 :public a
	{};

	class c1 :public b1
	{};
	class c2 :public b3
	{};

	class d : public c1, public b2, public c2
	{
	public:
		void printSize() {
			cout << sizeof(*this) << " byte" << endl;
		}
	};
}

namespace first2 {
	class Base
	{
	public:
		void printSize() {
			cout << sizeof(*this) << " byte" << endl;
		}
	protected:
		int data;

	};

	class Middle1 :public virtual Base
	{};
	class Left1 :public virtual Base
	{};
	class Right1 :public virtual Base
	{};

	class Left2 :public virtual Left1
	{};
	class Right2 :public virtual Right1
	{};

	class Middle2 : public Left2, public Middle1, public Right2
	{};
}

namespace second
{
	class Data
	{
	public:
		virtual void norma() = 0;
	};

	class Complex :public Data
	{
	private:
		double real;
		double imaginary;

	public:
		Complex(double realPart, double imaginaryPart) {
			real = realPart;
			imaginary = imaginaryPart;
		}

		void norma() override
		{
			double square = imaginary * imaginary;
			cout << "Norma: " << real + square << endl;
		}
	};

	class Vector :public Data
	{
	private:
		double vec[10];

	public:
		Vector() {
			for (int i = 0; i < 10; i++) {
				vec[i] = 0;
			}
		}
		Vector(double val) {
			for (int i = 0; i < 10; i++) {
				vec[i] = val;
			}
		}

		double& operator[](int index) {
			return vec[index];
		}
		void norma() override
		{
			cout << "Norma: \n";
			for (int i = 0; i < 10; i++) {
				cout << "Vec[" << i << "] = " << sqrt(vec[i]) << endl;
			}
		}
	};

	class Matrix :public Data
	{
	private:
		double matrix[2][2];

	public:
		Matrix() {
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 2; j++) {
					matrix[i][j] = 0;
				}
			}
		}
		Matrix(double val) {
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 2; j++) {
					matrix[i][j] = val;
				}
			}
		}

		void randInicialisation() {
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 2; j++) {
					matrix[i][j] = rand() % 100;
				}
			}
		}

		void printMat() {
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 2; j++) {
					cout << matrix[i][j] << '\t';
				}
				cout << endl;
			}
		}

		void setElement(int i_index, int j_index, double val) {
			this->matrix[i_index][j_index] = val;
		}

		void norma() override
		{
			double determinant;
			determinant = this->matrix[0][0] * this->matrix[1][1] - this->matrix[0][1] * this->matrix[1][0];
			cout << "Norma: " << determinant << endl;
		}
	};

	void getNorma(Data* obj)
	{
		obj->norma();
	}
}


/*Створити ієрархію типів, що
описують класи сутностей. Класи мають поля характерні сутності та успадковувати поля
батьківських класів. Визначити конструктори та віртуальні деструктори, перевантажити
операції введення та виведення. В похідному класі визначити виводить інформацію про
об’єкт класу, що успадковане від батьківських класів. Продумати ієрархію типів таким
чином щоб похідний клас успадковував двох батьків(множинне спадкування).
Задача 3.3. Ієрархія типів складається з сутностей: людина, батько, мати, дочка.*/
namespace third
{
	class Human
	{
	protected:
		int age;
		string name;
		double height = 166.6;
		double weith = 66.6;
		string sex;
	public:
		Human() {}
		Human(string name) {
			this->name = name;
		}
		Human(string name, int age, string sex) {
			this->name = name;
			this->age = age;
			this->sex = sex;
		}
		virtual ~Human() {
			cout << "Human died >:|\n";
		}

		void change_gender(string new_gender) {
			this->sex = new_gender;
		}
		void change_name(string new_name) {
			this->name = new_name;
		}
		void change_weith(double new_weith) {
			this->weith = new_weith;
		}
		void change_height(double new_height) {
			this->height = new_height;
		}
		void change_age(int new_age) {
			this->age = new_age;
		}
		friend istream& operator>>(istream& input, Human& obj);
		friend ostream& operator<<(ostream& output, Human& obj);

	};

	istream& operator>>(istream& input, Human& obj) {
		cout << "enter data about human\n";
		cout << "enter name: ";
		input >> obj.name;
		cout << "enter age: ";
		input >> obj.age;
		cout << "enter sex: ";
		input >> obj.sex;
		return input;
	}
	ostream& operator<<(ostream& output, Human& obj) {
		if (obj.age != NULL && obj.height != NULL && obj.weith != NULL) {
			output << "Data about human\n";
			output << "Name: " << obj.name << endl;
			output << "Age: " << obj.age << endl;
			output << "Height: " << obj.height << endl;
			output << "Weith: " << obj.weith << endl;
			output << "Sex: " << obj.sex << endl;
			return output;
		}
		else {
			output << "Error incorrect parameters";
			return output;
		}
	}


	class Mother :public virtual Human
	{
	private:
		string employment_place = "----";

	protected:
		string hobby;

	public:
		Mother() {}
		Mother(string name) :Human(name) {
			this->sex = "woman";
		}
		Mother(string name, int age) :Human(name, age, "woman") {}

		~Mother() override
		{
			cout << "Mother died\n";
		}

		virtual void setWorkspace(string employment_place) {
			this->employment_place = employment_place;
		}
		void chooseHobby(string hobby)
		{
			if (hobby != "consol input") {
				this->hobby = hobby;
			}
			else {
				cout << "enter hobby for object";
				cin >> this->hobby;
			}
		}

		void embroider() {
			cout << "I embroider\n";
		}

		friend istream& operator>>(istream& input, Mother& obj);
		friend ostream& operator<<(ostream& output, Mother& obj);
	};

	istream& operator>>(istream& input, Mother& obj) {
		cout << "enter data about mother\n";
		cout << "enter name: ";
		input >> obj.name;
		cout << "enter age: ";
		input >> obj.age;
		cout << "enter employment place: ";
		input >> obj.employment_place;
		return input;
	}
	ostream& operator<<(ostream& output, Mother& obj) {
		if (obj.age != NULL && obj.height != NULL && obj.weith != NULL) {
			output << "Data about mother\n";
			output << "Name: " << obj.name << endl;
			output << "Age: " << obj.age << endl;
			output << "Height: " << obj.height << endl;
			output << "Weith: " << obj.weith << endl;
			if (obj.employment_place != "----") {
				output << "Employment place: " << obj.employment_place << endl;
			}
			output << "Hobby" << obj.hobby << endl;
		}
		else {
			output << "Error incorrect parameters";
		}
		return output;
	}


	class Father :public virtual Human
	{
	private:
		string employment_place = "----";

	protected:
		string sport;

	public:
		Father() {}

		Father(string name) :Human(name) {
			this->sex = "man";
		}
		Father(string name, int age) :Human(name, age, "man") {}

		~Father() override
		{
			cout << "Father died\n";
		}

		virtual void setWorkspace(string employment_place) {
			this->employment_place = employment_place;
		}
		void chooseSprot(string sport)
		{
			if (sport != "consol input") {
				this->sport = sport;
			}
			else {
				cout << "enter sport for object";
				cin >> this->sport;
			}
		}

		void rideBicycle() {
			cout << "I ride a bicycle :)\n";
		}

		friend istream& operator>>(istream& input, Father& obj);
		friend ostream& operator<<(ostream& output, Father& obj);
	};

	istream& operator>>(istream& input, Father& obj) {
		cout << "enter data about father\n";
		cout << "enter name: ";
		input >> obj.name;
		cout << "enter age: ";
		input >> obj.age;
		cout << "enter employment place: ";
		input >> obj.employment_place;
		return input;
	}
	ostream& operator<<(ostream& output, Father& obj) {
		if (obj.age != NULL && obj.height != NULL && obj.weith != NULL) {
			output << "Data about father\n";
			output << "Name: " << obj.name << endl;
			output << "Age: " << obj.age << endl;
			output << "Height: " << obj.height << endl;
			output << "Weith: " << obj.weith << endl;
			if (obj.employment_place != "----") {
				output << "Employment place: " << obj.employment_place << endl;
			}
			output << "Sprot" << obj.sport << endl;
		}
		else {
			output << "Error incorrect parameters";
		}
		return output;
	}


	class Daughter :public Mother, public Father
	{
	private:
		string study_place;

	public:
		Daughter(string name) :Mother(name), Father(name) {}

		Daughter(string name, int age) {
			this->age = age;
			this->name = name;
		}

		~Daughter()override {
			cout << "Daughter married an Arab and moved to the UAE";
		}

		void setWorkspace(string study_place)override {
			this->study_place = study_place;
		}
		friend istream& operator>>(istream& input, Daughter& obj);
		friend ostream& operator<<(ostream& output, Daughter& obj);
	};

	istream& operator>>(istream& input, Daughter& obj) {
		cout << "enter data about daughter\n";
		cout << "enter name: ";
		input >> obj.name;
		cout << "enter age: ";
		input >> obj.age;
		cout << "enter study place: ";
		input >> obj.study_place;
		return input;
	}
	ostream& operator<<(ostream& output, Daughter& obj) {
		if (obj.age != NULL && obj.height != NULL && obj.weith != NULL) {
			output << "Data about daughter\n";
			output << "Name: " << obj.name << endl;
			output << "Age: " << obj.age << endl;
			output << "Height: " << obj.height << endl;
			output << "Weith: " << obj.weith << endl;
			if (obj.study_place != "----") {
				output << "Study place: " << obj.study_place << endl;
			}
			output << "Hobby: " << obj.hobby << endl;
			output << "Sprot: " << obj.sport << endl;

		}
		else {
			output << "Error incorrect parameters";
		}
		return output;
	}
}

using namespace first1;
using namespace first2;

void Task1()
{
	a a_obj;
	cout << "a size: ";
	a_obj.printSize();

	b1 b1_obj;
	cout << "b1 size: ";
	b1_obj.printSize();

	b2 b2_obj;
	cout << "b2 size: ";
	b2_obj.printSize();

	b3 b3_obj;
	cout << "b3 size: ";
	b3_obj.printSize();

	c1 c1_obj;
	cout << "c1 size: ";
	c1_obj.printSize();

	c2 c2_obj;
	cout << "c2 size: ";
	c2_obj.printSize();

	d d_obj;
	cout << "d size: ";
	d_obj.printSize();

	cout << "\n\n";

	Base base_obj;
	cout << "base size: ";
	base_obj.printSize();

	Middle1 mid1_obj;
	cout << "Middle1 size: ";
	mid1_obj.printSize();

	Left1 left1_obj;
	cout << "left1 size: ";
	left1_obj.printSize();

	Right1 right1_obj;
	cout << "Right1 size: ";
	right1_obj.printSize();

	Left2 left2_obj;
	cout << "Left2 size: ";
	left2_obj.printSize();

	Right2 right2_obj;
	cout << "Right2 size: ";
	right2_obj.printSize();

	Middle2 mid2_obj;
	cout << "Middle2 size: ";
	mid2_obj.printSize();
}


using namespace second;

void Task2()
{
	Complex complex_number(23, 4.5);
	Vector vec(9);
	Matrix mat;
	mat.randInicialisation();
	cout << "Matrix:\n";
	mat.printMat();
	cout << "norma for complex: ";
	getNorma(&complex_number);
	cout << "\nnorma for vector: ";
	getNorma(&vec);
	cout << "\nnorma for matrix: ";
	getNorma(&mat);
}


using namespace third;

void Task3()
{
	Human person("Somebody");
	cin >> person;
	cout << endl << person << endl;

	Mother mom("Kortnie", 30);
	Father dad("Kurt", 27);

	cout << "Kortnie:\n" << mom << endl;
	cout << "Kurt:\n" << dad << endl;

	Daughter dau("Frensis", 14);
	dau.setWorkspace("Happy Medium School");
	dau.chooseHobby("painting");
	dau.chooseSprot("modelling");
	cout << "Frensis:\n" << dau << endl;
	dau.embroider();
	dau.rideBicycle();
}

int main()
{
	int choise = 0;
	cout << "enter number:\n" << "1. Task1;\n" << "2. Task2;\n" << "3. Task3\n";
	cin >> choise;
	if (choise == 1) {
		Task1();
	}
	else if (choise == 2) {
		Task2();
	}
	else if (choise == 3) {
		Task3();
	}
	else
		cout << "incorect input";

	return 0;
}













// OOPLab3Tpl.cpp : Цей файл містить є шаблоном для 
// виконання лаб. роботи №6. 
// Він містинь функцію "main" з якої починається та закінчується виконання програми.
//
//
//#include <iostream>
//
//// Ваші файли загловки 
////
//#include "Lab6Example.h"
//int main()
//{
//    std::cout << " Lab #6  !\n";
//    //  Код виконання завдань
//    //  Головне меню завдань
//    //  Функції та класи можуть знаходитись в інших файлах проекту
//
//    Example();
//
//}