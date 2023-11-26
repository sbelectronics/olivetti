: banner ." Brutprim: the worlds worst prime number generator. www.smbaker.com" CR ;
: check 2 BEGIN 2DUP = IF DROP . EXIT THEN 2DUP MOD 0= IF 46 EMIT DROP DROP EXIT THEN 1+ AGAIN ;
: brutprim banner 255 3 DO I check LOOP ;
