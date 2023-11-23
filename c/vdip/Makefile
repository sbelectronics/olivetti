BUILD=../build
MAP=../build

all: $(BUILD)/vdir.cmd \
     $(BUILD)/vget.cmd \
	 $(BUILD)/vcd.cmd \
	 $(BUILD)/vput.cmd \
	 $(BUILD)/pdir.cmd \
	 $(BUILD)/pget.cmd \
	 $(BUILD)/pcd.cmd \
	 $(BUILD)/pput.cmd

$(BUILD)/vget.cmd: vget.c vutil.c vinc.c oliport.c vutil.h vinc.h oliport.h
	z8k-pcos-gcc -o $(BUILD)/vget.cmd vget.c vutil.c vinc.c oliport.c -Wl,-multi,-map,$(MAP)/vget.map -O2 -D SECONDARY_VDIP

$(BUILD)/vdir.cmd: vdir.c vutil.c vinc.c oliport.c vutil.h vinc.h oliport.h
	z8k-pcos-gcc -o $(BUILD)/vdir.cmd vdir.c vutil.c vinc.c oliport.c -Wl,-multi,-map,$(MAP)/vdir.map -O2 -D SECONDARY_VDIP

$(BUILD)/vcd.cmd: vcd.c vutil.c vinc.c oliport.c vutil.h vinc.h oliport.h
	z8k-pcos-gcc -o $(BUILD)/vcd.cmd vcd.c vutil.c vinc.c oliport.c -Wl,-multi,-map,$(MAP)/vcd.map -O2 -D SECONDARY_VDIP

$(BUILD)/vput.cmd: vput.c vutil.c vinc.c oliport.c vutil.h vinc.h oliport.h
	z8k-pcos-gcc -o $(BUILD)/vput.cmd vput.c vutil.c vinc.c oliport.c -Wl,-multi,-map,$(MAP)/vput.map -O2 -D SECONDARY_VDIP

$(BUILD)/pget.cmd: vget.c vutil.c vinc.c oliport.c vutil.h vinc.h oliport.h
	z8k-pcos-gcc -o $(BUILD)/pget.cmd vget.c vutil.c vinc.c oliport.c -Wl,-multi,-map,$(MAP)/pget.map -O2

$(BUILD)/pdir.cmd: vdir.c vutil.c vinc.c oliport.c vutil.h vinc.h oliport.h
	z8k-pcos-gcc -o $(BUILD)/pdir.cmd vdir.c vutil.c vinc.c oliport.c -Wl,-multi,-map,$(MAP)/pdir.map -O2

$(BUILD)/pcd.cmd: vcd.c vutil.c vinc.c oliport.c vutil.h vinc.h oliport.h
	z8k-pcos-gcc -o $(BUILD)/pcd.cmd vcd.c vutil.c vinc.c oliport.c -Wl,-multi,-map,$(MAP)/pcd.map -O2

$(BUILD)/pput.cmd: vput.c vutil.c vinc.c oliport.c vutil.h vinc.h oliport.h
	z8k-pcos-gcc -o $(BUILD)/pput.cmd vput.c vutil.c vinc.c oliport.c -Wl,-multi,-map,$(MAP)/pput.map -O2

clean:
	rm -f $(BUILD)/*.cmd
