# screw_plus_decryptor
Decrypt encrypted file by php_screw_plus

# Compile
```
$ gcc -o unscrew unscrew.c
```

# Usage
```
$ ./unscrew [Key] [File]
```

### Example
```
$ cat sample.php
849ee5c6824b997a29�զW�e4��n���s�䔦�D�`�{�<�I~%

$ ./unscrew ThisIsTheKey1234567 sample.php
<?php
echo "hello, world!";

$ ./unscrew ThisIsTheKey1234567 sample.php > sample.src.php
```


# How to get encryption key

## linux
```
$ objdump -s -j .rodata php_screw_plus.so

php_screw_plus.so:	file format ELF64-x86-64

Contents of section .rodata:
 38e4 656e6162 6c656400 7068705f 73637265  enabled.php_scre
 38f4 775f706c 75732073 7570706f 72740025  w_plus support.%
 3904 30327800 46775770 5a4b7848 37747743  02x.ThisIsTheKey
 3914 4147344a 514d4f00 73686f77 5f736f75  1234567.show_sou
 3924 72636500 68696768 6c696768 745f6669  rce.highlight_fi
 3934 6c650072 62007068 705f7363 7265775f  le.rb.php_screw_
 3944 706c7573 00312e35 2e300041 50493230  plus.1.5.0.API20
 3954 31353130 31322c4e 54530000 00002000  151012,NTS.... .
 
```

## MacOSX
```
$ objdump -s -j __cstring php_screw_plus.so

php_screw_plus.so:	file format Mach-O 64-bit x86-64

Contents of section __cstring:
 3f14 25303278 00546869 73497354 68654b65  %02x.ThisIsTheKe
 3f24 79313233 34353637 0073686f 775f736f  y1234567.show_so
 3f34 75726365 00686967 686c6967 68745f66  urce.highlight_f
 3f44 696c6500 72620070 68705f73 63726577  ile.rb.php_screw
 3f54 5f706c75 7300312e 352e3000 41504932  _plus.1.5.0.API2
 3f64 30313331 3232362c 4e545300 7068705f  0131226,NTS.php_
 3f74 73637265 775f706c 75732073 7570706f  screw_plus suppo
 3f84 72740065 6e61626c 656400             rt.enabled.
```

key : ThisIsTheKey1234567
