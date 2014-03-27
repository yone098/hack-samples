<?hh
function loop_test() {
  $sum = 0;
  for ($i = 0; $i < 1000000; $i++) {
    $sum += $i * 2;
  }
}

function main() {
  $startTime = microtime(true);
  loop_test();
  $endTime = microtime(true);
  echo $endTime - $startTime . "秒\n";


  $startTime = microtime(true);
  loop_test();
  $endTime = microtime(true);
  echo $endTime - $startTime . "秒\n";
}

main();
