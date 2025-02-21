# Documentation
Documentation for Lotus language

## Variable declaration
```Lotus
let a = 10;
let b = 2 + 2 * 3
```

## Arrays and objects
```Lotus
let a = [10, 20, 30];
let b = {
    Name = "John"
    Age = 30
}

print(b.Name)
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
Lambdas have higher priority than regular functions, so in this situation - lambda will be called
```Lotus
let a = def() {
    print("Lambda");
}

def a() {
    print("Regular function");
}

a();
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

## Import
```Lotus
Math <<< "Math"
* <<< "Time"

print(Math::PI)
```

## Infinite arguments
```Lotus
def a(args*) {
    print(args);
}
```
**IMPORTANT**: The infinite argument must be the last argument in function

## Standard functions
```Lotus
print(args*); # Prints arguments
input(); # Takes input and returns string
typeof(arg); # Returns type of the argument
size(arg); # Returns size of the array
sizeof(arg); # Returns size of argument in RAM
int(arg); # Casts argument to integer
float(arg); # Casts argument to float
bool(arg); # Casts argument to bool
string(arg); # Casts argument to string
```

## Math module
**Constants**
```Lotus
PI
E
```
**Functions**
```Lotus
absolute(value); # Returns absolute value of the value
round(value); # Rounds the value
min(value1, value2); # Returns the smaller of the two given values
max(value1, value2); # Returns the bigger of the two given values
sqrt(value); # Returns square root of the value
```

## Time module
**Functions**
```Lotus
sleep(duration); # Stops the code execution for "duration" milliseconds
```