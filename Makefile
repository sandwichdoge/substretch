OBJECTS=SubLine/SubLine.o SubLine/SubLine_ass/SubLine_ass.o \
		main.o

all: substretch.out

substretch.out: $(OBJECTS)
	$(CXX) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c $(CFLAGS) $< -o $@

clean:
	find . -name "*.o" | xargs rm -f
	rm *.out -f