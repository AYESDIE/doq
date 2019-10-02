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

int main()
{
    doq::document D1("julius_caesar.txt"),
                  D2("hamlet.txt");

    doq::term_matrix<2> TM(D1, D2);
    
    TM.stat(TM["Brutus"] & TM["Caesar"] & ~TM["Calpurnia"]);

    return 0;
}
```

<p>
  <a href="https://discord.gg/FXmq4p2"><img src="https://img.shields.io/badge/discord-join-7289DA.svg?logo=discord&longCache=true&style=flat" /></a>
</p>

Project under .asd