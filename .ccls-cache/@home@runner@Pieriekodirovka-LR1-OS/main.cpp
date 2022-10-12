#include <iostream>
#include <vector>
#include <string.h>
#include <cmath>
#include <fstream>

using namespace std;

// Файловая таблица кодировки. Таблица перекодировки должна задаваться в
// ресурсном текстовом файле, имя которого передается программе через аргумент
// командной строки вместе с именами исходного и результирующего файлов. Таблица
// должна иметь формат текстового файла, строки которого содержат коды строчных
// и заглавных букв алфавита в исходной и результирующей кодировке. Указанные
// коды должны быть заданы цифрами в системе счисления с основанием 16.

typedef class translation {
public:
	translation(int _OldCode, int _NewCode) {
		OldCode = _OldCode;
		NewCode = _NewCode;
	}
	int OldCode;
	int NewCode;
	void Print() {
		cout << OldCode << " -> " << NewCode << endl;
	}
} translation;


int main(int argv, char **argc) {
	vector<translation> GetTranslations(string CodeFileName);
	void PrintTranslations(vector<translation>);
	void Convert(string, string, vector<translation>&);

	if (argv != 4) {
		cout << "Correct format: ./main source result code";
		exit(1);
	}

	// Creating alphabet of Translation based on file "code"
	vector<translation> Translations = GetTranslations(argc[3]);
	// Printing alphabet 
	PrintTranslations(Translations);
	// Converting text and printing it into result file.
	Convert(argc[1], argc[2], Translations);
}


// Converts text and prints it into result file.
void Convert(string SourceFileName, string ResultFileName, vector<translation>& Translations) {
	ifstream SourceFile(SourceFileName);  // Text to translate.
	ofstream ResultFile(ResultFileName);  // Destination of Translation.
	if (!SourceFile.is_open() || !ResultFile.is_open()) {
		printf("File opening error\n");
		exit(3);
	}
	char TranslateSymbol(char, vector<translation>&);
	cout << "\033[44m\033[37m\033[44m" << "---> Converting process <---" << "\033[0m" << endl;
	while (!SourceFile.eof()) {
		char c;
		SourceFile.get(c);
		char TranslatedSymbol = TranslateSymbol(c, Translations);
		
		ResultFile << TranslatedSymbol;
		if (c != TranslatedSymbol) {
			cout << "\033[32m";
		}
		cout << c << " -> " << TranslatedSymbol << endl;
		if (c != TranslatedSymbol) {
			cout << "\033[0m";
		}
	}
}

// Converts symbol using dictionary. 
char TranslateSymbol(char c, vector<translation>& Translations) {
	for (int i = 0; i < Translations.size(); i++) {
		if (Translations[i].OldCode == (int)c) {
			return (char)Translations[i].NewCode;
		}
	}
	return c;
}

// Prints all the translations in dictionary.
void PrintTranslations(vector<translation> Translations) {
	for (int i = 0; i < Translations.size(); i++) {
		Translations[i].Print();
	}
	cout << endl;
}

// Converts hexadecimal number to decimal number.
int ToDecimal(string Number) {
  int result = 0;
  for (int i = 0; i < Number.length(); i++) {
    if (Number[i] >= 'A' && Number[i] <= 'F') {
      result += (10 + (int)(Number[i] - 'A')) * pow(16, Number.length() - i - 1);
    } else if (Number[i] >= '0' && Number[i] <= '9') {
      result += ((int)Number[i] - '0') * pow(16, Number.length() - i - 1);
    } else {
      printf("Wrong symbols\n");
      return -1;
    }
  }
  return result;
}

vector<translation> GetTranslations(string CodeFileName) {
  ifstream CodeFile(CodeFileName);  // Translation codes.
	if (!CodeFile.is_open()) {  // Making sure file opened successfully.
		printf("File opening error\n");
		exit(2);
	}
	vector<translation> Translations;
	string Old;
	string New;
	cout << "\n\033[44m\033[37m" << "Dictionary:" << "\033[0m" << endl;
	while (!CodeFile.eof()) {
		CodeFile >> Old;
		CodeFile >> New;
		cout << Old << " " << New << endl;
		Translations.emplace_back(translation(ToDecimal(Old), ToDecimal(New)));
	}

	return Translations;
}