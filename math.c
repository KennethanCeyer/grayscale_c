#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdio.h>

#ifdef _WIN32
    #define API extern __declspec(dllexport)
#else
    #define API
#endif

API PyObject* sum(PyObject* pList) {
    PyObject* pListItem;
    double result = 0;
    int length;
    int i;

    if (!PyList_Check(pList)) {
        PyErr_SetString(PyExc_TypeError, "parameter must be a list.");
        return NULL;
    }

    length = PyList_Size(pList);
    for (i=0; i<length; ++i) {
        pListItem = PyList_GetItem(pList, (Py_ssize_t)i);
        result += PyFloat_AsDouble(pListItem);
    }

    return PyFloat_FromDouble(result);
}

API PyObject* mean(PyObject* pList) {
    PyObject* pSum;
    int length;

    pSum = sum(pList);
    length = PyList_Size(pList);

    return PyFloat_FromDouble(PyFloat_AsDouble(pSum) / length);
}

API PyObject* var(PyObject* pList) {
    PyObject* pListItem;
    double result = 0;
    double meanValue;
    int length;
    int i;

    if (!PyList_Check(pList)) {
        PyErr_SetString(PyExc_TypeError, "parameter must be a list.");
        return NULL;
    }

    meanValue = PyFloat_AsDouble(mean(pList));
    length = PyList_Size(pList);
    for (i=0; i<length; ++i) {
        pListItem = PyList_GetItem(pList, (Py_ssize_t)i);
        result += pow(PyFloat_AsDouble(pListItem) - meanValue, 2);
    }
    result /= length;

    return PyFloat_FromDouble(result);
}

API PyObject* std(PyObject* pList) {
    return PyFloat_FromDouble(sqrt(PyFloat_AsDouble(var(pList))));
}
