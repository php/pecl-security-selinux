--TEST--
Information functions
--SKIPIF--
<?php 
if(!extension_loaded('selinux')) die('skip selinux extension not loaded');
if (selinux_getenforce() <0)     die('skip selinux is disabled');
?>
--FILE--
<?php
$functions = array(
	'selinux_is_enabled',
	'selinux_mls_is_enabled',
	'selinux_getenforce',
	'selinux_policyvers',
	'selinux_getenforcemode',
	'selinux_getpolicytype',
	'selinux_policy_root',
);
foreach ($functions as $function) {
	echo "$function: ";
	var_dump($function());
}
?>
Done
--EXPECTF--
selinux_is_enabled: bool(%s)
selinux_mls_is_enabled: bool(%s)
selinux_getenforce: int(%d)
selinux_policyvers: int(%d)
selinux_getenforcemode: string(%d) "%s"
selinux_getpolicytype: string(%d) "%s"
selinux_policy_root: string(%d) "/etc/selinux/%s"
Done