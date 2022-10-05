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
  int ToDecimal(string Number);

  // if (argv != 4) {
  //   printf("Use correct format: ./a.out source result code\n");
  //   return 1;
  // }

  // FILE *SourceFile = fopen(argc[1], "r");
  // FILE *ResultFile = fopen(argc[2], "w");
  ifstream CodeFile("code");
	ifstream SourceFile("source");
	if (!CodeFile.is_open()) {
		printf("Ошибка открытия файла\n");
		return 2;
	}

  // printf("%s %d", argc[2], ToDecimal(argc[2], 3));

	string Old;
	string New;
	vector<translation> Translations;
	cout << "Jopa1" << endl;
	while (!CodeFile.eof()) {
		// cout << "Jopa2" << endl;
		CodeFile >> Old;
		CodeFile >> New;
		cout << Old << " " << New << endl;
		Translations.emplace_back(translation(ToDecimal(Old), ToDecimal(New)));
	}

	for (int i = 0; i < Translations.size(); i++) {
		Translations[i].Print();
	}
}

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