#define STRING_LEN 50   // Макс. кол-во элементов в строке
#define MAX 10          // Максимальное кол-во введенных строк

int sorting(const char arrOfStrings[][STRING_LEN], int counter, char choice);
int first_word_lenght(char *string);
void print_results(char *arr[], int counter);
void scrambling(char *arr[], int top, int seek);
char * get_strings(char *string, int num, bool *state);
char get_menu_input();
char get_choice();