#
# SPDX-License-Identifier: GPL-3.0-or-later
#
# Copyright (C) 2018, Harshit Jain
#

CC ?= gcc
CLANG_FORMAT ?= clang-format

default: devupload

devupload.o: devupload.c
	$(CC) -c devupload.c -o devupload.o

devupload: devupload.o
	$(CC) $(CFLAGS) devupload.o -o devupload
	-rm -f devupload.o

clean:
	-rm -f devupload.o
	-rm -f devupload

clang-format:
	@$(CLANG_FORMAT) -style='{IndentWidth: 4}' devupload.c > formatted.c
	@-mv formatted.c devupload.c

install: devupload
	sudo mv devupload /usr/local/bin/
	@echo "\033[01;33mNow you can use devupload binary with command line"
	@echo "Example: devupload -a my{rom:kernel}.zip 'Which would trigger afh uploader'\033[0m"
	@echo "Example: devupload -b my{rom:kernel}.zip 'Which would trigger basketbuild uploader'\033[0m"
	@echo "Example: devupload -t my{rom:kernel}.zip 'Which would trigger transfer.sh uploader'\033[0m"