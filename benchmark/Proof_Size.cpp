#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

char ch[200];
//double leaf_mnt4, leaf_mnt6, mnt4to6, mnt6to4;
long long mnt4_size, mnt6_size, max_records, input4_size, input6_size;
long long proof_size[2], primary_input_size[2];

long long divide(long long L, long long R, long long l, long long r, long long e)
{
        if (L == R) return proof_size[e]+primary_input_size[e];
        if (l <= L && R <= r) return proof_size[e]+primary_input_size[e];
        if (R < l || L > r) return 0;

        long long Mid = (L + R) / 2;
        long long sum = 0;
        if (!(Mid < l || L > r)) sum += divide(L, Mid, l, r, e ^ 1);
        if (!(R < l || Mid+1 > r)) sum += divide(Mid + 1, R, l, r, e ^ 1);
        return sum;
}

long long calc(int epoch)
{
        long long sum = divide(1, max_records, max_records - epoch + 1, max_records, 0);
        sum = min(sum, divide(1, max_records, max_records - epoch + 1, max_records, 1));
        return sum;
}

int main()
{
        FILE* inp = fopen("Proof_Size_Input.txt", "r");
//        FILE* out = fopen("KeyGen_Time_Output.txt", "w");
        fscanf(inp, "%s%lld", ch, &max_records);
        fscanf(inp, "%s%lld", ch, &mnt4_size);
        fscanf(inp, "%s%lld", ch, &mnt6_size);
        fscanf(inp, "%s%lld", ch, &input4_size);
        fscanf(inp, "%s%lld", ch, &input6_size);
//        fscanf(inp, "%s%lf", ch, &mnt4to6);
//        fscanf(inp, "%s%lf", ch, &mnt6to4);

        proof_size[0] = mnt4_size;
        proof_size[1] = mnt6_size;
        primary_input_size[0] = input4_size;
        primary_input_size[1] = input6_size;
        for (;; ) {
                int epoch;
                printf("Number of Records:");
                scanf("%d", &epoch);
                if (epoch == 0) break;
                printf("%lld\n", calc(epoch));
        }
        return 0;
}
