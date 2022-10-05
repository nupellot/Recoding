#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Файловая таблица кодировки. Таблица перекодировки должна задаваться в
// ресурсном текстовом файле, имя которого передается программе через аргумент
// командной строки вместе с именами исходного и результирующего файлов. Таблица
// должна иметь формат текстового файла, строки которого содержат коды строчных
// и заглавных букв алфавита в исходной и результирующей кодировке. Указанные
// коды должны быть заданы цифрами в системе счисления с основанием 16.

typedef struct {
	int OldCode;
	int NewCode;
} translation;


int main(int argv, char **argc) {
  int ToDecimal(char *kek, int AmountOfSymbols);

  // if (argv != 4) {
  //   printf("Use correct format: ./a.out source result code\n");
  //   return 1;
  // }

  // FILE *SourceFile = fopen(argc[1], "r");
  // FILE *ResultFile = fopen(argc[2], "w");
  FILE *CodeFile = fopen("code", "r");
	if (CodeFile == NULL) {
		printf("Ошибка открытия файла\n");
		return 2;
	}

  // printf("%s %d", argc[2], ToDecimal(argc[2], 3));

	char Old[30];
	char New[30];
	int AmountOfTranslations = 0;
	translation* Translations = calloc(0, sizeof(translation) * AmountOfTranslations);
	while (fscanf(CodeFile, "%s %s\n", Old, New) != EOF) {
		printf("%s %s\n", Old, New);
		AmountOfTranslations++;
		Translations = realloc(Translations, sizeof(translation) * AmountOfTranslations);
		Translations[AmountOfTranslations - 1].OldCode = ToDecimal(Old);
	}

	
}

int ToDecimal(char *kek, int AmountOfSymbols) {
  int result = 0;
  for (int i = 0; i < AmountOfSymbols; i++) {
    if (kek[i] >= 'A' && kek[i] <= 'F') {
      result += (10 + (int)(kek[i] - 'A')) * pow(16, AmountOfSymbols - i - 1);
    } else if (kek[i] >= '0' && kek[i] <= '9') {
      result += ((int)kek[i] - '0') * pow(16, AmountOfSymbols - i - 1);
    } else {
      printf("Wrong symbols\n");
      return -1;
    }
  }
  return result;
}