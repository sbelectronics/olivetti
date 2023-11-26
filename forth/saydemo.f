hex
41 constant spc_port

: quiet 0 41 out ;
: waitphon begin 41 in 1 and until ;
: sayphon begin 41 in 1 and until 41 out ;
: saystack begin dup FF = IF waitphon quiet exit then sayphon again ;

: scott-was-here 
  FF 3C 1B 00 2B 1E 2E 00 11 02 17 29 37 
  saystack ;

: zilog-z8000 
  FF 15 0B 00 00 1D 2B 20 18 1D 02 0D 02 14 02 13
  2B 02 22 18 18 2D 06 2B 
  saystack ;

