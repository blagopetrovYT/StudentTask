#include <iostream>
#include <fstream>

const int FN_SIZE = 10;
struct Student {
	char* name;
	int age;
	char fn[FN_SIZE];
};

struct StudentCollection {
	Student* data;
};

void writeStudentToFile(Student& s, std::ofstream& oFile) {
	int len = strlen(s.name);
	oFile.write((const char*)&len, sizeof(len));
	oFile.write(s.name, len);
	oFile.write((const char*)&s.age, sizeof(s.age));
	oFile.write((const char*)&s.fn, sizeof(s.fn));
}

void readStudentFromFile(Student& s, std::ifstream& iFile) {
	int nameLen = 0;
	iFile.read((char*)&nameLen, sizeof(nameLen));
	s.name = new char[nameLen + 1];
	iFile.read(s.name, nameLen);
	s.name[nameLen] = '\0';

	iFile.read((char*)&s.age, sizeof(s.age));
	iFile.read((char*)&s.fn, sizeof(s.fn));
}

int main()
{
	int n;
	std::cout << "Enter number of students";
	std::cin >> n;
	{
		std::ofstream oFile("myFile.dat", std::ios::binary);
		if (!oFile.is_open()) {
			std::cout << "Error";
			return -1;
		}

		std::cout << "Write the students by name, age and fn:" << std::endl << std::endl;
		StudentCollection collection;
		collection.data = new Student[n];

		for (int i = 0; i < n; i++) {
			std::cout << "Lenght of name of student " << i + 1 << ": ";
			int len;
			std::cin >> len;
			len++; // za terminirashtata nula trqbwa da ima mqsto!!!

			collection.data[i].name = new char[len];
			std::cin >> collection.data[i].name;
			std::cin >> collection.data[i].age;
			std::cin >> collection.data[i].fn;

			writeStudentToFile(collection.data[i], oFile);
		}

		for (int i = 0; i < n; i++) {
			delete[] collection.data[i].name;
		}
		delete[] collection.data;

		oFile.close();
	}
	{
		std::ifstream iFile("myFile.dat", std::ios::binary);
		if (!iFile.is_open()) {
			std::cout << "Error";
			return -1;
		}

		StudentCollection collection;
		collection.data = new Student[n];

		for (int i = 0; i < n; i++) {
			readStudentFromFile(collection.data[i], iFile);
		}

		for (int i = 0; i < n; i++) {
			std::cout << collection.data[i].name << collection.data[i].age << collection.data[i].fn;
		}


		for (int i = 0; i < n; i++) {
			delete[] collection.data[i].name;
		}
		delete[] collection.data;

		iFile.close();
	}
}


