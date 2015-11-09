Toka is a concatenative programming language related to Forth. It should be easy to learn, extend, and use. Development is ongoing, and updates occur almost daily.

The language is not compatible with any known existing Forth implementation, although some Forth code can be ported to Toka. Among the provided features are a memory allocator with basic garbage collection, dynamic allocations for functions and data, a decompiler, and a basic FFI.

The implementation was designed to be easily portable between Unix-like systems. Toka has currently been tested on the following architectures and systems:

| **x86** | **x86-64** | **MIPS** | **ARM** |
|:--------|:-----------|:---------|:--------|
| Linux   | Linux      | NetBSD/pmax | NetBSD/cats |
| NetBSD  |            | Linux    | OpenBSD/cats |
| FreeBSD |            |          | _Windows Mobile_ |
| OpenBSD |            |          |         |
| DragonFly BSD |            |          |         |
| OpenSolaris |            |          |         |
| _BeOS_  |            |          |         |
| _Cygwin_ |            |          |         |
| _Windows (Win32)_ |            |          |         |

Ports shown in _italics_ work, but may have limitations or minor issues.