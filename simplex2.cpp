# include <iostream>
# include <cmath>
# include <array>
# include <limits>
# include <algorithm>
# include <iomanip>
# include <string>
# include <vector>
 
typedef std::vector<std::vector<double>> Arr;
 
void print(const Arr& table);
bool isContainNeg(const std::vector<double>& table);
void solve(Arr table);
 
int main()
{
    setlocale(LC_ALL, "rus");
 
    Arr table =
    {
        {
            {0,  0,   1,  2,   3},
            {4,  4,   4,  1,   1},
            {5,  3,   1,  2,   0},
            {6,  2,   0, 0.5,  1},
            {0,  0,   7,  5,   3}
        }
    };
 
    solve(table);
 
    //составим двойственную задачу    
 
    table =
    {
        {
            {0,  0,   1,   2,   3},
            {4,  -7,   -4,   -1,   0},
            {6,  -5,   -1,   -2,   -0.5},
            {7,  -3,   -1,   0,   -1},
            {0,  0,   -4,   -3,   -2}
        }
    };
 
    std::cout << "Dvoystvenna9 zada4a:\n";
 
    solve(table);
    std::cin.get();
    std::cin.get();
    return 0;
}
 
void solve(Arr table)
{
 
    const std::size_t N = table.size();
    const std::size_t M = table[0].size();
    print(table);
 
    while (true)
    {
        std::size_t Vrow = 0, Vcol = 0;
        double min = std::numeric_limits<double>::lowest();
 
        for (std::size_t j = 1; j < N - 1; j++)
        {
            if (table[j][1] > min && table[j][1] < 0 && isContainNeg(table[j]))
            {
                min = table[j][1];
                Vrow = j;
            }
        }
 
        if (Vrow != 0)
        {
            std::cout << "Ведущей выбрана строка X" << table[Vrow][0] << "(имеет отрицательный свободный член)\n";
            min = 0;
            for (std::size_t j = 2; j < M; j++)
            {
                if (table[Vrow][j] < min)
                {
                    min = table[Vrow][j];
                    Vcol = j;
                }
            }
            if (min == 0)
            {
                std::cout << " Нет допустимого решения\n";
                return;
            }
            std::cout << "Ведущим выбран столбец X" << table[0][Vcol] << "(минимальный отрицательный)\n";
        }
        else
        {
            for (std::size_t j = 2; j < M; j++)
            {
                if (table[N - 1][j] > 0)
                {
                    Vcol = j;
                    break;
                }
            }
            if (Vcol == 0)
            {
                std::cout << "Получено оптимальное решение\n";
                return;
            }
            std::cout << "Ведущим выбран столбец X" << table[0][Vcol] << "(первый положительный)\n";
            min = std::numeric_limits<double>::max();
            for (std::size_t j = 1; j < N - 1; j++)
            {
                //минимальное положительное отношение свободного члена
                auto d = table[j][1] / table[j][Vcol];
                if (d > 0 && min > d)
                {
                    min = d;
                    Vrow = j;
                }
            }
            std::cout << "Ведущей выбрана строка X" << table[Vrow][0] << "(минимальное положительное отношение)\n";
        }
 
        //жордановы преобразования
        for (std::size_t i = 1; i < N; i++)
        {
            if (i != Vrow)
            {
                for (std::size_t j = 1; j < M; j++)
                {
                    if (j != Vcol)
                    {
                        table[i][j] = table[i][j] - table[i][Vcol] * table[Vrow][j] / table[Vrow][Vcol];
                    }
                }
            }
        }
 
        for (std::size_t j = 1; j < M; j++)
        {
            if (j != Vcol)
            {
                table[Vrow][j] = table[Vrow][j] / table[Vrow][Vcol];
            }
        }
 
        for (std::size_t i = 1; i < N; i++)
        {
            if (i != Vrow)
            {
                table[i][Vcol] = -table[i][Vcol] / table[Vrow][Vcol];
            }
        }
 
        table[Vrow][Vcol] = 1.0 / table[Vrow][Vcol];
 
        std::swap(table[0][Vcol], table[Vrow][0]);
 
        print(table);
    }
}
 
//вывод симплекс-таблицы
void print(const Arr& table)
{
 
    std::cout << std::right << std::setw(8) << "" << "  ";
    std::cout << std::right << std::setw(8) << "Si0" << "  ";
    for (std::size_t j = 2; j < table[0].size(); j++)
    {
        std::cout << std::right << std::setw(8) << "X" + std::to_string(int(table[0][j])) << "  ";
    }
    std::cout << '\n';
 
    for (std::size_t i = 1; i < table.size(); i++)
    {
        if (i != table.size() - 1)
        {
            std::cout << std::right << std::setw(8) << "X" + std::to_string(int(table[i][0])) << "  ";
        }
        else
        {
            std::cout << std::right << std::setw(8) << "F" << "  ";
        }
        for (std::size_t j = 1; j < table[0].size(); j++)
        {
            std::cout << std::right << std::setw(8) << std::setprecision(4) << table[i][j] << "  ";
        }
        std::cout << '\n';
    }
 
    std::cout << "Значение целевой функции " << table[table.size() - 1][1] << '\n';
}
 
//если есть хотя-бы 1 отрицательный элемент -
//возвращаем true, иначе - false
bool isContainNeg(const std::vector<double>& table)
{
    for (std::size_t i = 2; i < table.size(); i++)
    {
        if (table[i] < 0)
        {
            return true;
        }
    }
    return false;
}
