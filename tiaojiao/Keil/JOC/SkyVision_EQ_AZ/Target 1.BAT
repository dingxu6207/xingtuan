SET RVCT31INC=C:\Keil\ARM\RV31\INC
SET RVCT31LIB=C:\Keil\ARM\RV31\LIB
SET CPU_TYPE=LPC2148
SET CPU_VENDOR=NXP (founded by Philips)
SET UV2_TARGET=Target 1
SET CPU_CLOCK=0x00000000
C:\Keil\ARM\BIN31\ArmAsm --Via "startup._ia"
C:\Keil\ARM\BIN31\ArmCC --Via "main.__i"
C:\Keil\ARM\BIN31\ArmLink --Via "skv.lnp"
C:\Keil\ARM\BIN31\fromelf.exe "skv.axf" --i32combined --output "skv.hex"
