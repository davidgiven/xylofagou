OBJDIR = .obj
CFLAGS = -I$(HOME)/include -g -O3 -flto -ffunction-sections -fdata-sections
LDFLAGS = -L$(HOME)/lib -flto -lsqlite3 -lcgicc -lboost_json 
CXX = g++

SRCS = \
	src/actors.cc \
	src/initdb_cmd.cc \
	src/main.cc \
	src/properties.cc \
	src/sql.cc \
	src/utils.cc \
	src/webfinger_cgi.cc \

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

