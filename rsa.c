#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

unsigned long int *RSA_factors(unsigned long int n, time_t start, time_t stop)
{
	unsigned long int *factors;
	unsigned long int f1 = (unsigned long int)sqrt(n), f2 = f1;

	factors = malloc(2 * sizeof(unsigned long int));
	if (factors == NULL)
		exit(EXIT_FAILURE);
	while (f1 * f2 != n)
	{
		while(f1 * f2 < n)
			f2++;
		if (f1 * f2 != n)
		{
			f2--;
			f1--;
		}
		stop = time(NULL);
		if (stop - start > 5)
		{
			free(factors);
			exit(EXIT_FAILURE);
		}
	}
	factors[0] = f1;
	factors[1] = f2;
	return (factors);
}

int main(int argc, char **argv)
{
	FILE *test;
	size_t buffer_len = 0;
	char *buffer = NULL;
	char *buffUL = NULL;
	unsigned long int N, *factors;
	time_t start, stop;

	test = fopen(argv[1], "r");
	if (test == NULL)
		exit(EXIT_FAILURE);
	start = time(NULL);
	while (getline(&buffer, &buffer_len, test) != EOF)
	{
		if (buffer != NULL)
		{
			N = strtoul(buffer, &buffUL, 10);
			factors = RSA_factors(N, start, stop);
			printf("%lu=%lu*%lu\n", N, factors[1], factors[0]);
			free(buffer);
			buffer = NULL;
			free(factors);
			factors = NULL;
		}
	}
	free(buffer);
	buffer = NULL;
	buffUL = NULL;
	fclose(test);
	return (0);
}
