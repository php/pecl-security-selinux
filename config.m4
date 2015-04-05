PHP_ARG_ENABLE(selinux,whether to enable libselinux binding support,
[  --enable-selinux        Enable SELinux support])

if test "$PHP_SELINUX" != "no"; then
  PHP_NEW_EXTENSION(selinux, selinux.c, $ext_shared)
  AC_CHECK_LIB(selinux, is_selinux_enabled,
               AC_DEFINE(HAVE_SELINUX,1, [Enable PHP/SELinux binding])
               PHP_ADD_LIBRARY_WITH_PATH(selinux),
               AC_MSG_ERROR("libselinux is not available hoge"))

  PHP_CHECK_FUNC_LIB(security_compute_create_name, selinux)
fi
