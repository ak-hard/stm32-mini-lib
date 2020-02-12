CC = $(PREFIX)gcc
CXX = $(PREFIX)g++
AS = $(PREFIX)gcc
LD = $(PREFIX)gcc
OBJCP = $(PREFIX)objcopy -O binary
OBJDUMP = $(PREFIX)objdump
AR = $(PREFIX)ar

OBJDIR=obj
SRCDIR=.
BINDIR=bin

define make-obj-c
ifneq ($(MAKECMDGOALS),clean)
$(patsubst %.c,$(OBJDIR)/%.d,$1): $2/$1
	$(CC) $(CFLAGS) -M -MF $$@ -MT $(patsubst %.c,$(OBJDIR)/%.o,$1) $$<
-include $(patsubst %.c,$(OBJDIR)/%.d,$1)
endif
CLEAN_FILES += $(patsubst %.c,$(OBJDIR)/%.d,$1)
$(patsubst %.c,$(OBJDIR)/%.o,$1): $2/$1 $(patsubst %.c,$(OBJDIR)/%.d,$1)
	$(CC) $(CFLAGS) -o $$@ -c $2/$1
CLEAN_FILES += $(patsubst %.c,$(OBJDIR)/%.o,$1)
endef

define make-obj-cpp
ifneq ($(MAKECMDGOALS),clean)
$(patsubst %.cpp,$(OBJDIR)/%.d,$1): $2/$1
	$(CXX) $(CXXFLAGS) -M -MF $$@ -MT $(patsubst %.cpp,$(OBJDIR)/%.o,$1) $$<
-include $(patsubst %.cpp,$(OBJDIR)/%.d,$1)
endif
CLEAN_FILES += $(patsubst %.cpp,$(OBJDIR)/%.d,$1)
$(patsubst %.cpp,$(OBJDIR)/%.o,$1): $2/$1 $(patsubst %.cpp,$(OBJDIR)/%.d,$1)
	$(CXX) $(CXXFLAGS) -o $$@ -c $2/$1
CLEAN_FILES += $(patsubst %.cpp,$(OBJDIR)/%.o,$1)
endef

define make-obj-asm
ifneq ($(MAKECMDGOALS),clean)
$(patsubst %.s,$(OBJDIR)/%.d,$1): $2/$1
	$(AS) $(ASFLAGS) -M -MF $$@ -MT $(patsubst %.s,$(OBJDIR)/%.o,$1) $$<
-include $(patsubst %.s,$(OBJDIR)/%.d,$1)
endif
CLEAN_FILES += $(patsubst %.s,$(OBJDIR)/%.d,$1)
$(patsubst %.s,$(OBJDIR)/%.o,$1): $2/$1
	$(AS) $(ASFLAGS) -o $$@ -c $2/$1
CLEAN_FILES += $(patsubst %.s,$(OBJDIR)/%.o,$1)
endef

define make-link
$(patsubst %.c,$(OBJDIR)/%.o,$1): $2/$1 $(patsubst %.c,$(OBJDIR)/%.d,$1)
	$(CC) $(CFLAGS) -o $$@ -c $2/$1
CLEAN_FILES += $(patsubst %.c,$(OBJDIR)/%.o,$1)
endef

