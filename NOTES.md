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

Ports

| Port Num | Description |
| -------- | ----------- |
|    001   | fdc status / command |
|    003   | fdc track |
|    005   | fdc sector |
|    007   | fdc data |
|    021   | TTL latch |
|    061   | CRTC address |
|    063   | CRTC data |
|    081   | 8255A port A |
|    083   | 8255A port B |
|    085   | 8255A port C |
|    087   | 8255A control |
|    0A1   | 8251 kbd data |
|    0A3   | 8251 kbd status/control |
|    0C1   | 8251 tty data |
|    0C3   | 8251 tty status/control |
|    121   | 8253 counter 0 (TTY/printer) |
|    123   | 8253 counter 1 (keyboard) |
|    125   | 8253 counter 2 (RTC NVI) |
|    127   | 8253 control |
|    140-1 | 8259 master |
|    142-3 | 8259 master |
|    181   | reg file loc 1 |
|    183   | reg file loc 2 |
|    185   | reg file loc 3 |
|    187   | reg file loc 4 |
|    101   | gpib 8292 A0=0 |
|    103   | gpib 8292 A0 = 1 |
|    161   | gpib 8291 data in/out |
|    163   | gpib 8291 interrupt status / mask 1 |
|    165   | gpib 8291 interrupt status / mask 2 |
|    167   | gpib 8291 serial poll status / map |
|    169   | gpib 8291 address status / mode |
|    16B   | gpib 8291 cmd pass through / aux mode |
|    16D   | gpib 8291 address 0 / address 0/1 |
|    16F   | gpib 8291 address 1 / EOS |
|    1A0   | gpib 8259 |
|    1A2   | gpib 8259 |
|    1CB   | hdd cyl hi |
|    1C9   | hdd cyl lo |
|    1CD   | hdd head select |
|    1C7   | hdd sector |
|    1CF   | hdd command status |
|    1C3   | hdd error, cylinder to start write precomp |
|    1C1   | data port |
|    1C5   | sector count |
|    881   | dualser modem status port |
|    841   | dualser 8259 interrupt command |
|    843   | dualser 8259 data register |
|    803   | dualser 8251a 0 control port |
|    801   | dualser 8251a 0 control port |
|    823   | dualser 8251a 1 control port |
|    821   | dualser 8251a 1 control port |
|    867   | dualser 8253 control port |
|    861   | dualser 8253 out 0 register |
|    863   | dualser 8253 out 1 register |
|    865   | dualser 8253 out 2 register |

# High Speed Serial Idea

* Replace 8251 with TMP82C51AP-10

* Remove Jumper P-P1

* Remove Jumper P2-N2

* Connect 1.8432 MHz to N2 and P1 for 115200 baud. Use 921.6 KHz for 57600 or 614.4 KHz for 38400. I actually have the 614.4 oscillators.

* 8251 requirement is CLK set to at least 30x baud rate. The clk is 2 MHz, so would have expected this to work up to 57,600 baud.

* results
  
  | baud rate | TxC, RxC clocks              | result |
  | -------   | ---------------------------- | ------ |
  | 115,200   | 1.8432 MHz osc.              | transmit fine, but receive unreliable |
  | 57,600    | 1.8432 MHz osc divided by 2  | transmit fine, but receive unreliable |
  | 38,400    | 4.9152 MHz osc divided by 8  | transmit fine, but receive unreliable |
  | 28,800    | 1.8342 Mhz osc divided by 4  | works, receives at 1042 bytes per second |
  | 19,200    | 4.9152 MHz osc divided by 16 | works, receives at 1042 bytes per second |
  | 9,600     | 4.9152 MHz osc divided by 32 | works, receives at 875 bytes per second |
  
* conclusion 1 - there's no point in going above 19,200 baud as we max out somewhere around 12,000 baud. This is as fast
  as xmodem can pull data out of the ring buffer. The ring buffer can probably burst up faster than that. Optimizing
  the xmodem receiver code might be able to help.

* note - we should have been able to sustain up to 57,600 baud without errors but could not. Maybe this is due to imperfections in
  in the wiring. I put the crystal and divider in a solderless breadboard and had relatively long jumper wires.

# Dual Serial Board Notes

* See port numbers above

* Just wire the baud rates to a jumper for simplicity?

* Will need to connect an 8259 for the interrupts. 
