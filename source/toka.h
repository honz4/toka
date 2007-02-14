/******************************************************
 * Toka
 *
 * Common include for all modules
 ******************************************************/

#define FALSE 0
#define TRUE -1
#define ON   -1
#define OFF   0

typedef void (*Inst)();

#include "headers/config.h"

#include "headers/bits.h"
#include "headers/class.h"
#include "headers/cmdline.h"
#include "headers/conditionals.h"
#include "headers/console.h"
#include "headers/data.h"
#include "headers/debug.h"
#include "headers/decompile.h"
#include "headers/dictionary.h"
#include "headers/ffi.h"
#include "headers/files.h"
#include "headers/gc.h"
#include "headers/initial.h"
#include "headers/interpret.h"
#include "headers/math.h"
#include "headers/parser.h"
#include "headers/quotes.h"
#include "headers/stack.h"
#include "headers/toka.h"
#include "headers/vm.h"
