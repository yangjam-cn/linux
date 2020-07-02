Target = file_demo
ARCH ?= x86
ifeq ($(ARCH), x86)
	CC = gcc
else
	CC = arm-linux-gnueabihf-gcc
endif

build_dir = build_$(ARCH)
src_dir = .
inc_dir = includes .

sources = $(foreach dir, $(src_dir), $(wildcard $(dir)/*.c))
objects = $(patsubst %.c, $(build_dir)/%.o, $(notdir $(sources)))
includes = $(foreach dir, $(inc_dir), $(wildcard $(dir)/*.h))
CFLAGS = $(patsubst %, -I%, $(inc_dir))

$(build_dir)/$(Target): $(objects) | create_build
	$(CC) $^ -o $@
$(build_dir)/%.o: $(src_dir)/%.c $(includes) | create_build
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean cleanall create_build
clean:
	rm -rf $(build_dir)

cleanall:
	rm -rf build_x86 build_arm

create_build:
	@mkdir -p $(build_dir)

