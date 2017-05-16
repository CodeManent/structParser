sp				:= $(sp).x
dirstack_$(sp)	:= $(d)
d				:= $(dir)

# Add rules for the subdirectories
dir := $(d)/APT
include $(dir)/Rules.mk

dir := $(d)/Symbol
include $(dir)/Rules.mk



BISON_GENERATED_$(d) := $(d)/location.hh \
                        $(d)/Parser.tab.cc \
                        $(d)/Parser.tab.hh \
                        $(d)/position.hh \
                        $(d)/stack.hh

FLEX_GENERATED_$(d) := $(d)/lex.yy.c

$(BISON_GENERATED_$(d)) : $(d)/Parser.yy
	cd ScriptParser ; bison Parser.yy

$(FLEX_GENERATED_$(d)): $(d)/Scanner.l
	cd ScriptParser; flex Scanner.l

OBJS_$(d)	:= $(BINDIR)/$(d)/Parser.tab.o \
               $(BINDIR)/$(d)/lex.yy.o \
               $(BINDIR)/$(d)/Driver.o

DEPS_$(d)	:= $(OBJS_$(d):%.o=%.d)

# Add dependency so bison files are generated before analysis of Driver.cpp
# and lex.yy.o because we need Parser.tab.h
$(BINDIR)/$(d)/Driver.d: $(BINDIR)/$(d)/Parser.tab.h
$(BINDIR)/$(d)/lex.yy.d: $(BINDIR)/$(d)/Parser.tab.h

CLEAN		:= $(CLEAN) $(OBJS_$(d)) $(DEPS_$(d)) $(BISON_GENERATED_$(d)) $(FLEX_GENERATED_$(d))

-include $(DEPS_$(d))

TARGET_OBJS := $(TARGET_OBJS)  $(OBJS_$(d))

#Retrieve previous dir from dirstack
d				:= $(dirstack_$(sp))
#Decrease stack pointer
sp				:= $(basename $(sp))
