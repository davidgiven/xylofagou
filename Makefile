OBJDIR = .obj
CFLAGS = -I$(HOME)/include -g -Os -ffunction-sections -fdata-sections
LDFLAGS = -L$(HOME)/lib -lsqlite3 -lcgicc -lboost_json 
CXX = g++

SRCS = $(wildcard src/*.cc)
OBJS = $(patsubst %.cc, $(OBJDIR)/%.o, $(SRCS))

xylofagou.cgi: $(OBJS)
	@echo LINK $@
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

