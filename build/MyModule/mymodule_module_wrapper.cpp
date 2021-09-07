
#include <sbkpython.h>
#include <shiboken.h>
#include <algorithm>
#include <signature.h>
#include "mymodule_python.h"



// Extra includes

// Current module's type array.
PyTypeObject **SbkMyModuleTypes = nullptr;
// Current module's PyObject pointer.
PyObject *SbkMyModuleModuleObject = nullptr;
// Current module's converter array.
SbkConverter **SbkMyModuleTypeConverters = nullptr;
// Global functions ------------------------------------------------------------

static PyMethodDef MyModule_methods[] = {
    {0} // Sentinel
};

// Classes initialization functions ------------------------------------------------------------
void init_Example(PyObject *module);


// Module initialization ------------------------------------------------------------
static struct PyModuleDef moduledef = {
    /* m_base     */ PyModuleDef_HEAD_INIT,
    /* m_name     */ "MyModule",
    /* m_doc      */ nullptr,
    /* m_size     */ -1,
    /* m_methods  */ MyModule_methods,
    /* m_reload   */ nullptr,
    /* m_traverse */ nullptr,
    /* m_clear    */ nullptr,
    /* m_free     */ nullptr
};

// The signatures string for the global functions.
// Multiple signatures have their index "n:" in front.
static const char *MyModule_SignatureStrings[] = {
    nullptr}; // Sentinel

extern "C" LIBSHIBOKEN_EXPORT PyObject *PyInit_MyModule()
{
    if (SbkMyModuleModuleObject != nullptr)
        return SbkMyModuleModuleObject;
    // Create an array of wrapper types for the current module.
    static PyTypeObject *cppApi[SBK_MyModule_IDX_COUNT];
    SbkMyModuleTypes = cppApi;

    // Create an array of primitive type converters for the current module.
    static SbkConverter *sbkConverters[SBK_MyModule_CONVERTERS_IDX_COUNT];
    SbkMyModuleTypeConverters = sbkConverters;

    PyObject *module = Shiboken::Module::create("MyModule", &moduledef);

    // Make module available from global scope
    SbkMyModuleModuleObject = module;

    // Initialize classes in the type system
    init_Example(module);
    // Register primitive types converters.

    Shiboken::Module::registerTypes(module, SbkMyModuleTypes);
    Shiboken::Module::registerTypeConverters(module, SbkMyModuleTypeConverters);

    if (PyErr_Occurred()) {
        PyErr_Print();
        Py_FatalError("can't initialize module MyModule");
    }
    FinishSignatureInitialization(module, MyModule_SignatureStrings);

    return module;
}
