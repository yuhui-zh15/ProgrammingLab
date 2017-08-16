#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>

using namespace std;

int n = 1000000;

int main()
{
	srand(time(0));
	printf("%d\n", n);
	for (int i = 1; i < n; i++) printf("%d ", rand() % 100000);
	printf("50000");
	printf("\n");
	return 0;
}
