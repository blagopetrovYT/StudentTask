#include <iostream>
#include <fstream>
const int MAX_SIZE = 1024;
const int FIFTH_NUMBER_OF_FN = 4; 

enum class Major {
    Informatics = 4,
    Software = 6,
    ComputerScience = 8
};

struct Student {
    char FirstName[MAX_SIZE];
    char SecondName[MAX_SIZE];
    char EmailAddress[MAX_SIZE];
    char FN[MAX_SIZE];

    Major major;
};

struct StudentCollection {
    Student* data;
};

int getStudentsCount(std::ifstream& file) {
    int count = 0;
    char buff[MAX_SIZE];

    while (!file.eof()) {
        file.getline(buff, MAX_SIZE);
        count++;
    }

    file.seekg(0, std::ios::beg); // tova trqbwa da mi se obqsni!!!
    return count - 1; // tova sushto 

}

void parseField(char* destination, char*& source) {
    while (*source != ',' && *source != '\0') {
        *destination = *source;
        destination++;
        source++;
    }

    source++;
    *destination = '\0';
}

void setMajor(Student& student) {
    if (student.FN[FIFTH_NUMBER_OF_FN] == (int)Major::Informatics) {
        student.major = Major::Informatics;
    }
    else if (student.FN[FIFTH_NUMBER_OF_FN] == (int)Major::Software) {
        student.major = Major::Software;
    }
    else if (student.FN[FIFTH_NUMBER_OF_FN] == (int)Major::ComputerScience) {
        student.major = Major::ComputerScience;
    }
}

void initialiseStudent(Student& student, char* buff) {
    parseField(student.FirstName, buff);
    parseField(student.SecondName, buff);
    parseField(student.EmailAddress, buff);
    parseField(student.FN, buff);

    setMajor(student);
}

int getthesizeandinfo(StudentCollection& collection, char* fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cout << "Error";
    }

    int StudentsCount = getStudentsCount(file);
    collection.data = new Student[StudentsCount];

    char buff[MAX_SIZE];

    for (int i = 0; i < StudentsCount; i++) {

        file.getline(buff, MAX_SIZE);
        initialiseStudent(collection.data[i], buff);
    }

    file.close();
    return StudentsCount;
}

void printByFn(char* Fn, StudentCollection& collection, int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(collection.data[i].FN, Fn) == 0) {
            std::cout << "First name: " << collection.data[i].FirstName << "Second name: " << collection.data[i].SecondName <<
                "Email: " << collection.data[i].EmailAddress << "FN: " << collection.data[i].FN;
            if (collection.data[i].FN[FIFTH_NUMBER_OF_FN] == (int)Major::Informatics) {
                std::cout << "Major: Informatics";
            }
            else if (collection.data[i].FN[FIFTH_NUMBER_OF_FN] == (int)Major::Software) {
                std::cout << "Major: Software";
            }
            else if (collection.data[i].FN[FIFTH_NUMBER_OF_FN] == (int)Major::ComputerScience) {
                std::cout << "Major: ComputerScience";
            }
        }
    }
}

void changeItNow(char* old, char* source) {
    strcpy_s(old,MAX_SIZE, source);
}

void changeEmail(StudentCollection& collection, int size, char* Fn, char* NewEmail) {
    for (int i = 0; i < size; i++) {
        if (strcmp(collection.data[i].FN, Fn) == 0) {
            changeItNow(collection.data[i].EmailAddress, NewEmail);
        }
    }
}

void createfile(StudentCollection& collection, int size, char* FileName) {
    std::ofstream file(FileName);
    if (!file.is_open()) {
        std::cout << "Error";
    }

    for (int i = 0; i < size; i++) {
        file << collection.data[i].FirstName << collection.data[i].SecondName << collection.data[i].EmailAddress << collection.data[i].FN;
        if (collection.data[i].FN[FIFTH_NUMBER_OF_FN] == (int)Major::Informatics) {
            file << "Informatics";
        }
        else if (collection.data[i].FN[FIFTH_NUMBER_OF_FN] == (int)Major::Software) {
            file << "Software";
        }
        else if (collection.data[i].FN[FIFTH_NUMBER_OF_FN] == (int)Major::ComputerScience) {
            file << "ComputerScience";
        }
    }

    file.close();
}

int main()
{
    std::cout << "Open file: " << std::endl;
    char fileName[MAX_SIZE];
    std::cin.getline(fileName, MAX_SIZE); // pisal sum si gi s getline za da mi e po qsno

    StudentCollection collection;
    int StudentsCount = getthesizeandinfo(collection,fileName);
    if (StudentsCount < 1) {
        return -1;
    }

    std::cout << "FIle successfully opened" << std::endl;

    char command[MAX_SIZE];

    do {
        std::cin.getline(command, MAX_SIZE);

        if (strcmp(command, "print") == 0) {
            char Fn[MAX_SIZE];
            std::cin.getline(Fn, MAX_SIZE);

            printByFn(Fn, collection, StudentsCount);
        }
        else if (strcmp(command, "edit") == 0) {
            char Fn[MAX_SIZE];
            std::cin.getline(Fn, MAX_SIZE);

            char NewEmail[MAX_SIZE];
            std::cin.getline(NewEmail, MAX_SIZE);

            changeEmail(collection, StudentsCount, Fn, NewEmail);
        }
        else if (strcmp(command, "save")) {
            char NewFileName[MAX_SIZE];
            std::cin.getline(NewFileName, MAX_SIZE);

            createfile(collection, StudentsCount, NewFileName);
         
        }
    } while (strcmp(command,"stop") == 0); // ne sum siguren dali do while e podhodqshto 

    delete[] collection.data;
}


