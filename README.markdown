assert
================================

Content
-------------------------

Redefine assert() macro to print file name and line number. Define new
macro "Assert_isinf_isnan()" to verify if number if inifite or NaN (not-a-number).

Compilation
-------------------------
No need to compile, it's just a header file. Include "Assert.hpp"

To install:

``` bash
$ make install
```

By default, it will be installed in ${HOME}/usr. You can install somewhere else
using DESTDIR:

``` bash
$ make gcc shared static install DESTIR=/usr
```

License
-------------------------

This code is distributed under the terms of the [GNU General Public License v3 (GPLv3)](http://www.gnu.org/licenses/gpl.html) and is Copyright 2011 Nicolas Bigaouette.

