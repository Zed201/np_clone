#include <python3.12/Python.h>

static PyMethodDef methods[] = {
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef npc = {
    PyModuleDef_HEAD_INIT,
    "npc",
    NULL,
    -1,
    methods
};

PyMODINIT_FUNC PyInit_npc(void){
    return PyModule_Create(&npc);
}