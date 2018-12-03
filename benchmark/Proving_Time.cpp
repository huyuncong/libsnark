#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

char ch[200];
double leaf_mnt4, leaf_mnt6, mnt4to6, mnt6to4;

double calc(int epoch)
{
        int height = 0, x = 1;
        for (; x < epoch; x <<=1, height++ ) ;
        double sum = leaf_mnt4*epoch;
        x >>=1;
        for (int i = 1; x; x>>=1, i++) {
                if (i & 1) sum += mnt4to6 * x;
                else sum += mnt6to4 * x;
        }
        return sum;
}

double calc2(int epoch)
{
        int height = 0, x = 1;
        for (; x < epoch; x <<=1, height++ ) ;
        double sum = leaf_mnt6*epoch;
        x >>=1;
        for (int i = 1; x; x>>=1, i++) {
                if (!(i & 1)) sum += mnt4to6 * x;
                else sum += mnt6to4 * x;
        }
        return sum;
}

int main()
{
        FILE* inp = fopen("Proving_Time_Input.txt", "r");
//        FILE* out = fopen("KeyGen_Time_Output.txt", "w");

        fscanf(inp, "%s%lf", ch, &leaf_mnt4);
        fscanf(inp, "%s%lf", ch, &leaf_mnt6);
        fscanf(inp, "%s%lf", ch, &mnt4to6);
        fscanf(inp, "%s%lf", ch, &mnt6to4);

        for (;; ) {
                int epoch;
                printf("Number of Epoch:");
                scanf("%d", &epoch);
                if (epoch == 0) break;
                printf("%f\n", min(calc(epoch), calc2(epoch)));
        }
        return 0;
}
