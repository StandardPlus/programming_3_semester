// Даны три массива разной размерности. Определить в каком массиве больше сумма элементов.

#include <cstdio>
#include <locale.h>

const int nmax = 100;

int ArrayInputFromFile(int *n, double x[], char *fname);
int FindCountLessThanNumberInArray(double x[], int n, double number);
void PrintArrayOnScreen(int n, double x[]);

int main(int argc, char *argv[])
{
    double a[nmax], b[nmax], c[nmax];
    int a_size, b_size, c_size;
    int a_less_number_count, b_less_number_count, c_less_number_count;
    double number;
    double min;

    setlocale(LC_ALL, "rus"); // Меняем кодировку для консольного приложения

    if (argc < 4)
    {
        printf("Недостаточно параметров!\n");
        return 1;
    }
    if (!ArrayInputFromFile(&a_size, a, argv[1]))
        return 1;
    if (!ArrayInputFromFile(&b_size, b, argv[2]))
        return 1;
    if (!ArrayInputFromFile(&c_size, c, argv[3]))
        return 1;

    printf("Введите заданное число: ");
    scanf("%lf", &number);

    a_less_number_count = FindCountLessThanNumberInArray(a, a_size, number);
    b_less_number_count = FindCountLessThanNumberInArray(b, b_size, number);
    c_less_number_count = FindCountLessThanNumberInArray(c, c_size, number);

    min = a_less_number_count;
    if (b_less_number_count < min)
        min = b_less_number_count;
    if (c_less_number_count < min)
        min = c_less_number_count;

    printf("Массив A: ");
    PrintArrayOnScreen(a_size, a);
    printf("Массив B: ");
    PrintArrayOnScreen(b_size, b);
    printf("Массив C: ");
    PrintArrayOnScreen(c_size, c);

    if (a_less_number_count == b_less_number_count && b_less_number_count == c_less_number_count)
        printf("Количество элементов в массиве A, меньших чем %lf, совпадает с количеством в массивах B и C", number);
    else
    {
        if (a_less_number_count == b_less_number_count)
            printf("Количество элементов в массиве A, меньших чем %lf, совпадает с количеством в массиве B", number);
        if (b_less_number_count == c_less_number_count)
            printf("Количество элементов в массиве B, меньших чем %lf, совпадает с количеством в массиве C", number);
        if (a_less_number_count == c_less_number_count)
            printf("Количество элементов в массиве A, меньших чем %lf, совпадает с количеством в массиве C", number);
    }

    if (a_less_number_count == min)
        printf("Массив А имеет минимальное количество элементов, меньших числа %5.2lf и равно: %5.2lf\n", number, min);
    else if (b_less_number_count == min)
        printf("Массив B имеет минимальное количество элементов, меньших числа %5.2lf и равно: %5.2lf\n", number, min);
    else if (c_less_number_count == min)
        printf("Массив C имеет минимальное количество элементов, меньших числа %5.2lf и равно: %5.2lf\n", number, min);
}

int ArrayInputFromFile(int *n, double x[], char *fname)
{
    FILE *file;

    if ((file = fopen(fname, "r")) == NULL)
    {
        printf("Невозможно открыть файл '%s'\n", fname);
        return 0;
    }
    if (fscanf(file, "%d", n) < 1)
    {
        printf("Ошибка чтения из файла '%s'\n", fname);
        fclose(file);
        return 0;
    }
    if (*n < 0 || *n > nmax)
    {
        printf("Кол-во эл-тов массива должно быть от 1 до %d. (файл '%s')\n", nmax, fname);
        return 0;
    }
    for (int i = 0; i < *n; i++)
        if (fscanf(file, "%lf", &x[i]) < 1)
        {
            printf("Ошибка чтения из файла '%s'\n", fname);
            fclose(file);
            return 0;
        }
    fclose(file);
    return 1;
}

int FindCountLessThanNumberInArray(double x[], int n, double number)
{
    double count = 0;

    for (int i = 0; i < n; i++)
        if (x[i] < number)
            count++;

    return count;
}

void PrintArrayOnScreen(int n, double x[])
{
    for (int i = 0; i < n; i++)
        printf("%5.2lf ", x[i]);
    printf("\n");
}