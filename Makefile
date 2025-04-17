# See LICENSE file for copyright and license details.

include config.mk

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
LIB = $(OUT_DIR)/$(LIB_NAME).a

all: $(LIB)

$(LIB): $(OBJ)
	@mkdir -p $(@D)
	$(AR) rcs $@ $^

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR) $(OUT_DIR)

.PHONY: all clean
