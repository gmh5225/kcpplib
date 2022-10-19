#include <wdm.h>

// char *_sys_errlist[] =
//{
//	/*  0              */  "No error",
//	/*  1 EPERM        */  "Operation not permitted",
//	/*  2 ENOENT       */  "No such file or directory",
//	/*  3 ESRCH        */  "No such process",
//	/*  4 EINTR        */  "Interrupted function call",
//	/*  5 EIO          */  "Input/output error",
//	/*  6 ENXIO        */  "No such device or address",
//	/*  7 E2BIG        */  "Arg list too long",
//	/*  8 ENOEXEC      */  "Exec format error",
//	/*  9 EBADF        */  "Bad file descriptor",
//	/* 10 ECHILD       */  "No child processes",
//	/* 11 EAGAIN       */  "Resource temporarily unavailable",
//	/* 12 ENOMEM       */  "Not enough space",
//	/* 13 EACCES       */  "Permission denied",
//	/* 14 EFAULT       */  "Bad address",
//	/* 15 ENOTBLK      */  "Unknown error",                     /* not POSIX */
//	/* 16 EBUSY        */  "Resource device",
//	/* 17 EEXIST       */  "File exists",
//	/* 18 EXDEV        */  "Improper link",
//	/* 19 ENODEV       */  "No such device",
//	/* 20 ENOTDIR      */  "Not a directory",
//	/* 21 EISDIR       */  "Is a directory",
//	/* 22 EINVAL       */  "Invalid argument",
//	/* 23 ENFILE       */  "Too many open files in system",
//	/* 24 EMFILE       */  "Too many open files",
//	/* 25 ENOTTY       */  "Inappropriate I/O control operation",
//	/* 26 ETXTBSY      */  "Unknown error",                     /* not POSIX */
//	/* 27 EFBIG        */  "File too large",
//	/* 28 ENOSPC       */  "No space left on device",
//	/* 29 ESPIPE       */  "Invalid seek",
//	/* 30 EROFS        */  "Read-only file system",
//	/* 31 EMLINK       */  "Too many links",
//	/* 32 EPIPE        */  "Broken pipe",
//	/* 33 EDOM         */  "Domain error",
//	/* 34 ERANGE       */  "Result too large",
//	/* 35 EUCLEAN      */  "Unknown error",                     /* not POSIX */
//	/* 36 EDEADLK      */  "Resource deadlock avoided",
//	/* 37 UNKNOWN      */  "Unknown error",
//	/* 38 ENAMETOOLONG */  "Filename too long",
//	/* 39 ENOLCK       */  "No locks available",
//	/* 40 ENOSYS       */  "Function not implemented",
//	/* 41 ENOTEMPTY    */  "Directory not empty",
//	/* 42 EILSEQ       */  "Illegal byte sequence",
//	/* 43              */  "Unknown error"
//};

char *_sys_errlist[] = {
    /*  0              */ "0",
    /*  1 EPERM        */ "1",
    /*  2 ENOENT       */ "2",
    /*  3 ESRCH        */ "3",
    /*  4 EINTR        */ "4",
    /*  5 EIO          */ "5",
    /*  6 ENXIO        */ "6",
    /*  7 E2BIG        */ "7",
    /*  8 ENOEXEC      */ "8",
    /*  9 EBADF        */ "9",
    /* 10 ECHILD       */ "10",
    /* 11 EAGAIN       */ "11",
    /* 12 ENOMEM       */ "12",
    /* 13 EACCES       */ "13",
    /* 14 EFAULT       */ "14",
    /* 15 ENOTBLK      */ "15", /* not POSIX */
    /* 16 EBUSY        */ "16",
    /* 17 EEXIST       */ "17",
    /* 18 EXDEV        */ "18",
    /* 19 ENODEV       */ "19",
    /* 20 ENOTDIR      */ "20",
    /* 21 EISDIR       */ "21",
    /* 22 EINVAL       */ "22",
    /* 23 ENFILE       */ "23",
    /* 24 EMFILE       */ "24",
    /* 25 ENOTTY       */ "25",
    /* 26 ETXTBSY      */ "26", /* not POSIX */
    /* 27 EFBIG        */ "27",
    /* 28 ENOSPC       */ "28",
    /* 29 ESPIPE       */ "29",
    /* 30 EROFS        */ "30",
    /* 31 EMLINK       */ "31",
    /* 32 EPIPE        */ "32",
    /* 33 EDOM         */ "33",
    /* 34 ERANGE       */ "34",
    /* 35 EUCLEAN      */ "35", /* not POSIX */
    /* 36 EDEADLK      */ "36",
    /* 37 UNKNOWN      */ "37",
    /* 38 ENAMETOOLONG */ "38",
    /* 39 ENOLCK       */ "39",
    /* 40 ENOSYS       */ "40",
    /* 41 ENOTEMPTY    */ "41",
    /* 42 EILSEQ       */ "42",
    /* 43              */ "43"};

int _sys_nerr = sizeof(_sys_errlist) / sizeof(_sys_errlist[0]) - 1;

#define _sys_err_msg(m) _sys_errlist[(((m) < 0) || ((m) >= _sys_nerr) ? _sys_nerr : (m))]

const char *
_get_sys_err_msg(int m)
{
    return _sys_err_msg(m);
}

#define _SYS_MSGMAX 38
#define _ERRMSGLEN_ (94 + _SYS_MSGMAX + 2)

char *__cdecl strerror(int errnum)
{
    static char errmsg[_ERRMSGLEN_ + 1];
    RtlSecureZeroMemory(errmsg, sizeof(errmsg));

    //暂时不实现，直接返回空
    // mycrt_strncpy_a(errmsg, _ERRMSGLEN_, _get_sys_err_msg(errnum),);

    return (errmsg);
}

int _kerrno = 0;

int *__cdecl _errno(void)
{
    return &_kerrno;
}
