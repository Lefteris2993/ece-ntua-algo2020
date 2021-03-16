#include <stdio.h>
#include <vector>

struct bundle {
    int quantity;
    int price;
    bundle(int q, int p) : quantity(q), price(p) {}
};

class merchant {
    public:
        std::vector<bundle> typeA, typeB, typeC;

        void addBundle(char t, int q, int p) {
            switch (t) {
                case 'A':
                    typeA.push_back(bundle(q, p));
                    break;
                case 'B':
                    typeB.push_back(bundle(q, p));
                    break;
                case 'C':
                    typeC.push_back(bundle(q, p));
                    break;
                default :
                    printf("WTF\n");
            }
        }

        merchant() {};
        ~merchant() {};
};

int minTypeCosts (std::vector<bundle>* bundles, int* cost, int N) { //return max valid idex for *cost
    for (int i = 0; i < N+1; i++) {
        cost[i] = __INT_MAX__;
    }
    cost[0] = 0;

    int count = 0;
    for (int i = 0; i < (*bundles).size(); i++) {
        int q = (*bundles)[i].quantity;
        int p = (*bundles)[i].price;

        count += q;

        for (int j = std::min(count, N); j > 0; j--) {
            cost[j] = std::min(cost[j], cost[std::max(j-q, 0)] + p);
        }
    }
    return std::min(count, N);    
}


int minCosts(merchant* merch, int* cost, int N) { //return max valid index for *cost
    int A[N+1], B[N+1], C[N+1];
    int Anum = minTypeCosts(&((*merch).typeA), A, N+1);
    int Bnum = minTypeCosts(&((*merch).typeB), B, N+1);
    int Cnum = minTypeCosts(&((*merch).typeC), C, N+1);

    int sets = std::min(std::min(Anum, Bnum), std::min(Bnum, Cnum));

    for (int i = 0; i < std::min(sets + 1, N+1); i++) {
        cost[i] = A[i] + B[i] + C[i];
    }

    return std::min(sets + 1, N+1);
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    
    merchant merchant_1, merchant_2, merchant_3;

    while(getchar() != '\n'); 
    for (int i = 0; i < M; i++) {
        char m = getchar();
        char type = getchar();
        int q, p;
        scanf("%d %d", &q, &p);

        switch (m)
        {
            case '1':
                merchant_1.addBundle(type, q, p);
                break;
            case '2':
                merchant_2.addBundle(type, q, p);
                break;
            case '3':
                merchant_3.addBundle(type, q, p);
                break;
            default:
                printf("WTF\n");
                return 42;
        }

        while(getchar() != '\n'); 
    }

    int cost_1[N+1], cost_2[N+1], cost_3[N+1];

    int m1 = minCosts(&merchant_1, cost_1, N);
    int m2 = minCosts(&merchant_2, cost_2, N);
    int m3 = minCosts(&merchant_3, cost_3, N);

    int result = __INT_MAX__;
	for(int i1 = 0; i1 < m1; i1++)
		for(int i2 = 0; i2 < m2; i2++)
			for(int i3 = std::max(0, N - i1 - i2); i3 < m3; i3++) {
				if(i1 + i2 + i3 >= N)
					result = std::min(result, cost_1[i1] + cost_2[i2] + cost_3[i3]);
			}

	if (result==__INT_MAX__)
		printf("-1\n");
	else
		printf("%d\n", result);
	return 0;    
}
