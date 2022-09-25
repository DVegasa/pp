#include <omp.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>
#include <time.h>
#include <stdlib.h>

using namespace std;

void sleep(int ms) {
    this_thread::sleep_for(chrono::milliseconds(ms));
}

int random(int min, int max) {
    return rand() % (max - min + 1) + min;
}

int main ()
{
    srand(time(NULL));

    const int LIMIT = 5;
    const int CONSUMERS = 2;
    const int PRODUCERS = 3;
    const int CONSUMERS_DELAY = 4200;
    const int PRODUCERS_DELAY = 5000;


    vector<int> q = {};
    omp_lock_t lock;
    omp_init_lock(&lock);



    #pragma omp parallel num_threads(CONSUMERS + PRODUCERS)
    {
        int tn = omp_get_thread_num();
        int i = 0;

        while (true) {
            i++;

            printf("(");
            for (int i = 0; i < q.size(); i++) {
                printf("%d ", q[i]);
            }
            printf(")\n");


            if (tn < CONSUMERS) {
                // Код потребителя
                sleep(CONSUMERS_DELAY);
                printf("БРАТЕЛЬ#%d - проснулся (%d)\n", tn, i);

                if (q.size() > 0) {
                    omp_set_lock(&lock);
                    if (q.size() <= 0) continue;

                    int item = q.back();
                    q.pop_back();
                    omp_unset_lock(&lock);
                    printf("БРАТЕЛЬ#%d - ВЗЯЛ %d\n", tn, item);
                } else {
                    printf("БРАТЕЛЬ#%d - нечего брать \n", tn);
                }

            } else {
                // Код производителя
                sleep(PRODUCERS_DELAY);
                printf("КЛАТЕЛЬ#%d - проснулся (%d)\n", tn, i);

                int value = random(100, 999);
                while (true) {
                    if (q.size() >= LIMIT) {
                        printf("КЛАТЕЛЬ#%d - хочу, но не могу! \n", tn);
                        sleep(200);

                    } else {
                        omp_set_lock(&lock);
                        if (q.size() >= LIMIT) {
                            printf("КЛАТЕЛЬ#%d - хочу, но не могу! \n", tn);
                            omp_unset_lock(&lock);
                            continue;
                        }

                        q.push_back(value);
                        omp_unset_lock(&lock);
                        printf("КЛАТЕЛЬ#%d - ПОЛОЖИЛ %d\n", tn, value);
                        break;
                    }
                }
            }

        }
    }

    omp_destroy_lock(&lock);

    return 0;
}
