COMPILER = arm-linux-gnueabihf-
CC = $(COMPILER)gcc
LD = $(COMPILER)ld
OBJCOPY = $(COMPILER)objcopy
OBJDUMP = $(COMPILER)objdump
OBJS = start.o main.o beep.o
TARGET = Buzzer

%.o : %.s
	$(CC) -c $^ -o $@

%.o : %.c
	$(CC) -c $^ -o $@


$(TARGET).bin:$(OBJS)

	$(LD) -Ttext 0x87800000 $^ -o $(TARGET).elf
	$(OBJCOPY) -O binary -S -g $(TARGET).elf $@
	$(OBJDUMP) -D $(TARGET).elf > $(TARGET).dis

clean:
	rm $(OBJS) $(TARGET).elf $(TARGET).bin $(TARGET).dis
load:
	./imxdownload $(TARGET).bin /dev/sdb