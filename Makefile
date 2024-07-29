CC := clang
CFLAGS := -std=c99 -Wall -Wextra -pedantic
CFLAGS += -Wno-keyword-macro -Wno-gnu-zero-variadic-macro-arguments
CPPFLAGS := -MMD -Iinclude
LDFLAGS :=

ifdef RELEASE
CFLAGS += -O3
else
CFLAGS += -g -O1 -fsanitize=address -fsanitize=undefined
endif

.PHONY := all run clean

SRC_DIR := src
BUILD_DIR := build
# TODO: Choose a name for your executable
EXEC := $(BUILD_DIR)/exec

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
DEPS := $(OBJS:%.o=%.d)

all: $(EXEC)

run: $(EXEC)
	./$(EXEC) $(ARGS)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

-include $(DEPS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(BUILD_DIR)
