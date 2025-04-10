#---------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

TOPDIR ?= $(CURDIR)
include $(DEVKITARM)/3ds_rules
#---------------------------------------------------------------------------------

TARGET      := lib3dslua547
BUILD       := build
LUA_SRC     := source
INCLUDES    := include
LIBDIR      := lib

ARCH        := -march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft

CFLAGS      += -O2 -Wall -DLUA_32BITS -D__3DS__ -mword-relocations -ffunction-sections $(ARCH)
CFLAGS      += $(foreach dir, $(INCLUDES), -I$(CURDIR)/$(dir))

ASFLAGS     += -g $(ARCH)
LDFLAGS     :=

CFILES      := $(wildcard $(LUA_SRC)/*.c)
OFILES      := $(patsubst $(LUA_SRC)/%.c, $(BUILD)/%.o, $(CFILES))

OUTPUT      := $(LIBDIR)/$(TARGET).a

#---------------------------------------------------------------------------------
all: $(OUTPUT)

$(OUTPUT): $(BUILD) $(LIBDIR) $(OFILES)
	@echo "Archiving into $@"
	$(AR) rcs $@ $(OFILES)
	$(RANLIB) $@

$(BUILD)/%.o: $(LUA_SRC)/%.c
	@echo "Compiling $<"
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD) $(LIBDIR):
	@mkdir -p $@

#---------------------------------------------------------------------------------
clean:
	@echo Cleaning up...
	@rm -rf $(BUILD) $(OUTPUT) $(LIBDIR)