/* Support files for GNU libc.  Files in the system namespace go here.
   Files in the C namespace (ie those that do not start with an
   underscore) go in .c.  */

#include <_ansi.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>
#include <errno.h>
#include <reent.h>

//#include "rpi1.h"
#include "../cmn00/rpi_gpio.h"
//#include "../cmn00/rpi_serial.h"
#include "../cmn00/mini_serial.h"
// int uart0_putc (int c); // 2017 TT
//#define uart0_putc m_serialPutChar
//#define uart0_getc m_serialGetChar

extern void *__bss_end;
unsigned int heap_end=(unsigned int)&__bss_end;
unsigned int prev_heap_end;

/* Forward prototypes.  */
int     _system     _PARAMS ((const char *));
int     _rename     _PARAMS ((const char *, const char *));
int     isatty      _PARAMS ((int));
clock_t _times      _PARAMS ((struct tms *));
int     _gettimeofday   _PARAMS ((struct timeval *, struct timezone *));
void    _raise      _PARAMS ((void));
int     _unlink     _PARAMS ((void));
int     _link       _PARAMS ((void));
int     _stat       _PARAMS ((const char *, struct stat *));
int     _fstat      _PARAMS ((int, struct stat *));
caddr_t _sbrk       _PARAMS ((int));
int     _getpid     _PARAMS ((int));
int     _kill       _PARAMS ((int, int));
void    _exit       _PARAMS ((int));
int     _close      _PARAMS ((int));
int     _open       _PARAMS ((const char *, int, ...));
int     _write      _PARAMS ((int, char *, int));
int     _lseek      _PARAMS ((int, int, int));
int     _read       _PARAMS ((int, char *, int));
void    initialise_monitor_handles _PARAMS ((void));

/* Register name faking - works in collusion with the linker.  */
register char * stack_ptr asm ("sp");

//static int
//remap_handle (int fh)
//{
    //return 0;
//}

void
initialise_monitor_handles (void)
{
}

//  Note: If you enable folloing 2, printf function will not work!
// static int
// get_errno (void)
// {
//     return(0);
// }

// static int
// error (int result)
// {
//   errno = get_errno ();
//   return result;
// }


int
_read (int file,
       char * ptr,
       int len)
{
  return len;
}


int
_lseek (int file,
    int ptr,
    int dir)
{
    return 0;
}


int
_write (int    file,
    char * ptr,
    int    len)
{
    int r;
    for(r=0;r<len;r++){
//      uart0_putc(ptr[r]);
	m_serialPutChar(ptr[r]);
    }
    return len;
}

int
_open (const char * path,
       int          flags,
       ...)
{
    return 0;
}


int
_close (int file)
{
    return 0;
}

void
_exit (int n)
{
    while(1);
}

int
_kill (int n, int m)
{
    return(0);
}

int
_getpid (int n)
{
  return 1;
  n = n;
}


caddr_t _sbrk (int incr) {
  prev_heap_end = heap_end;
  if (heap_end + incr > stack_ptr)
    return (caddr_t) -1;
  heap_end += incr;
  return (caddr_t) prev_heap_end;
}

int
_fstat (int file, struct stat * st)
{
  return 0;
}

int _stat (const char *fname, struct stat *st)
{
  return 0;
}

int
_link (void)
{
  return -1;
}

int
_unlink (void)
{
  return -1;
}

void
_raise (void)
{
  return;
}

int
_gettimeofday (struct timeval * tp, struct timezone * tzp)
{
    if(tp)
    {
        tp->tv_sec = 10;
        tp->tv_usec = 0;
    }
    if (tzp)
    {
        tzp->tz_minuteswest = 0;
        tzp->tz_dsttime = 0;
    }
    return 0;
}

clock_t
_times (struct tms * tp)
{
    clock_t timeval;

    timeval = 10;
    if (tp)
    {
        tp->tms_utime  = timeval;   /* user time */
        tp->tms_stime  = 0; /* system time */
        tp->tms_cutime = 0; /* user time, children */
        tp->tms_cstime = 0; /* system time, children */
    }
    return timeval;
};


int
_isatty (int fd)
{
  return 1;
  fd = fd;
}

int
_system (const char *s)
{
  if (s == NULL)
    return 0;
  errno = ENOSYS;
  return -1;
}

int
_rename (const char * oldpath, const char * newpath)
{
  errno = ENOSYS;
  return -1;
}
