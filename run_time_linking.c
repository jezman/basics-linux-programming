#include <stdio.h>
#include <stddef.h>
#include <dlfcn.h>
#include <stdlib.h>

int (*someSecretFunctionPrototype)(int);

int init_lib(const char *library, const char *function)
{
    void *hdl = dlopen(library, RTLD_LAZY);

    if (NULL == hdl)
        return 0;

    someSecretFunctionPrototype = (int (*)(int))dlsym(hdl, function);

    if (NULL == someSecretFunctionPrototype)
        return 0;

    return 1;
}

int main(int argc, char *argv[])
{
    char *libName = argv[1];
    char *funcName = argv[2];

    if (init_lib(libName, funcName))
    {
        printf("%d\n", someSecretFunctionPrototype(atoi(argv[3])));
    }
    else {
        printf("library was not loaded.\n");
    }

    return 0;
}
