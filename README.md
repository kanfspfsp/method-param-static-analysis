# method-param-static-analysis
A basic static analysis which raises a warning if a method has more than 3 parameters.

## Table of contents
* **[Initial Setup](#Initial-Setup)**
* **[Running Static Analysis](#Running-Static-Analysis)**
* **[Tested On Repositories](#tested-on-repositories)**


## INITIAL SETUP 


### If Clang, LLVM and clang-tidy is not setup

If clang, llvm and clang-tidy is not setup, run the below commands in order:

```
$ git clone https://github.com/kanfspfsp/method-param-static-analysis.git
```
This has source code for my custom static analysis, clang, llvm and clang-tidy.

```
$ cd method-param-static-analysis
$ mkdir build && cd build/
$ cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
$ make check-clang-tools
$ export PATH=$PWD/bin:$PATH
```


### If clang, LLVM and Clang-Tidy is setup

```
$  cd llvm/tools/clang/tools/extra/clang-tidy
$  ./add_new_check.py misc more-than-three-parameters
$  cd misc

# Now replace the contents of MoreThanThreeParametersCheck.cpp with the contents of https://github.com/kanfspfsp/method-param-static-analysis/blob/master/tools/clang/lib/StaticAnalyzer/Checkers/SimpleMethodChecker.cpp

# Now run the below make command
$  make check-clang-tools


# Now finally run the static analysis on any file:

$  clang-tidy -checks='-*,misc-more-than-three-parameters' /any/problematic.cpp

```


## RUNNING STATIC ANALYSIS

Consider a test c++ file, which has the code like:

```
#include <stdio.h>

struct A {

    int add2Numbers(int a,int b)
    {
        return a+b;
    }
    int add4Numbers(int a,int b, int c, int d)
    {
        return a+b+c+d;

    }
    int add5number(int a,int b, int c, int d, int e)
    {
        return a+b+c+d+e;
    }
};
```
If we run the below command for the test file above

```
$ clang-tidy -checks='-*,misc-more-than-three-parameters' /some/path/test.cpp
```
The "-*" removes all the other checks and adds the custom check that I have developed named: misc-more-than-three-parameters.

Output:

```
Running without flags.
2 warnings generated.
/Users/kanfspfsp/Desktop/test.cpp:9:9: warning: Method has more than 3 Parameters [misc-more-than-three-parameters]
int add4Numbers(int a,int b, int c, int d)
^
/Users/kanfspfsp/Desktop/test.cpp:14:9: warning: Method has more than 3 Parameters [misc-more-than-three-parameters]
int add5number(int a,int b, int c, int d, int e)
```

This output throws a warning for only those functions which have more than 3 parameters.





## TESTED ON REPOSITORIES

I have tested this custom static analysis on a few famous github repositories: 

Below are the links to the warning output files generated.

MongoDB : https://github.com/mongodb/mongo   -
> Report: mongodb.out (https://github.com/kanfspfsp/method-param-static-analysis/blob/master/mongodb.out)

Facebook hhvm : https://github.com/facebook/hhvm
> Report: mockitoOut.csv (https://github.com/kanfspfsp/method-param-static-analysis/blob/master/hhvm.out)

Godot Game Engine: https://github.com/godotengine/godot
> Report: godot.out (https://github.com/kanfspfsp/method-param-static-analysis/blob/master/godot.out)


The command I used to mine through repositories:

```
find . -iname *.h -o -iname *.cpp | xargs clang-tidy -checks='-*,misc-more-than-three-parameters' | grep -A 2  "warning: Method has more than 3 Parameters"
```
