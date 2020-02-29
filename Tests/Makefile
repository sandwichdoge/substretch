OBJECTS=testSubUtils.o ../SubUtils/SubUtils.o \
		main.o

CFLAGS+=-I../CommonCPP -pthread -I. -fsanitize=address

all: runtests.out
	./runtests.out

debug: CFLAGS+= -DDEBUG -g -fsanitize=address
debug: all

runtests.out: $(OBJECTS)
	$(CXX) $^ -o $@ $(LDFLAGS) libgtest.a -pthread -fsanitize=address

%.o: %.cpp
	$(CXX) -c $(CFLAGS) $< -o $@

clean:
	find . -name "*.o" | xargs rm -f
	rm *.out -f