#include <python3.12/Python.h>

static PyObject* print(PyObject *self, PyObject *ptr){
    printf("eoiqbfwqef\n");
    return Py_BuildValue("");
}

static PyMethodDef methods[] = {
    {"print", print, METH_VARARGS, "func"},
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
