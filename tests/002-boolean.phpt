--TEST--
Boolean functions
--SKIPIF--
<?php 
if(!extension_loaded('selinux')) die('skip selinux extension not loaded');
if (selinux_getenforce() <0)     die('skip selinux is disabled');
?>
--FILE--
<?php
$bools = selinux_get_boolean_names();
if (is_array($bools) && count($bools) > 10) {
	$bool = $bools[0];
	var_dump(selinux_get_boolean_pending($bool));
	var_dump(selinux_get_boolean_active($bool));
	var_dump(selinux_get_boolean_active('a dumy one which doesnt exist'));
} else {
	echo "Cannot retrieve boolean names\n";
}
?>
Done
--EXPECTF--
int(%d)
int(%d)
int(-1)
Done