/*
 * User-supplied callbacks and default implementations.
 * Class and permission mappings.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <selinux/selinux.h>
#include "callbacks.h"
#include <string.h>

/* default implementations */
static int __attribute__ ((format(printf, 2, 3)))
default_selinux_log(int type __attribute__((unused)), const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	int rc = vfprintf(stderr, fmt, ap);
	va_end(ap);
	return rc;
}

static int
default_selinux_validate(char **ctx)
{
	return security_check_context(*ctx);
}

/* callback pointers */
int __attribute__ ((format(printf, 2, 3)))
(*selinux_log)(int, const char *, ...) =
	default_selinux_log;

int (*selinux_audit) (void *, security_class_t, char *, size_t) = 0;

int
(*selinux_validate)(char **ctx) =
	default_selinux_validate;

int (*selinux_netlink_setenforce) (int enforcing) = 0;

int (*selinux_netlink_policyload) (int seqno) = 0;

/* callback setting function */
void
selinux_set_callback(int type, union selinux_callback cb)
{
	switch (type) {
	case SELINUX_CB_LOG:
		selinux_log = cb.func_log;
		break;
	case SELINUX_CB_AUDIT:
		selinux_audit = cb.func_audit;
		break;
	case SELINUX_CB_VALIDATE:
		selinux_validate = cb.func_validate;
		break;
	case SELINUX_CB_SETENFORCE:
		selinux_netlink_setenforce = cb.func_setenforce;
		break;
	case SELINUX_CB_POLICYLOAD:
		selinux_netlink_policyload = cb.func_policyload;
		break;
	}
}

/* callback getting function */
union selinux_callback
selinux_get_callback(int type)
{
	union selinux_callback cb;

	switch (type) {
	case SELINUX_CB_LOG:
		cb.func_log = selinux_log;
		break;
	case SELINUX_CB_AUDIT:
		cb.func_audit = selinux_audit;
		break;
	case SELINUX_CB_VALIDATE:
		cb.func_validate = selinux_validate;
		break;
	case SELINUX_CB_SETENFORCE:
		cb.func_setenforce = selinux_netlink_setenforce;
		break;
	case SELINUX_CB_POLICYLOAD:
		cb.func_policyload = selinux_netlink_policyload;
		break;
	default:
		memset(&cb, 0, sizeof(cb));
		errno = EINVAL;
		break;
	}
	return cb;
}
