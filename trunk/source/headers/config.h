#ifdef UNIX
#define LIBRARY "/usr/share/toka/library/"
#define BOOTSTRAP "/usr/share/toka/bootstrap.toka"
#endif

#ifdef WIN32
#define NOFFI
#define LIBRARY "c:\\toka\\library\\"
#define BOOTSTRAP "c:\\toka\\bootstrap.toka"
#endif
