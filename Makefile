amd64_asm_files := $(shell find src/platforms/amd64/boot -name *.asm)
amd64_asm_obj := $(patsubst src/platforms/amd64/boot/%.asm, build/amd64/%.o, $(amd64_asm_files))

$(amd64_asm_obj): build/amd64/%.o : src/platforms/amd64/boot/%.asm
	mkdir -p $(dir $@) && \
	nasm -f elf64 $(patsubst build/amd64/%.o, src/platforms/amd64/boot/%.asm, $@) -o $@

.PHONY: build-amd64
build-amd64: $(amd64_asm_obj)
	mkdir -p dist/amd64 && \
	ld -n -o dist/amd64/kernel.exe -T build/amd64/linker.ld $(amd64_asm_obj) && \
	cp dist/amd64/kernel.exe build/amd64/image/boot/kernel.exe && \
	grub2-mkrescue -d /usr/share/grub2/i386-pc -o dist/amd64/kernel.iso build/amd64/image

clean:
	rm -rf dist build/*/*.o build/*/*.exe build/*/*/*.exe
