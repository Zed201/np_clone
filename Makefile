PY=$(shell which python3 || which python)
LIB_FILE:=''
define find_lib
	$(eval LIB_FILE:=$(shell find ./build -name 'npc*'))
	@echo $(LIB_FILE)
endef
build_:
	$(PY) setup.py build_ext

all: build_
	$(MAKE) move;
	
move:
	$(call find_lib)
	mv $(LIB_FILE) ./npc.so

clean:
	rm -rf ./build ./npc.so
