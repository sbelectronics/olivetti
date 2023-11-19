
all: DSKA0003_pcos30e.img DSKA0004_olitest.img DSKA0010_spiele_demos.img DSKA0011_giochi_games.img DSKA0012_olidraw.img DSKA0013_other.img DSKA0005_pcos13.img DSKA0006_pcos20h.img DSKA0007_pcos40b.img DSKA0008_pcos40bu.img DSKA0014_zork.img DSKA0015_forth.img DSKA0016_tools.img

DSKA0003_pcos30e.img:
	dd if=FF_pcos_41a_LBA.img of=DSKA0003_pcos30e.img bs=1 count=2048
	dd if=../junk/pcos30e.img of=DSKA0003_pcos30e.img bs=1 skip=4096 oflag=append conv=notrunc

DSKA0004_olitest.img:
	dd if=FF_pcos_41a_LBA.img of=DSKA0004_olitest.img bs=1 count=2048
	dd if=../groessler2/diskimages/olitest.img of=DSKA0004_olitest.img bs=1 skip=4096 oflag=append conv=notrunc

DSKA0005_pcos13.img:
	dd if=FF_pcos_41a_LBA.img of=DSKA0005_pcos13.img bs=1 count=2048
	dd if=../groessler2/diskimages/pcos13.img of=DSKA0005_pcos13.img bs=1 skip=4096 oflag=append conv=notrunc

DSKA0006_pcos20h.img:
	dd if=FF_pcos_41a_LBA.img of=DSKA0006_pcos20h.img bs=1 count=2048
	dd if=../groessler2/diskimages/pcos20h.img of=DSKA0006_pcos20h.img bs=1 skip=4096 oflag=append conv=notrunc

DSKA0007_pcos40b.img:
	dd if=FF_pcos_41a_LBA.img of=DSKA0007_pcos40b.img bs=1 count=2048
	dd if=../groessler2/diskimages/pcos40b.img of=DSKA0007_pcos40b.img bs=1 skip=4096 oflag=append conv=notrunc

DSKA0008_pcos40bu.img:
	dd if=FF_pcos_41a_LBA.img of=DSKA0008_pcos40bu.img bs=1 count=2048
	dd if=../groessler2/diskimages/pcos40bu.img of=DSKA0008_pcos40bu.img bs=1 skip=4096 oflag=append conv=notrunc

DSKA0010_spiele_demos.img:
	dd if=FF_pcos_41a_LBA.img of=DSKA0010_spiele_demos.img bs=1 count=2048
	dd if=../groessler2/diskimages/spiele+uhr.img of=DSKA0010_spiele_demos.img bs=1 skip=4096 oflag=append conv=notrunc

DSKA0011_giochi_games.img:
	dd if=FF_pcos_41a_LBA.img of=DSKA0011_giochi_games.img bs=1 count=2048
	dd if=../groessler2/diskimages/giochi.img of=DSKA0011_giochi_games.img bs=1 skip=4096 oflag=append conv=notrunc

DSKA0012_olidraw.img:
	dd if=FF_pcos_41a_LBA.img of=DSKA0012_olidraw.img bs=1 count=2048
	dd if=../groessler2/diskimages/olidraw_it.img of=DSKA0012_olidraw.img bs=1 skip=4096 oflag=append conv=notrunc

DSKA0013_other.img:
	rm -f DSKA0013_other.img DSKA0013_other.raw
	m20 DSKA0013_other.raw new
	find other-src -maxdepth 1 -type f -exec m20 DSKA0013_other.raw put {} \;
	dd if=FF_pcos_41a_LBA.img of=DSKA0013_other.img bs=1 count=2048
	dd if=DSKA0013_other.raw of=DSKA0013_other.img bs=1 skip=4096 oflag=append conv=notrunc

DSKA0014_zork.img:
	cp ~/projects/misc/z8kzork/build/olizork.cmd zork/
	rm -f DSKA0014_zork.img DSKA0014_zork.raw
	m20 DSKA0014_zork.raw new
	m20 DSKA0014_zork.raw put zork/zork.txt
	m20 DSKA0014_zork.raw put zork/olizork.cmd	
	m20 DSKA0014_zork.raw put zork/zork1.dat
	m20 DSKA0014_zork.raw put zork/zork3.dat
	dd if=FF_pcos_41a_LBA.img of=DSKA0014_zork.img bs=1 count=2048
	dd if=DSKA0014_zork.raw of=DSKA0014_zork.img bs=1 skip=4096 oflag=append conv=notrunc
	cp DSKA0014_zork.img release/m20zork-unpadded.img
	dd if=release/m20zork-unpadded.img of=release/m20zork-padded.img bs=1 count=2048
	dd if=/dev/zero of=release/m20zork-padded.img bs=1 count=2048 oflag=append conv=notrunc
	dd if=release/m20zork-unpadded.img of=release/m20zork-padded.img bs=1 skip=2048 oflag=append conv=notrunc

DSKA0015_forth.img:
	rm -f DSKA0015_forth.img DSKA0015_forth.raw
	m20 DSKA0015_forth.raw new
	m20 DSKA0015_forth.raw put ../c/build/lbforth.cmd
	dd if=FF_pcos_41a_LBA.img of=DSKA0015_forth.img bs=1 count=2048
	dd if=DSKA0015_forth.raw of=DSKA0015_forth.img bs=1 skip=4096 oflag=append conv=notrunc
	cp DSKA0015_forth.img release/m20forth-unpadded.img
	dd if=release/m20forth-unpadded.img of=release/m20forth-padded.img bs=1 count=2048
	dd if=/dev/zero of=release/m20forth-padded.img bs=1 count=2048 oflag=append conv=notrunc
	dd if=release/m20forth-unpadded.img of=release/m20forth-padded.img bs=1 skip=2048 oflag=append conv=notrunc

DSKA0016_tools.img:
	rm -f DSKA0016_tools.img DSKA0016_tools.raw
	m20 DSKA0016_tools.raw new
	m20 DSKA0016_tools.raw put ../c/build/xmodemr.cmd
	m20 DSKA0016_tools.raw put ../c/build/xmodems.cmd
	m20 DSKA0016_tools.raw put ../c/build/ymodemr.cmd
	m20 DSKA0016_tools.raw put ../c/xmodem.txt
	m20 DSKA0016_tools.raw put ../basic/stty.bas
	m20 DSKA0016_tools.raw put ../basic/stty96.bas
	dd if=FF_pcos_41a_LBA.img of=DSKA0016_tools.img bs=1 count=2048
	dd if=DSKA0016_tools.raw of=DSKA0016_tools.img bs=1 skip=4096 oflag=append conv=notrunc
	cp DSKA0016_tools.raw release/m20tools-padded.img
	cp DSKA0016_tools.img release/m20tools-unpadded.img
	dd if=release/m20tools-unpadded.img of=release/m20tools-padded.img bs=1 count=2048
	dd if=/dev/zero of=release/m20tools-padded.img bs=1 count=2048 oflag=append conv=notrunc
	dd if=release/m20tools-unpadded.img of=release/m20tools-padded.img bs=1 skip=2048 oflag=append conv=notrunc	

clean:
	rm -f DSKA0003_pcos30e.img DSKA0004_olitest.img DSKA0010_spiele_demos.img DSKA0011_giochi_games.img DSKA0012_olidraw.img DSKA0013_other.img DSKA0005_pcos13.img DSKA0006_pcos20h.img DSKA0007_pcos40b.img DSKA0008_pcos40bu.img DSKA0014_zork.img DSKA0015_forth.img DSKA0016_tools.img release/*.img
