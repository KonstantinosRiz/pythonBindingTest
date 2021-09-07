

#ifndef SBK_MYMODULE_PYTHON_H
#define SBK_MYMODULE_PYTHON_H

#include <sbkpython.h>
#include <sbkconverter.h>
// Bound library includes
#include <example.h>
// Conversion Includes - Primitive Types

// Type indices
enum : int {
    SBK_EXAMPLE_IDX                                          = 0,
    SBK_MyModule_IDX_COUNT                                   = 1
};
// This variable stores all Python types exported by this module.
extern PyTypeObject **SbkMyModuleTypes;

// This variable stores the Python module object exported by this module.
extern PyObject *SbkMyModuleModuleObject;

// This variable stores all type converters exported by this module.
extern SbkConverter **SbkMyModuleTypeConverters;

// Converter indices
enum : int {
    SBK_MyModule_CONVERTERS_IDX_COUNT                        = 1
};
// Macros for type check

namespace Shiboken
{

// PyType functions, to get the PyObjectType for a type T
template<> inline PyTypeObject *SbkType< ::Example >() { return reinterpret_cast<PyTypeObject *>(SbkMyModuleTypes[SBK_EXAMPLE_IDX]); }

} // namespace Shiboken

#endif // SBK_MYMODULE_PYTHON_H

