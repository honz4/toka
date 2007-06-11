: | 10 parse 2drop ;

|
| Toka in gForth
|
| This is a long-term project, to aid in implementing
| Toka on PalmOS based devices (via Quartus) and perhaps
| other systems without GCC.
|
| Once loaded, the underlying Forth language will be suppressed,
| leaving only Toka visible.
|
| Todo:
|  - Finish core primitives
|  - Garbage Collector (fill in empty stubs)
|  - Actual support for 'parser' state variable
|  - Command line arguments (as a Toka style array)
| ------------------------------------------------------------

require lib.fs
[IFUNDEF] libc  library libc libc.so.6  [THEN]

1 (int) libc malloc malloc
2 (addr) libc strcpy strcpy
1 (int) libc strlen strlen


: c-string ( addr u -- addr' )
    tuck pad swap move pad + 0 swap c! pad ;

variable USED
1024 USED !
variable ROOT
128 cells constant QUOTE-SIZE

: remaining dictionary-end here - USED @ - ;
: malloc allocate drop ;


|
| Cell and Character Sizing
| Just to be safe, using 64-bit sizing for cells.
|
8 constant cell-size
1 constant char-size


|
| Quotes
| gForth is kind of hairy in this. This bit of
| code will need a fair amount of tweaking to
| adapt to other Forths.
|
: [ here state @
    remaining here + dp !
    QUOTE-SIZE USED +!
    noname :
; immediate
: ] postpone ;
    state ! dp !
    lastxt state @ if postpone literal ] then
; immediate

|
| Naming of quotes and data
|
: is create , does> @ execute ;
: is-macro create , immediate does> @ execute ;
: is-data create , does> @ ;


|
| Map in (and rename where necessary) 
| Forth words. These are words that work
| the same in Forth and Toka.
| 
[ execute ] is invoke
[ + ] is +
[ - ] is -
[ * ] is *
[ /mod ] is /mod
[ @ ] is @
[ ! ] is !
[ c@ ] is c@
[ c! ] is c!
[ lshift ] is <<
[ rshift ] is >>
[ and ] is and
[ or ] is or
[ xor ] is xor
[ emit ] is emit
[ . ] is .
[ <> ] is <>
[ = ] is =
[ < ] is <
[ > ] is >
[ swap ] is swap
[ drop ] is drop
[ dup ] is dup
[ words ] is :names
[ .s ] is :stack
[ bye ] is bye
[ include ] is include
[ ' state @ if postpone literal then ] is-macro `
[ postpone literal ] is #
[ compile, ] is compile
[ depth ] is depth
[ state ] is compiler
[ base  ] is base
[ dp    ] is heap
[ last  ] is last


|
| Useful constants
|
[ -1 ] is TRUE
[  0 ] is FALSE


|
| Some things (such as 'parse', '>number', 'type', etc
| need to return/use zero terminated strings for Toka
| to operate properly. This wraps the Forth versions with
| the necessary code to emulate Toka behaviour.
|
[ parse
  dup 1+ malloc >r
  c-string
  r@ swap strcpy drop
  r>
] is parse
[ dup strlen 1+ ] is count
[ count 1- type ] is type
[ count 1- >number ] is >number


|
| Recently completed
|
variable i
[ rot TRUE = if drop invoke else nip invoke then ] is ifTrueFalse
[ swap 1- for r@ 1+ i ! >r r@ invoke r> next drop ] is iterate
[ swap 1 do r@ i ! >r r@ invoke r> loop drop ] is +iterate
[ begin >r r@ invoke TRUE <> if r> drop exit then r> again ] is whileTrue
[ begin >r r@ invoke FALSE <> if r> drop exit then r> again ] is whileFalse
[ ROOT @ compile ] is-macro recurse
[ i @ ] is i


|
| Stubs and Incomplete or Buggy
|
[ ] is #args
[ ] is arglist
[ ] is end.
[ ] is needs
[ ] is gc
[ ] is :gc
[ ] is keep
[ ] is :see
[ ] is file.open
[ ] is file.close
[ ] is file.write
[ ] is file.read
[ ] is file.size
[ ] is file.seek

variable escape-sequences  escape-sequences off
variable parser  parser on

cr cr
include bootstrap.toka
