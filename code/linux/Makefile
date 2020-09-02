files=$(obj)
object=test
CC=g++

pre=$(patsubst %.cpp, %.i, $(files))
coms=$(patsubst %.i, %.s, $(pre))
como=$(patsubst %.s, %.o, $(coms))


$(object): $(como)
	$(CC) $^ -o $@
$(como): $(coms)
	$(CC) -c $^ -o $@
$(coms): $(pre)
	$(CC) -S $^ -o $@
$(pre): $(files)
	$(CC) -E $^ -o $@

.PHONY: clean
clean:
	rm *.i *.s *.o test
