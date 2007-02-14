void add_entry(char *name, void *xt, void *class);
void name_quote();
void name_macro();
void name_data();
void find_word();
void return_quote();

typedef struct {
  Inst xt;
  Inst class;
  char name[128];
} ENTRY;

