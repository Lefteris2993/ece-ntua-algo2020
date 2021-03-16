#include <stdio.h>
#include <stdlib.h>  // qsort

struct car { 
    int price;
    int capacity;
};

struct modes {
    int Ts; //econ 
    int Cs;
    int Tf; //sport
    int Cf;
};

int compareCars(const void* p1, const void* p2) {
    struct car c1 = * ( (struct car *) p1 );
    struct car c2 = * ( (struct car *) p2 );

    if (c1.capacity < c2.capacity) return -1;
    if (c1.capacity > c2.capacity) return 1;
    else return 0;
}

int compareDist(const void* p1, const void* p2) {
    int a = *((int *) p1);
    int b = *((int *) p2);

    if (a < b) return -1;
    if (a > b) return 1;
    else return 0;
}

int compareDistDesc(const void* p1, const void* p2) {
    return -1 * compareDist(p1, p2);
}

int isCapable(const struct car Car, const int* dist, const int K, const int T, const struct modes mode) {
    double time = 0.0;

    for (int i = 0; i < K+1; i++) {
        if (Car.capacity / (double) mode.Cs < dist[i]) {
            return 0;
        } else if (Car.capacity / (double) mode.Cf > dist[i]) {
            time += dist[i] * (double) mode.Tf;
        } else {
            time += (double) mode.Ts * (Car.capacity - mode.Cf * dist[i]) / (double) (mode.Cs - mode.Cf);
            time += (double) mode.Tf * (dist[i] - (Car.capacity - mode.Cf * dist[i]) / (double) (mode.Cs - mode.Cf));
        }
        if (time > T) return 0;
    }
    return 1;
}


int main() {
    int N, K, D, T;
    scanf("%d %d %d %d", &N, &K, &D, &T);

    struct car cars[N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &(cars[i].price), &(cars[i].capacity));
    }

    int distances[K];
    for (int i = 0; i < K; i++) {
        scanf("%d", &distances[i]);
    }

    struct modes mode;
    scanf("%d %d %d %d", &(mode.Ts), &(mode.Cs), &(mode.Tf), &(mode.Cf));

    struct car a;
    qsort(cars, N, sizeof(a), compareCars);// sort cars by capacity
    qsort(distances, K, sizeof(int), compareDist);// sort distances

    int realDistances[K+1];
    realDistances[0] = distances[0];
    for (int i = 1; i < K; i++) {
        realDistances[i] = distances[i] - distances[i-1];
    }
    realDistances[K] = D - distances[K-1];
    qsort(realDistances, K + 1, sizeof(int), compareDistDesc);

    int start = 0;
    int end = N;
    int answer = -1;
    while(start < end) {
        int mid = (start + end) / 2;
        if (isCapable(cars[mid], realDistances, K, T, mode)) {
            end = mid - 1;
            answer = mid;
        } else {
            start = mid + 1;
        }
    }

    if (answer == -1) {
        printf("-1\n");
    } else {
        int minPrice = cars[answer].price;
        for (int i = answer; i < N; i++) {
            if (cars[i].price < minPrice) {
                minPrice = cars[i].price;
            }
        }
        printf("%d\n", minPrice);
    }
}