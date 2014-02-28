default:
	@echo 'Please check the Makefiles in each subdirectory for correct settings, then run make all-examples.'

all-examples:
	$(MAKE) -C audio multi-play
	$(MAKE) -C fb
	$(MAKE) -C lines
	$(MAKE) -C net all
	$(MAKE) -C pw-ch4 pw
	$(MAKE) -C pw-ch5 pw
	$(MAKE) -C pw-ch6 pw
	$(MAKE) -C pw-ch7 pw
	$(MAKE) -C pw-final pw
	$(MAKE) -C sdl all-examples
	$(MAKE) -C tcl all

clean:
	$(MAKE) -C audio clean
	$(MAKE) -C fb clean
	$(MAKE) -C lines clean
	$(MAKE) -C net clean
	$(MAKE) -C pw-ch4 clean
	$(MAKE) -C pw-ch5 clean
	$(MAKE) -C pw-ch6 clean
	$(MAKE) -C pw-ch7 clean
	$(MAKE) -C pw-final clean
	$(MAKE) -C sdl clean
	$(MAKE) -C tcl clean
