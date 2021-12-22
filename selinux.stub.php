<?php

/**
 * @generate-function-entries
 * @generate-legacy-arginfo
 */

/* global state API */
function selinux_is_enabled(): bool {}
function selinux_mls_is_enabled(): bool {}
function selinux_getenforce(): int {}
function selinux_setenforce(int $mode): bool {}
function selinux_policyvers(): int|false {}
function selinux_deny_unknown(): bool {}

/*  wrappers for the /proc/pid/attr API */
function selinux_getcon(): string|false {}
function selinux_setcon(string $context): bool {}
function selinux_getpidcon(int $pid): string|false {}
function selinux_getprevcon(): string|false {}
function selinux_getexeccon(): string|false {}
function selinux_setexeccon(string $context): bool {}
function selinux_getfscreatecon(): string|false {}
function selinux_setfscreatecon(string $context): bool {}
function selinux_getkeycreatecon(): string|false {}
function selinux_setkeycreatecon(string $context): bool {}
function selinux_getsockcreatecon(): string|false {}
function selinux_setsockcreatecon(string $context): bool {}

/* get/set file context */
function selinux_getfilecon(string $filename): string|false {}
function selinux_lgetfilecon(string $filename): string|false {}
/**
 * @param resource $stream
 */
function selinux_fgetfilecon($stream): string|false {}
function selinux_setfilecon(string $filename, string $context): bool {}
function selinux_lsetfilecon(string $filename, string $context): bool {}
/**
 * @param resource $stream
 */
function selinux_fsetfilecon($stream, string $context): bool {}

/* labeled networking  */
/**
 * @param resource $stream
 */
function selinux_getpeercon($stream): string|false {}

/* security_compute_XXXX() wrappers */
function selinux_compute_av(string $scontext, string $tcontext, string $tclass): array|false {}
#ifdef HAVE_SECURITY_COMPUTE_CREATE_NAME
function selinux_compute_create(string $scontext, string $tcontext, string $tclass, string $name=null): string|false {}
#endif
function selinux_compute_relabel(string $scontext, string $tcontext, string $tclass): string|false {}
function selinux_compute_member(string $scontext, string $tcontext, string $tclass): string|false {}
function selinux_compute_user(string $scontext, string $username): array|false {}

/* get initial context */
function selinux_get_initial_context(string $name): string|false {}

/* sanity check in security context */
function selinux_check_context(string $context): bool {}
function selinux_canonicalize_context(string $context): string|false {}

/* booleans */
function selinux_get_boolean_names(): array|false {}
function selinux_get_boolean_pending(string $bool_name): int {}
function selinux_get_boolean_active(string $bool_name): int {}
function selinux_set_boolean(string $bool_name, int $bool_value): bool {}
function selinux_commit_booleans(): bool {}

/* mcstrans */
function selinux_trans_to_raw_context(string $context): string|false {}
function selinux_raw_to_trans_context(string $context): string|false {}

/* selabel wrappers */
function selinux_file_label_lookup(string $pathname, int $mode, bool $validate=false, bool $baseonly=false, string $subset=null, string $specfile=null): string|false {}
function selinux_media_label_lookup(string $device_name, bool $validate=false, string $specfile=null): string|false {}
function selinux_x_label_lookup(string $x_key, string $x_type): string|false {}
function selinux_db_label_lookup(string $db_key, string $db_type): string|false {}

/* configuration files */
function selinux_getenforcemode(): string|false {}
function selinux_getpolicytype(): string|false {}
function selinux_policy_root(): string|false {}

