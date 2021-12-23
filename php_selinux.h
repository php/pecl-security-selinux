#ifndef PHP_SELINUX_H
#define PHP_SELINUX_H

extern zend_module_entry		selinux_module_entry;
#define phpext_selinux_ptr		&selinux_module_entry

#define PHP_SELINUX_VERSION "0.6.1-dev"
#define PHP_SELINUX_STATE   "stable"

#endif	/* PHP_SELINUX_H */
