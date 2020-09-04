files=$(obj)
object=test
type=$(suffix $(files))
ifeq ($(type), "cpp")
	CC=g++
	pre=$(patsubst %.cpp, %.i, $(files))
else
	CC=gcc
	pre=$(patsubst %.c, %.i, $(files))
endif

coms=$(patsubst %.i, %.s, $(pre))
como=$(patsubst %.s, %.o, $(coms))


$(object): $(como)
	$(CC) $^ -lpthread -o $@
$(como): $(coms)
	$(CC) -c $^ -o $@
$(coms): $(pre)
	$(CC) -S $^ -o $@
$(pre): $(files)
	$(CC) -E $^ -o $@

.PHONY: clean
clean:
	rm *.i *.s *.o test && clear
