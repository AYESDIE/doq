# doq

## Datamining Library in C++

![](https://cdn.discordapp.com/attachments/617951895386062868/628960765478699018/doq.png)

**doq** is an intutive, fast, scalable C++ datamining library. It aims to implement a wide array of datamining methods and functions.

### Dependencies

doq has the following dependency:

```
CMake       >= 3.1
```

### Building doq from source:

doq uses CMake as a build system. One can consult any CMake tutorials for further documentation, but this tutorial should be enough to get doq built and installed.

First, unpack the doq source and change into the unpacked directory. Here, we use doq-x.y.z where x.y.z is the version.

```
$ tar -xzf doq-x.y.z.tar.gz
$ cd doq-x.y.z
```

Then, make a build directory. The directory can have any name, not just `build`, but `build` is sufficient.

```
$ mkdir build
$ cd build
```

The next step is to run CMake to configure the project.  Running CMake is the
equivalent to running `./configure` with autotools.

```
$ cmake ../
```

Once CMake is configured, building the library is as simple as typing `make`.

```
$ make
```

If you wish to install doq to `/usr/local/include`, once it has built, make sure you have root privileges (or write permissions to that directory), and simply type

```
# make install
```

### Usage:

```cpp
#include <doq.hpp>

using namespace doq;

int main()
{
    Document D1("julius_caesar.txt"), D2("hamlet.txt");

    TermMatrix<VanillaTokenizer, 2> TM(VanillaTokenizer(), D1, D2);
    
    TM.stat(TM[Wildcard("Bru*us")] && TM["Caesar"] && (!TM[Soundex("Kalpernia")]));

    return 0;
}
```