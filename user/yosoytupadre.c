#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void) {
    printf("Proceso hijo:  %d\n", getpid());
    printf("Proceso padre: %d\n", getppid());
    printf("Proceso actual: %d\n", getancestor(0));
    printf("Proceso padre: %d\n", getancestor(1));
    printf("Proceso abuelo: %d\n", getancestor(2));
    printf("Proceso bisabuelo: %d\n", getancestor(3));
    exit(0);
}