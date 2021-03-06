/*	$NetBSD: policy.c,v 1.2 2010/06/24 13:03:05 hannken Exp $	*/

/*-
 * Copyright (c) 2009 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Andrew Doran.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*-
 * Copyright (c) 2007 Pawel Jakub Dawidek <pjd@FreeBSD.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/param.h>
#include <sys/priv.h>
#include <sys/vnode.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/policy.h>

int
secpolicy_zfs(kauth_cred_t cred)
{

	return kauth_authorize_generic(cred, KAUTH_GENERIC_ISSUSER, NULL);
}

int
secpolicy_sys_config(kauth_cred_t cred, int checkonly __unused)
{

	return kauth_authorize_generic(cred, KAUTH_GENERIC_ISSUSER, NULL);
}

int
secpolicy_zinject(kauth_cred_t cred)
{

	return kauth_authorize_generic(cred, KAUTH_GENERIC_ISSUSER, NULL);
}

int
secpolicy_fs_mount(kauth_cred_t cred, vnode_t *mvp, struct mount *vfsp)
{

	return kauth_authorize_system(cred, KAUTH_SYSTEM_MOUNT,
	    KAUTH_REQ_SYSTEM_MOUNT_NEW, vfsp, NULL, NULL);
}

int
secpolicy_fs_unmount(kauth_cred_t cred, struct mount *vfsp)
{

	return kauth_authorize_system(cred, KAUTH_SYSTEM_MOUNT,
	    KAUTH_REQ_SYSTEM_MOUNT_UNMOUNT, vfsp, NULL, NULL);
}

/*
 * This check is done in kern_link(), so we could just return 0 here.
 */
int
secpolicy_basic_link(kauth_cred_t cred)
{

	return kauth_authorize_generic(cred, KAUTH_GENERIC_ISSUSER, NULL);
}

int
secpolicy_vnode_stky_modify(kauth_cred_t cred)
{

	return (EPERM);
}

int
secpolicy_vnode_remove(kauth_cred_t cred)
{

	return kauth_authorize_generic(cred, KAUTH_GENERIC_ISSUSER, NULL);
}


int
secpolicy_vnode_owner(cred_t *cred, uid_t owner)
{
	uid_t uid;

	uid = crgetuid(cred);
	
	if (owner == uid)
		 return (0);

	return 0;
//	return kauth_authorize_system(cred, KAUTH_SYSTEM_MOUNT,
//	    KAUTH_REQ_SYSTEM_MOUNT_NEW, vfsp, NULL, NULL);
}

int
secpolicy_vnode_access(kauth_cred_t cred, struct vnode *vp, uint64_t owner,
    int mode)
{
	int error;

	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY);
	error = VOP_ACCESS(vp, mode, cred);
	VOP_UNLOCK(vp);
	return error;
}

/*
 * Check privileges for setting xvattr attributes
 */
int
secpolicy_xvattr(xvattr_t *xvap, uid_t owner, cred_t *cr, vtype_t vtype)
{
/*	return kauth_authorize_system(cred, KAUTH_SYSTEM_MOUNT,
	KAUTH_REQ_SYSTEM_MOUNT_UPDATE, vfsp, NULL, NULL);*/
	return 0;
}

int
secpolicy_vnode_setid_retain(kauth_cred_t cred, boolean_t issuidroot __unused)
{

	return  (kauth_authorize_generic(cred, KAUTH_GENERIC_ISSUSER, NULL));
}

int
secpolicy_vnode_setids_setgids(kauth_cred_t cred, gid_t gid)
{

	if (!groupmember(gid, cred))
		return  (kauth_authorize_generic(cred, KAUTH_GENERIC_ISSUSER,
			NULL));
	return (0);
}

int
secpolicy_vnode_chown(struct kauth_cred *cred, boolean_t check_self)
{

	return  (kauth_authorize_generic(cred, KAUTH_GENERIC_ISSUSER,
		NULL));
	/* return (priv_check_cred(cred, PRIV_VFS_CHOWN, 0)); */
}

int
secpolicy_vnode_create_gid(struct kauth_cred *cred)
{

	return (EPERM);
}

int
secpolicy_vnode_setdac(struct kauth_cred *cred, uid_t owner)
{

	return 0;
	/*return (priv_check_cred(cred, PRIV_VFS_ADMIN, 0));*/
}

int
secpolicy_setid_setsticky_clear(struct vnode *vp, struct vattr *vap,
    const struct vattr *ovap, kauth_cred_t cred)
{
	/*
	 * Privileged processes may set the sticky bit on non-directories,
	 * as well as set the setgid bit on a file with a group that the process
	 * is not a member of. Both of these are allowed in jail(8).
	 */
	if (vp->v_type != VDIR && (vap->va_mode & S_ISTXT)) {
		if (kauth_authorize_generic(cred, KAUTH_GENERIC_ISSUSER, NULL) != 0)
			return (EFTYPE);
	}
	/*
	 * Check for privilege if attempting to set the
	 * group-id bit.
	 */
	if ((vap->va_mode & S_ISGID) != 0)
		return (secpolicy_vnode_setids_setgids(cred, ovap->va_gid));
       
	return (0);
}

int
secpolicy_vnode_setattr(kauth_cred_t cred, struct vnode *vp, struct vattr *vap,
    const struct vattr *ovap, int flags,
    int unlocked_access(void *, int, kauth_cred_t ), void *node)
{

	return 0;
}

void
secpolicy_setid_clear(struct vattr *vap, kauth_cred_t cred)
{
	if (kauth_authorize_generic(cred, KAUTH_GENERIC_ISSUSER, NULL) != 0)
		return;

	if ((vap->va_mode & (S_ISUID | S_ISGID)) != 0) {
			vap->va_mask |= AT_MODE;
			vap->va_mode &= ~(S_ISUID|S_ISGID);
	}
	
	return;
}

#ifdef notyet
int
secpolicy_vnode_setdac(kauth_cred_t cred, uid_t owner)
{

	if (owner == cred->cr_uid)
		return (0);
	return (priv_check_cred(cred, PRIV_VFS_ADMIN, 0));
}

int
secpolicy_vnode_setattr(kauth_cred_t cred, struct vnode *vp, struct vattr *vap,
    const struct vattr *ovap, int flags,
    int unlocked_access(void *, int, kauth_cred_t ), void *node)
{
	int mask = vap->va_mask;
	int error;

	if (mask & AT_SIZE) {
		if (vp->v_type == VDIR)
			return (EISDIR);
		error = unlocked_access(node, VWRITE, cred);
		if (error)
			return (error);
	}
	if (mask & AT_MODE) {
		/*
		 * If not the owner of the file then check privilege
		 * for two things: the privilege to set the mode at all
		 * and, if we're setting setuid, we also need permissions
		 * to add the set-uid bit, if we're not the owner.
		 * In the specific case of creating a set-uid root
		 * file, we need even more permissions.
		 */
		error = secpolicy_vnode_setdac(cred, ovap->va_uid);
		if (error)
			return (error);
		error = secpolicy_setid_setsticky_clear(vp, vap, ovap, cred);
		if (error)
			return (error);
	} else {
		vap->va_mode = ovap->va_mode;
	}
	if (mask & (AT_UID | AT_GID)) {
		error = secpolicy_vnode_setdac(cred, ovap->va_uid);
		if (error)
			return (error);

		/*
		 * To change the owner of a file, or change the group of a file to a
		 * group of which we are not a member, the caller must have
		 * privilege.
		 */
		if (((mask & AT_UID) && vap->va_uid != ovap->va_uid) ||
		    ((mask & AT_GID) && vap->va_gid != ovap->va_gid &&
		     !groupmember(vap->va_gid, cred))) {
			error = priv_check_cred(cred, PRIV_VFS_CHOWN, 0);
			if (error)
				return (error);
		}

		if (((mask & AT_UID) && vap->va_uid != ovap->va_uid) ||
		    ((mask & AT_GID) && vap->va_gid != ovap->va_gid)) {
			secpolicy_setid_clear(vap, cred);
		}
	}
	if (mask & (AT_ATIME | AT_MTIME)) {
		/*
		 * From utimes(2):
		 * If times is NULL, ... The caller must be the owner of
		 * the file, have permission to write the file, or be the
		 * super-user.
		 * If times is non-NULL, ... The caller must be the owner of
		 * the file or be the super-user.
		 */
		error = secpolicy_vnode_setdac(cred, ovap->va_uid);
		if (error && (vap->va_vaflags & VA_UTIMES_NULL))
			error = unlocked_access(node, VWRITE, cred);
		if (error)
			return (error);
	}
	return (0);
}

int
secpolicy_vnode_create_gid(kauth_cred_t cred)
{

	return (EPERM);
}

int
secpolicy_vnode_setid_retain(kauth_cred_t cred, boolean_t issuidroot __unused)
{

	return (priv_check_cred(cred, PRIV_VFS_RETAINSUGID, 0));
}

void
secpolicy_setid_clear(struct vattr *vap, kauth_cred_t cred)
{

	if (kauth_authorize_generic(cred, KAUTH_GENERIC_ISSUSER, NULL))
		return;
	
	if ((vap->va_mode & (S_ISUID | S_ISGID)) != 0) {
		if (priv_check_cred(cred, PRIV_VFS_RETAINSUGID, 0)) {
			vap->va_mask |= AT_MODE;
			vap->va_mode &= ~(S_ISUID|S_ISGID);
		}
	}
}
#endif
