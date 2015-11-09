This list is also in doc/GLOSSARY and is rebuilt by TokaDoc before checkins to the SVN repository are done. When in doubt, check your local copy first as it may be slightly more up to date. Also see WordListBootstrap for the other words and data structures that are provided by the core Toka language.

```
<<       ( ab-c )    Shift 'b' left by 'a' bits
>>       ( ab-c )    Shift 'b' right by 'a' bits
and      ( ab-c )    Perform a bitwise AND
or       ( ab-c )    Perform a bitwise OR
xor      ( ab-c )    Perform a bitwise XOR
#args    (  -n )     Return the number of arguments
arglist  (  -a )     Return a pointer to the 
                     argument list.
<        ( ab-f )    Compare 'a' and 'b', return
                     a flag
>        ( ab-f )    Compare 'a' and 'b', return
                     a flag
=        ( ab-f )    Compare 'a' and 'b', return
                     a flag
<>       ( ab-f )    Compare 'a' and 'b', return
                     a flag
.        ( n- )      Display the TOS
emit     ( c- )      Display the ASCII character
                     for TOS
type     ( a- )      Display a string
bye      ( - )       Quit Toka
#        ( n- )      Push the following cell to
                     the stack.
@        ( a-n )     Fetch the value in memory
                     location 'a'
!        ( na- )     Store 'n' to memory location
                     'a'
c@        ( a-n )    Fetch a byte from memory
                     location 'a'
c!        ( na- )    Store byte 'n' to memory
                     location 'a'
copy     ( sdc- )    Copy 'c' bytes from 's' to
                     'd'
cell-size ( -n )     Return the size of a cell
char-size ( -n )     Return the size of a char
:words   ( - )       Display a list of all named
                     quotes and data
:stack   ( - )       Display all values on the
                     data stack
:gc      (  -  )     Display information about
                     the garbage collection list
:see     (  "- )     Decompile the specified quote
is       ( a"- )     Attach a name to a quote
         ( a$- )     Non-parsing form
is-super ( a"- )     Attach a name to a quote
         ( a$- )     Non-parsing form
is-macro ( a"- )     Attach a name to a quote
         ( a$- )     Non-parsing form
is-data  ( a"- )     Attach a name to data memory
         ( a$- )     Non-parsing form
\        ( "-a )     Return a quote corresponding
                     to the specified word.
         ( $-a )     Non-parsing form
from     ( "- )      Set the library to import from
         ( $- )      Non-parsing form
import   ( n"- )     Import a function taking 'n'
                     arguments.
         ( n$- )     Non-parsing form
as       ( "- )      Rename the last defined word
         ( $-  )     Non-parsing form
file.open  ( $m-n )  Open a specified file with
                     the specified mode.
file.close ( n- )    Close the specified file handle
file.read  ( nbl-r ) Read 'l' bytes into buffer 'b'
                     from file handle 'n'. Returns
                     the number of bytes read.
file.write ( nbl-w ) Write 'l' bytes from buffer 'b'
                     to file handle 'n'. Returns
                     the number of bytes written.
file.size  ( n-s )   Return the size (in bytes)
                     of the specified file.
file.seek  ( nom-a ) Seek a new position in the
                     file. Valid modes are
                     START, CURRENT, and END. These
                     have values of 1, 2, and 3.
file.pos   ( n-a )   Return a pointer to the current
                     offset into the file.
keep     ( a-a )     Mark quotes/allocated memory
                     as permanent.
gc       ( - )       Clean the garbage
malloc   ( n-a )     Allocate 'n' bytes of memory
heap     ( -a )      Variable pointing to the top
                     of the local heap
compiler ( -a )      Variable holding the compiler
                     state
count    ( a-ac )    Return an address/count pair
                     for a string
+        ( ab-c )    Add TOS and NOS
-        ( ab-c )    Subtract TOS from NOS
*        ( ab-c )    Multiply TOS by NOS
/mod     ( ab-cd )   Divide and get remainder
base     ( -a )      Variable containg the current
                     numeric base
parser   ( -a )      Variable holding current parser
                     mode.
>number  ( a-nf )    Attempt to convert a string
                     to a number
parse    ( d-a )     Parse until the character 
                     represented by 'd' is found.
                     Return a pointer to the string
include   ( "- )     Attempt to open a file and
                     add it to the input stack.
          ( $- )     Non-parsing form
needs     ( "- )     Attempt to include a file
                     from the library (normally
                     /usr/share/toka/library)
          ( $- )     Non-parsing form
[        ( -a )      Create a new quote
]        ( - )       Close an open quote
invoke   ( a- )      Execute a quote
iterate  ( na- )     Execute a quote 'n' times
+iterate ( na- )     Execute a quote 'n' times
t/f      ( fab- )    Invoke 'a' if 'f' flag is
                     true, 'b' if false.
recurse  ( - )       Compile a call to the top
                     quote.
i        ( -n )      Return the current loop index
while    ( a- )      Execute quote. If the quote
                     returns TRUE, execute again.
                     otherwise end the cycle.
dup      ( n-nn )    Duplicate the TOS
drop     ( n- )      Drop the TOS
swap     ( ab-ba )   Exchange the TOS and NOS
>r       ( n- )      Push TOS to return stack, DROP
r>       ( -n )      Pop TORS to the data stack
depth    ( -n )      Return the number of items
                     on the stack
```