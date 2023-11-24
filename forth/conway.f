\ https://gist.github.com/nfunato/5018107

64 constant _width_
16 constant _height_

: nrows _width_ * 2* ;
1        nrows constant _row_
_height_ nrows constant _size_

here @ _size_ cells allot create world DOCOL , ' LIT , , ' EXIT ,
world         value old
old _width_ + value new

: clear-world world _size_ erase ;
: flip-world  new old to new to old ;
: foreach-row ( xt -- )  _size_ 0 do i over execute _row_ +loop drop ;

: row+  _row_ + ;
: row-  _row_ - ;
: col+  1+ ;
: col-  1- dup _width_ and + ;  \ avoid borrow into row
: wrap ( i -- i   ) [ _size_ _width_ - 1- ] literal and ;
: wow@ ( i -- 0/1 ) wrap old + c@ ;
: wow! ( 0/1 i -- ) wrap old + c! ;
: ow@  ( i -- 0/1 ) old + c@ ;
: nw!  ( 0/1 i -- ) new + c! ;

: sum-neighbors ( i -- i n )
  dup  col- row- wow@     over      row- wow@  +  over col+ row- wow@  +
  over col-      wow@  +                          over col+      wow@  +
  over col- row+ wow@  +  over      row+ wow@  +  over col+ row+ wow@  + ;

variable *gen*                  \ generation
: clear  clear-world  0 *gen*  ! ;
: age    flip-world   1 *gen* +! ;

\ the core Game of Life rules: just 3=>born, 2or3=>still alive, else=>die
: gencell ( i -- )  sum-neighbors over ow@ or 3 = 1 and swap nw! ;
: genrow  ( i -- )  _width_ over + swap do i gencell loop ;
: gen     (   -- )  ['] genrow foreach-row age ;

: emit-pos    ( 0/1-- )  if [char] * else bl then emit ;
: showrow     ( i  -- )  cr  old + _width_ over + swap do i c@ emit-pos loop ;
: show        (    -- )  ['] showrow foreach-row  cr ." Generation " *gen* @ . ;

: home 0 0 at-xy ;
: life ( -- ) begin gen home show key? until ;

char | constant '|'
: pat ( i addr len -- )
  rot dup 2swap  over + swap do
    i c@ '|' = if drop row+ dup else
    i c@ bl  = 1+ over wow! col+ then
  loop 2drop ;

: blinker s" ***" pat ;
: toad s" ***| ***" pat ;
: pentomino s" **| **| *" pat ;
: pi s" **| **|**" pat ;
: glider s"  *|  *|***" pat ;
: pulsar s" *****|*   *" pat ;
: ship s"  ****|*   *|    *|   *" pat ;
: pentadecathalon s" **********" pat ;
: clock s"  *|  **|**|  *" pat ;

clear 0 glider life
