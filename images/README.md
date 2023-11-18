Find my released images in the `release` directory. I
only put up images for the disks that I've created myself. For
stock images check the groessler ftp site.

Two copies of each image are present.

The -unpadded images use 128 byte sectors on the first track. I
use them with my gotek. The can also be used with the greaseweazle using
the included `diskdefs-unpadded.cfg` file. For example:

"""
gw write --drive b release/m20forth-unpadded.img --format olivetti.m20.unpadded --diskdefs diskdefs-unpadded.cfg
"""

The -padded images use 256 byte sectors on the first track. This can be
used with the greaseweazle using the default diskdefs that is included
with greaseweazle or by using the included `diskdefs-padded.cfg` file.

"""
gw write --drive b release/m20forth-padded.img --format olivetti.m20.padded --diskdefs diskdefs-padded.cfg
"""

I do not publish the Olivetti Zork image because I do not have thr rights
to redistribute ZORK1.DAT, ZORK2.DAY, or ZORK3.DAT. You can get
these files from any CP/M or MSDOS ZORK disk. You can possibly
also find the published olivetti Zork image on other places on
the internet.
