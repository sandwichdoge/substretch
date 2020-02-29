OBJECTS=SubLine/SubLine.o \
		SubLine/SubLine_ass/SubLine_ass.o  SubLine/SubLine_srt/SubLine_srt.o \
		Parser/Parser.o \
		Optimizer/Optimizer.o \
		Builder/Builder.o \
		SubUtils/SubUtils.o \
		main.o
CFLAGS+=-I./CommonCPP

all: substretch.out

debug: CFLAGS+= -DDEBUG -g -fsanitize=address
debug: all

substretch.out: $(OBJECTS)
	$(CXX) $^ -o $@ $(LDFLAGS) -fsanitize=address

%.o: %.cpp
	$(CXX) -c $(CFLAGS) $< -o $@

clean:
	find . -name "*.o" | xargs rm -f
	rm *.out -f
