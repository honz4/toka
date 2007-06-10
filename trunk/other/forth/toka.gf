#! gforth 
: | 10 parse 2drop ;
|
| Toka in RetroForth
|
| This is a long-term project, to aid in implementing
| Toka on PalmOS based devices (via Quartus) and perhaps
| other systems without GCC.
|
| Once loaded, the underlying Forth language will be suppressed,
| leaving only Toka visible.
|
| Todo:
|  - Loops:
|    -  +iterate
|    -  i
|  - Finish core primitives
|  - Garbage Collector (fill in empty stubs)
|  - Actual support for 'parser' state variable
|  - Command line arguments (as a Toka style array)
| ------------------------------------------------------------


variable ROOT
128 cells constant QUOTE-SIZE

: malloc allocate drop ;

|
| Cell and Character Sizing
| This is easy, since RetroForth is tied to 32-bit
| x86 architecture :)
|
4 constant cell-size
1 constant char-size


|
| Quotes
|
: ] 
  postpone exit
  postpone [ 
  state off swap dp !
; immediate
: [ 
  here 
  QUOTE-SIZE malloc dup dp ! 
  state on 
; immediate
quit
|
| Naming of quotes and data
|
: is create , does> @ execute ;
: is-macro create , postpone immediate does> @ execute ;
: is-data create , does> @ ;

 [ .s ] .s

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
[ << ] is <<
[ >> ] is >>
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
[ :words ] is :names
[ .s ] is :stack
[ bye ] is bye
[ include ] is include
[ ' state @ if postpone literal then ] is-macro `
[ postpone literal ] is #
[ compile ] is compile
[ depth ] is depth
[ file.open ] is file.open
[ file.close ] is file.close
[ file.read ] is file.read
[ file.write ] is file.wrie
[ file.size ] is file.size
[ file.seek ] is file.seek

` state is-data compiler
` base is-data base
` dp is-data heap
` last is-data last

macro
` >r alias >r
` r> alias r>
forth


|
| Allow use of FFI (retro and toka share the same FFI model)
|
[ from ] is from
[ import ] is import


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
[ parse        ( char -- addr len )
  dup >r       ( addr len -- addr len | rs: len )
  over +       ( addr len -- addr addr+len | rs: len )
  0 swap c!    ( addr addr+len -- addr | rs: len )
  r> 1+ malloc ( addr -- addr new-addr )
  dup >r swap  ( addr new-addr -- new-addr addr | rs: new-addr )
  strcpy       ( new-addr addr -- count )
  drop r>      ( count -- new-addr )
] is parse
[ dup strlen 1+ ] is count
[ count 1- type ] is type
[ count 1- >number ] is >number


|
| Recently completed
|
variable i
[ rot TRUE = if drop invoke ;then nip invoke ] is ifTrueFalse
[ swap for r i ! >r r invoke r> next drop ] is iterate
[ repeat >r r invoke TRUE <> if r> drop ;then r> again ] is whileTrue
[ repeat >r r invoke FALSE <> if r> drop ;then r> again ] is whileFalse
[ ROOT @ compile ] is-macro recurse
[ i @ ] is i


|
| Stubs and Incomplete or Buggy
|
[ swap for r i ! >r r invoke r> next drop ] is +iterate
[ ] is #args
[ ] is arglist
[ ] is end.
[ ] is needs
[ ] is gc
[ ] is :gc
[ ] is keep
[ ] is :see
variable escape-sequences  escape-sequences off
variable parser  parser on

` malloc >entry :link 0 swap !

include bootstrap.toka
" Toka (for RetroForth)" type 10 emit
