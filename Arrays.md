# Introduction #

Toka has a couple of words to make dealing with arrays easier. These are defined in the standard bootstrap.

| is-array | n"- | Create a named array (_"_) of size _n_. |
|:---------|:----|:----------------------------------------|
| put-element | nia- | Store a value (_n_) into the array (_a_) at index (_i_). |
| get-element | ia-n | Read a value from the array (_a_) using index (_i_) |
| put-char-element | nia- | Store a character value (_n_) into the array (_a_) at index (_i_). |
| get-char-element | ia-n | Read a character value from the array (_a_) using index (_i_) |

# Example #

```
  10 cells is-array foo
  0 foo get-element .
  100 0 foo put-element 
  10 1 foo put-element 
  0 foo get-element .
  1 foo get-element .
```

# Tips #

  * The command line arguments are stored in an array (**arglist**).
    * At 0 is the name of the script
    * Actual arguments start at 1.
  * Be careful not to exceed the length of your array when giving an index