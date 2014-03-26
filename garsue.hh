<?hh

// 引数と戻り値は bool
function garsue(bool $x): bool {
  return !$x;
}

$ret = garsue(true);
var_dump($ret);

// 型が異なるためにエラー
//$str = "hoge";
//garsue($str);



///////////////////////////////////////////////////////
// Type Annotations
function test_type_annotation(): void {
  
}

///////////////////////////////////////////////////////
// ## Nullable Types
// ? 付きでNullable
interface mohikan {
  public function say(): string;
}

class mopemope implements mohikan {
  public function say(): string {
    return "コード書け!";
  }
}

// $mohikan に null が渡ってくる場合があるのでチェック
function say_args_null_ok(?mohikan $mohikan): string {
  if ($mohikan !== null) {
    return $mohikan->say();
  }
  return "mohikan が null です。";
}

// 引数 $mohikan が null なら実行されない
function say_args_null_ng(mohikan $mohikan): string {
  return $mohikan->say();
}

function test_nullable_type(): void {
  // null を指定
  say_args_null_ok(null);

  // mopemope インスタンスを指定
  $mopemope = new mopemope();
  say_args_null_ng($mopemope);

  // null 指定でエラー
  //say_args_null_ng(null);
}

test_nullable_type();


///////////////////////////////////////////////////////
// Collections
function test_collections(): void {
  // Vector
  echo "Collections Vection<T>\n";
  $vector = Vector<int> { 100, 200, 300, 400 };
  $vector[] = 700; // 追加
  $vector[0] = 111; // 上書き
  echo "vector->get(1):" . $vector->get(1) . "\n";
  var_dump($vector);

  $vector->removeKey(2);
  foreach ($vector as $v) { echo $v . "\n"; }

  // filter
  $v_filter = $vector->filter(function($v) { return 150 <= $v; });
  foreach($v_filter as $key => $val) {
    echo "key:" . $key . "=>" . $val . "\n";
  }

  // Map
  echo "Collections Map<K, V>\n";
  $map = Map<string, long> {"a" => 100, "b" => 200, "c" => 300};
  
  $map["d"] = 400;
  echo "map[0] = " . $map["a"] . "\n";
  // get
  echo "map->get(\"b\") = ". $map->get("b") . "\n";

  // contains
  var_dump($map->contains("a"));

  // map filterWithKey
  $map_filter = $map->filterWithKey(function($k, $v) { 
    return ($k === "b" || $k === "c");
  });
  var_dump($map_filter);
}

test_collections();

///////////////////////////////////////////////////////
// Override
class Yone {
  public function yone_098(): string {
    return "yone_098";
  }
}

class Yone098 {
  <<Override>> public function yone_123(): string {
    return "yone_123";
  }
}

function test_override(): void {
  echo "call test_override()\n";

  $yone = new Yone098();
  // エラーになる
  //echo "yone->yone_098() : " . $yone->yone_098() . "\n";
}

test_override();


///////////////////////////////////////////////////////
// Type Aliasiling
type mopeInt = int;
function sum(mopeInt $v): int {}

newtype yone_name = string;
// 引数は yone_name 型しか受け付けない	
function foo(yone_name $v): void {}

newtype mopePoint = (long, long);
function test_point(mopePoint $v): void {}
// Override


///////////////////////////////////////////////////////
// Typeing XHP
function test_xhp(string $text, string $style): :div {
  return
    <div style={$style}>
      <p>{$text}</p>
    </div>;
}

test_xhp("Garsue!", "color=red");



