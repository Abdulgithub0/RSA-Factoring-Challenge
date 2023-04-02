#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gmp.h>

/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 *
 * Description - The factorization algorithm used called Pollard's rho.
 * return
 */

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
            mpz_set_ui(i, 2);
            while (mpz_cmp_ui(i, 100000000) < 0)
            {
                if (mpz_divisible_ui_p(nump, mpz_get_ui(i)))
                {
                    mpz_divexact_ui(j, nump, mpz_get_ui(i));
                    gmp_printf("%Zd=%Zd*%Zd\n", nump, j, i);
                    break;
                }
                mpz_add_ui(i, i, 1);
            }
        }
        else
        {
            unsigned long long int numi, numj;
            numj = num;
            numi = 2;
            while (numi <= 100000000)
            {
                if ((num % numi) == 0)
                {
                    printf("%llu=%llu*%llu\n", num, num / numi, numi);
                    break;
                }
                numi++;
            }
	    /*
            if (numi > 100000000)
            {
                will added 1 more zero to 100000000 then.
            }*/
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
