#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
class Student {
private:
	std::string id_student_;
	std::string surname_;
	std::string name_;
	std::string patronymic_;
	std::string class_;
	std::string age_;

	//другие пол€, которые мы можем добавить и потом удалить
	std::vector<std::string> other_field_;

	//вывод с вектора в файл
	friend void vec_student_to_file(std::vector<Student> vec);
	
public:

	Student() = default;
	Student(std::string id_student, std::string surname,std::string name,std::string patronymic,std::string class_name, std::string age):
	id_student_(id_student),surname_(surname),name_(name),patronymic_(patronymic), class_(class_name),age_(age) {}

	//все функции дружественные чтобы не писать сеттеры и геттеры, дл€ трех классов их было бы много
	//еще можно сделать одну дружественную функцию дл€ нескольких классов, что и сделано дл€ некоторых

	//считываем с файла в вектор класса
	friend std::vector<Student> from_file_student();

	friend void add_student(std::vector<Student>& vec_student);//добавить студента
	friend void add_new_field_student();  //добавить новое поле (столбец)
	friend void remove_from_file();   //удалить поле(столбец)
	friend void change_student();    //изменить какую-то €чейку таблицы
	
	friend void add_to_file();       //добавитьв файл (обща€ функци€ дл€ 3 классов)
	friend void update_all();       //обновить общую бд
	friend void average_grade();     //посчитать среднюю оценку
	friend void delete_student();    //удалить (отчислить) студента

};

void vec_student_to_file(std::vector<Student> vec) {
	std::ofstream fout;
	fout.open("Students.csv");

	for (size_t i = 0; i < vec.size(); i++) {
		fout << vec[i].id_student_ << ";" << vec[i].surname_ << ";" << vec[i].name_ << ";" << vec[i].patronymic_ << ";" << vec[i].class_ << ";" << vec[i].age_ << ";";
		for (size_t j = 0; j < vec[i].other_field_.size(); j++) {
			fout << vec[i].other_field_[j] + ";";
		}
		fout << std::endl;
	}
	fout.close();
}



std::vector<Student> from_file_student() {
	std::ifstream fin("Students.csv");   //csv файл это таблица, открываетс€ в любой ос
	if (!fin.is_open()) {
		fin.close();
		std::ofstream fout("Students.csv");
		fout << "id;surname;name;patronymic;class;age;" << std::endl; //вывод главных полей, если файл не создан
		fout.close();
		fin.open("Students.csv");
	}
	std::vector <Student> vec;
	std::string str;

	//считываем с файла в вектор
	while (!fin.eof()) {
		std::getline(fin, str);
		if (str.length() == 0) {
			break;
		}
		Student s;

		//обрезаем считанную строку, везде одинаково, поэтому удобно
		s.id_student_ = str.substr(0, str.find(';'));
		str.erase(0, str.find(';') + 1);

		s.surname_ = str.substr(0, str.find(';'));
		str.erase(0, str.find(';') + 1);

		s.name_ = str.substr(0, str.find(';'));
		str.erase(0, str.find(';') + 1);

		s.patronymic_ = str.substr(0, str.find(';'));
		str.erase(0, str.find(';') + 1);

		s.class_ = str.substr(0, str.find(';'));
		str.erase(0, str.find(';') + 1);

		s.age_ = str.substr(0, str.find(';'));
		str.erase(0, str.find(';') + 1);


		for (; str.find(';') != std::string::npos; ) {
			s.other_field_.push_back(str.substr(0, str.find(';')));
			str.erase(0, str.find(';') + 1);
		}

		vec.push_back(s);

	}

	fin.close();
	return vec;
}

void add_new_field_student() {

	std::vector<Student> vec_student = from_file_student();
	std::string new_field;
	std::cout << "Enter new_field" << std::endl;
	std::cin >> new_field;

	//добавим в вектор новых стобцов
	vec_student[0].other_field_.push_back(new_field);
	for (size_t i = 1; i < vec_student.size(); i++) {
		vec_student[i].other_field_.push_back(";");
	}

	vec_student_to_file(vec_student);
}


void change_student() {
	std::string id;
	std::string param;
	std::string new_param;

	std::cout << "Enter id" << std::endl;
	std::cin >> id;
	std::cout << "Enter name of parametr" << std::endl;
	std::cin >> param;

	std::cout << "Enter new parametr" << std::endl;
	std::cin >> new_param;

	std::vector<Student> vec_student = from_file_student();

	//поиск параметра по заданному пользователем
	for (size_t i = 0; i < vec_student.size(); i++) {
		if (id == vec_student[i].id_student_) {
			if (param == vec_student[0].surname_) {
				vec_student[i].surname_ = new_param;
			}
			if (param == vec_student[0].name_) {
				vec_student[i].name_ = new_param;
			}
			if (param == vec_student[0].patronymic_) {
				vec_student[i].patronymic_ = new_param;
			}
			if (param == vec_student[0].age_) {
				vec_student[i].age_ = new_param;
			}
			if (param == vec_student[0].class_) {
				vec_student[i].class_ = new_param;
			}
			//поиск в дополнительных столбцах
			for (size_t j = 0; j < vec_student[0].other_field_.size(); j++) {
				if (vec_student[0].other_field_[j] == param) {
					vec_student[i].other_field_[j] = new_param;
				}
			}
		}
	}
	vec_student_to_file(vec_student);

}

void add_student(std::vector<Student>& vec_student) {
	size_t count;
	std::cout << "Enter count of student" << std::endl;
	std::cin >> count;
	for (size_t i = 0; i < count; i++) {
		Student S;

		//заполнение id, если файл пустой, то id = "1". »менно "1", а не 1
		if (vec_student.size() == 1) {
			S.id_student_ = "1";
		}
		else {
			//если не пустой, то смотрим на последний id  в таблице и увеличиваем на 1
			S.id_student_ = std::to_string(stoi(vec_student[vec_student.size() - 1].id_student_) + 1);
		}

		std::cout << "\nEnter Surname" << std::endl;
		std::cin >> S.surname_;

		std::cout << "\nEnter Name" << std::endl;
		std::cin >> S.name_;

		std::cout << "\nEnter Patrnymic" << std::endl;
		std::cin >> S.patronymic_;

		std::cout << "\nEnter Age" << std::endl;
		std::cin >> S.age_;

		std::cout << "\nEnter Class" << std::endl;
		std::cin >> S.class_;

		for (size_t j = 0; j < vec_student[0].other_field_.size(); j++) {
			std::cout << "\nEnter " << vec_student[0].other_field_[j] << std::endl;
			std::string curr;
			std::cin >> curr;
			S.other_field_.push_back(curr);
		}

		vec_student.push_back(S);
	}

}

//удаление просто из вектора студентов
void delete_student() {
	std::string id;
	std::cout << "Enter id" << std::endl;
	std::cin >> id;
	std::vector<Student> vec_student = from_file_student();

	for (size_t i = 0; i < vec_student.size(); i++) {
		if (vec_student[i].id_student_ == id) {
			vec_student.erase(vec_student.begin() + i);
		}
	}
	vec_student_to_file(vec_student);

}
