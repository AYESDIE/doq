# doq

## Datamining Library in C++

![](https://cdn.discordapp.com/attachments/617951895386062868/628960765478699018/doq.png)

Installation:
```
$ mkdir build && cd build
$ cmake ../
$ make
```

Usage:
```cpp
#include <doq.hpp>

using namespace doq;

int main()
{
    Document D1("julius_caesar.txt"),
             D2("hamlet.txt");

    TermMatrix<VanillaTokenization, 2> TM(VanillaTokenization(),
        D1, D2);
    
    TM.stat(TM["Brutus"] && TM["Caesar"] && (!TM[Soundex("Kalpernia")]));

    return 0;
}
```

<p>
  <a href="https://discord.gg/FXmq4p2"><img src="https://img.shields.io/badge/discord-join-7289DA.svg?logo=discord&longCache=true&style=flat" /></a>
</p>

Project under .asd