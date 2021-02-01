#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <Windows.h>
#include "Header.h"

/*
 * \brief: Сортировка, выбранная пользователем, от меньшего к большему
 * \param: const arrOfString[][] Константный массив со строками, с которого будут браться значения.
 * \param: counter Кол-во строк, введенных пользователем.
 * \param: choice Выбранный пункт меню
 * \return 0: Код работы
 */
int sortingAndPrint(const char arrOfStrings[][STRING_LEN], int counter, char choice) {
	char *temp, *arr[MAX];
	int i, top, seek;

	// Указываем указатели на строки из arrOfStrings, чтобы работать с ними, т.к. arrOfStrings - const
	for (i = 0; i < counter; i++)
		arr[i] = arrOfStrings[i];

	// Сортировка arr, зависящая от выбора пользователя
	for (top = 0; top < counter - 1; top++)
		for (seek = top + 1; seek < counter; seek++) {
			switch (choice) {
			case 'a':
				for (i = 0; i < counter; i++)
					printf("%s\n", *(arrOfStrings + i));

				return 0;
			case 'b':
				if (strcmp(arr[top], arr[seek]) > 0)
					scrambling(arr, top, seek);
				break;
			case 'c':
				if (strlen(arr[top]) > strlen(arr[seek]))
					scrambling(arr, top, seek);
				break;
			case 'd':
				if (firstWordLenght(arr[top]) > firstWordLenght(arr[seek]))
					scrambling(arr, top, seek);
				break;
			default:
				puts("Error\n");
				break;
			}
		}

	// Вывод результата сортировки
	for (i = 0; i < counter; i++)
		puts(arr[i]);

	return 0;
}

/*
 * \brief: Перестановка элементов top и seek местами, если top больше чем seek
 * \param: *arr[] Массив, где хранятся указатели на исходный двумерный массив arrOfStrings
 * \param: top Больший элемент
 * \param: seek Меньший элемент
 */
void scrambling(char *arr[], int top, int seek) {
	char *temp;

	temp = arr[top];
	arr[top] = arr[seek];
	arr[seek] = temp;
}

/*
 * \brief: Вычисление длины первого слова строки string
 * \param: *string Указатель на строку, откуда берется вся строка
 * \return length: Длина первого слова
 */
int firstWordLenght(char *string) {
	int lenght = 0;

	while (isspace(*string))
		string++;

	while (!isspace(*string) && *string) {
		lenght++;
		string++;
	}

	return lenght;
}

/*
 * \brief: Получает ввод пользователя и проверяет его на правильность
 * \return ch: Символ для выбора из меню 
 */
char get_menu_input() {
	char ch, temp;

	if ((ch = getchar()) == '\n')
		while (ch == '\n')
			ch = getchar();
	
	if (ch >= -1 && ch <= 255) {   // Проверка на ввод допустимых символов ASCII
		if (isalpha(ch))
			while (getchar() != '\n')
				;
	}
	else
		return 0;

	return ch;
}

/*
 * \brief: Отображает меню и держить ch в диапазоне от 'a' до 'e'
 * \return: Символ для передачи его в функцию сортировки sortingAndPrint
 */
char get_choice() {
	int ch;

	printf("\nВыберите пункт:\n");
	printf("a. Печать исходных строк\n");
	printf("b. Печать строк в порядке ASCII\n");
	printf("c. Печать строк в порядке возрастания их длины\n");
	printf("d. Печать строк в порядке возрастания длины первого слова\n");
	printf("e. Выход\n");
	ch = get_menu_input();

	while (ch < 'a' || ch > 'e') {
		printf("Select a, b, c, d or e.\n");
		ch = get_menu_input();
	}

	return ch;
}

/*
 * \brief: Принимает ввод от пользователя и записывает строки в *string
 * \param: *string: Указатель на строку, куда нужно записать введенныем пользователем символы
 * \param: num: Макс. длина строки
 * \param: *state: Состояние ввода. Нужно, если пользователь ввел EOF для прекращения ввода
 * \return string: Указатель на созданную строку
 */
char * ownfgets(char *string, int num, int *state) {
	int counter = 0;
	char ch;

	while ((ch = getchar()) && counter != num - 1) {
		if (ch == '\n')
			break;
		if (ch == 26 || ch == EOF) {   // 26 - это EOF
			*state = FALSE;
			break;
		}
		if (ch <= 31)   // Вместо непечаемых символов подставляем пробел
			*(string + counter) = ' ';
		else
			*(string + counter) = ch;

		counter++;
	}
	*(string + counter) = '\0';

	// Очищаем входной буфер для последующего ввода
	while (ch != '\n' && ch != EOF && ch != 26)
		ch = getchar();

	return string;
}