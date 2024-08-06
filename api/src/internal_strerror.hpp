/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: internal_strerror.hpp                                          */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/08/03 03:35:20                                            */
/*   Updated:  2024/08/03 03:39:09                                            */
/*                                                                            */
/* ************************************************************************** */

#pragma once

;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpragmas"
#pragma GCC diagnostic warning "-Weverything"
#pragma GCC diagnostic ignored "-Wempty-translation-unit"
#pragma GCC diagnostic ignored "-Wunused-macros"
#pragma GCC diagnostic ignored "-Wextra-semi"
#pragma GCC diagnostic ignored "-Wunsafe-buffer-usage"
#pragma GCC diagnostic ignored "-Wc++98-compat"
#pragma GCC diagnostic ignored "-Wwritable-strings"
#pragma GCC diagnostic ignored "-Wlanguage-extension-token"
#pragma GCC diagnostic ignored "-Wpre-c++20-compat-pedantic"
#pragma GCC diagnostic ignored "-Wc++20-designator"
#pragma GCC diagnostic ignored "-Wc++98-compat-extra-semi"
#pragma GCC diagnostic ignored "-Wc99-designator"
;

#include <cerrno>

inline char const *internal_strerror(int code)
{
	char const *table[] = {
		[EPERM] = "Operation not permitted\n",
		[ENOENT] = "No such file or directory\n",
		[ESRCH] = "No such process\n",
		[EINTR] = "Interrupted system call\n",
		[EIO] = "Input/output error\n",
		[ENXIO] = "No such device or address\n",
		[E2BIG] = "Argument list too long\n",
		[ENOEXEC] = "Exec format error\n",
		[EBADF] = "Bad file descriptor\n",
		[ECHILD] = "No child processes\n",
		[EAGAIN] = "Resource temporarily unavailable\n",
		[ENOMEM] = "Cannot allocate memory\n",
		[EACCES] = "Permission denied\n",
		[EFAULT] = "Bad address\n",
		[ENOTBLK] = "Block device required\n",
		[EBUSY] = "Device or resource busy\n",
		[EEXIST] = "File exists\n",
		[EXDEV] = "Invalid cross-device link\n",
		[ENODEV] = "No such device\n",
		[ENOTDIR] = "Not a directory\n",
		[EISDIR] = "Is a directory\n",
		[EINVAL] = "Invalid argument\n",
		[ENFILE] = "Too many open files in system\n",
		[EMFILE] = "Too many open files\n",
		[ENOTTY] = "Inappropriate ioctl for device\n",
		[ETXTBSY] = "Text file busy\n",
		[EFBIG] = "File too large\n",
		[ENOSPC] = "No space left on device\n",
		[ESPIPE] = "Illegal seek\n",
		[EROFS] = "Read-only file system\n",
		[EMLINK] = "Too many links\n",
		[EPIPE] = "Broken pipe\n",
		[EDOM] = "Numerical argument out of domain\n",
		[ERANGE] = "Numerical result out of range\n",
		[EDEADLK] = "Resource deadlock avoided\n",
		[ENAMETOOLONG] = "File name too long\n",
		[ENOLCK] = "No locks available\n",
		[ENOSYS] = "Function not implemented\n",
		[ENOTEMPTY] = "Directory not empty\n",
		[ELOOP] = "Too many levels of symbolic links\n",
		[ENOMSG] = "No message of desired type\n",
		[EIDRM] = "Identifier removed\n",
		[ECHRNG] = "Channel number out of range\n",
		[EL2NSYNC] = "Level 2 not synchronized\n",
		[EL3HLT] = "Level 3 halted\n",
		[EL3RST] = "Level 3 reset\n",
		[ELNRNG] = "Link number out of range\n",
		[EUNATCH] = "Protocol driver not attached\n",
		[ENOCSI] = "No CSI structure available\n",
		[EL2HLT] = "Level 2 halted\n",
		[EBADE] = "Invalid exchange\n",
		[EBADR] = "Invalid request descriptor\n",
		[EXFULL] = "Exchange full\n",
		[ENOANO] = "No anode\n",
		[EBADRQC] = "Invalid request code\n",
		[EBADSLT] = "Invalid slot\n",
		[EBFONT] = "Bad font file format\n",
		[ENOSTR] = "Device not a stream\n",
		[ENODATA] = "No data available\n",
		[ETIME] = "Timer expired\n",
		[ENOSR] = "Out of streams resources\n",
		[ENONET] = "Machine is not on the network\n",
		[ENOPKG] = "Package not installed\n",
		[EREMOTE] = "Object is remote\n",
		[ENOLINK] = "Link has been severed\n",
		[EADV] = "Advertise error\n",
		[ESRMNT] = "Srmount error\n",
		[ECOMM] = "Communication error on send\n",
		[EPROTO] = "Protocol error\n",
		[EMULTIHOP] = "Multihop attempted\n",
		[EDOTDOT] = "RFS specific error\n",
		[EBADMSG] = "Bad message\n",
		[EOVERFLOW] = "Value too large for defined data type\n",
		[ENOTUNIQ] = "Name not unique on network\n",
		[EBADFD] = "File descriptor in bad state\n",
		[EREMCHG] = "Remote address changed\n",
		[ELIBACC] = "Can not access a needed shared library\n",
		[ELIBBAD] = "Accessing a corrupted shared library\n",
		[ELIBSCN] = ".lib section in a.out corrupted\n",
		[ELIBMAX] = "Attempting to link in too many shared libraries\n",
		[ELIBEXEC] = "Cannot exec a shared library directly\n",
		[EILSEQ] = "Invalid or incomplete multibyte or wide character\n",
		[ERESTART] = "Interrupted system call should be restarted\n",
		[ESTRPIPE] = "Streams pipe error\n",
		[EUSERS] = "Too many users\n",
		[ENOTSOCK] = "Socket operation on non-socket\n",
		[EDESTADDRREQ] = "Destination address required\n",
		[EMSGSIZE] = "Message too long\n",
		[EPROTOTYPE] = "Protocol wrong type for socket\n",
		[ENOPROTOOPT] = "Protocol not available\n",
		[EPROTONOSUPPORT] = "Protocol not supported\n",
		[ESOCKTNOSUPPORT] = "Socket type not supported\n",
		[EOPNOTSUPP] = "Operation not supported\n",
		[EPFNOSUPPORT] = "Protocol family not supported\n",
		[EAFNOSUPPORT] = "Address family not supported by protocol\n",
		[EADDRINUSE] = "Address already in use\n",
		[EADDRNOTAVAIL] = "Cannot assign requested address\n",
		[ENETDOWN] = "Network is down\n",
		[ENETUNREACH] = "Network is unreachable\n",
		[ENETRESET] = "Network dropped connection on reset\n",
		[ECONNABORTED] = "Software caused connection abort\n",
		[ECONNRESET] = "Connection reset by peer\n",
		[ENOBUFS] = "No buffer space available\n",
		[EISCONN] = "Transport endpoint is already connected\n",
		[ENOTCONN] = "Transport endpoint is not connected\n",
		[ESHUTDOWN] = "Cannot send after transport endpoint shutdown\n",
		[ETOOMANYREFS] = "Too many references: cannot splice\n",
		[ETIMEDOUT] = "Connection timed out\n",
		[ECONNREFUSED] = "Connection refused\n",
		[EHOSTDOWN] = "Host is down\n",
		[EHOSTUNREACH] = "No route to host\n",
		[EALREADY] = "Operation already in progress\n",
		[EINPROGRESS] = "Operation now in progress\n",
		[ESTALE] = "Stale file handle\n",
		[EUCLEAN] = "Structure needs cleaning\n",
		[ENOTNAM] = "Not a XENIX named type file\n",
		[ENAVAIL] = "No XENIX semaphores available\n",
		[EISNAM] = "Is a named type file\n",
		[EREMOTEIO] = "Remote I/O error\n",
		[EDQUOT] = "Disk quota exceeded\n",
		[ENOMEDIUM] = "No medium found\n",
		[EMEDIUMTYPE] = "Wrong medium type\n",
		[ECANCELED] = "Operation canceled\n",
		[ENOKEY] = "Required key not available\n",
		[EKEYEXPIRED] = "Key has expired\n",
		[EKEYREVOKED] = "Key has been revoked\n",
		[EKEYREJECTED] = "Key was rejected by service\n",
		[EOWNERDEAD] = "Owner died\n",
		[ENOTRECOVERABLE] = "State not recoverable\n",
		[ERFKILL] = "Operation not possible due to RF-kill\n",
		[EHWPOISON] = "Memory page has hardware error\n",
	};

	return (table[code]);
}

#pragma GCC diagnostic pop
