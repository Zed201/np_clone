PY=$(shell which python3 || which python)
all:
	$(PY) setup.py build_ext --inplace

clean:
	rm -rf ./build npc*