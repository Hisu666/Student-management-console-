#include <iostream>
#include <fstream>

using namespace std;

int strLen(char *str);
int equals(char *str1, char *str2);

void removeCharacterFromString(char *str, int delPos);
void standardName(char *str);
void formatName(char *str);
void standardID(char *ID);
void standardClass(char *Class);

bool isCharacter(char x);
bool isNumber(char x);
bool isWhiteSpace(char x);
bool isUpperCase(char x);
bool isLowerCase(char x);
bool isSpecialCharacter(char x);

void toLowerCaseString(char *str);
void toUpperCaseString(char *str);

int equalsIgnoreCases(char *str1, char *str2);

typedef struct {

	char studentName[31];
	char studentID[11];
	char dateOfBirth[11];
	char studentClass[15];
	float avgMark;

	void setStudentInfo() {

		cin.ignore();
		do 
		{

			cout << "Student name? ";
			gets(studentName);

			if(strLen(studentName) > 30) {
				cout << "\nName can't have more than 30 characters!" << endl ;
				system("pause");
				system("cls");
			}
			else if(!equals(studentName, "")) {
				cout << "\nCan't leave student name empty!" << endl ;
				system("pause");
				system("cls");
			}

		} while(strLen(studentName) > 30 || !equals(studentName, ""));

		formatName(studentName);

		do
		{

			cout << "Student ID? ";
			gets(studentID);

			if(strLen(studentID) > 10) {
				cout << "\nID can't have more than 10 characters!" << endl ;
				system("pause");
				system("cls");
			}
			else if(!equals(studentID, "")) {
				cout << "\nCan't leave student ID empty!" << endl ;
				system("pause");
				system("cls");
			}

		} while(strLen(studentID) > 10 || !equals(studentID, ""));

		standardID(studentID);

		do
		{

			cout << "Date of birth? ";
			gets(dateOfBirth);	

			if(strLen(dateOfBirth) > 10) {
				cout << "\nDoB can't have more than 10 characters!" << endl ;
				system("pause");
				system("cls");
			}
			else if(!equals(dateOfBirth, "")) {
				cout << "\nCan't leave student DoB empty!" << endl ;
				system("pause");
				system("cls");
			}

		} while(strLen(dateOfBirth) > 10 || !equals(dateOfBirth, ""));
		

		do
		{

			cout << "Student Class? ";
			gets(studentClass);

			if(strLen(studentClass) > 10) {
				cout << "\nClass can't have more than 10 characters!" << endl ;
				system("pause");
				system("cls");
			}
			else if(!equals(studentClass, "")) {
				cout << "\nCan't leave student class empty!" << endl ;
				system("pause");
				system("cls");
			}			

		} while(strLen(studentClass) > 10 || !equals(studentClass, ""));
		
		standardClass(studentClass);

		do
		{

			cout << "Average mark? ";
			cin >> avgMark;	

			if(avgMark < 0) {
				cout << "\nMark cant less than 0!" << endl;
				system("pause");
				system("cls");
			} else if(avgMark > 10) {
				cout << "\nMark cant greater than 10!" << endl;
				system("pause");
				system("cls");
			}

		} while(avgMark < 0 || avgMark > 10);
		
	}

	void getStudentInfo() {
		printf("%-25s%-10s%-15s%-15s%-8.2f\n", studentName, studentID, dateOfBirth, studentClass, avgMark);
	}

} Student;


typedef struct Node {
	Student data;
	Node *pNext;
} Node;


typedef struct List {
	Node *pHead;
	Node *pTail;
} List;


/*Prototype functions*/
Node *initNode(Student data);
void initLinkedList(List &l);
void getLinkedList(List l);
void freeLinkedList(List &l);

void addNodeToTail(List &l, Node *p);

void removeNodeAtHead(List &l);
void removeNodeAtTail(List &l);
void removeStudentFromTheList(List &l, int &amount, int delPos);

void menu();
void execute(List &l, int &amount, int mode);



void swap(Student &first, Student &second);
char *getLastName(char *str);
void sortStudentListAscendingByClass(List &l);
void sortStudentListAscendingByAvgMark(List &l);
void sortStudentListAscendingByLastName(List &l);

void searchStudentByName(List l, char *searchName);
void searchStudentsInTheSameClass(List l, char *Class);

void removeAllStudentsInAClass(List &l, int &amount, char *Class);
void removeStudentsUnderAvgMark(List &l, int &amount);

float maxAvgMark(List l);
void printStudentsWithHighestAvgMarkToFile(ofstream &fileout, List l);


/*Main function*/
int main(int argc, char const *argv[]) {
	
	List l;
	initLinkedList(l);

	int amount = 0, mode = -1;
	execute(l, amount, mode);

	return 0;
}


/*Full source code*/
Node *initNode(Student data) {
	Node *p = new Node;
	if(p == NULL)
	{
		cout << "\nOpps! Memory full!" << endl;
		return NULL;
	}

	p->data = data;
	p->pNext = NULL;

	return p;
}

void initLinkedList(List &l) {
	l.pHead = NULL;
	l.pTail = NULL;
}

void freeLinkedList(List &l) {
	Node *contain;
	while(l.pHead != NULL)
	{
		contain = l.pHead;
		l.pHead = l.pHead->pNext;
		delete contain;
	}
}

void addNodeToTail(List &l, Node *p) {
	if(l.pHead == NULL)
		l.pHead = l.pTail = p;
	else
	{
		l.pTail->pNext = p;
		l.pTail = p;
	}
}

void getLinkedList(List l) {
	if(l.pHead == NULL)
	{
		cout << "List is empty!" << endl;
		return;
	}

	printf("%-5s%-25s%-10s%-15s%-15s%-8s\n","No:", "Name:", "ID:", "DoB:", "Class:", "AvgMark:");
	int idx = 1;
	for(Node *i = l.pHead; i != NULL; i = i->pNext) {
		printf("%-5d", idx++);
		i->data.getStudentInfo();
	}
}

void removeNodeAtHead(List &l) {
	if(l.pHead == NULL)
		return;
	Node *contain = l.pHead;
	l.pHead = l.pHead->pNext;
	delete contain;
}

void removeNodeAtTail(List &l) {
	if(l.pHead == NULL)
		return;

	if(l.pHead != NULL && l.pHead->pNext == NULL)
	{
		Node *contain = l.pHead;
		l.pHead = l.pHead->pNext;
		delete contain;
		return;
	}

	for(Node *i = l.pHead; i != NULL; i = i->pNext)
	{
		if(i->pNext == l.pTail)
		{
			delete l.pTail;
			l.pTail = i;
			i->pNext = NULL;
		}
	}
}

void removeStudentFromTheList(List &l, int &amount, int delPos) {
	if(delPos == 1)
	{
		removeNodeAtHead(l);
		amount--;
		return;
	}

	if(delPos == amount)
	{
		removeNodeAtTail(l);
		amount--;
		return;
	}

	int idx = 0;
	Node *contain;
	for(Node *i = l.pHead; i != NULL; i = i->pNext)
	{
		idx++;
		if(idx == delPos)
		{
			Node *temp = i;
			contain->pNext = temp->pNext;
			delete temp;
		}
		contain = i;
	}

}

int strLen(char *str) {
	int count = 0;
	while(str[count] != '\0')	count++;
	return count;
}

void removeCharacterFromString(char *str, int delPos) {
	int len = strLen(str);
	for(int i = delPos; i < len - 1; i++)
		str[i] = str[i + 1];
	str[len - 1] = '\0';
}

int equals(char *str1, char *str2) {

	int len1 = strLen(str1);
	int len2 = strLen(str2);

	int lenMin = (len1 < len2) ? len1 : len2;
	for(int i = 0; i < lenMin; i++)
	{
		if(str1[i] > str2[i])
			return 1;
		else if(str1[i] < str2[i])
			return -1;
	}

	if(len1 > len2)
		return 1;
	else if(len1 < len2)
		return -1;

	return 0;
}

bool isCharacter(char x) {
	return (x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z');
}

bool isNumber(char x) {
	return (x >= '0' && x <= '9');
}

bool isWhiteSpace(char x) {
	return (x == ' ' || x == '\t');
}

bool isUpperCase(char x) {
	return (x >= 'A' && x <= 'Z');
}

bool isLowerCase(char x) {
	return (x >= 'a' && x <= 'z');
}

bool isSpecialCharacter(char x) {
	return !isCharacter(x) && !isWhiteSpace(x) && !isNumber(x);
}

void toLowerCaseString(char *str) {
	int len = strLen(str);
	for(int i = 0; i < len; i++)
		if(isUpperCase(str[i]))
			str[i] += 32;
}

void toUpperCaseString(char *str) {
	int len = strLen(str);
	for(int i = 0; i < len; i++)
		if(isLowerCase(str[i]))
			str[i] -= 32;
}

void standardName(char *str) {
	while(!isCharacter(str[0]))
		removeCharacterFromString(str, 0);

	for(int i = 1; i < strLen(str); i++)
		if(!isCharacter(str[i]) && !isCharacter(str[i+1]))
			removeCharacterFromString(str, i--);

	while(!isCharacter(str[strLen(str) - 1]))
		removeCharacterFromString(str, str[strLen(str) - 1]);
}

void formatName(char *str) {
	standardName(str);
	toLowerCaseString(str);

	str[0] -= 32;
	int len = strLen(str);
	for(int i = 1; i < len - 1; i++)
		if(isWhiteSpace(str[i]) && isLowerCase(str[i + 1]))
			str[i+1] -= 32;
}

void standardID(char *ID) {
	for(int i = 0; i < strLen(ID); i++)
		if(isWhiteSpace(ID[i]) || isSpecialCharacter(ID[i]))
			removeCharacterFromString(ID, i--);
}

void standardClass(char *Class) {
	for(int i = 0; i < strLen(Class); i++)
		if(isSpecialCharacter(Class[i]) || isWhiteSpace(Class[i]))
			removeCharacterFromString(Class, i--);

	toUpperCaseString(Class);
}

int equalsIgnoreCases(char *str1, char *str2) {
	toLowerCaseString(str1);
	toLowerCaseString(str2);
	return equals(str1, str2);
}

void swap(Student &first, Student &second) {
	Student temp = first;
	first = second;
	second = temp;
}

void sortStudentListAscendingByClass(List &l) {
	for(Node *i = l.pHead; i != NULL; i = i->pNext)
		for(Node *j = i->pNext; j != NULL; j = j->pNext)
			if(!equalsIgnoreCases(i->data.studentClass, j->data.studentClass))
				swap(i->data, j->data);
}

void sortStudentListAscendingByAvgMark(List &l) {
	for(Node *i = l.pHead; i != NULL; i = i->pNext)
		for(Node *j = i->pNext; j != NULL; j = j->pNext)
			if(i->data.avgMark > j->data.avgMark)
				swap(i->data, j->data);
}

char *getLastName(char *str) {

	int len = strLen(str);
	int whiteSpaceIdx = -1;
	for(int i = len - 1; i >= 0; i--)
		if(isWhiteSpace(str[i])) 
		{
			whiteSpaceIdx = i + 1;
			break;
		}

	int idx = 0;
	char *res = new char[len - whiteSpaceIdx + 1];
	for(int i = whiteSpaceIdx; i < len; i++)
		res[idx++] = str[i];
	res[idx] = '\0';

	return res;
	delete[] res;
}


void sortStudentListAscendingByLastName(List &l) {
	for(Node *i = l.pHead; i != NULL; i = i->pNext)
		for(Node *j = i->pNext; j != NULL; j = j->pNext)
		{
			char *first = getLastName(i->data.studentName);
			char *second = getLastName(j->data.studentName);
			if(equalsIgnoreCases(first, second) == 1)
				swap(i->data, j->data);
		}	
}


void searchStudentByName(List l, char *searchName) {
	char isFound = 'n';
	printf("%-5s%-25s%-10s%-15s%-15s%-8s\n","No:", "Name:", "ID:", "DoB:", "Class:", "AvgMark:");
	int idx = 1;
	for(Node *i = l.pHead; i != NULL; i = i->pNext)
		if(!equalsIgnoreCases(i->data.studentName, searchName))
		{
			isFound = 'y';
			printf("%-5d", idx++);
			i->data.getStudentInfo();
		}

	if(isFound == 'n')
	{
		cout << "\nThere is no student named \"" << searchName << "\" in the list!" << endl;
		return;
	}

}

void searchStudentsInTheSameClass(List l, char *Class) {

	cout << "\n\t\tStudent(s) in the same class:\n";

	char isFound = 'n';
	printf("%-5s%-25s%-10s%-15s%-15s%-8s\n","No:", "Name:", "ID:", "DoB:", "Class:", "AvgMark:");
	int idx = 1;
	for(Node *i = l.pHead; i != NULL; i = i->pNext)
		if(!equalsIgnoreCases(i->data.studentClass, Class))
		{
			isFound = 'y';
			printf("%-5d", idx++);
			i->data.getStudentInfo();
		}

	if(isFound == 'n')
	{
		cout << "\nThere is no student the class \"" << Class << "!" << endl;
		return;
	}
}

void menu() {
	system("cls");
	cout << "              Student Management Application             " << endl;
	cout << "<------------------------------------------------------->" << endl;
	cout << ".| [01] > Add new student info.                         |." << endl;
	cout << ".| [02] > Display Student-list.                         |." << endl;
	cout << ".| [03] > Sort Student-list ascending by last-name.     |." << endl;
	cout << ".| [04] > Sort Student-list ascending by class.         |." << endl;
	cout << ".| [05] > Sort Student-list ascending by average mark.  |." << endl;
	cout << ".| [06] > Search student by name.                       |." << endl;
	cout << ".| [07] > Search student by class.                      |." << endl;
	cout << ".| [08] > Remove a student from the list.               |." << endl;
	cout << ".| [09] > Remove all students in a class.               |." << endl;
	cout << ".| [10] > Remove student(s) with avgMark < 5.           |." << endl;
	cout << ".| [11] > Print student(s) with highest mark to file.   |." << endl;
	cout << ".| [12] > Reset Student-list.                           |." << endl;
	cout << ".| [00] > Exit.                                         |." << endl;
	cout << "<------------------------------------------------------->" << endl << endl;
	cout << "[Mode]:  ";
}

void execute(List &l, int &amount, int mode) {
	do
	{
		menu();
		cin >> mode;

		switch(mode)
		{

			case 0:
			{
				system("cls");
				cout << "See ya! Thanks For using!" << endl;
				freeLinkedList(l);
				system("pause");
				return;
			}

			case 1:
			{
				system("cls");

				Student data;
				Node *p;
				char esp;

				do
				{
					system("cls");

					data.setStudentInfo();
					p = initNode(data);
					addNodeToTail(l, p);
					amount++;
					cout << "\nDone! Student info added to the list...." << endl;

					cin.ignore();
					cout << "\nContinue [y/n]?   ";
					cin >> esp;

				} while(esp != 'n');

				break;
			}

			case 2:
			{
				system("cls");

				if(l.pHead == NULL)
				{
					cout << "List is empty!" << endl;
					system("pause");
					break;
				}

				cout << "\n\t\tSTUDENT INFO:\n";
				getLinkedList(l);

				system("pause");
				break;
			}

			case 3:
			{

				system("cls");

				if(l.pHead == NULL)
				{
					cout << "List is empty!" << endl;
					system("pause");
					break;
				}

				sortStudentListAscendingByLastName(l);
				cout << "List has been sorted successfully! Please choose mode [2] to review!" << endl;

				system("pause");
				break;
			}

			case 4:
			{
				system("cls");

				if(l.pHead == NULL)
				{
					cout << "List is empty!" << endl;
					system("pause");
					break;
				}

				sortStudentListAscendingByClass(l);
				cout << "List has been sorted successfully! Please choose mode [2] to review!" << endl;
				
				system("pause");
				break;
			}

			case 5:
			{
				system("cls");

				if(l.pHead == NULL)
				{
					cout << "List is empty!" << endl;
					system("pause");
					break;
				}

				sortStudentListAscendingByAvgMark(l);
				cout << "List has been sorted successfully! Please choose mode [2] to review!" << endl;

				system("pause");
				break;
			}

			case 6:
			{
				system("cls");

				cin.ignore();
				char searchName[31];
				cout << "Search for? ";
				gets(searchName);
				searchStudentByName(l, searchName);

				system("pause");
				break;
			}

			case 7:
			{
				system("cls");

				cin.ignore();
				char Class[14];
				cout << "Search students in class? ";
				gets(Class);
				searchStudentsInTheSameClass(l, Class);

				system("pause");
				break;
			}


			case 8:
			{
				system("cls");
				if(l.pHead == NULL)
				{
					cout << "List is empty!" << endl;
					system("pause");
					break;
				}

				getLinkedList(l);

				int pos;
				do {
					cout << "\nRemove Student at position? ";
					cin >> pos;	
					if(pos < 1 || pos > amount)
					{
						cout << "\nPosition must in range [1, " << amount << "]!" << endl;
						system("pause");
					}
				} while(pos < 1 || pos > amount);

				removeStudentFromTheList(l, amount, pos);
				cout << "\nDone..." << endl;
				system("pause");
				break;
			}
			
			case 9:
			{
				system("cls");
				if(l.pHead == NULL)
				{
					cout << "List is empty!" << endl;
					system("pause");
					break;
				}

				getLinkedList(l);

				cin.ignore();
				char Class[15];
				cout << "\nRemove student(s) in class? ";
				gets(Class);

				removeAllStudentsInAClass(l, amount, Class);

				system("pause");
				break;
			}

			case 10:
			{
				system("cls");
				if(l.pHead == NULL)
				{
					cout << "List is empty!" << endl;
					system("pause");
					break;
				}

				removeStudentsUnderAvgMark(l, amount);
				system("pause");
				break;
			}

			case 11:
			{
				system("cls");
				if(l.pHead == NULL)
				{
					cout << "List is empty!" << endl;
					system("pause");
					break;
				}

				ofstream fileout;
				printStudentsWithHighestAvgMarkToFile(fileout, l);
				cout << "Done..." << endl;

				system("pause");
				break;
			}

			case 12:
			{
				system("cls");

				freeLinkedList(l);
				cout << "Done! Student-list has been reseted successfully!" << endl;

				system("pause");
				break;
			}

			default:
			{
				system("cls");

				cout << "Error! Mode invalid! Please re-check your choice!" << endl;

				system("pause");
				break;
			}

		}

	} while(mode != 0);
}

void removeAllStudentsInAClass(List &l, int &amount, char *Class) {
	int idx = 0;
	char isFound = 'n';
	for(Node *i = l.pHead; i != NULL; i = i->pNext)
	{
		idx++;
		if(!equalsIgnoreCases(i->data.studentClass, Class)) 
		{
			isFound = 'y';
			removeStudentFromTheList(l, amount, idx--);
		}
	}

	if(isFound == 'n')
	{
		cout << "\nThere is no class named \"" << Class << "\" in the list!" << endl;
		return;
	}

	cout << "\nRemoved successfully! Please choose mode [2] to review!" << endl;
}

void removeStudentsUnderAvgMark(List &l, int &amount) {
	int idx = 0;
	char isFound = 'n';
	for(Node *i = l.pHead; i != NULL; i = i->pNext)
	{
		idx++;
		if(i->data.avgMark < 5) 
		{
			isFound = 'y';
			removeStudentFromTheList(l, amount, idx--);
		}
	}

	if(isFound == 'n')
	{
		cout << "\nThere is no student with avgMark < 5 in the list!" << endl;
		return;
	}

	cout << "\nRemoved successfully! Please choose mode [2] to review!" << endl;
}

float maxAvgMark(List l) {
	
	float max = l.pHead->data.avgMark;
	for(Node *i = l.pHead->pNext; i != NULL; i = i->pNext)
		max = (max > i->data.avgMark) ? max : i->data.avgMark;

	return max;
}

void printStudentsWithHighestAvgMarkToFile(ofstream &fileout, List l) {
	
	fileout.open("highestAvgMark.txt", ios::out);
	if(fileout.fail()) 
	{
		cout << "Error occured! Cant write data to file!" << endl;
		return;
	}

	int max = maxAvgMark(l);
	fileout << "Highest AvgMark: " << max << endl;
	for(Node *i = l.pHead; i != NULL; i = i->pNext)
		if(i->data.avgMark == max)
		{
			fileout << i->data.studentName << endl;
			fileout << i->data.studentClass << endl;
			fileout << i->data.studentID << endl;
			fileout << i->data.dateOfBirth << endl;
		}
	
	fileout.close();
}