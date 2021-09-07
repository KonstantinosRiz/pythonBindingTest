
// default includes
#include <shiboken.h>
#include <typeinfo>
#include <iterator>

// module include
#include "mymodule_python.h"

// main header
#include "example_wrapper.h"

// inner classes

#include <cctype>
#include <cstring>



template <class T>
static const char *typeNameOf(const T &t)
{
    const char *typeName =  typeid(t).name();
    auto size = std::strlen(typeName);
#if defined(Q_CC_MSVC) // MSVC: "class QPaintDevice * __ptr64"
    if (auto lastStar = strchr(typeName, '*')) {
        // MSVC: "class QPaintDevice * __ptr64"
        while (*--lastStar == ' ') {
        }
        size = lastStar - typeName + 1;
    }
#else // g++, Clang: "QPaintDevice *" -> "P12QPaintDevice"
    if (size > 2 && typeName[0] == 'P' && std::isdigit(typeName[1])) {
        ++typeName;
        --size;
    }
#endif
    char *result = new char[size + 1];
    result[size] = '\0';
    memcpy(result, typeName, size);
    return result;
}


// Target ---------------------------------------------------------

extern "C" {
static int
Sbk_Example_Init(PyObject *self, PyObject *args, PyObject *kwds)
{
    SbkObject *sbkSelf = reinterpret_cast<SbkObject *>(self);
    if (Shiboken::Object::isUserType(self) && !Shiboken::ObjectType::canCallConstructor(self->ob_type, Shiboken::SbkType< ::Example >()))
        return -1;

    ::Example *cptr{};
    Shiboken::AutoDecRef errInfo{};
    static const char *fullName = "MyModule.Example.__init__";
    SBK_UNUSED(fullName)
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { nullptr, nullptr };
    SBK_UNUSED(pythonToCpp)
    const Py_ssize_t numArgs = PyTuple_GET_SIZE(args);
    SBK_UNUSED(numArgs)
    PyObject *pyArgs[] = {0, 0};

    // invalid argument lengths


    if (!PyArg_UnpackTuple(args, "Example", 1, 2, &(pyArgs[0]), &(pyArgs[1])))
        return -1;


    // Overloaded function decisor
    // 0: Example::Example(Example)
    // 1: Example::Example(double,double)
    if (numArgs == 2
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<double>(), (pyArgs[0])))
        && (pythonToCpp[1] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<double>(), (pyArgs[1])))) {
        overloadId = 1; // Example(double,double)
    } else if (numArgs == 1
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppReferenceConvertible(reinterpret_cast<SbkObjectType *>(SbkMyModuleTypes[SBK_EXAMPLE_IDX]), (pyArgs[0])))) {
        overloadId = 0; // Example(Example)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_Example_Init_TypeError;

    // Call function/method
    switch (overloadId) {
        case 0: // Example(const Example & Example)
        {
            if (!Shiboken::Object::isValid(pyArgs[0]))
                return -1;
            ::Example cppArg0_local = ::Example(double(0), double(0));
            ::Example *cppArg0 = &cppArg0_local;
            if (Shiboken::Conversions::isImplicitConversion(reinterpret_cast<SbkObjectType *>(SbkMyModuleTypes[SBK_EXAMPLE_IDX]), pythonToCpp[0]))
                pythonToCpp[0](pyArgs[0], &cppArg0_local);
            else
                pythonToCpp[0](pyArgs[0], &cppArg0);


            if (!PyErr_Occurred()) {
                // Example(Example)
                cptr = new ::Example(*cppArg0);
            }
            break;
        }
        case 1: // Example(double a, double b)
        {
            double cppArg0;
            pythonToCpp[0](pyArgs[0], &cppArg0);
            double cppArg1;
            pythonToCpp[1](pyArgs[1], &cppArg1);

            if (!PyErr_Occurred()) {
                // Example(double,double)
                cptr = new ::Example(cppArg0, cppArg1);
            }
            break;
        }
    }

    if (PyErr_Occurred() || !Shiboken::Object::setCppPointer(sbkSelf, Shiboken::SbkType< ::Example >(), cptr)) {
        delete cptr;
        return -1;
    }
    if (!cptr) goto Sbk_Example_Init_TypeError;

    Shiboken::Object::setValidCpp(sbkSelf, true);
    if (Shiboken::BindingManager::instance().hasWrapper(cptr)) {
        Shiboken::BindingManager::instance().releaseWrapper(Shiboken::BindingManager::instance().retrieveWrapper(cptr));
    }
    Shiboken::BindingManager::instance().registerWrapper(sbkSelf, cptr);


    return 1;

    Sbk_Example_Init_TypeError:
        Shiboken::setErrorAboutWrongArguments(args, fullName, errInfo);
        return -1;
}

static PyObject *Sbk_ExampleFunc_add(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::Example *>(Shiboken::Conversions::cppPointer(SbkMyModuleTypes[SBK_EXAMPLE_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};
    Shiboken::AutoDecRef errInfo{};
    static const char *fullName = "MyModule.Example.add";
    SBK_UNUSED(fullName)

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // add()
            double cppResult = cppSelf->add();
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<double>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_Example___copy__(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto &cppSelf = *reinterpret_cast< ::Example *>(Shiboken::Conversions::cppPointer(SbkMyModuleTypes[SBK_EXAMPLE_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject *pyResult = Shiboken::Conversions::copyToPython(reinterpret_cast<SbkObjectType *>(SbkMyModuleTypes[SBK_EXAMPLE_IDX]), &cppSelf);
    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyMethodDef Sbk_Example_methods[] = {
    {"add", reinterpret_cast<PyCFunction>(Sbk_ExampleFunc_add), METH_NOARGS},

    {"__copy__", reinterpret_cast<PyCFunction>(Sbk_Example___copy__), METH_NOARGS},
    {nullptr, nullptr} // Sentinel
};

} // extern "C"

static int Sbk_Example_traverse(PyObject *self, visitproc visit, void *arg)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_traverse(self, visit, arg);
}
static int Sbk_Example_clear(PyObject *self)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_clear(self);
}
// Class Definition -----------------------------------------------
extern "C" {
static SbkObjectType *_Sbk_Example_Type = nullptr;
static SbkObjectType *Sbk_Example_TypeF(void)
{
    return _Sbk_Example_Type;
}

static PyType_Slot Sbk_Example_slots[] = {
    {Py_tp_base,        nullptr}, // inserted by introduceWrapperType
    {Py_tp_dealloc,     reinterpret_cast<void *>(&SbkDeallocWrapper)},
    {Py_tp_repr,        nullptr},
    {Py_tp_hash,        nullptr},
    {Py_tp_call,        nullptr},
    {Py_tp_str,         nullptr},
    {Py_tp_getattro,    nullptr},
    {Py_tp_setattro,    nullptr},
    {Py_tp_traverse,    reinterpret_cast<void *>(Sbk_Example_traverse)},
    {Py_tp_clear,       reinterpret_cast<void *>(Sbk_Example_clear)},
    {Py_tp_richcompare, nullptr},
    {Py_tp_iter,        nullptr},
    {Py_tp_iternext,    nullptr},
    {Py_tp_methods,     reinterpret_cast<void *>(Sbk_Example_methods)},
    {Py_tp_getset,      nullptr},
    {Py_tp_init,        reinterpret_cast<void *>(Sbk_Example_Init)},
    {Py_tp_new,         reinterpret_cast<void *>(SbkObjectTpNew)},
    {0, nullptr}
};
static PyType_Spec Sbk_Example_spec = {
    "1:MyModule.Example",
    sizeof(SbkObject),
    0,
    Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_HAVE_GC,
    Sbk_Example_slots
};

} //extern "C"


// Type conversion functions.

// Python to C++ pointer conversion - returns the C++ object of the Python wrapper (keeps object identity).
static void Example_PythonToCpp_Example_PTR(PyObject *pyIn, void *cppOut)
{
    Shiboken::Conversions::pythonToCppPointer(Sbk_Example_TypeF(), pyIn, cppOut);
}
static PythonToCppFunc is_Example_PythonToCpp_Example_PTR_Convertible(PyObject *pyIn)
{
    if (pyIn == Py_None)
        return Shiboken::Conversions::nonePythonToCppNullPtr;
    if (PyObject_TypeCheck(pyIn, reinterpret_cast<PyTypeObject *>(Sbk_Example_TypeF())))
        return Example_PythonToCpp_Example_PTR;
    return {};
}

// C++ to Python pointer conversion - tries to find the Python wrapper for the C++ object (keeps object identity).
static PyObject *Example_PTR_CppToPython_Example(const void *cppIn)
{
    auto pyOut = reinterpret_cast<PyObject *>(Shiboken::BindingManager::instance().retrieveWrapper(cppIn));
    if (pyOut) {
        Py_INCREF(pyOut);
        return pyOut;
    }
    bool changedTypeName = false;
    auto tCppIn = reinterpret_cast<const ::Example *>(cppIn);
    const char *typeName = typeid(*tCppIn).name();
    auto sbkType = Shiboken::ObjectType::typeForTypeName(typeName);
    if (sbkType && Shiboken::ObjectType::hasSpecialCastFunction(sbkType)) {
        typeName = typeNameOf(tCppIn);
        changedTypeName = true;
    }
    PyObject *result = Shiboken::Object::newObject(Sbk_Example_TypeF(), const_cast<void *>(cppIn), false, /* exactType */ changedTypeName, typeName);
    if (changedTypeName)
        delete [] typeName;
    return result;
}

// C++ to Python copy conversion.
static PyObject *Example_COPY_CppToPython_Example(const void *cppIn)
{
    return Shiboken::Object::newObject(Sbk_Example_TypeF(), new ::Example(*reinterpret_cast<const ::Example *>(cppIn)), true, true);
}

// Python to C++ copy conversion.
static void Example_PythonToCpp_Example_COPY(PyObject *pyIn, void *cppOut)
{
    *reinterpret_cast<::Example *>(cppOut) = *reinterpret_cast< ::Example *>(Shiboken::Conversions::cppPointer(SbkMyModuleTypes[SBK_EXAMPLE_IDX], reinterpret_cast<SbkObject *>(pyIn)));
}
static PythonToCppFunc is_Example_PythonToCpp_Example_COPY_Convertible(PyObject *pyIn)
{
    if (PyObject_TypeCheck(pyIn, reinterpret_cast<PyTypeObject *>(Sbk_Example_TypeF())))
        return Example_PythonToCpp_Example_COPY;
    return {};
}

// The signatures string for the functions.
// Multiple signatures have their index "n:" in front.
static const char *Example_SignatureStrings[] = {
    "1:MyModule.Example(self,Example:MyModule.Example)",
    "0:MyModule.Example(self,a:double,b:double)",
    "MyModule.Example.add(self)->double",
    "MyModule.Example.__copy__()",
    nullptr}; // Sentinel

void init_Example(PyObject *module)
{
    _Sbk_Example_Type = Shiboken::ObjectType::introduceWrapperType(
        module,
        "Example",
        "Example",
        &Sbk_Example_spec,
        &Shiboken::callCppDestructor< ::Example >,
        0,
        0,
        0);
    auto pyType = reinterpret_cast<PyTypeObject *>(_Sbk_Example_Type);
    InitSignatureStrings(pyType, Example_SignatureStrings);
    SbkMyModuleTypes[SBK_EXAMPLE_IDX]
        = reinterpret_cast<PyTypeObject *>(Sbk_Example_TypeF());

    // Register Converter
    SbkConverter *converter = Shiboken::Conversions::createConverter(Sbk_Example_TypeF(),
        Example_PythonToCpp_Example_PTR,
        is_Example_PythonToCpp_Example_PTR_Convertible,
        Example_PTR_CppToPython_Example,
        Example_COPY_CppToPython_Example);

    Shiboken::Conversions::registerConverterName(converter, "Example");
    Shiboken::Conversions::registerConverterName(converter, "Example*");
    Shiboken::Conversions::registerConverterName(converter, "Example&");
    Shiboken::Conversions::registerConverterName(converter, typeid(::Example).name());

    // Add Python to C++ copy (value, not pointer neither reference) conversion to type converter.
    Shiboken::Conversions::addPythonToCppValueConversion(converter,
        Example_PythonToCpp_Example_COPY,
        is_Example_PythonToCpp_Example_COPY_Convertible);

}
