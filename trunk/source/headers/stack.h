#define TOS stack[sp]
#define NOS stack[sp-1]
#define TORS rstack[rsp]
#define NORS rstack[rsp-1]
#define DROP sp--

void stack_dup();
void stack_drop();
void stack_swap();

void stack_to_r();
void stack_from_r();

void stack_depth();
