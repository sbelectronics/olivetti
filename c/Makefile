all: build/hello.cmd build/lbforth.cmd build/xmodemr.cmd build/xmodems.cmd build/maltest.cmd build/ymodemr.cmd build/maze.cmd build/brutprim.cmd

build/hello.cmd: hello.c
	z8k-pcos-gcc -o build/hello.cmd hello.c

build/maltest.cmd: maltest.c
	z8k-pcos-gcc -o build/maltest.cmd maltest.c -Wl,-multi,-map,build/maltest.map -O2

build/lbforth.cmd: lbforth.c
	z8k-pcos-gcc -o build/lbforth.cmd lbforth.c -Wl,-multi,-map,build/lbforth.map -O2

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

clean:
	rm -f build/*.cmd
