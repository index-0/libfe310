# See LICENSE file for copyright and license details.

TOP = .

include config.mak

SRC := $(wildcard $(TOPSRC)/src/*.c)
OBJ := $(patsubst $(TOPSRC)/src/%.c,obj/%.o,$(SRC))

override CFLAGS += -I$(TOPSRC)/inc

all: lib/libfe310.a

lib/libfe310.a: $(OBJ)
	@mkdir -p $(@D)
	$(AR) rcs $@ $^

obj/%.o: $(TOPSRC)/src/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@rm -frv obj lib

dist: clean
	@rm -fv config.mak

install: all
	@mkdir -p $(DESTDIR)$(INCDIR) $(DESTDIR)$(LIBDIR)
	@cp -rv $(TOPSRC)/inc/fe310 $(DESTDIR)$(INCDIR)
	@cp -v lib/libfe310.a $(DESTDIR)$(LIBDIR)

uninstall:
	@rm -frv $(DESTDIR)$(INCDIR)/fe310
	@rm -fv $(DESTDIR)$(LIBDIR)/libfe310.a

.PHONY: all clean dist install uninstall
