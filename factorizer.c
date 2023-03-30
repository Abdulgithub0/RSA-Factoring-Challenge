#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>

int main(int argc, char **argv)
{
    char *end, *buffer;
    ssize_t total_read;
    size_t buf_len;

    if (argc != 2)
        return (0);
    FILE *fptr = fopen(argv[1], "r");

    buffer = NULL;
    buf_len = 0;
    mpz_t nump, i, j, result;
    mpz_init(nump);
    mpz_init(result);
    mpz_init(i);
    mpz_init(j);

    while (fscanf(fptr, "%ms", &buffer) == 1)
    {
        int line_length = strlen(buffer);
        if (line_length > 0 && buffer[line_length - 1] == '\n') {
            buffer[line_length - 1] = '\0';
        }

        unsigned long long int num = strtoull(buffer, &end, 10);
        if (buffer != end)
        {
            mpz_set_str(nump, buffer, 10);
            mpz_set_ui(i, 1);
            mpz_set_str(j, buffer, 10);

            // Use a larger factor limit for larger numbers
            mpz_t factor_limit;
            mpz_init(factor_limit);
            if (mpz_cmp(nump, "100000000000000000000000000") > 0) {
                mpz_set_ui(factor_limit, 1000000);
            } else {
                mpz_set_ui(factor_limit, 50000);
            }

            for (; mpz_cmp(i, factor_limit) <= 0; mpz_add_ui(i, i, 1), mpz_sub_ui(j, j, 1))
            {
                mpz_mul(result, i, j);
                if (mpz_cmp(result, nump) == 0)
                {
                    gmp_printf("%Zd=%Zd*%Zd\n", nump, j, i);
                    break;
                }
            }

            mpz_clear(factor_limit);
        }
        else
        {
            unsigned long long int numi, numj;
            numj = num;
            numi = 1;

            // Use a larger factor limit for larger numbers
            unsigned long long int factor_limit;
            if (num > 100000000000000000000000000ull) {
                factor_limit = 1000000ull;
            } else {
                factor_limit = 50000ull;
            }

            for (; numi <= factor_limit; numi++, numj--)
            {
                if ((numi * numj) == num)
                {
                    printf("%llu=%llu*%llu\n", num, numj, numi);
                    break;
                }
            }
        }
        free(buffer);
        buffer = NULL;
    }

    mpz_clear(nump);
    mpz_clear(i);
    mpz_clear(j);
    mpz_clear(result);
    fclose(fptr);
    return (0);
}
