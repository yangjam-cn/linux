input_file = $(obj)

GCC = g++
CFLAGS = -g -I/opt/opencv/install/include/opencv4  -L/opt/opencv/install/lib -lopencv_world

target = $(basename $(input_file))

$(target): $(input_file)
	$(GCC) $< $(CFLAGS) -o $@

