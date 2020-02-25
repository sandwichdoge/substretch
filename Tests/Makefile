OBJECTS=testSubUtils.o ../SubUtils/SubUtils.o \
		main.o

CFLAGS+=-I../CommonCPP -pthread -I.

all: runtests.out
	./runtests.out

runtests.out: $(OBJECTS)
	$(CXX) $^ -o $@ $(LDFLAGS) libgtest.a -pthread

%.o: %.cpp
	$(CXX) -c $(CFLAGS) $< -o $@

clean:
	find . -name "*.o" | xargs rm -f
	rm *.out -f