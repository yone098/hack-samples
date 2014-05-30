<?php
var_dump(function_exists('hni_fib'));
echo("hni_fib(10)=" . hni_fib(10));

$startTime = microtime(true);
for ($i = 1; $i <= 20; $i++) {
  echo(hni_fib($i) . " ");
}
$endTime = microtime(true);
echo("\n" . ($endTime - $startTime) . "[sec]\n");
