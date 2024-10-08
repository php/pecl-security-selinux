/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 25241063e6492ceecb42e7893fb922befbbfaf4d */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_selinux_is_enabled, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

#define arginfo_selinux_mls_is_enabled arginfo_selinux_is_enabled

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_selinux_getenforce, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_selinux_setenforce, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, mode, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_selinux_policyvers, 0, 0, MAY_BE_LONG|MAY_BE_FALSE)
ZEND_END_ARG_INFO()

#define arginfo_selinux_deny_unknown arginfo_selinux_is_enabled

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_selinux_getcon, 0, 0, MAY_BE_STRING|MAY_BE_FALSE)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_selinux_setcon, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, context, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_selinux_getpidcon, 0, 1, MAY_BE_STRING|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, pid, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_selinux_getprevcon arginfo_selinux_getcon

#define arginfo_selinux_getexeccon arginfo_selinux_getcon

#define arginfo_selinux_setexeccon arginfo_selinux_setcon

#define arginfo_selinux_getfscreatecon arginfo_selinux_getcon

#define arginfo_selinux_setfscreatecon arginfo_selinux_setcon

#define arginfo_selinux_getkeycreatecon arginfo_selinux_getcon

#define arginfo_selinux_setkeycreatecon arginfo_selinux_setcon

#define arginfo_selinux_getsockcreatecon arginfo_selinux_getcon

#define arginfo_selinux_setsockcreatecon arginfo_selinux_setcon

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_selinux_getfilecon, 0, 1, MAY_BE_STRING|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, filename, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_selinux_lgetfilecon arginfo_selinux_getfilecon

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_selinux_fgetfilecon, 0, 1, MAY_BE_STRING|MAY_BE_FALSE)
	ZEND_ARG_INFO(0, stream)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_selinux_setfilecon, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, filename, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, context, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_selinux_lsetfilecon arginfo_selinux_setfilecon

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_selinux_fsetfilecon, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_INFO(0, stream)
	ZEND_ARG_TYPE_INFO(0, context, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_selinux_getpeercon arginfo_selinux_fgetfilecon

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_selinux_compute_av, 0, 3, MAY_BE_ARRAY|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, scontext, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, tcontext, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, tclass, IS_STRING, 0)
ZEND_END_ARG_INFO()

#if defined(HAVE_SECURITY_COMPUTE_CREATE_NAME)
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_selinux_compute_create, 0, 3, MAY_BE_STRING|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, scontext, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, tcontext, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, tclass, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, name, IS_STRING, 1, "null")
ZEND_END_ARG_INFO()
#endif

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_selinux_compute_relabel, 0, 3, MAY_BE_STRING|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, scontext, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, tcontext, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, tclass, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_selinux_compute_member arginfo_selinux_compute_relabel

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_selinux_compute_user, 0, 2, MAY_BE_ARRAY|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, scontext, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, username, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_selinux_get_initial_context, 0, 1, MAY_BE_STRING|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_selinux_check_context arginfo_selinux_setcon

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_selinux_canonicalize_context, 0, 1, MAY_BE_STRING|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, context, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_selinux_get_boolean_names, 0, 0, MAY_BE_ARRAY|MAY_BE_FALSE)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_selinux_get_boolean_pending, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, bool_name, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_selinux_get_boolean_active arginfo_selinux_get_boolean_pending

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_selinux_set_boolean, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, bool_name, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, bool_value, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_selinux_commit_booleans arginfo_selinux_is_enabled

#define arginfo_selinux_trans_to_raw_context arginfo_selinux_canonicalize_context

#define arginfo_selinux_raw_to_trans_context arginfo_selinux_canonicalize_context

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_selinux_file_label_lookup, 0, 2, MAY_BE_STRING|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, pathname, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, mode, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, validate, _IS_BOOL, 0, "false")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, baseonly, _IS_BOOL, 0, "false")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, subset, IS_STRING, 1, "null")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, specfile, IS_STRING, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_selinux_media_label_lookup, 0, 1, MAY_BE_STRING|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, device_name, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, validate, _IS_BOOL, 0, "false")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, specfile, IS_STRING, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_selinux_x_label_lookup, 0, 2, MAY_BE_STRING|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, x_key, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, x_type, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_selinux_db_label_lookup, 0, 2, MAY_BE_STRING|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, db_key, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, db_type, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_selinux_getenforcemode arginfo_selinux_getcon

#define arginfo_selinux_getpolicytype arginfo_selinux_getcon

#define arginfo_selinux_policy_root arginfo_selinux_getcon

ZEND_FUNCTION(selinux_is_enabled);
ZEND_FUNCTION(selinux_mls_is_enabled);
ZEND_FUNCTION(selinux_getenforce);
ZEND_FUNCTION(selinux_setenforce);
ZEND_FUNCTION(selinux_policyvers);
ZEND_FUNCTION(selinux_deny_unknown);
ZEND_FUNCTION(selinux_getcon);
ZEND_FUNCTION(selinux_setcon);
ZEND_FUNCTION(selinux_getpidcon);
ZEND_FUNCTION(selinux_getprevcon);
ZEND_FUNCTION(selinux_getexeccon);
ZEND_FUNCTION(selinux_setexeccon);
ZEND_FUNCTION(selinux_getfscreatecon);
ZEND_FUNCTION(selinux_setfscreatecon);
ZEND_FUNCTION(selinux_getkeycreatecon);
ZEND_FUNCTION(selinux_setkeycreatecon);
ZEND_FUNCTION(selinux_getsockcreatecon);
ZEND_FUNCTION(selinux_setsockcreatecon);
ZEND_FUNCTION(selinux_getfilecon);
ZEND_FUNCTION(selinux_lgetfilecon);
ZEND_FUNCTION(selinux_fgetfilecon);
ZEND_FUNCTION(selinux_setfilecon);
ZEND_FUNCTION(selinux_lsetfilecon);
ZEND_FUNCTION(selinux_fsetfilecon);
ZEND_FUNCTION(selinux_getpeercon);
ZEND_FUNCTION(selinux_compute_av);
#if defined(HAVE_SECURITY_COMPUTE_CREATE_NAME)
ZEND_FUNCTION(selinux_compute_create);
#endif
ZEND_FUNCTION(selinux_compute_relabel);
ZEND_FUNCTION(selinux_compute_member);
ZEND_FUNCTION(selinux_compute_user);
ZEND_FUNCTION(selinux_get_initial_context);
ZEND_FUNCTION(selinux_check_context);
ZEND_FUNCTION(selinux_canonicalize_context);
ZEND_FUNCTION(selinux_get_boolean_names);
ZEND_FUNCTION(selinux_get_boolean_pending);
ZEND_FUNCTION(selinux_get_boolean_active);
ZEND_FUNCTION(selinux_set_boolean);
ZEND_FUNCTION(selinux_commit_booleans);
ZEND_FUNCTION(selinux_trans_to_raw_context);
ZEND_FUNCTION(selinux_raw_to_trans_context);
ZEND_FUNCTION(selinux_file_label_lookup);
ZEND_FUNCTION(selinux_media_label_lookup);
ZEND_FUNCTION(selinux_x_label_lookup);
ZEND_FUNCTION(selinux_db_label_lookup);
ZEND_FUNCTION(selinux_getenforcemode);
ZEND_FUNCTION(selinux_getpolicytype);
ZEND_FUNCTION(selinux_policy_root);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(selinux_is_enabled, arginfo_selinux_is_enabled)
	ZEND_FE(selinux_mls_is_enabled, arginfo_selinux_mls_is_enabled)
	ZEND_FE(selinux_getenforce, arginfo_selinux_getenforce)
	ZEND_FE(selinux_setenforce, arginfo_selinux_setenforce)
	ZEND_FE(selinux_policyvers, arginfo_selinux_policyvers)
	ZEND_FE(selinux_deny_unknown, arginfo_selinux_deny_unknown)
	ZEND_FE(selinux_getcon, arginfo_selinux_getcon)
	ZEND_FE(selinux_setcon, arginfo_selinux_setcon)
	ZEND_FE(selinux_getpidcon, arginfo_selinux_getpidcon)
	ZEND_FE(selinux_getprevcon, arginfo_selinux_getprevcon)
	ZEND_FE(selinux_getexeccon, arginfo_selinux_getexeccon)
	ZEND_FE(selinux_setexeccon, arginfo_selinux_setexeccon)
	ZEND_FE(selinux_getfscreatecon, arginfo_selinux_getfscreatecon)
	ZEND_FE(selinux_setfscreatecon, arginfo_selinux_setfscreatecon)
	ZEND_FE(selinux_getkeycreatecon, arginfo_selinux_getkeycreatecon)
	ZEND_FE(selinux_setkeycreatecon, arginfo_selinux_setkeycreatecon)
	ZEND_FE(selinux_getsockcreatecon, arginfo_selinux_getsockcreatecon)
	ZEND_FE(selinux_setsockcreatecon, arginfo_selinux_setsockcreatecon)
	ZEND_FE(selinux_getfilecon, arginfo_selinux_getfilecon)
	ZEND_FE(selinux_lgetfilecon, arginfo_selinux_lgetfilecon)
	ZEND_FE(selinux_fgetfilecon, arginfo_selinux_fgetfilecon)
	ZEND_FE(selinux_setfilecon, arginfo_selinux_setfilecon)
	ZEND_FE(selinux_lsetfilecon, arginfo_selinux_lsetfilecon)
	ZEND_FE(selinux_fsetfilecon, arginfo_selinux_fsetfilecon)
	ZEND_FE(selinux_getpeercon, arginfo_selinux_getpeercon)
	ZEND_FE(selinux_compute_av, arginfo_selinux_compute_av)
#if defined(HAVE_SECURITY_COMPUTE_CREATE_NAME)
	ZEND_FE(selinux_compute_create, arginfo_selinux_compute_create)
#endif
	ZEND_FE(selinux_compute_relabel, arginfo_selinux_compute_relabel)
	ZEND_FE(selinux_compute_member, arginfo_selinux_compute_member)
	ZEND_FE(selinux_compute_user, arginfo_selinux_compute_user)
	ZEND_FE(selinux_get_initial_context, arginfo_selinux_get_initial_context)
	ZEND_FE(selinux_check_context, arginfo_selinux_check_context)
	ZEND_FE(selinux_canonicalize_context, arginfo_selinux_canonicalize_context)
	ZEND_FE(selinux_get_boolean_names, arginfo_selinux_get_boolean_names)
	ZEND_FE(selinux_get_boolean_pending, arginfo_selinux_get_boolean_pending)
	ZEND_FE(selinux_get_boolean_active, arginfo_selinux_get_boolean_active)
	ZEND_FE(selinux_set_boolean, arginfo_selinux_set_boolean)
	ZEND_FE(selinux_commit_booleans, arginfo_selinux_commit_booleans)
	ZEND_FE(selinux_trans_to_raw_context, arginfo_selinux_trans_to_raw_context)
	ZEND_FE(selinux_raw_to_trans_context, arginfo_selinux_raw_to_trans_context)
	ZEND_FE(selinux_file_label_lookup, arginfo_selinux_file_label_lookup)
	ZEND_FE(selinux_media_label_lookup, arginfo_selinux_media_label_lookup)
	ZEND_FE(selinux_x_label_lookup, arginfo_selinux_x_label_lookup)
	ZEND_FE(selinux_db_label_lookup, arginfo_selinux_db_label_lookup)
	ZEND_FE(selinux_getenforcemode, arginfo_selinux_getenforcemode)
	ZEND_FE(selinux_getpolicytype, arginfo_selinux_getpolicytype)
	ZEND_FE(selinux_policy_root, arginfo_selinux_policy_root)
	ZEND_FE_END
};
