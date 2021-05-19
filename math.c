#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdio.h>

#ifdef _WIN32
    #define API extern __declspec(dllexport)
#else
    #define API
#endif

API PyObject* gs_sum(PyObject* pList) {
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

API PyObject* gs_mean(PyObject* pList) {
    PyObject* pSum;
    int length;

    pSum = gs_sum(pList);
    length = PyList_Size(pList);

    return PyFloat_FromDouble(PyFloat_AsDouble(pSum) / length);
}

API PyObject* gs_pow(PyObject* x, PyObject* y) {
    double xValue = PyFloat_AsDouble(x);
    double yValue = PyFloat_AsDouble(y);
    return PyFloat_FromDouble(pow(xValue, yValue));
}

API PyObject* gs_sqrt(PyObject* x) {
    double xValue = PyFloat_AsDouble(x);
    return PyFloat_FromDouble(sqrt(xValue));
}

API PyObject* gs_var(PyObject* pList) {
    PyObject* pListItem;
    double result = 0;
    double meanValue;
    int length;
    int i;

    if (!PyList_Check(pList)) {
        PyErr_SetString(PyExc_TypeError, "parameter must be a list.");
        return NULL;
    }

    meanValue = PyFloat_AsDouble(gs_mean(pList));
    length = PyList_Size(pList);
    for (i=0; i<length; ++i) {
        pListItem = PyList_GetItem(pList, (Py_ssize_t)i);
        result += pow(PyFloat_AsDouble(pListItem) - meanValue, 2);
    }
    result /= length;

    return PyFloat_FromDouble(result);
}

API PyObject* gs_std(PyObject* pList) {
    return PyFloat_FromDouble(sqrt(PyFloat_AsDouble(gs_var(pList))));
}

API PyObject* gs_min(PyObject* pList) {
        PyObject* pListItem;
        double result;
        int i = 0;
        int length;

        if (!PyList_Check(pList)) {
            PyErr_SetString(PyExc_TypeError, "parameter must be a list.");
            return NULL;
        }

        length = PyList_Size(pList);
        if (length == 0) {
            PyErr_SetString(PyExc_ValueError, "list should not be empty.");
            return NULL;
        }

        result = PyFloat_AsDouble(PyList_GetItem(pList, (Py_ssize_t)0));

        for (i=1; i<length; ++i) {
            pListItem = PyList_GetItem(pList, (Py_ssize_t)i);
            result = min(result, PyFloat_AsDouble(pListItem));
        }

        return PyFloat_FromDouble(result);
}

API PyObject* gs_max(PyObject* pList) {
        PyObject* pListItem;
        double result;
        int i = 0;
        int length;

        if (!PyList_Check(pList)) {
            PyErr_SetString(PyExc_TypeError, "parameter must be a list.");
            return NULL;
        }

        length = PyList_Size(pList);
        if (length == 0) {
            PyErr_SetString(PyExc_ValueError, "list should not be empty.");
            return NULL;
        }

        result = PyFloat_AsDouble(PyList_GetItem(pList, (Py_ssize_t)0));

        for (i=1; i<length; ++i) {
            pListItem = PyList_GetItem(pList, (Py_ssize_t)i);
            result = max(result, PyFloat_AsDouble(pListItem));
        }

        return PyFloat_FromDouble(result);
}
