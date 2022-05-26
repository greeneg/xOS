kernel_src := $(shell find src/kernel/ -name *.c)
kernel_obj := $(patsubst src/kernel/%.c, build/kernel/%.o, $(kernel_src))

amd64_c_src := $(shell find src/platforms/amd64/ -name *.c)
amd64_c_obj := $(patsubst src/platforms/amd64/%.c, build/amd64/%.o, $(amd64_c_src))

amd64_asm_src := $(shell find src/platforms/amd64/boot -name *.asm)
amd64_asm_obj := $(patsubst src/platforms/amd64/boot/%.asm, build/amd64/%.o, $(amd64_asm_src))

amd64_obj := $(amd64_c_obj) $(amd64_asm_obj)

$(kernel_obj): build/kernel/%.o : src/kernel/%.c
	mkdir -p $(dir $@) && \
	gcc -c -I src/includes -ffreestanding $(patsubst build/kernel/%.o, src/kernel/%.c, $@) -o $@

$(amd64_c_obj): build/amd64/%.o : src/platforms/amd64/%.c
	mkdir -p $(dir $@) && \
	gcc -c -I src/includes -ffreestanding $(patsubst build/amd64/%.o, src/platforms/amd64/%.c, $@) -o $@

$(amd64_asm_obj): build/amd64/%.o : src/platforms/amd64/boot/%.asm
	mkdir -p $(dir $@) && \
	nasm -f elf64 $(patsubst build/amd64/%.o, src/platforms/amd64/boot/%.asm, $@) -o $@

.PHONY: build-amd64
build-amd64: $(kernel_obj) $(amd64_obj)
	mkdir -p dist/amd64 && \
	ld -n -o dist/amd64/kernel.exe -T build/amd64/linker.ld $(kernel_obj) $(amd64_obj) && \
	cp dist/amd64/kernel.exe build/amd64/image/boot/kernel.exe && \
	grub2-mkrescue -d /usr/share/grub2/i386-pc -o dist/amd64/kernel.iso build/amd64/image

clean:
	rm -rf dist build/*/*.o build/*/*.exe build/*/*/*.exe build/*/*/*/*.exe
