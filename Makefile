## Build flags for all targets
#
CXXFLAGS = -g -Wall -std=c++0x -fpermissive -Wall
CC       = $(CXX)
CFLAGS   = $(CXXFLAGS)
LDFLAGS = -lGL -lGLU -lglut
LF_ALL   = 
LL_ALL   =

BINDIR=bin
# custom rules

#compilation rules
$(BINDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BINDIR)/%.o: %.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	
$(BINDIR)/%.o: %.c
	$(CC) $(CXXFLAGS)  -c -o $@ $<

#akefile driver creation rules
$(BINDIR)/%.d: %.c
	@$(CC) $(CXXFLAGS)  $< -MM -MF $@

$(BINDIR)/%.d: %.cpp
	@$(CXX) $(CXXFLAGS)   $< -MM -MF $@

$(BINDIR)/%.d: %.cc
	@$(CXX) $(CXXFLAGS)   $< -MM -MF $@

# Standard things

all: targets

dir:=.
include Rules.mk


# The variables TARGET_*, CLEAN and CMD_INST* may be added to by the Makefile
# fragments in the various subdirectories

.PHONY: targets
targets: $(TARGET_BIN) $(TARGET_SBIN) $(TARGET_ETC) $(TARGET_LIB)

.PHONY: clean
clean:
	$(RM) $(CLEAN)

.PHONY: run
run: $(TARGET_BIN)
	./$(TARGET_BIN)

# Prevent make from removing any build targets, including intermediate ones
.SECONDARY: $(CLEAN)
