OBJDIR = .obj
CFLAGS = -g
CXX = g++

SRCS = \
	src/main.cc \

OBJS = $(patsubst %.cc, $(OBJDIR)/%.o, $(SRCS))

xylofagou.cgi: $(OBJS)
	@echo LINK $<
	@mkdir -p $(dir $@)
	@$(CXX) $(LDFLAGS) -o $@ $<

$(OBJDIR)/%.o: %.cc
	@echo CXX $<
	@mkdir -p $(dir $@)
	@$(CXX) $(CFLAGS) -MT $@ -MMD -MP -MF $(patsubst %.o,%.d,$@) -c -o $@ $<

clean:
	@echo CLEAN
	@rm -f $(OBJS) xylofagou.cgi

-include $(patsubst %.o, %.d, $(OBJS))
.SECONDARY:
.DELETE_ON_ERROR:

