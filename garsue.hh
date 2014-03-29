<?hh // strict

//////////////////////////////////
// Type Annotations 
class AnnotatedClass {
  public int $i = 10;
  private string $str = "STRING";
  protected array $arr = array(1, 2);
  private AnnotatedClass $ac;

  function bar(mixed $mx): (function(mixed): long) {
    return function($str) use ($mx) {
      if ($str instanceof string) {
        return strlen($str);
      }
      return 0;
    };
  }
} 


function test_type_annotated(bool $flg): int {
  return 100;
}

function test_annotated_class(): void {
  $ac = new AnnotatedClass();
  var_dump($ac->bar("hoge"));
  var_dump($ac);
  // bool 型の引数に string を指定
  //test_type_annotated("hello!");
}

test_annotated_class();

echo "=== Nullable ===\n";
//////////////////////////////////
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

//////////////////////////////////
// Generics
echo "=== Generics ===\n";
// generic class
class Animal<T> {
  private ?T $name;

  public function set_name(?T $name): void {
    $this->name = $name;
  }

  public function get_name(): T {
    return $this->name;
  }

  public function get_age(): int {
    return 1;
  }
}

// generic method
function generic_method<T>(Animal<T> $cat): T {
  $value = $cat->get_name();
  
  return $value;
}

// Constaraints
class Wanko {
  public function get_age(): int {
    return 1;
  }
}

class Dog extends Wanko {
  public function get_age(): int {
    return 2;
  }

  public function is_dog(): bool {
    return true;
  }
}

class Poodle<T> {
  private T $data;

  public function __construct(T $d) {
    $this->data = $d;
  }

  public function get(): T {
    return $this->data;
  }
}

class TeacupPoodle<T as Wanko> extends Poodle<T> {
  private int $sum = 0;
  
  public function __construct(T $wanko) {
    parent::__construct($wanko);
    $this->sum += $wanko->get_age();
  }
}

function test_generics(): void {
  $dog = new Animal();
  $dog->set_name("Pochi");
  echo "dog->get_name():" . $dog->get_name() . "\n";

  $cat = new Animal();
  $cat->set_name("Mike");
  $cat_name = generic_method($cat);
  var_dump($cat_name);

  $dog = new Dog();
  echo "=== dog ===\n";
  var_dump($dog);

  $teacup_poodle = new TeacupPoodle($dog);
  echo "=== teacup_poodle ===\n";
  var_dump($teacup_poodle);
  
  $poodle2 = $teacup_poodle->get();
  echo "=== poodle2 ===\n";
  var_dump($poodle2);
  echo "=== poodle2->is_dog() ===\n";
  var_dump($poodle2->is_dog());
}

test_generics();


//////////////////////////////////
echo "=== Collections ===\n";
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


//////////////////////////////////
// Type Aliasing
type user_id = int;

// 引数の型は user_id 
function get_user_name(user_id $user_id): string {
  return "mopemope";
}

newtype password = string;
// 引数の型は password
function login(user_id $user_id, password $password): bool {
  return true;
}

//////////////////////////////////
echo "=== Ovreride ===\n";
// Override
class Yone {
  public function say_name(): string {
    return "yone";
  }
}

class Yone098 {
  <<Override>> public function sya_name(): string {
    return "yone098";
  }
}

function test_override(): void {
  $yone = new Yone098();
  // エラーになる
  //echo "yone->say_name() : " . $yone->say_name() . "\n";
}

test_override();

//////////////////////////////////
echo "=== Variable Number of Arguments ===\n";

// 引数は可変長引数
function test_many_args(int $num, ...): void {
  echo "num:" . $num . "\n";
  foreach (func_get_args() as $e) {
    var_dump($e);
  }
}


// Variable Number of Arguments
function test_valiable_number_of_arg(): void {
  test_many_args(100, "garsue", 1, array(), new Yone(), 3.14);
}

test_valiable_number_of_arg();
