/*
 +----------------------------------------------------------------------+
 | Copyright (c) The PHP Group                                          |
 +----------------------------------------------------------------------+
 | This source file is subject to version 3.01 of the PHP license,      |
 | that is bundled with this package in the file LICENSE, and is        |
 | available through the world-wide-web at the following url:           |
 | http://www.php.net/license/3_01.txt                                  |
 | If you did not receive a copy of the PHP license and are unable to   |
 | obtain it through the world-wide-web, please send a note to          |
 | license@php.net so we can mail you a copy immediately.               |
 +----------------------------------------------------------------------+
 | Author: KaiGai Kohei <kaigai@ak.jp.nec.com>                          |
 +----------------------------------------------------------------------+
*/
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_selinux.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <selinux/selinux.h>
#include <selinux/label.h>

/*
 * SELinux arginfo
 */
ZEND_BEGIN_ARG_INFO(arginfo_selinux_is_enabled, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_mls_is_enabled, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_getenforce, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_setenforce, 0)
	ZEND_ARG_INFO(0, mode)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_policyvers, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_deny_unknown, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_getcon, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_setcon, 0)
	ZEND_ARG_INFO(0, context)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_getpidcon, 0)
	ZEND_ARG_INFO(0, pid)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_getprevcon, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_getexeccon, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_setexeccon, 0)
	ZEND_ARG_INFO(0, context)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_getfscreatecon, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_setfscreatecon, 0)
	ZEND_ARG_INFO(0, context)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_getkeycreatecon, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_setkeycreatecon, 0)
	ZEND_ARG_INFO(0, context)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_getsockcreatecon, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_setsockcreatecon, 0)
	ZEND_ARG_INFO(0, context)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_getfilecon, 0)
	ZEND_ARG_INFO(0, filename)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_lgetfilecon, 0)
	ZEND_ARG_INFO(0, filename)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_fgetfilecon, 0)
	ZEND_ARG_INFO(0, stream)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_setfilecon, 0)
	ZEND_ARG_INFO(0, filename)
	ZEND_ARG_INFO(0, context)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_lsetfilecon, 0)
	ZEND_ARG_INFO(0, filename)
	ZEND_ARG_INFO(0, context)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_fsetfilecon, 0)
	ZEND_ARG_INFO(0, stream)
	ZEND_ARG_INFO(0, context)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_getpeercon, 0)
	ZEND_ARG_INFO(0, stream)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_compute_av, 0)
	ZEND_ARG_INFO(0, scontext)
	ZEND_ARG_INFO(0, tcontext)
	ZEND_ARG_INFO(0, tclass)
ZEND_END_ARG_INFO()

#ifdef HAVE_SECURITY_COMPUTE_CREATE_NAME
ZEND_BEGIN_ARG_INFO_EX(arginfo_selinux_compute_create, 0, 0, 3)
	ZEND_ARG_INFO(0, scontext)
	ZEND_ARG_INFO(0, tcontext)
	ZEND_ARG_INFO(0, tclass)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()
#endif

ZEND_BEGIN_ARG_INFO(arginfo_selinux_compute_relabel, 0)
	ZEND_ARG_INFO(0, scontext)
	ZEND_ARG_INFO(0, tcontext)
	ZEND_ARG_INFO(0, tclass)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_compute_member, 0)
	ZEND_ARG_INFO(0, scontext)
	ZEND_ARG_INFO(0, tcontext)
	ZEND_ARG_INFO(0, tclass)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_compute_user, 0)
	ZEND_ARG_INFO(0, scontext)
	ZEND_ARG_INFO(0, username)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_get_initial_context, 0)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_check_context, 0)
	ZEND_ARG_INFO(0, context)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_canonicalize_context, 0)
	ZEND_ARG_INFO(0, context)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_get_boolean_names, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_get_boolean_pending, 0)
	ZEND_ARG_INFO(0, bool_name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_get_boolean_active, 0)
	ZEND_ARG_INFO(0, bool_name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_set_boolean, 0)
	ZEND_ARG_INFO(0, bool_name)
	ZEND_ARG_INFO(0, bool_value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_commit_booleans, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_trans_to_raw_context, 0)
	ZEND_ARG_INFO(0, context)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_raw_to_trans_context, 0)
	ZEND_ARG_INFO(0, context)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_selinux_file_label_lookup, 0, 0, 2)
	ZEND_ARG_INFO(0, pathname)
	ZEND_ARG_INFO(0, mode)
	ZEND_ARG_INFO(0, validate)
	ZEND_ARG_INFO(0, baseonly)
	ZEND_ARG_INFO(0, subset)
	ZEND_ARG_INFO(0, specfile)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_selinux_media_label_lookup, 0, 0, 1)
	ZEND_ARG_INFO(0, device_name)
	ZEND_ARG_INFO(0, validate)
	ZEND_ARG_INFO(0, specfile)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_x_label_lookup, 0)
	ZEND_ARG_INFO(0, x_key)
	ZEND_ARG_INFO(0, x_type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_db_label_lookup, 0)
	ZEND_ARG_INFO(0, db_key)
	ZEND_ARG_INFO(0, db_type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_getenforcemode, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_getpolicytype, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_selinux_policy_root, 0)
ZEND_END_ARG_INFO()

/*
 * SELinux functions
 */
zend_function_entry selinux_functions[] = {
	/* global state API */
	PHP_FE(selinux_is_enabled,		arginfo_selinux_is_enabled)
	PHP_FE(selinux_mls_is_enabled,		arginfo_selinux_mls_is_enabled)
	PHP_FE(selinux_getenforce,		arginfo_selinux_getenforce)
	PHP_FE(selinux_setenforce,		arginfo_selinux_setenforce)
	PHP_FE(selinux_policyvers,		arginfo_selinux_policyvers)
	PHP_FE(selinux_deny_unknown,		arginfo_selinux_deny_unknown)

	/*  wrappers for the /proc/pid/attr API */
	PHP_FE(selinux_getcon,			arginfo_selinux_getcon)
	PHP_FE(selinux_setcon,			arginfo_selinux_setcon)
	PHP_FE(selinux_getpidcon,		arginfo_selinux_getpidcon)
	PHP_FE(selinux_getprevcon,		arginfo_selinux_getprevcon)
	PHP_FE(selinux_getexeccon,		arginfo_selinux_getexeccon)
	PHP_FE(selinux_setexeccon,		arginfo_selinux_setexeccon)
	PHP_FE(selinux_getfscreatecon,		arginfo_selinux_getfscreatecon)
	PHP_FE(selinux_setfscreatecon,		arginfo_selinux_setfscreatecon)
	PHP_FE(selinux_getkeycreatecon,		arginfo_selinux_getkeycreatecon)
	PHP_FE(selinux_setkeycreatecon,		arginfo_selinux_setkeycreatecon)
	PHP_FE(selinux_getsockcreatecon,	arginfo_selinux_getsockcreatecon)
	PHP_FE(selinux_setsockcreatecon,	arginfo_selinux_setsockcreatecon)

	/* get/set file context */
	PHP_FE(selinux_getfilecon,		arginfo_selinux_getfilecon)
	PHP_FE(selinux_lgetfilecon,		arginfo_selinux_lgetfilecon)
	PHP_FE(selinux_fgetfilecon,		arginfo_selinux_fgetfilecon)

	PHP_FE(selinux_setfilecon,		arginfo_selinux_setfilecon)
	PHP_FE(selinux_lsetfilecon,		arginfo_selinux_lsetfilecon)
	PHP_FE(selinux_fsetfilecon,		arginfo_selinux_fsetfilecon)

	/* labeled networking  */
	PHP_FE(selinux_getpeercon,		arginfo_selinux_getpeercon)

	/* security_compute_XXXX() wrappers */
	PHP_FE(selinux_compute_av,		arginfo_selinux_compute_av)
#ifdef HAVE_SECURITY_COMPUTE_CREATE_NAME
	PHP_FE(selinux_compute_create,		arginfo_selinux_compute_create)
#endif
	PHP_FE(selinux_compute_relabel,		arginfo_selinux_compute_relabel)
	PHP_FE(selinux_compute_member,		arginfo_selinux_compute_member)
	PHP_FE(selinux_compute_user,		arginfo_selinux_compute_user)

	/* get initial context */
	PHP_FE(selinux_get_initial_context,	arginfo_selinux_get_initial_context)

	/* sanity check in security context */
	PHP_FE(selinux_check_context,		arginfo_selinux_check_context)
	PHP_FE(selinux_canonicalize_context,	arginfo_selinux_canonicalize_context)

	/* booleans */
	PHP_FE(selinux_get_boolean_names,	arginfo_selinux_get_boolean_names)
	PHP_FE(selinux_get_boolean_pending,	arginfo_selinux_get_boolean_pending)
	PHP_FE(selinux_get_boolean_active,	arginfo_selinux_get_boolean_active)
	PHP_FE(selinux_set_boolean,		arginfo_selinux_set_boolean)
	PHP_FE(selinux_commit_booleans,		arginfo_selinux_commit_booleans)

	/* mcstrans */
	PHP_FE(selinux_trans_to_raw_context,	arginfo_selinux_trans_to_raw_context)
	PHP_FE(selinux_raw_to_trans_context,	arginfo_selinux_raw_to_trans_context)

	/* selabel wrappers */
	PHP_FE(selinux_file_label_lookup,	arginfo_selinux_file_label_lookup)
	PHP_FE(selinux_media_label_lookup,	arginfo_selinux_media_label_lookup)
	PHP_FE(selinux_x_label_lookup,		arginfo_selinux_x_label_lookup)
	PHP_FE(selinux_db_label_lookup,		arginfo_selinux_db_label_lookup)

	/* configuration files */
	PHP_FE(selinux_getenforcemode,		arginfo_selinux_getenforcemode)
	PHP_FE(selinux_getpolicytype,		arginfo_selinux_getpolicytype)
	PHP_FE(selinux_policy_root,		arginfo_selinux_policy_root)

	{NULL, NULL, NULL},
};

/*
 * SELinux module entry
 */
zend_module_entry selinux_module_entry = {
	STANDARD_MODULE_HEADER,
	"selinux",
	selinux_functions,
	NULL,			/* module_startup_func */
	NULL,			/* module_shutdown_func */
	NULL,			/* request_startup_func */
	NULL,			/* request_shutdown_func */
	NULL,			/* info_func */
	PHP_SELINUX_VERSION,
	STANDARD_MODULE_PROPERTIES,
};

#ifdef COMPILE_DL_SELINUX
ZEND_GET_MODULE(selinux)
#endif

/* {{{ proto bool selinux_is_enabled(void)
   Returns 'true' if SELinux is working on the host. */
PHP_FUNCTION(selinux_is_enabled)
{
	if (ZEND_NUM_ARGS() != 0)
		ZEND_WRONG_PARAM_COUNT();

	if (is_selinux_enabled() > 0)
		RETURN_TRUE;
	RETURN_FALSE;
}
/* }}} */

/* {{{ proto bool selinux_mls_is_enabled(void)
   Returns 'true' if SELinux is working with MLS policy. */
PHP_FUNCTION(selinux_mls_is_enabled)
{
	if (ZEND_NUM_ARGS() != 0)
		ZEND_WRONG_PARAM_COUNT();

	if (is_selinux_mls_enabled() > 0)
		RETURN_TRUE;
	RETURN_FALSE;
}
/* }}} */

/* {{{ proto int selinux_getenforce(void)
   Returns the current state of SELinux enforcing/permissive mode */
PHP_FUNCTION(selinux_getenforce)
{
	if (ZEND_NUM_ARGS() != 0)
		ZEND_WRONG_PARAM_COUNT();

	RETURN_LONG(security_getenforce());
}
/* }}} */

/* {{{ proto bool selinux_setenforce(int mode)
   Sets the state of SELinux enforcing/permissive mode */
PHP_FUNCTION(selinux_setenforce)
{
	zend_long mode;

	if (zend_parse_parameters(ZEND_NUM_ARGS(),
                                  "l", &mode) == FAILURE)
		return;

	if (!security_setenforce(mode))
		RETURN_TRUE;
	RETURN_FALSE;
}
/* }}} */

/* {{{ proto int selinux_policyvers(void)
   Returns the version of the security policy in the kernel. */
PHP_FUNCTION(selinux_policyvers)
{
	int policyvers;

	if (ZEND_NUM_ARGS() != 0)
		ZEND_WRONG_PARAM_COUNT();

	policyvers = security_policyvers();
	if (policyvers < 0)
		RETURN_FALSE;
	RETURN_LONG(policyvers);
}
/* }}} */

/* {{{ proto int selinux_deny_unknown(void)
   Returns the attitude for unknown classes/permissions */
PHP_FUNCTION(selinux_deny_unknown)
{
	if (ZEND_NUM_ARGS() != 0)
		ZEND_WRONG_PARAM_COUNT();

	if (security_deny_unknown() > 0)
		RETURN_TRUE;
	RETURN_FALSE;
}
/* }}} */

/* {{{ proto string selinux_getcon(void)
   Returns the context of the current process. */
PHP_FUNCTION(selinux_getcon)
{
	security_context_t context;

	if (ZEND_NUM_ARGS() != 0)
		ZEND_WRONG_PARAM_COUNT();

	if (getcon(&context) < 0)
		RETURN_FALSE;

	if (!context)
		RETURN_EMPTY_STRING();
	RETVAL_STRING(context);
	freecon(context);
}
/* }}} */

/* {{{ proto bool selinux_setcon(string context)
   Sets the context of the current process. */
PHP_FUNCTION(selinux_setcon)
{
	security_context_t context;
	size_t length;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s",
				  &context, &length) == FAILURE)
		return;

	if (length == 0)
		context = NULL;

	if (setcon(context) < 0)
		RETURN_FALSE;
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto string selinux_getpidcon(long pid)
   Returns the context of the process for the specified PID. */
PHP_FUNCTION(selinux_getpidcon)
{
	security_context_t context;
	zend_long pid;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "l",
				  &pid) == FAILURE)
		return;

	if (getpidcon((pid_t) pid, &context) < 0)
		RETURN_FALSE;

	if (!context)
		RETURN_EMPTY_STRING();
	RETVAL_STRING(context);
	freecon(context);
}
/* }}} */

/* {{{ proto string selinux_getprevcon(void)
   Returns the context of the process before the last execve(2). */
PHP_FUNCTION(selinux_getprevcon)
{
	security_context_t context;

	if (ZEND_NUM_ARGS() != 0)
		ZEND_WRONG_PARAM_COUNT();

	if (getprevcon(&context) < 0)
		RETURN_FALSE;

	if (!context)
		RETURN_EMPTY_STRING();
	RETVAL_STRING(context);
	freecon(context);
}
/* }}} */

/* {{{ proto string selinux_getexeccon(void)
   Returns the context used for executing a new program. */
PHP_FUNCTION(selinux_getexeccon)
{
	security_context_t context;

	if (ZEND_NUM_ARGS() != 0)
		ZEND_WRONG_PARAM_COUNT();

	if (getexeccon(&context) < 0)
		RETURN_FALSE;

	if (!context)
		RETURN_EMPTY_STRING();
	RETVAL_STRING(context);
	freecon(context);
}
/* }}} */

/* {{{ proto bool selinux_setexeccon(string context)
   Sets the context used for executing a new program. */
PHP_FUNCTION(selinux_setexeccon)
{
	security_context_t context;
	size_t length;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s",
				  &context, &length) == FAILURE)
		return;

	if (length == 0)
		context = NULL;

	if (setexeccon(context) < 0)
		RETURN_FALSE;
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto string selinux_getfscreatecon(void)
   Returns the context used for executing a new program. */
PHP_FUNCTION(selinux_getfscreatecon)
{
	security_context_t context;

	if (ZEND_NUM_ARGS() != 0)
		ZEND_WRONG_PARAM_COUNT();

	if (getfscreatecon(&context) < 0)
		RETURN_FALSE;

	if (!context)
		RETURN_EMPTY_STRING();
	RETVAL_STRING(context);
	freecon(context);
}
/* }}} */

/* {{{ proto bool selinux_setfscreatecon(string context)
   Sets the context used for creating a new file system object. */
PHP_FUNCTION(selinux_setfscreatecon)
{
	char *context;
	size_t length;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s",
				  &context, &length) == FAILURE)
		return;

	if (length == 0)
		context = NULL;

	if (setfscreatecon(context) < 0)
		RETURN_FALSE;
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto string selinux_getkeycreatecon(void)
   Returns the context used for creating a new kernel keyring. */
PHP_FUNCTION(selinux_getkeycreatecon)
{
	security_context_t context;

	if (ZEND_NUM_ARGS() != 0)
		ZEND_WRONG_PARAM_COUNT();

	if (getkeycreatecon(&context) < 0)
		RETURN_FALSE;

	if (!context)
		RETURN_EMPTY_STRING();
	RETVAL_STRING(context);
	freecon(context);
}
/* }}} */

/* {{{ proto bool selinux_setkeycreatecon(string context)
   Sets the context used for creating a new kernel keyring. */
PHP_FUNCTION(selinux_setkeycreatecon)
{
	char *context;
	size_t length;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s",
				  &context, &length) == FAILURE)
		return;

	if (length == 0)
		context = NULL;

	if (setkeycreatecon(context) < 0)
		RETURN_FALSE;
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto string selinux_getsockcreatecon(void)
   Returns the context used for creating a new socket object. */
PHP_FUNCTION(selinux_getsockcreatecon)
{
	security_context_t context;

	if (ZEND_NUM_ARGS() != 0)
		ZEND_WRONG_PARAM_COUNT();

	if (getsockcreatecon(&context) < 0)
		RETURN_FALSE;

	if (!context)
		RETURN_EMPTY_STRING();
	RETVAL_STRING(context);
	freecon(context);
}
/* }}} */

/* {{{ proto bool selinux_setsockcreatecon(string context)
   Sets the context used for creating a new socket object. */
PHP_FUNCTION(selinux_setsockcreatecon)
{
	security_context_t context;
	size_t length;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s",
				  &context, &length) == FAILURE)
		return;

	if (length == 0)
		context = NULL;

	if (setsockcreatecon(context) < 0)
		RETURN_FALSE;
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto string selinux_getfilecon(string filename)
   Returns the context associated with the given filename. */
PHP_FUNCTION(selinux_getfilecon)
{
	security_context_t context;
	char *filename;
	size_t length;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s",
				  &filename, &length) == FAILURE)
		return;

	if (getfilecon(filename, &context) < 0)
		RETURN_FALSE;

	RETVAL_STRING(context);
	freecon(context);
}
/* }}} */

/* {{{ proto string selinux_lgetfilecon(string filename)
   Identical to selinux_getfilecon, except in the case of a symbolic link. */
PHP_FUNCTION(selinux_lgetfilecon)
{
	security_context_t context;
	char *filename;
	size_t length;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s",
				  &filename, &length) == FAILURE)
		return;

	if (lgetfilecon(filename, &context) < 0)
		RETURN_FALSE;

	RETVAL_STRING(context);
	freecon(context);
}
/* }}} */

/* {{{ proto string selinux_fgetfilecon(resource stream)
   Identical to selinux_getfilecon,  only the open file pointed to by stream. */
PHP_FUNCTION(selinux_fgetfilecon)
{
	zval *z;
	php_stream *stream;
	security_context_t context;
	int fdesc;

	if (zend_parse_parameters(ZEND_NUM_ARGS(),
				  "z", &z) == FAILURE)
		return;
	php_stream_from_zval_no_verify(stream, z);

	if (!stream)
		RETURN_FALSE;

	if (php_stream_cast(stream, PHP_STREAM_AS_FD,
			    (void **) &fdesc, REPORT_ERRORS) != SUCCESS)
		RETURN_FALSE;

	if (fgetfilecon(fdesc, &context) < 0)
		RETURN_FALSE;

	RETVAL_STRING(context);
	freecon(context);
}
/* }}} */

/* {{{ proto bool selinux_setfilecon(string filename, string context)
   Sets the security context of the file system object. */
PHP_FUNCTION(selinux_setfilecon)
{
	char *filename, *context;
	size_t filename_len, context_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "ss",
				  &filename, &filename_len,
				  &context, &context_len) == FAILURE)
		return;

	if (setfilecon(filename, context) < 0)
		RETURN_FALSE;
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool selinux_lsetfilecon(string filename, string context)
   Identical to selinux_setfilecon, except in the case of a symbolic link. */
PHP_FUNCTION(selinux_lsetfilecon)
{
	char *filename, *context;
	size_t filename_len, context_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "ss",
				  &filename, &filename_len,
				  &context, &context_len) == FAILURE)
		return;

	if (lsetfilecon(filename, context) < 0)
			RETURN_FALSE;
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool selinux_fsetfilecon(resource stream, string context)
   Identical to selinux_setfilecon, only the open file pointed to by stream. */
PHP_FUNCTION(selinux_fsetfilecon)
{
	zval *z;
	php_stream *stream;
	security_context_t context;
	int fdesc;
	size_t context_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "zs",
				  &z, &context, &context_len) == FAILURE)
		return;

	php_stream_from_zval_no_verify(stream, z);
	if (!stream)
		RETURN_FALSE;

	if (php_stream_cast(stream, PHP_STREAM_AS_FD,
			    (void **) &fdesc, REPORT_ERRORS) != SUCCESS)
		RETURN_FALSE;

	if (fsetfilecon(fdesc, context) < 0)
		RETURN_FALSE;
	RETURN_TRUE;
}

/* proto string selinux_getpeercon(resource stream)
   Returns the context of the peer socket of given stream. */
PHP_FUNCTION(selinux_getpeercon)
{
	zval *z;
	php_stream *stream;
	security_context_t context;
	int sockfd;

	if (zend_parse_parameters(ZEND_NUM_ARGS(),
				  "z", &z) == FAILURE)
		return;

	php_stream_from_zval_no_verify(stream, z);
	if (!stream)
		RETURN_FALSE;

	if (php_stream_cast(stream, PHP_STREAM_AS_FD,
			    (void **) &sockfd, REPORT_ERRORS) != SUCCESS)
		RETURN_FALSE;
	if (getpeercon(sockfd, &context) < 0)
		RETURN_FALSE;
	RETVAL_STRING(context);
	freecon(context);
}
/* }}} */

/* {{{ proto array selinux_compute_av(string scon, string tcon, srting tclass)
   Retutns the access vector for the given scon, tcon and tclass. */
PHP_FUNCTION(selinux_compute_av)
{
	char *scontext, *tcontext, *tclass_name;
	size_t scontext_len, tcontext_len, tclass_len;
	security_class_t tclass;
	access_vector_t perm;
	struct av_decision avd;
	int permissive = 0;
	zval zallowed, zauditallow, zauditdeny;
	zval *allowed=&zallowed, *auditallow=&zauditallow, *auditdeny=&zauditdeny;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "sss",
				  &scontext, &scontext_len,
				  &tcontext, &tcontext_len,
				  &tclass_name, &tclass_len) == FAILURE)
		return;

	tclass = string_to_security_class(tclass_name);
	if (security_compute_av_flags(scontext, tcontext,
				      tclass, -1, &avd) < 0)
		RETURN_FALSE;

	if (avd.flags & SELINUX_AVD_FLAGS_PERMISSIVE)
	    permissive = 1;

	array_init(allowed);
	array_init(auditallow);
	array_init(auditdeny);

	for (perm = 1; perm; perm <<= 1)
	{
		char *perm_name
			= (char *) security_av_perm_to_string(tclass, perm);

		if (!perm_name)
			continue;

		add_assoc_bool(allowed, perm_name,
			       (avd.allowed & perm) ? 1 : 0);
		add_assoc_bool(auditallow, perm_name,
			       (avd.auditallow & perm) ? 1 : 0);
		add_assoc_bool(auditdeny, perm_name,
			       (avd.auditdeny & perm) ? 1 : 0);
	}

	array_init(return_value);
	add_assoc_zval(return_value, "allowed", allowed);
	add_assoc_zval(return_value, "auditallow", auditallow);
	add_assoc_zval(return_value, "auditdeny", auditdeny);
	add_assoc_long(return_value, "seqno", avd.seqno);
	add_assoc_bool(return_value, "permissive", permissive);
}
/* }}} */

#ifdef HAVE_SECURITY_COMPUTE_CREATE_NAME
/* {{{ proto string selinux_compute_create(string scon, string tcon, string tclass
                                           [, string objname])
   Returns the context for a new object in a particular class and contexts. */
PHP_FUNCTION(selinux_compute_create)
{
	char *scontext, *tcontext, *tclass_name, *objname;
	size_t scontext_len, tcontext_len, tclass_len, objname_len;
	security_context_t context;
	security_class_t tclass;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "sss|s",
				  &scontext, &scontext_len,
				  &tcontext, &tcontext_len,
				  &tclass_name, &tclass_len,
				  &objname, &objname_len) == FAILURE)
		return;

	tclass = string_to_security_class(tclass_name);
	if (security_compute_create_name(scontext, tcontext,
					 tclass, objname, &context) < 0)
		RETURN_FALSE;

	RETVAL_STRING(context);
	freecon(context);
}
/* }}} */
#endif

/* {{{ proto string selinux_compute_relabel(string scon, string tcon, string tclass)
   Returns the context used when an object is relabeled. */
PHP_FUNCTION(selinux_compute_relabel)
{
	char *scontext, *tcontext, *tclass_name;
	size_t scontext_len, tcontext_len, tclass_len;
	security_context_t context;
	security_class_t tclass;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "sss",
				  &scontext, &scontext_len,
				  &tcontext, &tcontext_len,
				  &tclass_name, &tclass_len) == FAILURE)
		return;

	tclass = string_to_security_class(tclass_name);
	if (security_compute_relabel(scontext, tcontext, tclass, &context) < 0)
		RETURN_FALSE;
	RETVAL_STRING(context);
	freecon(context);
}
/* }}} */

/* {{{ proto string selinux_compute_member(string scon, string tcon, string tclass)
   Returns the context to use when labeling a polyinstantiated object instance. */
PHP_FUNCTION(selinux_compute_member)
{
	char *scontext, *tcontext, *tclass_name;
	size_t scontext_len, tcontext_len, tclass_len;
	security_context_t context;
	security_class_t tclass;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "sss",
				  &scontext, &scontext_len,
				  &tcontext, &tcontext_len,
				  &tclass_name, &tclass_len) == FAILURE)
		return;

	tclass = string_to_security_class(tclass_name);
	if (security_compute_member(scontext, tcontext, tclass, &context) < 0)
		RETURN_FALSE;
	RETVAL_STRING(context);
	freecon(context);
}
/* }}} */

/* {{{ proto array selinux_compute_user(string scon, string username)
   Returns a set of user contexts that can be reached from a source context. */
PHP_FUNCTION(selinux_compute_user)
{
	char *scontext, *username;
	size_t scontext_len, username_len;
	security_context_t *contexts;
	int i;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "ss",
				  &scontext, &scontext_len,
				  &username, &username_len) == FAILURE)
		return;

	if (security_compute_user(scontext, username, &contexts) < 0)
		RETURN_FALSE;

	array_init(return_value);
	for (i=0; contexts[i]; i++)
	{
		add_next_index_string(return_value, contexts[i]);
	}
	freeconary(contexts);
}
/* }}} */

/* {{{ proto string selinux_get_initial_context(string name)
   Returns the context of a kernel initial security identifier specified by name.*/
PHP_FUNCTION(selinux_get_initial_context)
{
	char *name;
	size_t length;
	security_context_t context;

	if (zend_parse_parameters(ZEND_NUM_ARGS(),
				  "s", &name, &length) == FAILURE)
		return;

	if (security_get_initial_context(name, &context) < 0)
		RETURN_FALSE;

	RETVAL_STRING(context);
	freecon(context);
}
/* }}} */

/* {{{ proto bool selinux_check_context(string context)
   Checks whether the given context is valid, or not. */
PHP_FUNCTION(selinux_check_context)
{
	char *context;
	size_t length;

	if (zend_parse_parameters(ZEND_NUM_ARGS(),
				  "s", &context, &length) == FAILURE)
		return;

	if (security_check_context(context) < 0)
		RETURN_FALSE;
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto string selinux_canonicalize_context(string context)
   Returns canonicalized context if the given one is valid. */
PHP_FUNCTION(selinux_canonicalize_context)
{
	security_context_t canonicalized;
	char *context;
	size_t length;

	if (zend_parse_parameters(ZEND_NUM_ARGS(),
				  "s", &context, &length) == FAILURE)
		return;

	if (security_canonicalize_context(context, &canonicalized) < 0)
		RETURN_FALSE;

	RETVAL_STRING(canonicalized);
	freecon(canonicalized);
}
/* }}} */

/* {{{ proto array selinux_get_boolean_names(void)
   Returns a list of boolean name, supported by the working policy. */
PHP_FUNCTION(selinux_get_boolean_names)
{
	char **bool_names;
	int i, length;

	if (ZEND_NUM_ARGS() != 0)
		ZEND_WRONG_PARAM_COUNT();

	if (security_get_boolean_names(&bool_names, &length) < 0)
		RETURN_FALSE;

	array_init(return_value);
	for (i=0; i < length; i++) {
		add_next_index_string(return_value, bool_names[i]);
		free(bool_names[i]);
	}
	free(bool_names);
}
/* }}} */

/* {{{ proto int selinux_get_boolean_pending(string bool_name)
   Returns a pending value for boolean specified in bool_name. */
PHP_FUNCTION(selinux_get_boolean_pending)
{
	char *bool_name;
	size_t length;
	long value;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s",
				  &bool_name, &length) == FAILURE)
		RETURN_LONG(-1);

	value = security_get_boolean_pending(bool_name);
	RETURN_LONG(value);
}
/* }}} */

/* {{{ proto int selinux_get_boolean_active(string bool_name)
   Returns an active value for boolean specified in bool_name. */
PHP_FUNCTION(selinux_get_boolean_active)
{
	char *bool_name;
	size_t length;
	long value;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s",
				  &bool_name, &length) == FAILURE)
		RETURN_LONG(-1);

	value = security_get_boolean_active(bool_name);
	RETURN_LONG(value);
}
/* }}} */

/* {{{ proto bool selinux_set_boolean(string bool_name, bool value)
   Sets the pending value for boolean specified in bool_name.*/
PHP_FUNCTION(selinux_set_boolean)
{
	char *bool_name;
	size_t length;
	zend_bool new_value;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "sb",
				  &bool_name, &length, &new_value) == FAILURE)
		return;

	if (security_set_boolean(bool_name, new_value) < 0)
		RETURN_FALSE;
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool selinux_commit_booleans(void)
   Commits all the pending values for booleans. */
PHP_FUNCTION(selinux_commit_booleans)
{
	if (ZEND_NUM_ARGS() != 0)
		ZEND_WRONG_PARAM_COUNT();

	if (security_commit_booleans() < 0)
		RETURN_FALSE;
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto string selinux_trans_to_raw_context(string context)
   Translate a human-readable context into internal system format.*/
PHP_FUNCTION(selinux_trans_to_raw_context)
{
	security_context_t raw_context;
	char *context;
	size_t length;

	if (zend_parse_parameters(ZEND_NUM_ARGS(),
				  "s", &context, &length) == FAILURE)
		return;

	if (selinux_trans_to_raw_context(context, &raw_context) < 0 || !raw_context)
		RETURN_FALSE;
	RETVAL_STRING(raw_context);
	freecon(raw_context);
}
/* }}} */

/* {{{ proto string selinux_raw_to_trans_context(string context)
   Translate a human-readable context from internal system format. */
PHP_FUNCTION(selinux_raw_to_trans_context)
{
	security_context_t trans_context;
	char *context;
	size_t length;

	if (zend_parse_parameters(ZEND_NUM_ARGS(),
				  "s", &context, &length) == FAILURE)
		return;

	if (selinux_raw_to_trans_context(context, &trans_context) < 0)
		RETURN_FALSE;
	RETVAL_STRING(trans_context);
	freecon(trans_context);
}
/* }}} */

/* {{{ proto string selinux_file_label_lookup(string pathname, int mode
                                              [, bool validate
                                              [, bool baseonly
                                              [, string subset
                                              [, string specfile ]]]])
   Returns the expected security context for given pathname/mode */
PHP_FUNCTION(selinux_file_label_lookup)
{
	char *pathname;
	char *subset = NULL;
	char *specfile = NULL;
	zend_bool validate = 0;
	zend_bool baseonly = 0;
	size_t pathname_len, subset_len, specfile_len;
	zend_long mode;
	security_context_t context;
	struct selabel_handle *hnd;
	struct selinux_opt opts[4] = {
		{ SELABEL_OPT_VALIDATE, NULL },
		{ SELABEL_OPT_BASEONLY, NULL },
		{ SELABEL_OPT_SUBSET, NULL },
		{ SELABEL_OPT_PATH, NULL }
	};

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "sl|bbss",
				  &pathname, &pathname_len, &mode,
				  &validate, &baseonly,
				  &subset, &subset_len,
				  &specfile, &specfile_len) == FAILURE)
		return;

	/* set options */
	opts[0].value = (validate ? (char *) 1 : (char *) 0);
	opts[1].value = (baseonly ? (char *) 1 : (char *) 0);
	opts[2].value = subset;
	opts[3].value = specfile;

	hnd = selabel_open(SELABEL_CTX_FILE, opts, 4);
	if (!hnd)
		RETURN_FALSE;

	if (selabel_lookup(hnd, &context, pathname, (int)mode) < 0)
	{
		selabel_close(hnd);
		RETURN_FALSE;
	}
	selabel_close(hnd);
	RETVAL_STRING(context);
	freecon(context);
}

/* {{{ proto string selinux_media_label_lookup(string device_name
                                               [, bool validate [, string specfile]])
   Returns the expected security context for given device */
PHP_FUNCTION(selinux_media_label_lookup)
{
	char *device;
	char *specfile = NULL;
	zend_bool validate = 0;
	size_t device_len, specfile_len;
	security_context_t context;
	struct selabel_handle *hnd;
	struct selinux_opt opts[2] = {
		{ SELABEL_OPT_VALIDATE, NULL },
		{ SELABEL_OPT_PATH, NULL }
	};

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s|bs",
				  &device, &device_len,
				  &validate,
				  &specfile, &specfile_len) == FAILURE)
		return;

	/* set option */
	opts[0].value = (validate ? (char *) 1 : (char *) 0);
	opts[1].value = specfile;

	hnd = selabel_open(SELABEL_CTX_MEDIA, opts, 2);
	if (!hnd)
		RETURN_FALSE;

	if (selabel_lookup(hnd, &context, device, 0) < 0)
	{
		selabel_close(hnd);
		RETURN_FALSE;
	}
	selabel_close(hnd);
	RETVAL_STRING(context);
	freecon(context);
}

/* {{{ proto string selinux_x_label_lookup(string x_key, string x_type)
   Returns the expected security context for given device */
PHP_FUNCTION(selinux_x_label_lookup)
{
	char   *x_key, *x_type;
	size_t	x_key_len, x_type_len;
	int	i;
	static struct {
		char   *type;
		int	code;
	} x_catalog[] = {
		{ "property",		SELABEL_X_PROP },
		{ "extension",		SELABEL_X_EXT },
		{ "client",		SELABEL_X_CLIENT },
		{ "event",		SELABEL_X_EVENT },
		{ "selection",		SELABEL_X_SELN },
		{ "poly_property",	SELABEL_X_POLYPROP },
		{ "poly_selection",	SELABEL_X_POLYSELN },
		{ NULL, -1 }
	};

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "ss",
				  &x_key,  &x_key_len,
				  &x_type, &x_type_len) == FAILURE)
		return;

	for (i=0; x_catalog[i].type != NULL; i++)
	{
		security_context_t	context;
		struct selabel_handle  *hnd;

		if (strcmp(x_type, x_catalog[i].type) != 0)
			continue;

		hnd = selabel_open(SELABEL_CTX_X, NULL, 0);
		if (!hnd)
			RETURN_FALSE;

		if (selabel_lookup(hnd, &context, x_key, x_catalog[i].code) < 0)
		{
			selabel_close(hnd);
			RETURN_FALSE;
		}
		selabel_close(hnd);
		RETVAL_STRING(context);
		freecon(context);

		return;
	}
	RETURN_FALSE;
}
/* }}} */

/* {{{ proto string selinux_db_label_lookup(string x_name, string x_type)
   Returns the expected security context for given device */
PHP_FUNCTION(selinux_db_label_lookup)
{
	char   *db_key, *db_type;
	size_t	db_key_len, db_type_len;
	int	i;
	static struct {
		char   *type;
		int	code;
	} db_catalog[] = {
		{ "database",	SELABEL_DB_DATABASE },
		{ "schema",	SELABEL_DB_SCHEMA },
		{ "table",	SELABEL_DB_TABLE },
		{ "column",	SELABEL_DB_COLUMN },
		{ "sequence",	SELABEL_DB_SEQUENCE },
		{ "view",	SELABEL_DB_VIEW },
		{ "procedure",	SELABEL_DB_PROCEDURE },
		{ "blob",	SELABEL_DB_BLOB },
		{ "tuple",	SELABEL_DB_TUPLE },
#ifdef SELABEL_DB_LANGUAGE
		{ "language",	SELABEL_DB_LANGUAGE },
#endif
		{ NULL, -1 }
	};

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "ss",
				  &db_key,  &db_key_len,
				  &db_type, &db_type_len) == FAILURE)
		return;

	for (i=0; db_catalog[i].type != NULL; i++)
	{
		security_context_t	context;
		struct selabel_handle  *hnd;

		if (strcmp(db_type, db_catalog[i].type) != 0)
			continue;

		hnd = selabel_open(SELABEL_CTX_DB, NULL, 0);
		if (!hnd)
			RETURN_FALSE;

		if (selabel_lookup(hnd, &context, db_key, db_catalog[i].code) < 0)
		{
			selabel_close(hnd);
			RETURN_FALSE;
		}
		selabel_close(hnd);
		RETVAL_STRING(context);
		freecon(context);

		return;
	}
	RETURN_FALSE;
}
/* }}} */

/* {{{ proto string selinux_getenforcemode(void)
   Returns the initial state on the system, configured in /etc/selinux/config. */
PHP_FUNCTION(selinux_getenforcemode)
{
	int enforce;

	if (ZEND_NUM_ARGS() != 0)
		ZEND_WRONG_PARAM_COUNT();
	if (selinux_getenforcemode(&enforce))
		RETURN_FALSE;

	if (enforce > 0) {
		RETVAL_STRING("enforcing");
	} else if (enforce < 0) {
		RETVAL_STRING("disabled");
	} else {
		RETVAL_STRING("permissive");
	}
}
/* }}} */

/* {{{ proto string selinux_getpolicytype(void)
   Returns the default policy type on the system, configured in /etc/selinux/config. */
PHP_FUNCTION(selinux_getpolicytype)
{
	char *policytype;

	if (ZEND_NUM_ARGS() != 0)
		ZEND_WRONG_PARAM_COUNT();
	if (selinux_getpolicytype(&policytype) < 0)
		RETURN_FALSE;
	RETVAL_STRING(policytype);
	free(policytype);
}
/* }}} */

/* {{{ proto string selinux_policy_root(void)
   Returns the directory path which stores the policy and context configuration. */
PHP_FUNCTION(selinux_policy_root)
{
	char *root;

	if (ZEND_NUM_ARGS() != 0)
		ZEND_WRONG_PARAM_COUNT();

	root = (char *) selinux_policy_root();
	if (!root)
		RETURN_FALSE;
	RETVAL_STRING(root);
}
/* }}} */
