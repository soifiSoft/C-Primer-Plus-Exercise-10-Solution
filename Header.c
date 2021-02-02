#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "Header.h"

/*
 * \brief: Сортировка, выбранная пользователем, от меньшего к большему
 * \param: const arrOfString[][] Константный массив со строками, с которого будут браться значения.
 * \param: counter Кол-во строк, введенных пользователем.
 * \param: choice Выбранный пункт меню
 * \return 0: Код работы
 */
int sorting(const char arrOfStrings[][STRING_LEN], int counter, char choice) {
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
				print_results(arr, counter);
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
				if (first_word_lenght(arr[top]) > first_word_lenght(arr[seek]))
					scrambling(arr, top, seek);
				break;
			default:
				puts("Error\n");
				break;
			}
		}

	print_results(arr, counter);

	return 0;
}

/*
 * \brief: Вычисление длины первого слова строки string
 * \param: *string Указатель на строку, откуда берется вся строка
 * \return length: Длина первого слова
 */
int first_word_lenght(char *string) {
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
 * \brief: Вывод результата сортировки
 * \param: *arr Массив, где хранятся указатели на отсортированные строки
 * \param: counter Кол-во введенных строк
 */
void print_results(char *arr[], int counter) {
	int i;

	printf("\nРезультат:\n");
	for (i = 0; i < counter; i++)
		puts(arr[i]);
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
 * \brief: Принимает ввод от пользователя и записывает строки в *string
 * \param: *string: Указатель на строку, куда нужно записать введенныем пользователем символы
 * \param: *state: Состояние ввода. Нужно, если пользователь ввел EOF для прекращения ввода
 * \param: num: Макс. длина строки
 * \return string: Указатель на созданную строку
 */
char * get_strings(char *string, int num, bool *state) {
	int counter = 0;
	char ch;

	while ((ch = getchar()) && counter != num - 1) {
		if (ch == '\n')
			break;
		if (ch == 26 || ch == EOF) {   // 26 - это EOF
			*state = false;
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
 * \brief: Отображает меню и держит ch в диапазоне от 'a' до 'e'
 * \return: Символ для передачи его в функцию сортировки sorting
 */
char get_choice() {
	int ch;

	printf("\n---------------------------------------------------------\n");
	printf("a. Печать исходных строк\n");
	printf("b. Печать строк в порядке ASCII\n");
	printf("c. Печать строк в порядке возрастания их длины\n");
	printf("d. Печать строк в порядке возрастания длины первого слова\n");
	printf("e. Выход");
	printf("\n---------------------------------------------------------\n");
	printf("\nВыберите пункт: ");
	ch = get_menu_input();

	while (ch < 'a' || ch > 'e') {
		printf("Выберите a, b, c, d или e: ");
		ch = get_menu_input();
	}

	return ch;
}