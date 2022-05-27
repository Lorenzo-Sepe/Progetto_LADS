#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *f = fopen("graph_input.txt", "r");
    if (f == NULL) {
        exit(EXIT_FAILURE);
    }

    int nver;
    if (fscanf(f, "%d", &nver) == 1) {
        for (int i = 0; i < nver; ++i) {
            // Read a list of vertices and dump it on stdout with commas
            int res;
            do {
                int idx;
                res = fscanf(f, "%d%*[ ]", &idx);
                if (res != 1) {
                    break;
                }
                printf("%d, ", idx);
                char newline[2];
                res = fscanf(f, "%[\n]", newline);
            } while (res == 0);
            if (res == -1) {
                printf("EOF found\n");
                break;
            }
            if (res == 0) {
                printf(" failed to read integer value\n");
                break;
            }
            if (res == 1) {
                printf("newline found\n");
            }
        }
    }

    fclose(f);
    exit(EXIT_SUCCESS);
//system("PAUSE");
}