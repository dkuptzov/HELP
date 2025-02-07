#include <stdio.h>

int main() {
    char str[100];

    printf("Введите строку символов: ");
    fgets(str, sizeof(str), stdin);

    int i = 0;
    while (str[i] != '\0' && str[i] != '\n') {
        if ((str[i] >= '0' && str[i] <= '9') ||   // Проверка на цифры
            (str[i] >= 'A' && str[i] <= 'Z') ||   // Проверка на заглавные буквы
            (str[i] >= 'a' && str[i] <= 'z')) {   // Проверка на строчные буквы
            printf("Ошибка! Найден недопустимый символ.\n");
            return 1;
        }
        i++;
    }

    printf("Строка введена корректно.\n");
    return 0;
}
