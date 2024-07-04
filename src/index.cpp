#include <python3.12/Python.h>
#include <Python.h>

static PyObject* test(PyObject *self, PyObject *ptr) {
    printf("eoiqbfwqef\n");
    Py_RETURN_NONE;
}

static PyMethodDef methods[] = {
    {"print", test, METH_VARARGS, "func"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef npc_meth = {
    PyModuleDef_HEAD_INIT,
    "npc",
    NULL,
    -1,
    methods
};

PyMODINIT_FUNC PyInit_npc(void) {
    return PyModule_Create(&npc_meth);
}
