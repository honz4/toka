/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: initial.c
 *|F|
 *
 * Copyright (C) 2007 Charles R. Childers
 * Distributed under the terms of the MIT/X11 License
 * (see doc/LICENSE for full terms)
 *
 ******************************************************/

#include "toka.h"

extern long base, compiler, last, isp, parser, escapes;
extern Inst *heap;


/******************************************************
 *|F| build_dictionary()
 *|F| Attach names and classes to the various initial
 *|F| words in the Toka language.
 *|F|
 ******************************************************/
void build_dictionary()
{
  /* bits.c */
  add_entry("<<",        &lshift,        &forth_class);
  add_entry(">>",        &rshift,        &forth_class);
  add_entry("and",       &and,           &forth_class);
  add_entry("or",        &or,            &forth_class);
  add_entry("xor",       &xor,           &forth_class);

  /* cmdline.c */
  add_entry("#args",     &num_args,      &forth_class);
  add_entry("arglist",   &get_arg_list,  &forth_class);

  /* conditionals.c */
  add_entry("<",         &less_than,     &forth_class);
  add_entry(">",         &greater_than,  &forth_class);
  add_entry("=",         &equals,        &forth_class);
  add_entry("<>",        &not_equals,    &forth_class);

  /* console.c */
  add_entry(".",         &dot,           &forth_class);
  add_entry("emit",      &emit,          &forth_class);
  add_entry("type",      &type,          &forth_class);
  add_entry("bye",       &bye,           &forth_class);

  /* data.c */
  add_entry("@",         &fetch,         &forth_class);
  add_entry("!",         &store,         &forth_class);
  add_entry("c@",        &fetch_char,    &forth_class);
  add_entry("c!",        &store_char,    &forth_class);
  add_entry("#",         &make_literal,  &forth_class);
  add_entry("copy",      &copy,          &forth_class);
  add_entry("cell-size", &cell_size,     &forth_class);
  add_entry("char-size", &char_size,     &forth_class);

  /* debug.c */
  add_entry(":names",    &names,         &forth_class);
  add_entry(":stack",    &display_stack, &forth_class);
  add_entry(":gc",       &gc_info,       &forth_class);

  /* decompile.c */
  add_entry(":see",      &see,           &forth_class);

  /* dictionary.c */
  add_entry("`",         &return_quote,  &forth_class);
  add_entry("is",        &name_quote,    &forth_class);
  add_entry("is-super",  &name_super,    &forth_class);
  add_entry("is-macro",  &name_macro,    &forth_class);
  add_entry("is-data",   &name_data,     &forth_class);
  add_entry("last",      &last,          &data_class);

  /* ffi.c */
#ifndef NOFFI
  add_entry("from",      &ffi_from,      &forth_class);
  add_entry("import",    &ffi_import,    &forth_class);
  add_entry("as",        &ffi_rename,    &forth_class);
#endif

  /* files.c */
  add_entry("file.open", &file_open,     &forth_class);
  add_entry("file.close",&file_close,    &forth_class);
  add_entry("file.read", &file_read,     &forth_class);
  add_entry("file.write",&file_write,    &forth_class);
  add_entry("file.size", &file_size,     &forth_class);
  add_entry("file.seek", &file_seek,     &forth_class);
  add_entry("file.pos",  &file_pos,      &forth_class);

  /* gc.c */
  add_entry("malloc",    &toka_malloc,   &forth_class);
  add_entry("keep",      &gc_keep,       &forth_class);
  add_entry("gc",        &gc,            &forth_class);

  /* interpret.c */
  add_entry("count",     &count,         &forth_class);
  add_entry("compiler",  &compiler,      &data_class);

  /* math.c */
  add_entry("+",         &add,           &forth_class);
  add_entry("-",         &subtract,      &forth_class);
  add_entry("*",         &multiply,      &forth_class);
  add_entry("/mod",      &divmod,        &forth_class);

  /* parser.c */
  add_entry("parse",     &parse,         &forth_class);
  add_entry(">number",   &to_number,     &forth_class);
  add_entry("include",   &include,       &forth_class);
  add_entry("needs",     &needs,         &forth_class);
  add_entry("end.",      &force_eof,     &forth_class);
  add_entry("base",      &base,          &data_class);
  add_entry("parser",    &parser,        &data_class);
  add_entry("escape-sequences",&escapes, &data_class);

  /* quotes.c */
  add_entry("[",         &begin_quote,   &self_class);
  add_entry("]",         &end_quote,     &self_class);
  add_entry("recurse",   &recurse,       &self_class);
  add_entry("invoke",    &invoke,        &forth_class);
  add_entry("iterate",   &iterate,       &forth_class);
  add_entry("+iterate",  &alt_iterate,   &forth_class);
  add_entry("i",         &quote_index,   &forth_class);
  add_entry("t/f",       &truefalse,     &forth_class);
  add_entry("whileTrue",  &quote_while_true,  &forth_class);
  add_entry("whileFalse", &quote_while_false, &forth_class);

  /* stack.c */
  add_entry("dup",       &stack_dup,     &forth_class);
  add_entry("drop",      &stack_drop,    &forth_class);
  add_entry("swap",      &stack_swap,    &forth_class);
  add_entry(">r",        &stack_to_r,    &forth_class);
  add_entry("r>",        &stack_from_r,  &forth_class);
  add_entry("depth",     &stack_depth,   &forth_class);

  /* vm.c */
  add_entry("heap",      &heap,          &data_class);
}
