# 后端的编译选项
CC = /usr/bin/gcc
STDC_OPT = -std=c11
OPT = -c


ulist_parse.o: ulist_parse.c
	$(CC) $(OPT) $< $(STDC_OPT) -o $@

utask_io.o: utask_io.c
	$(CC) $(OPT) $< $(STDC_OPT) -o $@

utask_struct.o: utask_struct.c
	$(CC) $(OPT) $< $(STDC_OPT) -o $@

udata:
	make utask_io.o ulist_parse.o utask_struct.o