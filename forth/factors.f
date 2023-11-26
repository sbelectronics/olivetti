\ https://rosettacode.org/wiki/Factors_of_an_integer#Forth

: factors dup 2/ 1+ 1 do dup i mod 0= if i swap then loop ;
: .factors factors begin dup dup . 1 <> while drop repeat drop cr ; 
