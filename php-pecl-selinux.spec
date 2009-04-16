# PECL(PHP Extension Community Library) related definitions
%{!?__pecl:     %{expand: %%global __pecl     %{_bindir}/pecl}}
%define pecl_name selinux

Summary: SELinux binding for PHP scripting language
Name: php-pecl-selinux
Version: @PACKAGE_VERSION@
Release: 1%{?dist}
License: PHP
Group: Development/Languages
URL: http://pecl.php.net/package/%{pecl_name}
Source: http://pecl.php.net/get/%{pecl_name}-%{version}.tgz
BuildRoot: %(mktemp -ud %{_tmppath}/%{name}-%{version}-%{release}-XXXXXX)
BuildRequires: php-devel >= 5.2.0, php-pear, libselinux-devel >= 2.0.80
Requires: php >= 5.2.0, libselinux >= 2.0.80
Requires(post): %{__pecl}
Requires(postun): %{__pecl}
%if 0%{?php_zend_api}
Requires: php(zend-abi) = %{php_zend_api}
Requires: php(api) = %{php_core_api}
%else
Requires: php-api = %{php_apiver}
%endif
Provides: php-pecl(%{pecl_name}) = %{version}-%{release}

%description
This package is an extension to the PHP Hypertext Preprocessor.
It wraps the libselinux library and provides a set of interfaces
to the PHP runtime engine.
The libselinux is a set of application program interfaces towards in-kernel
SELinux, contains get/set security context, communicate security server,
translate between raw and readable format and so on.

%prep
%setup -c -q

%build
pushd %{pecl_name}-%{version}
%{_bindir}/phpize
%configure  --enable-selinux
make %{?_smp_mflags}
(echo "; Enable SELinux extension module"
 echo "extension=selinux.so") > selinux.ini
popd

%install
pushd %{pecl_name}-%{version}
rm -rf $RPM_BUILD_ROOT
install -D -p -m 0755 modules/selinux.so %{buildroot}%{php_extdir}/selinux.so
install -D -p -m 0644 selinux.ini %{buildroot}%{_sysconfdir}/php.d/selinux.ini

# Install XML package description
%{__mkdir_p} %{buildroot}%{pecl_xmldir}
%{__install} -m 644 ../package.xml %{buildroot}%{pecl_xmldir}/%{name}.xml
popd

%clean
rm -rf $RPM_BUILD_ROOT

%if 0%{?pecl_install:1}
%post
%{pecl_install} %{pecl_xmldir}/%{name}.xml >/dev/null || :
%endif

%if 0%{?pecl_uninstall:1}
%postun
if [ $1 -eq 0 ] ; then
    %{pecl_uninstall} %{pecl_name} >/dev/null || :
fi
%endif

%files
%defattr(-,root,root,-)
%doc %{pecl_name}-%{version}/LICENSE %{pecl_name}-%{version}/README
%config(noreplace) %{_sysconfdir}/php.d/selinux.ini
%{php_extdir}/selinux.so
%{pecl_xmldir}/%{name}.xml

%changelog
* Thu Mar 12 2009 KaiGai Kohei <kaigai@kaigai.gr.jp> - 0.2.1-1
- Specfile to build RPM package is added.

* Thu Mar  5 2009 KaiGai Kohei <kaigai@kaigai.gr.jp> - 0.1.2-1
- The initial release of SELinux binding for PHP script language.
