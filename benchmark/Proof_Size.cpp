#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

char ch[200];
//double leaf_mnt4, leaf_mnt6, mnt4to6, mnt6to4;
long long mnt4_size, mnt6_size, max_records, input_size;
long long proof_size[2], primary_input_size[2];

long long divide(long long L, long long R, long long l, long long r)
{
        if (L == R){
		return proof_size[0]+primary_input_size[0];
	}
	
	if (l <= L && R <= r){
		long long gap = R - L + 1;

		long long log2_gap = round(log2(gap));

		int e = 0;
		if(log2_gap & 1 == 0){
			e = 0;
		}else{
			e = 1;
		}

		return proof_size[e] + primary_input_size[e];
	}
	
	if (R < l || L > r) return 0;

        long long Mid = (L + R) / 2;
        long long sum = 0;
        if (!(Mid < l || L > r)) sum += divide(L, Mid, l, r);
        if (!(R < l || Mid+1 > r)) sum += divide(Mid + 1, R, l, r);
        return sum;
}

long long calc(int epoch)
{
        long long sum = divide(1, max_records, 42300 - epoch + 1, 43200);
        return sum;
}

int main()
{
        FILE* inp = fopen("Proof_Size_Input.txt", "r");
//        FILE* out = fopen("KeyGen_Time_Output.txt", "w");
        fscanf(inp, "%s%lld", ch, &max_records);
        fscanf(inp, "%s%lld", ch, &mnt4_size);
        fscanf(inp, "%s%lld", ch, &mnt6_size);
        fscanf(inp, "%s%lld", ch, &input_size);
//        fscanf(inp, "%s%lf", ch, &mnt4to6);
//        fscanf(inp, "%s%lf", ch, &mnt6to4);

        proof_size[0] = mnt4_size;
        proof_size[1] = mnt6_size;
        primary_input_size[0] = input_size;
        primary_input_size[1] = input_size;
 
//	for (;; ) {
//                int epoch;
//                printf("Number of Records:");
//                scanf("%d", &epoch);
//                if (epoch == 0) break;
//                printf("%lld\n", calc(epoch));
//      }

	// six months
	int epoch = 1;
	printf("six months: %lld\n", calc(epoch));

	// one month
	epoch = 43200 - 30 * 24 * 10;
	printf("one month: %lld\n", calc(epoch));

	// two weeks
	epoch = 43200 - 14 * 24 * 10;
	printf("two weeks: %lld\n", calc(epoch));

	// one week
	epoch = 43200 - 7 * 24 * 10;
	printf("one week: %lld\n", calc(epoch));

	// one day
	epoch = 43200 - 24 * 10;
	printf("one day: %lld\n", calc(epoch));

	return 0;
}
