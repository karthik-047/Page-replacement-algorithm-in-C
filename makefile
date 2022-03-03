TARGET = paging_sys
SRC = paging_sys.c
INC = paging_sys.h
HELPER = helper_fn.c
CC = gcc


all: $(TARGET)

paging_sys: $(SRC) $(HELPER) $(INC)
	$(CC) -o $(TARGET) $(SRC) $(HELPER)
	
.PHONY: clean
clean:
	rm -f $(TARGET)
