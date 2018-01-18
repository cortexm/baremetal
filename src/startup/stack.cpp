// stack definition code

// top of stack
extern unsigned _stacktop;

// initial stack pointer is first address of program
__attribute__((section(".stack"), used)) unsigned *stack_init = &_stacktop;
