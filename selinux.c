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
#if PHP_VERSION_ID < 80000
#define RETURN_THROWS() return
#include "selinux_legacy_arginfo.h"
#else
#include "selinux_arginfo.h"
#endif


/*
 * SELinux module entry
 */
zend_module_entry selinux_module_entry = {
	STANDARD_MODULE_HEADER,
	"selinux",
	ext_functions,
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
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}
	if (is_selinux_enabled() > 0) {
		RETURN_TRUE;
	}
	RETURN_FALSE;
}
/* }}} */

/* {{{ proto bool selinux_mls_is_enabled(void)
   Returns 'true' if SELinux is working with MLS policy. */
PHP_FUNCTION(selinux_mls_is_enabled)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}
	if (is_selinux_mls_enabled() > 0) {
		RETURN_TRUE;
	}
	RETURN_FALSE;
}
/* }}} */

/* {{{ proto int selinux_getenforce(void)
   Returns the current state of SELinux enforcing/permissive mode */
PHP_FUNCTION(selinux_getenforce)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}
	RETURN_LONG(security_getenforce());
}
/* }}} */

/* {{{ proto bool selinux_setenforce(int mode)
   Sets the state of SELinux enforcing/permissive mode */
PHP_FUNCTION(selinux_setenforce)
{
	zend_long mode;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &mode) == FAILURE) {
		RETURN_THROWS();
	}
	if (!security_setenforce(mode)) {
		RETURN_TRUE;
	}
	RETURN_FALSE;
}
/* }}} */

/* {{{ proto int selinux_policyvers(void)
   Returns the version of the security policy in the kernel. */
PHP_FUNCTION(selinux_policyvers)
{
	int policyvers;

	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}
	policyvers = security_policyvers();
	if (policyvers < 0) {
		RETURN_FALSE;
	}
	RETURN_LONG(policyvers);
}
/* }}} */

/* {{{ proto int selinux_deny_unknown(void)
   Returns the attitude for unknown classes/permissions */
PHP_FUNCTION(selinux_deny_unknown)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}
	if (security_deny_unknown() > 0) {
		RETURN_TRUE;
	}
	RETURN_FALSE;
}
/* }}} */

/* {{{ proto string selinux_getcon(void)
   Returns the context of the current process. */
PHP_FUNCTION(selinux_getcon)
{
	char *context;

	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}
	if (getcon(&context) < 0) {
		RETURN_FALSE;
	}
	if (!context) {
		RETURN_EMPTY_STRING();
	}
	RETVAL_STRING(context);
	freecon(context);
}
/* }}} */

/* {{{ proto bool selinux_setcon(string context)
   Sets the context of the current process. */
PHP_FUNCTION(selinux_setcon)
{
	char *context;
	size_t length;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &context, &length) == FAILURE) {
		RETURN_THROWS();
	}
	if (length == 0) {
		context = NULL;
	}

	if (setcon(context) < 0) {
		RETURN_FALSE;
	}
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto string selinux_getpidcon(long pid)
   Returns the context of the process for the specified PID. */
PHP_FUNCTION(selinux_getpidcon)
{
	char *context;
	zend_long pid;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &pid) == FAILURE) {
		RETURN_THROWS();
	}
	if (getpidcon((pid_t) pid, &context) < 0) {
		RETURN_FALSE;
	}
	if (!context) {
		RETURN_EMPTY_STRING();
	}
	RETVAL_STRING(context);
	freecon(context);
}
/* }}} */

/* {{{ proto string selinux_getprevcon(void)
   Returns the context of the process before the last execve(2). */
PHP_FUNCTION(selinux_getprevcon)
{
	char *context;

	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}
	if (getprevcon(&context) < 0) {
		RETURN_FALSE;
	}
	if (!context) {
		RETURN_EMPTY_STRING();
	}
	RETVAL_STRING(context);
	freecon(context);
}
/* }}} */

/* {{{ proto string selinux_getexeccon(void)
   Returns the context used for executing a new program. */
PHP_FUNCTION(selinux_getexeccon)
{
	char *context;

	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}
	if (getexeccon(&context) < 0) {
		RETURN_FALSE;
	}
	if (!context) {
		RETURN_EMPTY_STRING();
	}
	RETVAL_STRING(context);
	freecon(context);
}
/* }}} */

/* {{{ proto bool selinux_setexeccon(string context)
   Sets the context used for executing a new program. */
PHP_FUNCTION(selinux_setexeccon)
{
	char *context;
	size_t length;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &context, &length) == FAILURE) {
		RETURN_THROWS();
	}
	if (length == 0) {
		context = NULL;
	}
	if (setexeccon(context) < 0) {
		RETURN_FALSE;
	}
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto string selinux_getfscreatecon(void)
   Returns the context used for executing a new program. */
PHP_FUNCTION(selinux_getfscreatecon)
{
	char *context;

	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}
	if (getfscreatecon(&context) < 0) {
		RETURN_FALSE;
	}
	if (!context) {
		RETURN_EMPTY_STRING();
	}
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

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &context, &length) == FAILURE) {
		RETURN_THROWS();
	}
	if (length == 0) {
		context = NULL;
	}
	if (setfscreatecon(context) < 0) {
		RETURN_FALSE;
	}
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto string selinux_getkeycreatecon(void)
   Returns the context used for creating a new kernel keyring. */
PHP_FUNCTION(selinux_getkeycreatecon)
{
	char *context;

	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}
	if (getkeycreatecon(&context) < 0) {
		RETURN_FALSE;
	}
	if (!context) {
		RETURN_EMPTY_STRING();
	}
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

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &context, &length) == FAILURE) {
		RETURN_THROWS();
	}
	if (length == 0) {
		context = NULL;
	}
	if (setkeycreatecon(context) < 0) {
		RETURN_FALSE;
	}
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto string selinux_getsockcreatecon(void)
   Returns the context used for creating a new socket object. */
PHP_FUNCTION(selinux_getsockcreatecon)
{
	char *context;

	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}
	if (getsockcreatecon(&context) < 0) {
		RETURN_FALSE;
	}
	if (!context) {
		RETURN_EMPTY_STRING();
	}
	RETVAL_STRING(context);
	freecon(context);
}
/* }}} */

/* {{{ proto bool selinux_setsockcreatecon(string context)
   Sets the context used for creating a new socket object. */
PHP_FUNCTION(selinux_setsockcreatecon)
{
	char *context;
	size_t length;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &context, &length) == FAILURE) {
		RETURN_THROWS();
	}
	if (length == 0) {
		context = NULL;
	}
	if (setsockcreatecon(context) < 0) {
		RETURN_FALSE;
	}
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto string selinux_getfilecon(string filename)
   Returns the context associated with the given filename. */
PHP_FUNCTION(selinux_getfilecon)
{
	char *context;
	char *filename;
	size_t length;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &filename, &length) == FAILURE) {
		RETURN_THROWS();
	}
	if (getfilecon(filename, &context) < 0) {
		RETURN_FALSE;
	}
	RETVAL_STRING(context);
	freecon(context);
}
/* }}} */

/* {{{ proto string selinux_lgetfilecon(string filename)
   Identical to selinux_getfilecon, except in the case of a symbolic link. */
PHP_FUNCTION(selinux_lgetfilecon)
{
	char *context;
	char *filename;
	size_t length;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &filename, &length) == FAILURE) {
		RETURN_THROWS();
	}
	if (lgetfilecon(filename, &context) < 0) {
		RETURN_FALSE;
	}
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
	char *context;
	int fdesc;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "z", &z) == FAILURE) {
		RETURN_THROWS();
	}
	php_stream_from_zval_no_verify(stream, z);

	if (!stream) {
		RETURN_FALSE;
	}
	if (php_stream_cast(stream, PHP_STREAM_AS_FD,
			    (void **) &fdesc, REPORT_ERRORS) != SUCCESS) {
		RETURN_FALSE;
	}
	if (fgetfilecon(fdesc, &context) < 0) {
		RETURN_FALSE;
	}
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
				  &context, &context_len) == FAILURE) {
		RETURN_THROWS();
	}
	if (setfilecon(filename, context) < 0) {
		RETURN_FALSE;
	}
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
				  &context, &context_len) == FAILURE) {
		RETURN_THROWS();
	}
	if (lsetfilecon(filename, context) < 0) {
			RETURN_FALSE;
	}
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool selinux_fsetfilecon(resource stream, string context)
   Identical to selinux_setfilecon, only the open file pointed to by stream. */
PHP_FUNCTION(selinux_fsetfilecon)
{
	zval *z;
	php_stream *stream;
	char *context;
	int fdesc;
	size_t context_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "zs",
				  &z, &context, &context_len) == FAILURE) {
		RETURN_THROWS();
	}
	php_stream_from_zval_no_verify(stream, z);
	if (!stream) {
		RETURN_FALSE;
	}
	if (php_stream_cast(stream, PHP_STREAM_AS_FD,
			    (void **) &fdesc, REPORT_ERRORS) != SUCCESS) {
		RETURN_FALSE;
	}
	if (fsetfilecon(fdesc, context) < 0) {
		RETURN_FALSE;
	}
	RETURN_TRUE;
}

/* proto string selinux_getpeercon(resource stream)
   Returns the context of the peer socket of given stream. */
PHP_FUNCTION(selinux_getpeercon)
{
	zval *z;
	php_stream *stream;
	char *context;
	int sockfd;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "z", &z) == FAILURE) {
		RETURN_THROWS();
	}
	php_stream_from_zval_no_verify(stream, z);
	if (!stream) {
		RETURN_FALSE;
	}
	if (php_stream_cast(stream, PHP_STREAM_AS_FD,
			    (void **) &sockfd, REPORT_ERRORS) != SUCCESS) {
		RETURN_FALSE;
	}
	if (getpeercon(sockfd, &context) < 0) {
		RETURN_FALSE;
	}
	RETVAL_STRING(context);
	freecon(context);
}
/* }}} */

/* {{{ proto array selinux_compute_av(string scon, string tcon, string tclass)
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
				  &tclass_name, &tclass_len) == FAILURE) {
		RETURN_THROWS();
	}
	tclass = string_to_security_class(tclass_name);
	if (security_compute_av_flags(scontext, tcontext,
				      tclass, -1, &avd) < 0) {
		RETURN_FALSE;
	}
	if (avd.flags & SELINUX_AVD_FLAGS_PERMISSIVE) {
	    permissive = 1;
	}
	array_init(allowed);
	array_init(auditallow);
	array_init(auditdeny);

	for (perm = 1; perm; perm <<= 1)
	{
		char *perm_name
			= (char *) security_av_perm_to_string(tclass, perm);

		if (!perm_name) {
			continue;
		}
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
	char *scontext, *tcontext, *tclass_name, *objname = NULL;
	size_t scontext_len, tcontext_len, tclass_len, objname_len;
	char *context;
	security_class_t tclass;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "sss|s",
				  &scontext, &scontext_len,
				  &tcontext, &tcontext_len,
				  &tclass_name, &tclass_len,
				  &objname, &objname_len) == FAILURE) {
		RETURN_THROWS();
	}
	tclass = string_to_security_class(tclass_name);
	if (security_compute_create_name(scontext, tcontext,
					 tclass, objname, &context) < 0) {
		RETURN_FALSE;
	}
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
	char *context;
	security_class_t tclass;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "sss",
				  &scontext, &scontext_len,
				  &tcontext, &tcontext_len,
				  &tclass_name, &tclass_len) == FAILURE) {
		RETURN_THROWS();
	}
	tclass = string_to_security_class(tclass_name);
	if (security_compute_relabel(scontext, tcontext, tclass, &context) < 0) {
		RETURN_FALSE;
	}
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
	char *context;
	security_class_t tclass;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "sss",
				  &scontext, &scontext_len,
				  &tcontext, &tcontext_len,
				  &tclass_name, &tclass_len) == FAILURE) {
		RETURN_THROWS();
	}
	tclass = string_to_security_class(tclass_name);
	if (security_compute_member(scontext, tcontext, tclass, &context) < 0) {
		RETURN_FALSE;
	}
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
	char **contexts;
	int i;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "ss",
				  &scontext, &scontext_len,
				  &username, &username_len) == FAILURE) {
		RETURN_THROWS();
	}
	if (security_compute_user(scontext, username, &contexts) < 0) {
		RETURN_FALSE;
	}
	array_init(return_value);
	for (i=0; contexts[i]; i++)	{
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
	char *context;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &name, &length) == FAILURE) {
		RETURN_THROWS();
	}
	if (security_get_initial_context(name, &context) < 0) {
		RETURN_FALSE;
	}
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

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &context, &length) == FAILURE) {
		RETURN_THROWS();
	}
	if (security_check_context(context) < 0) {
		RETURN_FALSE;
	}
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto string selinux_canonicalize_context(string context)
   Returns canonicalized context if the given one is valid. */
PHP_FUNCTION(selinux_canonicalize_context)
{
	char *canonicalized;
	char *context;
	size_t length;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &context, &length) == FAILURE) {
		RETURN_THROWS();
	}
	if (security_canonicalize_context(context, &canonicalized) < 0) {
		RETURN_FALSE;
	}
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

	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}
	if (security_get_boolean_names(&bool_names, &length) < 0) {
		RETURN_FALSE;
	}
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

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &bool_name, &length) == FAILURE) {
		RETURN_LONG(-1);
	}
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

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &bool_name, &length) == FAILURE) {
		RETURN_LONG(-1);
	}
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
				  &bool_name, &length, &new_value) == FAILURE) {
		RETURN_THROWS();
	}
	if (security_set_boolean(bool_name, new_value) < 0) {
		RETURN_FALSE;
	}
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool selinux_commit_booleans(void)
   Commits all the pending values for booleans. */
PHP_FUNCTION(selinux_commit_booleans)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}
	if (security_commit_booleans() < 0) {
		RETURN_FALSE;
	}
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto string selinux_trans_to_raw_context(string context)
   Translate a human-readable context into internal system format.*/
PHP_FUNCTION(selinux_trans_to_raw_context)
{
	char *raw_context;
	char *context;
	size_t length;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &context, &length) == FAILURE) {
		RETURN_THROWS();
	}
	if (selinux_trans_to_raw_context(context, &raw_context) < 0 || !raw_context) {
		RETURN_FALSE;
	}
	RETVAL_STRING(raw_context);
	freecon(raw_context);
}
/* }}} */

/* {{{ proto string selinux_raw_to_trans_context(string context)
   Translate a human-readable context from internal system format. */
PHP_FUNCTION(selinux_raw_to_trans_context)
{
	char *trans_context;
	char *context;
	size_t length;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &context, &length) == FAILURE) {
		RETURN_THROWS();
	}
	if (selinux_raw_to_trans_context(context, &trans_context) < 0) {
		RETURN_FALSE;
	}
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
	char *context;
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
				  &specfile, &specfile_len) == FAILURE) {
		RETURN_THROWS();
	}

	/* set options */
	opts[0].value = (validate ? (char *) 1 : (char *) 0);
	opts[1].value = (baseonly ? (char *) 1 : (char *) 0);
	opts[2].value = subset;
	opts[3].value = specfile;

	hnd = selabel_open(SELABEL_CTX_FILE, opts, 4);
	if (!hnd) {
		RETURN_FALSE;
	}
	if (selabel_lookup(hnd, &context, pathname, (int)mode) < 0) {
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
	char *context;
	struct selabel_handle *hnd;
	struct selinux_opt opts[2] = {
		{ SELABEL_OPT_VALIDATE, NULL },
		{ SELABEL_OPT_PATH, NULL }
	};

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s|bs",
				  &device, &device_len,
				  &validate,
				  &specfile, &specfile_len) == FAILURE) {
		RETURN_THROWS();
	}

	/* set option */
	opts[0].value = (validate ? (char *) 1 : (char *) 0);
	opts[1].value = specfile;

	hnd = selabel_open(SELABEL_CTX_MEDIA, opts, 2);
	if (!hnd) {
		RETURN_FALSE;
	}
	if (selabel_lookup(hnd, &context, device, 0) < 0) {
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
				  &x_type, &x_type_len) == FAILURE) {
		RETURN_THROWS();
	}

	for (i=0; x_catalog[i].type != NULL; i++)
	{
		char *context;
		struct selabel_handle  *hnd;

		if (strcmp(x_type, x_catalog[i].type) != 0) {
			continue;
		}
		hnd = selabel_open(SELABEL_CTX_X, NULL, 0);
		if (!hnd) {
			RETURN_FALSE;
		}
		if (selabel_lookup(hnd, &context, x_key, x_catalog[i].code) < 0) {
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
				  &db_type, &db_type_len) == FAILURE) {
		RETURN_THROWS();
	}
	for (i=0; db_catalog[i].type != NULL; i++)
	{
		char *context;
		struct selabel_handle  *hnd;

		if (strcmp(db_type, db_catalog[i].type) != 0) {
			continue;
		}
		hnd = selabel_open(SELABEL_CTX_DB, NULL, 0);
		if (!hnd) {
			RETURN_FALSE;
		}
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

	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}
	if (selinux_getenforcemode(&enforce)) {
		RETURN_FALSE;
	}
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

	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}
	if (selinux_getpolicytype(&policytype) < 0) {
		RETURN_FALSE;
	}
	RETVAL_STRING(policytype);
	free(policytype);
}
/* }}} */

/* {{{ proto string selinux_policy_root(void)
   Returns the directory path which stores the policy and context configuration. */
PHP_FUNCTION(selinux_policy_root)
{
	char *root;

	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}
	root = (char *) selinux_policy_root();
	if (!root) {
		RETURN_FALSE;
	}
	RETVAL_STRING(root);
}
/* }}} */
