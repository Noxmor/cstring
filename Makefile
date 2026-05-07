PREFIX ?= /usr/local
INCLUDE_DIR := $(PREFIX)/include

test:
	python3 tests.py

install: test
	@echo "Installing cstring..."
	mkdir -p "$(INCLUDE_DIR)"
	cp include/cstring.h $(INCLUDE_DIR)
	@echo "Successfully installed cstring."

uninstall:
	@echo "Removing cstring..."
	rm -f $(INCLUDE_DIR)/cstring.h
	@echo "Successfully removed cstring."

.PHONY: test install uninstall
