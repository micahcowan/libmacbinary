# libmacbinary

## What this is

This project consists of code for accessing the structure of MacBinary-encoded
HFS files. Classic (68k and PowerPC) Macintosh disk files consisted of two
separate file "forks" on the disk: the "data" fork, used to hold any arbitrary
data (much like a normal file on any other system), and the "resource" fork,
which follows a specific, prescribed format, dividing its data into "resources"
of various "types".

Since other systems only permit a file to have a single set of contents, the
MacBinaryformat was quickly invented for interchange between different systems,
encoding both file forks of a classic Macintosh file into a single data file.

Today, many disk image inspection tools, and emulators, for the classic 68k
Macintosh, can automatically copy Macintosh files out to (say) a Windows
file, by encoding it automatically in MacBinary.

This project can decode just enough of a MacBinary-encoded file to get at its
data and resource forks (it doesn't bother with other things like file
attributes), and also contains facilities for navigating the resources
contained in the resource fork.

This project does *not* attempt to understand or parse the format of
the various standard resource types, many of which have further
organization expectations imposed on them: a resource is understood merely
as its raw data. Programs such as "rez" and "derez" on the Macintosh
are better suited to parsing resources semantically.

## Motivation
The primary intent of this project is to be used by a disassembler
targeted for code running on classic 68k Macintosh computers,
but which actually runs on more modern environments
(Windows, Linux, modern Mac OS, etc), and can directly disassemble
MacBinary-encoded programs.

## Sample output
Following is program output listing from the inluded example program
on an included example Macintosh application. The application
was compiled with FutureBASIC, which always adds the quirky
"ANDY" and "SCOT" resources as part of the generated program.

```
$ ./main fbapp.bin
fbapp.bin:

Start of file in memory: 0x7fa8edb46000
Start of res fork: 80
Application data in resource fork:
 642e 0000 0000 4a00 0200 0000 0000 3200     d.....J.......2.
 7000 4400 ba04 024e 6f00 0000 0000 3200     p.D....No.....2.
 1000 4400 5a04 0359 6573 0000 0000 0000     ..D.Z..Yes......
 0e00 1000 2e00 ba88 1752 6570 6c61 6365     .........Replace
 2065 7869 7374 696e 6720 d25e 30d3 203f      existing .^0. ?
 0000 0000 4a00 0100 0000 0000 3400 7000     ....J.......4.p.
 4600 ba04 024f 4b00 0000 0000 0e00 0c00     F....OK.........
 2e00 bc88 2a41 2073 7973 7465 6d20 6572     ....*A system er

Start of res map: 9b5a
Start of res type list: 9b76
7 items in list:
  ANDY (1)
    reslist starts 9bb0: 1:Gariepy
  ALRT (10)
    reslist starts 9bbc: 1 2 3 4 5 6 129 130 132 150
  DITL (10)
    reslist starts 9c34: 1 2 3 4 5 6 129 130 132 150
  SIZE (1)
    reslist starts 9cac: -1
  STR# (2)
    reslist starts 9cb8: 195 127
  SCOT (1)
    reslist starts 9cd0: 1:Terry
  CODE (5)
    reslist starts 9cdc: 0 1 4 5 128

CODE 0 contents:
 0000 0118 0000 1800 0000 00f8 0000 0020     ............... 
 0000 3f3c 0001 a9f0 0000 3f3c 0001 a9f0     ..?<......?<....
 008e 3f3c 0001 a9f0 01d2 3f3c 0002 a9f0     ..?<......?<....
 0160 3f3c 0002 a9f0 0192 3f3c 0002 a9f0     .`?<......?<....
 0104 3f3c 0002 a9f0 0130 3f3c 0002 a9f0     ..?<.....0?<....
 020e 3f3c 0002 a9f0 0000 3f3c 0002 a9f0     ..?<......?<....
 0320 3f3c 0003 a9f0 033c 3f3c 0003 a9f0     . ?<.....<?<....
 0000 3f3c 0003 a9f0 0270 3f3c 0003 a9f0     ..?<.....p?<....
 0318 3f3c 0003 a9f0 0008 3f3c 0003 a9f0     ..?<......?<....
 0360 3f3c 0003 a9f0 01ca 3f3c 0003 a9f0     .`?<......?<....
 0354 3f3c 0004 a9f0 017e 3f3c 0004 a9f0     .T?<.....~?<....
 0000 3f3c 0004 a9f0 01ee 3f3c 0004 a9f0     ..?<......?<....
 0000 3f3c 0005 a9f0 0006 3f3c 0005 a9f0     ..?<......?<....
 3fc2 3f3c 0005 a9f0 20e2 3f3c 0005 a9f0     ?.?<.... .?<....
 1a1c 3f3c 0005 a9f0 1a9e 3f3c 0005 a9f0     ..?<......?<....
 1aa8 3f3c 0005 a9f0 089a 3f3c 0005 a9f0     ..?<......?<....
 0000 3f3c 0080 a9f0                         ..?<....
```
