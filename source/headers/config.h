#define MAX_QUOTE_SIZE          128
#define MAX_DATA_STACK          100
#define MAX_RETURN_STACK       1024
#define MAX_DICTIONARY_ENTRIES 4096

#ifdef UNIX
#define LIBRARY "/usr/share/toka/library/"
#define BOOTSTRAP "/usr/share/toka/bootstrap.toka"
#endif

#ifdef WIN32
#define NOFFI
#define LIBRARY "c:\\toka\\library\\"
#define BOOTSTRAP "c:\\toka\\bootstrap.toka"
#endif
