<?hh // strict
// hhvm -m debug debug.hh
function test(): void {
  $sum = 0;
  for ($i = 1; $i <= 10; $i++) {
    $sum += $i;
    echo $sum . "\n";
  }
}

test();
