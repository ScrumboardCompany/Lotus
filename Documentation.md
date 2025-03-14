# Documentation
Documentation for Lotus language

## Comments
```Lotus
# One line comment

/*
Multiline comment
*/
```

## Expressions

**Arithmetic operators**
```Lotus
x + y
x - y
x * y
x / y
x ** y
x // y
```

**Bitwise operators**
```Lotus
x & y
x | y
x ^ y
~x
x << y
x >> y
```

**Logical operators**
```Lotus
x || y
x && y
!x
```

**Comparison operators**
```Lotus
x > y
x < y
x >= y
x <= y
x == y
x != y
```

**Assignment operators**
```Lotus
x += y
x -= y
x *= y
x /= y
x **= y
x //= y
x &= y
x |= y
x ^= y
x ~= y
x <<= y
x >>= y
```

**Unary operators**
```Lotus
+x
-x
!x
++x
x++
--x
x--
```

**Indexing**
```Lotus
x[i]
x[i] = y
```

**Calling**
```Lotus
x()
```

**Literals**
```Lotus
true
false
flagValue(flagName)
0xDEADBEEF # HEX numbers
__path__ # File path
__file__ # File name
__time__ # Time when compiled
__version__ # Lotus version
__line__ # Line where literal is used
```

## Variable declaration
```Lotus
let a = 10;
let b = 2 + 2 * 3
```

## Arrays and objects
```Lotus
let a = [10, 20, 30];
let b = {
    Name = "John";
    Age = 30;
}

print(b.Name) # Output: "John"
```
**Methods**
```Lotus
array.push(value) # Adds value to array at last index
array.push(value, index) # Adds value to array at passed index
array.push(value, start, end) # Adds value from start to end

array.pop() # Deletes value from array at last index
array.pop(index) # Deletes value from array at passed index
array.pop(start, end) # Deletes values from array from start to end indexes

array.clear() # Clears the array
array.empty() # Returns is array empty
```

## Loops
```Lotus
while(true) {
    print("Hello World!");
}

for(let i = 0; i < 10; i++) {
    print(i);
}

let a = [10, 20, 30];
foreach(el : a) {
    print(el);
}
```

## If else
```Lotus
let a = 10;

if (a > 10) {
    print("a is greater than 10");
} else if (a == 10) {
    print("a is equal to 10");
} else {
    print("a is less than 10");
}
```

## Try catch
```Lotus
def function() {
    throw(msg => "Exception", type => "Error");
}

try {
    function();
}
catch(ex) {
    println(ex.message(), ex.type());
}
```

## Switch case
```Lotus
let a = 10;

switch (a) {
    case 10 {
        print("a is equal to 10");
    }
    default {
        print("a is not equal to 10");
    }
}
```

## Functions and overloads
```Lotus
def a() {
    print("Hello World!");
}

def a(arg) {
    print(arg);
}
```

## Lambdas
```Lotus
let a = def() {
    print("Hello World!");
}
```
Regular functiona have higher priority than regular variables, so in this situation - regular function will be called
```Lotus
let a = def() {
    print("Lambda");
}

def a() {
    print("Regular function");
}

a();
```

## Enums
```Lotus
enum Lang { # You can also use string instead of int
    cpp = 0;
    js = 1;
    lotus; # lotus = biggest previous element value + 1 = js + 1 = 2, if there is string type in enum elements, you must specify value
    python = 3;
} # All elements of enum must have same type

let a = Lang::lotus;

print(int(a)) # output is 2
```

## Statics
```Lotus
static Counter {
public:
    count = 0;

    def increase() {
        ++this.count;
    }
    def get() {
        return Counter::count; # There are 2 ways to access elements in statics, but in case with private elements this option won't work
    }
}

print(Counter::get());
Counter::increase();
print(Counter::get());
```

## Classes
```Lotus
class Person {
public:
	age;
	name;

	def Person(age, name) {
		this.age = age; # Can access field inside class only with "this"
		this.name = name;
	}
}

let John = Person(30, "John");
print(John.age, John.name);
```
> **IMPORTANT** In classes and statics the access modifier is `private` by default!
> **IMPORTANT** Classes and statics can be named the same

**Available overloads**
```Lotus
__asInt__()
__asDouble__()
__asBool__()
__asString__()

__add__(other)
__substract__(other)
__multiply__(other)
__divide__(other)
__power__(other)
__divideModule__(other)

__bitwiseAnd__(other)
__bitwiseOr__(other)
__bitwiseXor__(other)
__bitwiseNot__
__bitwiseLeftShift__(other)
__bitwiseRightShift__(other)

__greater__(other)
__less__(other)
__greaterEqual__(other)
__lessEqual__(other)
__equality__(other)
__inequality__(other)
__logicalOr__(other)
__logicalAnd__(other)

__addSet__(other)
__substractSet__(other)
__multiplySet__(other)
__divideSet__(other)
__powerSet__(other)
__divideModuleSet__(other)
__bitwiseAndSet__(other)
__bitwiseOrSet__(other)
__bitwiseXorSet__(other)
__bitwiseNotSet__
__bitwiseLeftShiftSet__(other)
__bitwiseRightShiftSet__(other)

__unaryPlus__
__unaryMinus__
__unaryNot__
__prefixIncrement__
__postfixIncrement__
__prefixDecrement__
__postfixDecrement__

__size__
__getOfIndex__(index)
__setOfIndex__(index)
__call__() # Possible to specify any arguments
```


## Inheritance
```Lotus
class A {
protected:
    zero = 0;
}
class B : A {
public:
    def printZero() {
        print(this.zero); # If zero were in the private section it would write an error
    }
}

let b = B();
b.printZero();
```
Multiple inheritance separated by commas is also available
```Lotus
class A {}

class B {}

class C : A, B {}
```

## Import
```Lotus
* <<< "file.lts" # Imports everything from file.lts
A <<< "file.lts" # If flag ImportEverythingWithSameName is true, then imports everything with name A, otherwise it imports with this priority: class -> static -> enum -> function -> variable
variable A <<< "file.lts" # Imports variable A. Other possible types to import: class, static, enum, function
variable * <<< "file.lts" # Imports every variable
```
You can combine those imports
```Lotus
variable A, class *, B <<< "file.lts"
```
>**IMPORTANT**: If you specify `*` without type, you can't specify other elements to import

**Import from modules**
```Lotus
PI <<< Math
```
Or
```Lotus
PI <<< "Math"
```

## Infinite arguments
```Lotus
def a(args...) {
    print(args);
}
```
> **IMPORTANT**: The infinite argument must be the last argument in function

## Specified arguments
```Lotus
def a(b, c, d) {
    println(b, c, d);
}

a(1, 2, b => 10);
```

## Flags
```
flag flagName true/false; # set flag`s value
flag flagName default; # set flag`s value to default
```

**Available flags**
```Lotus
ImportEverythingWithSameName # default true
```

### ImportEverythingWithSameName

*Example 1*

**file1.lts**
```Lotus
let A = 10;

class A {};
```
**file2.lts**
```Lotus
flag ImportEverythingWithSameName false;
A <<< "file1.lts" # class A will be imported
```

*Example 2*

**file1.lts**
```Lotus
let A = 10;

class A {};
```
**file2.lts**
```Lotus
flag ImportEverythingWithSameName true;
A <<< "file1.lts" # class A and variable A will be imported
```

## [Standard](Lotus/src/parser/modules/standardModule.cpp)
**Structures**
```Lotus
exception # Class
```

**Functions**
```Lotus
exception();
exception(msg);
exception(msg, type);
exception.message(); # Returns message of the exception
exception.type(); # Returns type of the exception

print(args...); # Prints arguments
println(args...); # Prints arguments with split "\n"
input(); # Takes input and returns string
typeof(value); # Returns type of the value
swap(value1, value2) # Swaps the value1 and value2 values
size(value); # Returns size of the array
sizeof(value); # Returns size of value in RAM
int(value); # Casts value to integer
float(value); # Casts value to float
bool(value); # Casts value to bool
string(value); # Casts value to string
throw(); # Throw default exception
throw(msg); # Throw exception with msg
throw(msg, type); # Throw exception with msg and type
```

## [Math module](Lotus/src/parser/modules/mathModule.cpp)
**Functions**
```Lotus
absolute(value); # Returns absolute value of the value
round(value); # Rounds the value
min(value1, value2); # Returns the smaller of the two given values
max(value1, value2); # Returns the bigger of the two given values
sqrt(value); # Returns square root of the value
PI(); # Returns PI
E(); # Returns E
```

## [Time module](Lotus/src/parser/modules/timeModule.cpp)
**Structures**
```Lotus
Time # Class
Time # Static
```

**Fields**
```Lotus
Time.sec
Time.min
Time.hour
Time.day
Time.month
Time.year
Time.day_of_week
Time.day_of_year
Time.isdst
```

**Functions**
```Lotus
Time();
Time(sec, min, hour, day, month, year, isdst);

Time::now(); # Returns current world time
Time::sleep(duration); # Stops the code execution for "duration" milliseconds
```

## [Os module](Lotus/src/parser/modules/osModule.cpp)
**Structures**
```Lotus
File # Class
File # Static
```

**Functions**
```Lotus
File();
File(path);

File.path(); # Returns relative path
File.fullPath(); # Returns absolute path
File.name(); # Returns name
File.fullName(); # Returns name and extension
File.extension(); # Returns extension

File.setPath(path); # Sets relative path
File.read(); # Returns content of the file
File.remove(); # Deletes the file
File.write(content); # Rewrites content in the file
File.append(content); # Appends content to the file
File.rename(name); # Renames the file

File::create(path); # Creates file in specified path and returns absolute file path
File::exists(path); # Returns if specified file exists

execute(command); # Executes specified command and returns result
platform(); # Returns name of the user�s platform
```

## [Vector module](Lotus/src/parser/modules/vectorModule.cpp)
**Structures**
```Lotus
Vector2 # Class
Vector3 # Class
```

**Functions**
```Lotus
Vector2();
Vector2(X, Y);
Vector3();
Vector3(X, Y, Z);

Vector2.normalize();
Vector2.dot(otherVector);
Vector2.distance(otherVector);
Vector2.angleBetween(otherVector);
Vector2.lerp(otherVector, t);

Vector3.normalize();
Vector3.dot(otherVector);
Vector3.distance(otherVector);
Vector3.lerp(otherVector, t);

# Vector2 and Vector3 have operator overloads 
vector + otherVector
vector - otherVector
vector * scalar
vector / scalar
vector == otherVector
vector != otherVector
+vector
-vector
vector < otherVector
vector > otherVector
vector <= otherVector
vector >= otherVector
vector += otherVector
vector -= otherVector
vector *= scalar
vector /= scalar
size(vector)
string(vector)
```