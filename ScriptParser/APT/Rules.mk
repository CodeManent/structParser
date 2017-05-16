OBJS_$(dir)		:=  $(BINDIR)/$(dir)/SemanticAnalyzer.o \
                    $(BINDIR)/$(dir)/Visitor.o

DEPS_$(dir)		:= $(OBJS_$(dir):%.o=%.d)

CLEAN			:= $(CLEAN) $(OBJS_$(dir)) $(DEPS_$(dir))

TARGET_OBJS := $(TARGET_OBJS) $(OBJS_$(dir))

-include $(DEPS_$(dir))
