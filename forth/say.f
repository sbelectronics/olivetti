hex
41 constant spc_port

: quiet 0 41 out ;
: waitphon begin 41 in 1 and until ;
: sayphon begin 41 in 1 and until 41 out ;
: saystack begin dup FF = IF waitphon quiet exit then sayphon again ;

: scott-was-here 
  FF 3C 1B 00 2B 1E 2E 00 11 02 17 29 37 
  saystack ;

scott-was-here

: daisy-bell 
  FF 1F 0D 02 27 3A 28 02 15 14 10 02 2D 29 0C 37
  31 06 1C 02 14 02 23 18 02 0D 13 37 02 0F 12 02
  38 18 09 02 0F 02 0D 13 2E 37 02 29 1E 2D 02 2D
  1F 19 02 0D 18 1C 03 0A 1A 0C 27 07 2A 02 14 02
  21 0E 3A 28 1A 02 0D 0B 1A 2A 02 31 06 03 0A 1A
  0C 27 07 10 02 25 0C 2D 06 11 02 37 37 02 14 02
  13 3F 02 0D 0B 35 2E 02 11 0C 03 16 31 02 28 0F
  02 23 0F 2D 02 0F 12 02 17 28 02 2D 17 02 13 2B
  31 14 27 29 02 28 1A 1B 02 10 31 06 04 16 21 21
  02 34 37 38 1A 02 3A 17 31 02 13 10 02 23 0C 0C
  3D 02 31 13 2B 31 31 14 21 02 31 13 2B 31 31 14
  21 
  saystack ;

: zilog-z8000 
  FF 15 0B 00 00 1D 2B 20 18 1D 02 0D 02 14 02 13
  2B 02 22 18 18 2D 06 2B 
  saystack ;

scott-was-here
