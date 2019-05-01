
GCC := g++

OUTPUT := ch01_mt_example_tong
SOURCES := ch01_mt_example_tong.cpp
CCFLAGS := -std=c++11 -pthread

all: $(OUTPUT)
	
$(OUTPUT):
	$(GCC) -o $(OUTPUT) $(CCFLAGS) $(SOURCES)
	
clean:
	rm $(OUTPUT)
	
.PHONY: all
