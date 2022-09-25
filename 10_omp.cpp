#include <omp.h>
#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

int main ()
{
    /** Входные данные не спрашиваются у пользователя для ясности распараллеливания программы */
    vector<vector<double>> matrix = {
        {13, 21, 35, 24, 90, -3, -45},
        {43, 51, 65, 22, 70, -3, 211},
        {73, 81, 95, 24, 51, -3, -90}
    };

    vector<double> v = {7, 6, 22};


    vector<double> res = {};
    for (int i = 0; i < matrix[0].size(); i++) {
        res.push_back(0);
    }


    /** Проверка на валидность входных данных опущена для ясности распараллеливания программы */
    #pragma omp parallel for
    for (int i = 0; i < matrix[0].size(); i++)
    {
        for (int j = 0; j < v.size(); j++)
        {
            res[i] += matrix[j][i] * v[j];
            printf("[debug] thread %d: %.2f * %.2f = %.2f \n",
                    omp_get_thread_num(), v[j], matrix[j][i], res[i]
            );
        }
    }


    // Вывод результата
    cout << "===\n" << "RESULT: " << endl;
    for (int i = 0; i < res.size(); i++)
    {
        cout << res[i] << " ";
    }
    cout << endl;

    return 0;
}
