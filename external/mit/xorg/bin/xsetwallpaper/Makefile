#	$NetBSD: Makefile,v 1.1 2011/10/22 22:06:17 jmcneill Exp $

NOMAN=		# defined

.include <bsd.own.mk>

PROG=		xsetwallpaper
SRCS=		xsetwallpaper.c
SRCS+=		stb_image.c

CPPFLAGS+=	-I${NETBSDSRCDIR}/sys -I${NETBSDSRCDIR}/sys/dev/stbi

SRCPATH=        ${X11SRCDIR.local}/programs/xsetwallpaper

LDADD+=		-lm -lX11
DPADD+=		${LIBM} ${LIBX11}

.PATH:		${X11SRCDIR.local}/programs/xsetwallpaper
.PATH:		${NETBSDSRCDIR}/sys/dev/stbi

WARNS=		4

CPPFLAGS.stb_image.c+=	-Wno-shadow
CPPFLAGS.stb_image.c+=	-Wno-sign-compare
CPPFLAGS.stb_image.c+=	-Wno-missing-prototypes
CPPFLAGS.stb_image.c+=	-Wno-missing-field-initializers

.include <bsd.x11.mk>
.include <bsd.prog.mk>
