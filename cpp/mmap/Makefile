BIN=alloc-mem alloc-file

.PHONY: all
all: $(BIN)

%: %.c
	gcc -Wall -ggdb -o $@ $<

.PHONY: clean
clean:
	rm -rfv $(BIN)
