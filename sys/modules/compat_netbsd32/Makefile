#	$NetBSD: Makefile,v 1.9 2012/03/10 21:52:00 joerg Exp $

.include "../Makefile.inc"
.include "../Makefile.assym"

KMOD=	compat_netbsd32

CPPFLAGS+=	-DSYSVSHM -DSYSVSEM -DSYSVMSG -DCOMPAT_NETBSD32
CPPFLAGS+=	-DEXEC_ELF32 -DEXEC_ELF64 -DEXEC_AOUT
CPPFLAGS+=	-DCOREDUMP

.PATH:	${S}/compat/netbsd32
SRCS+=	netbsd32_compat_09.c netbsd32_compat_10.c
SRCS+=	netbsd32_compat_12.c netbsd32_compat_13.c
SRCS+=	netbsd32_compat_14.c netbsd32_compat_20.c
SRCS+=	netbsd32_compat_30.c netbsd32_compat_43.c
SRCS+=	netbsd32_compat_50.c
SRCS+=	netbsd32_core.c netbsd32_event.c
SRCS+=	netbsd32_exec_aout.c netbsd32_exec_elf32.c
SRCS+=	netbsd32_execve.c netbsd32_fs.c
SRCS+=	netbsd32_ioctl.c netbsd32_ipc.c
SRCS+=	netbsd32_lwp.c netbsd32_netbsd.c
SRCS+=	netbsd32_select.c
SRCS+=	netbsd32_sem.c netbsd32_signal.c
SRCS+=	netbsd32_socket.c netbsd32_syscalls.c
SRCS+=	netbsd32_sysctl.c netbsd32_sysent.c
SRCS+=	netbsd32_time.c netbsd32_wait.c
SRCS+=	netbsd32_mod.c

.if ${MACHINE_ARCH} == "x86_64"
.PATH:	${S}/arch/amd64/amd64
SRCS+=	netbsd32_machdep.c netbsd32_sigcode.S netbsd32_syscall.c
.endif

.if ${MACHINE_ARCH} == "sparc64"
.PATH:	${S}/arch/sparc64/sparc64
SRCS+=	netbsd32_machdep.c netbsd32_sigcode.S
.endif

.include <bsd.kmodule.mk>
