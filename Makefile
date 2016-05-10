include Makefile.in

EXE := uci_api
CFLAGS := -Wall -I$(INCLUDE_DIR)
LDFLAGS := -L$(LIBRARY_DIR1) -L$(LIBRARY_DIR2) -luci -lubox

$(EXE): main.o
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

main.o: main.c

clean:
	rm -f *.o $(EXE)
