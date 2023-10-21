```
# format and prep floppy
vf 0:
ps 0:
fc 10:* 0:

# rs232 console
# copy rs232.sav, scomm.cmd, ci.sav from the pcos 3.1 disk
rs323
sc com:,9600,none,0,8,half,off,256
ci 0,o,0
+Scom:, +Dcom:

# commands
fc <src> <dest>             # file copy
ff                          # free unused space
fk <fn>                     # delete a file
fl                          # file list (long)
fq                          # file list (quick)
fr <src>,<dest>             # file rename
pk <src-code>,<dest-code>   # redefine key code
sd                          # display device table
ps <dev>:                   # save OS
vf <dev>:                   # format device

# during power-on self test (must use reset button not CTRL-RESET)
L - loop on diags
D - loop on disk diags
F - boot from floppy
B - boot directly to basic
S - boot directly to PCOS without init files
```
