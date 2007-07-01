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

extern long base, compiler, last, isp, parser, escapes, prompt;
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
  add_entry("<<",        &lshift,        &word_class);
  add_entry(">>",        &rshift,        &word_class);
  add_entry("and",       &and,           &word_class);
  add_entry("or",        &or,            &word_class);
  add_entry("xor",       &xor,           &word_class);

  /* cmdline.c */
  add_entry("#args",     &num_args,      &word_class);
  add_entry("arglist",   &get_arg_list,  &word_class);

  /* conditionals.c */
  add_entry("<",         &less_than,     &word_class);
  add_entry(">",         &greater_than,  &word_class);
  add_entry("=",         &equals,        &word_class);
  add_entry("<>",        &not_equals,    &word_class);

  /* console.c */
  add_entry(".",         &dot,           &word_class);
  add_entry("emit",      &emit,          &word_class);
  add_entry("type",      &type,          &word_class);
  add_entry("bye",       &bye,           &word_class);

  /* data.c */
  add_entry("@",         &fetch,         &word_class);
  add_entry("!",         &store,         &word_class);
  add_entry("c@",        &fetch_char,    &word_class);
  add_entry("c!",        &store_char,    &word_class);
  add_entry("#",         &make_literal,  &word_class);
  add_entry("$#",        &make_string_literal,&word_class);
  add_entry("copy",      &copy,          &word_class);
  add_entry("cell-size", &cell_size,     &word_class);
  add_entry("char-size", &char_size,     &word_class);

  /* debug.c */
  add_entry(":stack",    &display_stack, &word_class);
  add_entry(":stat",     &vm_info,       &word_class);

  /* decompile.c */
  add_entry(":see",      &see,           &word_class);

  /* dictionary.c */
  add_entry("`",         &return_quote,  &macro_class);
  add_entry(":name",     &return_name,   &word_class);
  add_entry(":xt",       &return_xt,     &word_class);
  add_entry(":class",    &return_class,  &word_class);
  add_entry("is",        &name_quote,    &word_class);
  add_entry("is-macro",  &name_macro,    &word_class);
  add_entry("is-data",   &name_data,     &word_class);
  add_entry("last",      &last,          &data_class);

  /* ffi.c */
#ifndef NOFFI
  add_entry("from",      &ffi_from,      &word_class);
  add_entry("import",    &ffi_import,    &word_class);
  add_entry("as",        &ffi_rename,    &word_class);
#endif

  /* files.c */
  add_entry("file.open", &file_open,     &word_class);
  add_entry("file.close",&file_close,    &word_class);
  add_entry("file.read", &file_read,     &word_class);
  add_entry("file.write",&file_write,    &word_class);
  add_entry("file.size", &file_size,     &word_class);
  add_entry("file.seek", &file_seek,     &word_class);
  add_entry("file.pos",  &file_pos,      &word_class);

  /* gc.c */
  add_entry("malloc",    &toka_malloc,   &word_class);
  add_entry("keep",      &gc_keep,       &word_class);
  add_entry("gc",        &gc,            &word_class);

  /* interpret.c */
  add_entry("count",     &count,         &word_class);
  add_entry("compiler",  &compiler,      &data_class);

  /* math.c */
  add_entry("+",         &add,           &word_class);
  add_entry("-",         &subtract,      &word_class);
  add_entry("*",         &multiply,      &word_class);
  add_entry("/mod",      &divmod,        &word_class);

  /* parser.c */
  add_entry("parse",     &parse,         &word_class);
  add_entry(">number",   &to_number,     &word_class);
  add_entry("include",   &include,       &word_class);
  add_entry("needs",     &needs,         &word_class);
  add_entry("end.",      &force_eof,     &word_class);
  add_entry("base",      &base,          &data_class);
  add_entry("parser",    &parser,        &data_class);
  add_entry("escape-sequences",&escapes, &data_class);

  /* prompt.c */
  add_entry("prompt",    &prompt,        &data_class);

  /* quotes.c */
  add_entry("[",         &begin_quote,   &macro_class);
  add_entry("]",         &end_quote,     &macro_class);
  add_entry("recurse",   &recurse,       &macro_class);
  add_entry("invoke",    &invoke,        &word_class);
  add_entry("compile",   &compile,       &word_class);
  add_entry("iterate",   &iterate,       &word_class);
  add_entry("+iterate",  &alt_iterate,   &word_class);
  add_entry("i",         &quote_index,   &word_class);
  add_entry("ifTrueFalse",&truefalse,    &word_class);
  add_entry("whileTrue",  &quote_while_true,  &word_class);
  add_entry("whileFalse", &quote_while_false, &word_class);

  /* stack.c */
  add_entry("dup",       &stack_dup,     &word_class);
  add_entry("drop",      &stack_drop,    &word_class);
  add_entry("swap",      &stack_swap,    &word_class);
  add_entry(">r",        &stack_to_r,    &word_class);
  add_entry("r>",        &stack_from_r,  &word_class);
  add_entry("depth",     &stack_depth,   &word_class);

  /* vm.c */
  add_entry("heap",      &heap,          &data_class);
}
