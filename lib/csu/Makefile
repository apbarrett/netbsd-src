#	$NetBSD: Makefile,v 1.29 2011/01/31 17:54:20 drochner Exp $

.include <bsd.own.mk>

CSU_MACHINE_ARCH?=	${MACHINE_ARCH}

.if ${USE_COMPILERCRTSTUFF} != "yes"

ARCHDIR:=	${.CURDIR}/arch/${CSU_MACHINE_ARCH}
.PATH:	${ARCHDIR}
.  include "${ARCHDIR}/Makefile.inc"

.  include "${.CURDIR}/common/Makefile.inc"

.else

.  if exists(${CSU_MACHINE_ARCH}_elf/Makefile)
SUBDIR=	${CSU_MACHINE_ARCH}_elf
.  elif exists(${CSU_MACHINE_ARCH}/Makefile)
SUBDIR=	${CSU_MACHINE_ARCH}
.  elif exists(${MACHINE_CPU}_elf/Makefile)
SUBDIR=	${MACHINE_CPU}_elf
.  elif exists(${MACHINE_CPU}/Makefile)
SUBDIR=	${MACHINE_CPU}
.  else
.BEGIN:
	@echo no SUBDIR for ${MACHINE_ARCH}_elf, ${MACHINE_ARCH} nor \
	    ${MACHINE_CPU}
	@false
.  endif

.  include <bsd.subdir.mk>
.endif
