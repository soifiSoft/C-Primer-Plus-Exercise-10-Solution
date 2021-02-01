#define STRING_LEN 50   // Макс. кол-во элементов в строке
#define MAX 10          // Максимальное кол-во введенных строк

// Состояния для ввода новых строк (для указателя *state)
#define TRUE 1
#define FALSE 0

int sortingAndPrint(const char arrOfStrings[][STRING_LEN], int counter, char choice);
void scrambling(char *arr[], int top, int seek);
int firstWordLenght(char *string);
char get_menu_input();
char get_choice();
char * ownfgets(char *string, int num, int *state);