#include <stdlib.h>
#include <stdio.h>
#include "wren.h"

void writeFnWrapper(WrenVM* vm, const char* text)
{
    printf("%s", text);
}

void errorFnWrapper(WrenVM* vm, WrenErrorType type, const char* module, int line, const char* message)
{
    switch (type)
    {
        case WREN_ERROR_COMPILE:
            fprintf(stderr, "compile time error: %s:%d:%s\n",
                    module, line, message);
            break;
        case WREN_ERROR_RUNTIME:
            fprintf(stderr, "runtime error: %s\n", message);
            break;
        case WREN_ERROR_STACK_TRACE:
            fprintf(stderr, "stack trace: %s:%d:%s\n", module, line, message);
            break;
    }
}

int main(int argc, char **argv)
{
    printf("%s\n", "hello world");

    WrenConfiguration config;
    wrenInitConfiguration(&config);
    config.writeFn = writeFnWrapper;
    config.errorFn = errorFnWrapper;
    WrenVM* vm = wrenNewVM(&config);

    WrenInterpretResult result = wrenInterpret(vm, "System.print(\"hello wren vm\")");

    printf("%s", "wrenInterpret(): ");
    switch (result)
    {
        case WREN_RESULT_SUCCESS:
            printf("successful\n");
            break;
        case WREN_RESULT_COMPILE_ERROR:
            printf("compile error\n");
            break;
        case WREN_RESULT_RUNTIME_ERROR:
            printf("runtime error\n");
            break;
    }

    wrenFreeVM(vm);
    return 0;
}
