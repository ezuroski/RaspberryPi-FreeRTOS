#
#	FreeRTOS portable layer for RaspberryPi
#
OBJECTS += $(BUILD_DIR)FreeRTOS/Source/portable/GCC/RaspberryPi/port.o
OBJECTS += $(BUILD_DIR)FreeRTOS/Source/portable/GCC/RaspberryPi/portisr.o

#
#	FreeRTOS Core
#
OBJECTS += $(BUILD_DIR)FreeRTOS/Source/croutine.o
OBJECTS += $(BUILD_DIR)FreeRTOS/Source/list.o
OBJECTS += $(BUILD_DIR)FreeRTOS/Source/queue.o
OBJECTS += $(BUILD_DIR)FreeRTOS/Source/tasks.o

#
#	Onboard peripheral drivers
#
OBJECTS += $(BUILD_DIR)core/Drivers/interrupts.o
OBJECTS += $(BUILD_DIR)core/Drivers/gpio.o
OBJECTS += $(BUILD_DIR)core/Drivers/serial.o

#
#	External peripheral drivers
#
OBJECTS += $(BUILD_DIR)core/Drivers/tm1638.o

$(BUILD_DIR)FreeRTOS/Source/portable/GCC/RaspberryPi/port.o: CFLAGS += -I $(BASE)core/

#
#	Selected HEAP implementation for FreeRTOS.
#
OBJECTS += $(BUILD_DIR)/FreeRTOS/Source/portable/MemMang/heap_4.o

#
#	Startup and platform initialisation code.
#
OBJECTS += $(BUILD_DIR)core/startup.o


#
#	Main Test Program
#
OBJECTS += $(BUILD_DIR)core/main.o
