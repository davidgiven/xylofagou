OBJDIR = .obj
CFLAGS = -g
LDFLAGS = -lsqlite3 -lfmt
CXX = g++

SRCS = \
	src/main.cc \
	src/utils.cc \
	src/initdb_cmd.cc \
	src/wellknown_cgi.cc \

OBJS = $(patsubst %.cc, $(OBJDIR)/%.o, $(SRCS))

xylofagou.cgi: $(OBJS)
	@echo LINK $<
	@mkdir -p $(dir $@)
	@$(CXX) -o $@ $^ $(LDFLAGS)
	@echo done.

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

