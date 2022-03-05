#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#endif

#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <clocale>

using namespace std;

void printMenu(char* origStr, bool f1, char** words, unsigned wordsCounter);

char** createString(unsigned* argCounter, char*& entString);

char* findLetters(char* word);

void insertionSort(char* &arr);

void createAnswer(char** words, unsigned wordsCounter);

int main() {
	setlocale(LC_ALL, "Russian");

	// Главные переменные
	unsigned wordsCounter = 0;
	char** words = (char**)malloc(1);

	// Служебные переменные
	char* enteredString = (char*)malloc(1);
	bool isEntStringFilled = false;

	//Переменные для пользовательского ввода.
	int userChoice = -1;

	while (userChoice != 0) { // Главный меню-цикл.
		system("cls");
		printMenu(enteredString, isEntStringFilled , words, wordsCounter);
		cin >> userChoice;
		switch (userChoice) {
		case 1:
			cout << "Введите строку из слов, разграничителями служат символ запятой и пробела.\n";
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			words = createString(&wordsCounter, enteredString);
			isEntStringFilled = true;
			system("pause");
			break;
		case 2:
			cout << "Строка будет очищена после продолжения.\n";
			isEntStringFilled = false;
			system("pause");
			break;
		case 0:
			cout << "До свидания!\n";
			userChoice = 0;
			system("pause");
			break;
		default:
			cout << "Я не понимаю вас, повторите ввод\n";
			cin.clear();
			system("pause");
			break;
		}
	}
	return 0;
}


void printMenu(char* origStr, bool f1, char** words, unsigned wordsCounter) {
	cout << "Практическая работа #3 ИКБО-03-21 Мазанов А.Е. Вариант 17\n\n"
		"Задание 1 - C-style строка\n"
		"================Меню================\n";
	cout << "Ввёденная строка: ";
	if (f1) puts(origStr);
	else cout << "Не может быть получено\n";
	cout << "Строка, обработанная по заданию: ";
	if (f1) createAnswer(words, wordsCounter);
	else cout << " ---\n";
	cout << "====================================\n";
	cout << "ВВЕДИТЕ, ЧТОБЫ: \n"
		"1) Ввести строку.\n"
		"2) Очистить строку.\n"
		"3) Выход.\n"
		"Ваш выбор: ";
}


char** createString(unsigned* argCounter, char*& entString) {
	char** wordsArr = (char**)malloc(1);
	unsigned wordsCnt = 0;

	char tempCh = 0;

	char* tempWord = (char*)malloc(1);
	unsigned tempWordLen = 0;

	bool isFirstCharFound = false;
	bool isNextWord = false;

	unsigned entStringLen = 0;

	while (tempCh != '\n') {
		tempCh = getchar();

		if (tempCh != '\n') {
			entString = (char*)realloc(entString, ++entStringLen * sizeof(char));
			entString[entStringLen - 1] = tempCh;
		}

		if (tempCh == ',' || tempCh == ' ' || tempCh == '\n') {
			if (isFirstCharFound) {
				if (isNextWord) {
					tempWord = (char*)realloc(tempWord, ++tempWordLen * sizeof(char));
					tempWord[tempWordLen - 1] = '\0';
					wordsArr = (char**)realloc(wordsArr, ++wordsCnt * sizeof(char*));
					wordsArr[wordsCnt - 1] = tempWord;
				}
				if (tempCh == ',') {
					wordsArr = (char**)realloc(wordsArr, ++wordsCnt * sizeof(char*));
					tempWord = (char*)malloc(2);
					tempWord[0] = ',';
					tempWord[1] = '\0';
					wordsArr[wordsCnt - 1] = tempWord;
				}
				tempWord = 0;
				tempWordLen = 0;
				isNextWord = false;
			}
		}
		else {
			if (!isFirstCharFound) isFirstCharFound = true;
			tempWord = (char*)realloc(tempWord, ++tempWordLen * sizeof(char));
			tempWord[tempWordLen - 1] = tempCh;
			isNextWord = true;
		}
	}

	entString = (char*)realloc(entString, ++entStringLen * sizeof(char));
	entString[entStringLen - 1] = '\0';

	*argCounter = wordsCnt;
	return wordsArr;
}


void insertionSort(char* &arr) {
	for (int i = 1; i < strlen(arr); i++) {
		int j = i - 1;
		while (j >= 0 && arr[j] > arr[j + 1]){
			swap(arr[j], arr[j + 1]);
			j--;
		}
	}
}


char* findLetters(char* word) {
	char* letters = {};
	unsigned len = 0;
	letters = (char*)realloc(letters, ++len * sizeof(char));
	letters[len - 1] = toupper(word[0]);
	for (size_t i = 1; i < strlen(word); i++){
		if (strchr(letters, toupper(word[i])) == NULL) {
			letters = (char*)realloc(letters, ++len * sizeof(char));
			letters[len - 1] = toupper(word[i]);
		}
	}
	letters = (char*)realloc(letters, ++len * sizeof(char));
	letters[len - 1] = '\0';
	insertionSort(letters);
	return letters;
}


bool isSameLetters(char* chekingWord, char* firstWord) {
	return (strcmp(findLetters(chekingWord), findLetters(firstWord)) == 0);
}


void createAnswer(char** words, unsigned wordsCounter) {
	unsigned allWordsLen = 0;
	for (size_t i = 0; i < wordsCounter; i++){
		allWordsLen += strlen(words[i]);
	}
	char* answerString = (char*)malloc(allWordsLen);
	char* randomBulshit = new char[1]{ '\0' };
	bool isFirstWordPrint = false;
	for (size_t i = 1; i < wordsCounter; i++) {
		if (isSameLetters(words[i], words[0])) {
			printf("%s ", words[i]);
		}
	}
	cout << words[0] << " ";
	for (size_t i = 1; i < wordsCounter; i++) {
		if (!(isSameLetters(words[i], words[0]))) {
			printf("%s ", words[i]);
		}
	}
	printf("\n");
}