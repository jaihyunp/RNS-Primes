CC = g++
CFLAGS = -pthread -std=gnu++14 -Ofast -Wall -Wextra
# CFLAGS = -pthread -std=gnu++14 -Ofast -g -Wl,-rpath=lib/
# INC = -Iheaan/include -Llib -Iheaan/build/_deps/eigen-src
# LIBS = -lHEaaN -lntl -lgmp -lm -lcrypto -lomp

DIR_OBJS=obj
DIR_SRCS=src
DIR_BINS=bin

OBJS = \
$(DIR_OBJS)/prime.o \


DEPS = \
$(DIR_OBJS)/prime.d \


SRCS = \
$(DIR_SRCS)/prime.cpp \


TARGET_PRIME = $(DIR_BINS)/prime.exe

# Each subdirectory must supply rules for building sources it contributes
$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	$(CC) $(CFLAGS) -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


# All Target
all: prime

# Tool invocations
prime: $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC Archiver'
	$(CC) $(DIR_SRCS)/main.cpp $(OBJS) $(CFLAGS) -o $(TARGET_PRIME)
	@echo 'Finished building target: $@'
	@echo ' '


# Other Targets
clean:
	-$(RM) $(OBJS) $(DEPS) $(TARGET_PRIME)
	-@echo ' '

.PHONY: all clean dependents


