OBJECTS=SubLine/SubLine.o \
		SubLine/SubLine_ass/SubLine_ass.o  SubLine/SubLine_srt/SubLine_srt.o \
		Parser/Parser.o \
		Optimizer/Optimizer.o \
		SubUtils/SubUtils.o \
		main.o
CFLAGS+=-I./CommonCPP

all: substretch.out

substretch.out: $(OBJECTS)
	$(CXX) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c $(CFLAGS) $< -o $@

clean:
	find . -name "*.o" | xargs rm -f
	rm *.out -f
