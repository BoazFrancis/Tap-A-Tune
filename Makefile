# Make all three projects
all:
	+$(MAKE) -C src/emulator
	+$(MAKE) -C src/assembler
	+$(MAKE) -C src/extension
