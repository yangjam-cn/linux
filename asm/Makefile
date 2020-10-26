src = $(obj)
target = $(basename $(src))
asm_file = $(join $(target), .s)

$(target): $(src)
	gcc -S $^ -o $(asm_file)
	gcc $(asm_file) -o $@

