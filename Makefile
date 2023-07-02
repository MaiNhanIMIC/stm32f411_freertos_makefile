FREERTOS_FILES = FreeRTOS-Kernel
HEADER = -I./FreeRTOS-Kernel/include -I./FreeRTOS-Kernel/portable/GCC/ARM_CM4F -I./CMSIS/Include -I./CMSIS/Device/ST/STM32F4xx/Include 
FLAG = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -std=gnu11
DEFINE = -DSTM32F411xE
all:
	arm-none-eabi-gcc $(FREERTOS_FILES)/croutine.c $(HEADER) -c $(FLAG) -o "build/croutine.o"
	arm-none-eabi-gcc $(FREERTOS_FILES)/event_groups.c $(HEADER) -c $(FLAG) -o "build/event_groups.o"
	arm-none-eabi-gcc $(FREERTOS_FILES)/list.c $(HEADER) -c $(FLAG) -o "build/list.o"
	arm-none-eabi-gcc $(FREERTOS_FILES)/queue.c $(HEADER) -c $(FLAG) -o "build/queue.o"
	arm-none-eabi-gcc $(FREERTOS_FILES)/stream_buffer.c $(HEADER) -c $(FLAG) -o "build/stream_buffer.o"
	arm-none-eabi-gcc $(FREERTOS_FILES)/tasks.c $(HEADER) -c $(FLAG) -o "build/tasks.o"
	arm-none-eabi-gcc $(FREERTOS_FILES)/timers.c $(HEADER) -c $(FLAG) -o "build/timers.o"
	arm-none-eabi-gcc $(FREERTOS_FILES)/portable/GCC/ARM_CM4F/port.c $(HEADER) -c $(FLAG) -o "build/port.o"
	arm-none-eabi-gcc $(FREERTOS_FILES)/portable/MemMang/heap_4.c $(HEADER) -c $(FLAG) -o "build/heap.o"
	arm-none-eabi-gcc main.c -c $(DEFINE) $(HEADER) $(FLAG) -o "build/main.o"
	arm-none-eabi-gcc startup_stm32f411vetx.s -c $(FLAG) -o "build/startup.o"
	arm-none-eabi-gcc  "build/*.o" $(FLAG) -T"STM32F411VETX_FLASH.ld" -Wl,-Map="build/file.map" -Wl,--gc-sections -static -o "build/fw.elf"
	arm-none-eabi-objcopy -O ihex "build/fw.elf" "build/fw.hex"

load:
	"C:\Program Files (x86)\STMicroelectronics\STM32 ST-LINK Utility\ST-LINK Utility\ST-LINK_CLI.exe" -c SWD -SE 0 2 -P build/fw.hex -V -Run
clean:
	rm build/*.o