all: build/hello.cmd build/lbforth.cmd build/xmodemr.cmd build/xmodems.cmd build/maltest.cmd build/ymodemr.cmd build/maze.cmd build/brutprim.cmd build/pinb.cmd build/poutb.cmd \
     build/sum.cmd build/conway.cmd \
     vdip

h8-80186: build186/lbforth.com build186/sum.com build186/brutprim.com
	cp build186/*.com /home/smbaker/projects/pi/h8/h8-80186/commands/

build/hello.cmd: hello.c
	z8k-pcos-gcc -o build/hello.cmd hello.c

build/maltest.cmd: maltest.c
	z8k-pcos-gcc -o build/maltest.cmd maltest.c -Wl,-multi,-map,build/maltest.map -O2

build/lbforth.cmd: lbforth.c oliport.c myread.c
	z8k-pcos-gcc -o build/lbforth.cmd lbforth.c myread.c oliport.c -Wl,-multi,-map,build/lbforth.map -O2 -D OLIVETTI

build/xmodemr.cmd: xmodemr.c crc16.c
	z8k-pcos-gcc -o build/xmodemr.cmd xmodemr.c crc16.c -Wl,-multi,-map,build/xmodemr.map -O2

build/ymodemr.cmd: xmodemr.c crc16.c
	z8k-pcos-gcc -o build/ymodemr.cmd ymodemr.c crc16.c -Wl,-multi,-map,build/ymodemr.map -O2

build/xmodems.cmd: xmodems.c crc16.c
	z8k-pcos-gcc -o build/xmodems.cmd xmodems.c crc16.c -Wl,-multi,-map,build/xmodems.map -O2

build/maze.cmd: maze.c
	z8k-pcos-gcc -o build/maze.cmd maze.c -Wl,-multi,-map,build/maze.map -O2

build/brutprim.cmd: brutprim.c
	z8k-pcos-gcc -o build/brutprim.cmd brutprim.c -Wl,-multi,-map,build/brutprim.map -O2

build/pinb.cmd: pinb.c
	z8k-pcos-gcc -o build/pinb.cmd pinb.c -Wl,-multi,-map,build/pinb.map -O2

build/poutb.cmd: poutb.c
	z8k-pcos-gcc -o build/poutb.cmd poutb.c -Wl,-multi,-map,build/poutb.map -O2

build/sum.cmd: sum.c
	z8k-pcos-gcc -o build/sum.cmd sum.c -Wl,-multi,-map,build/sum.map -O2

build/conway.cmd: conway.c
	z8k-pcos-gcc -o build/conway.cmd conway.c -Wl,-multi,-map,build/conway.map -O2 -D OLIVETTI

build186/lbforth.com: lbforth.c
	WATCOM=/usr/bin/watcom INCLUDE=/usr/bin/watcom/h PATH=$PATH:/usr/bin/watcom/binl64 wcl -mt lbforth.c -dH8_80186 -fe=build186/lbforth.com

build186/sum.com: sum.c
	WATCOM=/usr/bin/watcom INCLUDE=/usr/bin/watcom/h PATH=$PATH:/usr/bin/watcom/binl64 wcl -mt sum.c -dH8_80186 -fe=build186/sum.com

build186/brutprim.com: brutprim.c
	WATCOM=/usr/bin/watcom INCLUDE=/usr/bin/watcom/h PATH=$PATH:/usr/bin/watcom/binl64 wcl -mt brutprim.c -dH8_80186 -fe=build186/brutprim.com

.PHONY: vdip
vdip:
	cd vdip && make

clean:
	rm -f build/*.cmd
