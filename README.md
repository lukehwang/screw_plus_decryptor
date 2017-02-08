# screw_plus_decryptor
Decrypt encrypted file by php_screw_plus

# Compile

# Usage
```
./unscrew [Key] [File]
```

### Example
```
./unscrew ThisIsTheKey12345667 sample.php
./unscrew ThisIsTheKey12345667 sample.php > sample.src.php
```



# How to get encryption key

```
$objdump -s -j .rodata php_screw_plus.so

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

key : ThisIsTheKey1234567
