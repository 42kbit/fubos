#!/bin/sh
#
# Generates grub iso image, that contains fubos.

OUT_DIR=.out
KFILE=kernel.bin
KDIR=$OUT_DIR/fubos
K=$KDIR/$KFILE
ISO_DIR=$KDIR/isofiles

CONFIGS_DIR=cfg

# https://os.phil-opp.com/multiboot-kernel/
#
# Creates following file tree
# isofiles
# | - boot
# |   | - grub
# |   |	 | - grub.cfg
# |   | - kernel.bin

mkdir -p $ISO_DIR/boot/grub
cp $K $ISO_DIR/boot
cp $CONFIGS_DIR/grub.cfg $ISO_DIR/boot/grub

grub-mkrescue -o $OUT_DIR/fubos.iso $ISO_DIR
if [ $? -ne 0 ]
then
	exit 1
fi

echo "File exported to $OUT_DIR"
echo "done"
