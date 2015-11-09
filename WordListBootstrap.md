This is a list of words provided by the standard Toka bootstrap. You may also want to look at WordListPrimitives for the core words used to build these.

## Arrays ##
| put-char-element | nia- | Store a character (/n/) into array /a/ at index /i/. |
|:-----------------|:-----|:-----------------------------------------------------|
| get-char-element | ia-n | Read a character (/n/) from array /a/ at index /i/.  |
| put-element      | nia- | Store a value (/n/) into array /a/ at index /i/.     |
| get-element      | ia-n | Read a value from array /a/ at index /i/.            |
| is-array         | n"-  | Create a new array of /n/ size.                      |


## Files ##
| file.slurp | $-a | Open a file (name passed by _$_) and read it into a dynamically allocated buffer (_a_). The file is then closed. |
|:-----------|:----|:-----------------------------------------------------------------------------------------------------------------|
| "R"        | -n  | Open text file for reading. The stream is positioned at the beginning of the file.                               |
| "R+"       | -n  | Open for reading and writing. The stream is positioned at the beginning of the file.                             |
| "W"        | -n  | Open for reading and writing. The stream is positioned at the beginning of the file.                             |
| "W+"       | -n  | Open for reading and writing. The file is created if it does not exist, otherwise it is truncated. The stream is positioned at the beginning of the file. |
| "A"        | -n  | Open for appending (writing at end of file). The file is created if it does not exist. The stream is positioned at the end of the file. |
| "A+"       | -n  | Open for reading and appending (writing at end of file). The file is created if it does not exist. The initial file position for reading is at the beginning of the file, but output is always appended to the end of the file. |
| START      | -n  | For use with _file.setpos_. Seek from beginning of a file.                                                       |
| CURRENT    | -n  | For use with _file.setpos_. Seek from current offset in a file.                                                  |
| END        | -n  | For use with _file.setpos_. Seek from end of a file.                                                             |


## Stack ##
| reset | ...- | |
|:------|:-----|:|
| 2drop | nn-  | |
| 2dup  | xy-xyxy | |
| tuck  | xy-yxy | |
| over  | xy-xyx | |
| -rot  |      | |
| rot   |      | |
| nip   | xy-y | |
| r@    | -r   | Fetch a copy of the TORS to the TOS |


## Math ##
| not | x-y | |
|:----|:----|:|
| mod | xy-z | |
| /   | xy-z | |
| negate | x-y | |
| 1-  | x-y | |
| 1+  | x-y | |
| **/**| abc-d | |


## Conditionals ##
| false? | nq- | |
|:-------|:----|:|
| true?  | nq- | |
| TRUE   | -n  | |
| FALSE  | -n  | |


## Constants ##
| TAB | -n | Return the ASCII value for a tab character (9) |
|:----|:---|:-----------------------------------------------|
| ESC | -n | Return the ASCII value for an escape character (27) |
| LF  | -n | Return the ASCII value for a line feed character (13) |
| CR  | -n | Return the ASCII value for a carriage return character (10) |
| SPACE | -n | Return the ASCII value for a space character (32) |


## Console ##
| tab | - | Display a TAB |
|:----|:--|:--------------|
| space | - | Display a SPACE |
| cr  | - | Display a LF  |
| clear | - | Clear the console output and position cursor to top left. |
| ^esc | a- | Display an ESC followed by a string. (Used for VT100/ANSI terminals) |
| t:  | "- | Parse to the end of the line, then display it. This can not be used inside a quote. |


## Unsorted ##
| octal | - | Set the current base for numeric conversions to octal (base 8) |
|:------|:--|:---------------------------------------------------------------|
| binary | - | Set the current base for numeric conversions to binary (base 2) |
| decimal | - | Set the current base for numeric conversions to decimal (base 10) |
| hex   | - | Set the current base for numeric conversions to hexadecimal (base 16) |

```
variable toggle off on -! +! cell- cell+ cells 
char- char+ chars >char 
help lnparse wsparse #! 
```