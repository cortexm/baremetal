// stack definition code

// top of stack
extern unsigned __stacktop;

// initial stack pointer is first address of program
__attribute__((section(".stack"), used)) unsigned *__stack_init = &__stacktop;
