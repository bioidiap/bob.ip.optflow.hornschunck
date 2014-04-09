/**
 * @author Andre Anjos <andre.anjos@idiap.ch>
 * @date Wed 09 Apr 2014 13:09:22 CEST
 *
 * @brief Bindings for Horn & Schunck's Optical Flow framework
 *
 * Copyright (C) 2011-2014 Idiap Research Institute, Martigny, Switzerland
 */

#include <xbob.blitz/cppapi.h>
#include <xbob.blitz/cleanup.h>
#include <xbob.extension/documentation.h>
#include <structmember.h>

#include "HornAndSchunckFlow.h"

/*************************************
 * Implementation of Flow base class *
 *************************************/

#define CLASS_NAME "Flow"

static auto s_flow_doc = xbob::extension::ClassDoc(
    XBOB_EXT_MODULE_PREFIX "." CLASS_NAME,

    "Calculates the Optical Flow between two images.",

    "This is a clone of the Vanilla Horn & Schunck method that uses a Sobel "
    "gradient estimator instead of the forward estimator used by the "
    "classical method. The Laplacian operator is also replaced with a more "
    "common method. For more details on the technique see the module's help."
    )
    .add_constructor(
        xbob::extension::FunctionDoc(
          CLASS_NAME,
          "Initializes the functor with the sizes of images to be treated."
          )
        .add_prototype("(height, width)", "")
        .add_parameter("(height, width)", "tuple", "the height and width of images to be fed into the the flow estimator")
        )
    ;


typedef struct {
  PyObject_HEAD
  bob::ip::optflow::HornAndSchunckFlow* cxx;
} PyBobIpOptflowHornSchunckFlowObject;


static int PyBobIpOptflowHornSchunckFlow_init
(PyBobIpOptflowHornSchunckFlowObject* self, PyObject* args, PyObject* kwds) {

  /* Parses input arguments in a single shot */
  static const char* const_kwlist[] = {"shape", 0};
  static char** kwlist = const_cast<char**>(const_kwlist);

  Py_ssize_t height = 0;
  Py_ssize_t width = 0;

  if (!PyArg_ParseTupleAndKeywords(args, kwds, "(nn)", kwlist,
        &height, &width)) return -1;

  try {
    blitz::TinyVector<int,2> shape;
    shape(0) = height; shape(1) = width;
    self->cxx = new bob::ip::optflow::HornAndSchunckFlow(shape);
  }
  catch (std::exception& ex) {
    PyErr_SetString(PyExc_RuntimeError, ex.what());
    return -1;
  }
  catch (...) {
    PyErr_Format(PyExc_RuntimeError, "cannot create new object of type `%s' - unknown exception thrown", Py_TYPE(self)->tp_name);
    return -1;
  }

  return 0;

}

static void PyBobIpOptflowHornSchunckFlow_delete
(PyBobIpOptflowHornSchunckFlowObject* self) {

  delete self->cxx;
  Py_TYPE(self)->tp_free((PyObject*)self);

}

s_shape = xbob::extension::VariableDoc(
    "shape",
    "tuple",
    "The shape pre-configured for this flow estimator: ``(height, width)``"
    );

static PyObject* PyBobIpOptflowHornSchunckFlow_getShape
(PyBobIpOptflowHornSchunckFlowObject* self, void* /*closure*/) {
  auto shape = self->cxx->getShape();
  return Py_BuildValue("nn", shape(0), shape(1));
}

static int PyBobIpOptflowHornSchunckFlow_setShape (PyBobIpOptflowHornSchunckFlowObject* self, PyObject* o, void* /*closure*/) {

  static const char* const_kwlist[] = {"shape", 0};
  static char** kwlist = const_cast<char**>(const_kwlist);

  Py_ssize_t height = 0;
  Py_ssize_t width = 0;

  if (!PyArg_Parse(o, "nn", &height, &width)) return -1;

  try {
    blitz::TinyVector<int,2> shape;
    shape(0) = height; shape(1) = width;
    self->cxx->setShape(shape);
  }
  catch (std::exception& ex) {
    PyErr_SetString(PyExc_RuntimeError, ex.what());
    return -1;
  }
  catch (...) {
    PyErr_Format(PyExc_RuntimeError, "cannot reset `shape' of %s: unknown exception caught", Py_TYPE(self)->tp_name);
    return -1;
  }

  return 0;

}

static PyGetSetDef PyBobIpOptflowHornSchunckFlow_getseters[] = {
    {
      s_shape.name(),
      (getter)PyBobIpOptflowHornSchunckFlow_getShape,
      (setter)PyBobIpOptflowHornSchunckFlow_setShape,
      s_shape.doc(),
      0
    },
    {0}  /* Sentinel */
};

#if PY_VERSION_HEX >= 0x03000000
#  define PYOBJECT_STR PyObject_Str
#else
#  define PYOBJECT_STR PyObject_Unicode
#endif

PyObject* PyBobIpOptflowHornSchunckFlow_Repr(PyBobIpOptflowHornSchunckFlowObject* self) {

  /**
   * Expected output:
   *
   * <xbob.ip.optflow.hornschunck.Flow((3, 2))>
   */

  auto shape = make_safe(PyBobIpOptflowHornSchunckFlow_getShape(self, 0));
  if (!shape) return 0;
  auto shape_str = make_safe(PyObject_Str(shape.get()));

  return PyUnicode_FromFormat("<%s(%U)>",
      Py_TYPE(self)->tp_name, shape_str.get());
  }

}

/**
      .def("__call__", &hs_call, (arg("self"), arg("alpha"), arg("iterations"), arg("image1"), arg("image2"), arg("image3")))
      .def("__call__", &hs_call2, (arg("self"), arg("alpha"), arg("iterations"), arg("image1"), arg("image2"), arg("image3"), arg("u"), arg("v")))
      .def("eval_ec2", &hs_ec2, (arg("self"), arg("u"), arg("v")), "Calculates the square of the smoothness error (Ec^2) by using the formula described in the paper: Ec^2 = (u_bar - u)^2 + (v_bar - v)^2. Sets the input matrix with the discrete values.")
      .def("eval_eb", &hs_eb, (arg("self"), arg("i1"), arg("i2"), arg("i3"), arg("u"), arg("v")), "Calculates the brightness error (Eb) as defined in the paper: Eb = (Ex*u + Ey*v + Et). Sets the input matrix with the discrete values")
      ;
**/

static auto s_estimate = xbob::extension::FunctionDoc(
    "estimate"
    "Estimates the optical flow leading to ``image3``."
    "This method will use the leading images ``image1`` and ``image2``, to "
    "estimate the optical flow leading to ``image3``. All input images should "
    "be 2D 64-bit float arrays with the shape ``(height, width)`` as "
    "specified in the construction of the object."
    )
    .add_prototype("alpha, iterations, image1, image2, image3, [u, v]", "u, v")
    .add_parameter("alpha", "float", "The weighting factor between brightness constness and the field smoothness. The higher :math:`\\alpha`, the smoother the field will become.")
    .add_parameter("iterations", "int", "Number of iterations for which to minimize the flow error")
    .add_parameter("image1, image2, image3", "array-like (2D, float64)",
      "Sequence of images to estimate the flow from")
    .add_parameter("u, v", "array (2D, float64)", "The estimated flows in the horizontal and vertical directions (respectively) will be output in these variables, which should have dimensions matching those of ``image``, ``image2`` and ``image3``. If you don't provide arrays for ``u`` and ``v``, then they will be allocated internally and returned. If must either provide neither ``u`` and ``v`` or both, otherwise an exception will be raised.")
    .add_return("u, v", "array (2D, float)", "The estimated flows in the horizontal and vertical directions (respectively)."
    )
    ;

static PyObject* PyBobIpOptflowHornSchunckFlow_estimate
(PyBobIpOptflowHornSchunckFlowObject* self, PyObject* args, PyObject* kwds) {

  static const char* const_kwlist[] = {
    "alpha",
    "iterations",
    "image1",
    "image2",
    "image3",
    "u",
    "v",
    };
  static char** kwlist = const_cast<char**>(const_kwlist);

  PyBlitzArrayObject* image1 = 0;
  PyBlitzArrayObject* image2 = 0;
  PyBlitzArrayObject* image3 = 0;

  if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&|O&", kwlist,
        &PyBlitzArray_Converter, &input,
        &PyBlitzArray_OutputConverter, &output
        )) return 0;

  //protects acquired resources through this scope
  auto input_ = make_safe(input);
  auto output_ = make_xsafe(output);

  if (input->type_num != NPY_FLOAT64) {
    PyErr_Format(PyExc_TypeError, "`%s' only supports 64-bit float arrays for input array `input'", Py_TYPE(self)->tp_name);
    return 0;
  }

  if (output && output->type_num != NPY_FLOAT64) {
    PyErr_Format(PyExc_TypeError, "`%s' only supports 64-bit float arrays for output array `output'", Py_TYPE(self)->tp_name);
    return 0;
  }

  if (input->ndim < 1 || input->ndim > 2) {
    PyErr_Format(PyExc_TypeError, "`%s' only accepts 1 or 2-dimensional arrays (not %" PY_FORMAT_SIZE_T "dD arrays)", Py_TYPE(self)->tp_name, input->ndim);
    return 0;
  }

  if (output && input->ndim != output->ndim) {
    PyErr_Format(PyExc_RuntimeError, "Input and output arrays should have matching number of dimensions, but input array `input' has %" PY_FORMAT_SIZE_T "d dimensions while output array `output' has %" PY_FORMAT_SIZE_T "d dimensions", input->ndim, output->ndim);
    return 0;
  }

  if (input->ndim == 1) {
    if (input->shape[0] != (Py_ssize_t)self->cxx->inputSize()) {
      PyErr_Format(PyExc_RuntimeError, "1D `input' array should have %" PY_FORMAT_SIZE_T "d elements matching `%s' input size, not %" PY_FORMAT_SIZE_T "d elements", self->cxx->inputSize(), Py_TYPE(self)->tp_name, input->shape[0]);
      return 0;
    }
    if (output && output->shape[0] != (Py_ssize_t)self->cxx->outputSize()) {
      PyErr_Format(PyExc_RuntimeError, "1D `output' array should have %" PY_FORMAT_SIZE_T "d elements matching `%s' output size, not %" PY_FORMAT_SIZE_T "d elements", self->cxx->outputSize(), Py_TYPE(self)->tp_name, output->shape[0]);
      return 0;
    }
  }
  else {
    if (input->shape[1] != (Py_ssize_t)self->cxx->inputSize()) {
      PyErr_Format(PyExc_RuntimeError, "2D `input' array should have %" PY_FORMAT_SIZE_T "d columns, matching `%s' input size, not %" PY_FORMAT_SIZE_T "d elements", self->cxx->inputSize(), Py_TYPE(self)->tp_name, input->shape[1]);
      return 0;
    }
    if (output && output->shape[1] != (Py_ssize_t)self->cxx->outputSize()) {
      PyErr_Format(PyExc_RuntimeError, "2D `output' array should have %" PY_FORMAT_SIZE_T "d columns matching `%s' output size, not %" PY_FORMAT_SIZE_T "d elements", self->cxx->outputSize(), Py_TYPE(self)->tp_name, output->shape[1]);
      return 0;
    }
    if (output && input->shape[0] != output->shape[0]) {
      PyErr_Format(PyExc_RuntimeError, "2D `output' array should have %" PY_FORMAT_SIZE_T "d rows matching `input' size, not %" PY_FORMAT_SIZE_T "d rows", input->shape[0], output->shape[0]);
      return 0;
    }
  }

  /** if ``output`` was not pre-allocated, do it now **/
  if (!output) {
    Py_ssize_t osize[2];
    if (input->ndim == 1) {
      osize[0] = self->cxx->outputSize();
    }
    else {
      osize[0] = input->shape[0];
      osize[1] = self->cxx->outputSize();
    }
    output = (PyBlitzArrayObject*)PyBlitzArray_SimpleNew(NPY_FLOAT64, input->ndim, osize);
    output_ = make_safe(output);
  }

  /** all basic checks are done, can call the machine now **/
  try {
    if (input->ndim == 1) {
      self->cxx->forward_(*PyBlitzArrayCxx_AsBlitz<double,1>(input),
          *PyBlitzArrayCxx_AsBlitz<double,1>(output));
    }
    else {
      auto bzin = PyBlitzArrayCxx_AsBlitz<double,2>(input);
      auto bzout = PyBlitzArrayCxx_AsBlitz<double,2>(output);
      blitz::Range all = blitz::Range::all();
      for (int k=0; k<bzin->extent(0); ++k) {
        blitz::Array<double,1> i_ = (*bzin)(k, all);
        blitz::Array<double,1> o_ = (*bzout)(k, all);
        self->cxx->forward_(i_, o_); ///< no need to re-check
      }
    }
  }
  catch (std::exception& e) {
    PyErr_SetString(PyExc_RuntimeError, e.what());
    return 0;
  }
  catch (...) {
    PyErr_Format(PyExc_RuntimeError, "%s cannot forward data: unknown exception caught", Py_TYPE(self)->tp_name);
    return 0;
  }

  Py_INCREF(output);
  return PyBlitzArray_NUMPY_WRAP(reinterpret_cast<PyObject*>(output));

}

PyDoc_STRVAR(s_load_str, "load");
PyDoc_STRVAR(s_load_doc,
"o.load(f) -> None\n\
\n\
Loads itself from a :py:class:`xbob.io.HDF5File`\n\
\n\
");

static PyObject* PyBobIpOptflowHornSchunckFlow_Load
(PyBobIpOptflowHornSchunckFlowObject* self, PyObject* f) {

  if (!PyBobIoHDF5File_Check(f)) {
    PyErr_Format(PyExc_TypeError, "`%s' cannot load itself from `%s', only from an HDF5 file", Py_TYPE(self)->tp_name, Py_TYPE(f)->tp_name);
    return 0;
  }

  auto h5f = reinterpret_cast<PyBobIoHDF5FileObject*>(f);

  try {
    self->cxx->load(*h5f->f);
  }
  catch (std::exception& e) {
    PyErr_SetString(PyExc_RuntimeError, e.what());
    return 0;
  }
  catch (...) {
    PyErr_Format(PyExc_RuntimeError, "cannot read data from file `%s' (at group `%s'): unknown exception caught", h5f->f->filename().c_str(),
        h5f->f->cwd().c_str());
    return 0;
  }

  Py_RETURN_NONE;
}

PyDoc_STRVAR(s_save_str, "save");
PyDoc_STRVAR(s_save_doc,
"o.save(f) -> None\n\
\n\
Saves itself at a :py:class:`xbob.io.HDF5File`\n\
\n\
");

static PyObject* PyBobIpOptflowHornSchunckFlow_Save
(PyBobIpOptflowHornSchunckFlowObject* self, PyObject* f) {

  if (!PyBobIoHDF5File_Check(f)) {
    PyErr_Format(PyExc_TypeError, "`%s' cannot write itself to `%s', only to an HDF5 file", Py_TYPE(self)->tp_name, Py_TYPE(f)->tp_name);
    return 0;
  }

  auto h5f = reinterpret_cast<PyBobIoHDF5FileObject*>(f);

  try {
    self->cxx->save(*h5f->f);
  }
  catch (std::exception& e) {
    PyErr_SetString(PyExc_RuntimeError, e.what());
    return 0;
  }
  catch (...) {
    PyErr_Format(PyExc_RuntimeError, "`%s' cannot write data to file `%s' (at group `%s'): unknown exception caught", Py_TYPE(self)->tp_name,
        h5f->f->filename().c_str(), h5f->f->cwd().c_str());
    return 0;
  }

  Py_RETURN_NONE;
}

PyDoc_STRVAR(s_is_similar_to_str, "is_similar_to");
PyDoc_STRVAR(s_is_similar_to_doc,
"o.is_similar_to(other [, r_epsilon=1e-5 [, a_epsilon=1e-8]]) -> bool\n\
\n\
Compares this LinearMachine with the ``other`` one to be\n\
approximately the same.\n\
\n\
The optional values ``r_epsilon`` and ``a_epsilon`` refer to the\n\
relative and absolute precision for the ``weights``, ``biases``\n\
and any other values internal to this machine.\n\
\n\
");

static PyObject* PyBobIpOptflowHornSchunckFlow_IsSimilarTo
(PyBobIpOptflowHornSchunckFlowObject* self, PyObject* args, PyObject* kwds) {

  /* Parses input arguments in a single shot */
  static const char* const_kwlist[] = {"other", "r_epsilon", "a_epsilon", 0};
  static char** kwlist = const_cast<char**>(const_kwlist);

  PyObject* other = 0;
  double r_epsilon = 1.e-5;
  double a_epsilon = 1.e-8;

  if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!|dd", kwlist,
        &PyBobIpOptflowHornSchunckFlow_Type, &other,
        &r_epsilon, &a_epsilon)) return 0;

  auto other_ = reinterpret_cast<PyBobIpOptflowHornSchunckFlowObject*>(other);

  if (self->cxx->is_similar_to(*other_->cxx, r_epsilon, a_epsilon))
    Py_RETURN_TRUE;
  else
    Py_RETURN_FALSE;

}

PyDoc_STRVAR(s_resize_str, "resize");
PyDoc_STRVAR(s_resize_doc,
"o.resize(input, output) -> None\n\
\n\
Resizes the machine. If either the input or output increases\n\
in size, the weights and other factors should be considered\n\
uninitialized. If the size is preserved or reduced, already\n\
initialized values will not be changed.\n\
\n\
.. note::\n\
\n\
   Use this method to force data compression. All will work\n\
   out given most relevant factors to be preserved are\n\
   organized on the top of the weight matrix. In this way,\n\
   reducing the system size will supress less relevant\n\
   projections.\n\
\n\
");

static PyObject* PyBobIpOptflowHornSchunckFlow_Resize
(PyBobIpOptflowHornSchunckFlowObject* self, PyObject* args, PyObject* kwds) {

  /* Parses input arguments in a single shot */
  static const char* const_kwlist[] = {"input", "output", 0};
  static char** kwlist = const_cast<char**>(const_kwlist);

  Py_ssize_t input = 0;
  Py_ssize_t output = 0;

  if (!PyArg_ParseTupleAndKeywords(args, kwds, "nn", kwlist,
        &input, &output)) return 0;

  try {
    self->cxx->resize(input, output);
  }
  catch (std::exception& ex) {
    PyErr_SetString(PyExc_RuntimeError, ex.what());
    return 0;
  }
  catch (...) {
    PyErr_Format(PyExc_RuntimeError, "cannot resize object of type `%s' - unknown exception thrown", Py_TYPE(self)->tp_name);
    return 0;
  }

  Py_RETURN_NONE;

}

static PyMethodDef PyBobIpOptflowHornSchunckFlow_methods[] = {
  {
    s_forward_str,
    (PyCFunction)PyBobIpOptflowHornSchunckFlow_forward,
    METH_VARARGS|METH_KEYWORDS,
    s_forward_doc
  },
  {
    s_load_str,
    (PyCFunction)PyBobIpOptflowHornSchunckFlow_Load,
    METH_O,
    s_load_doc
  },
  {
    s_save_str,
    (PyCFunction)PyBobIpOptflowHornSchunckFlow_Save,
    METH_O,
    s_save_doc
  },
  {
    s_is_similar_to_str,
    (PyCFunction)PyBobIpOptflowHornSchunckFlow_IsSimilarTo,
    METH_VARARGS|METH_KEYWORDS,
    s_is_similar_to_doc
  },
  {
    s_resize_str,
    (PyCFunction)PyBobIpOptflowHornSchunckFlow_Resize,
    METH_VARARGS|METH_KEYWORDS,
    s_resize_doc
  },
  {0} /* Sentinel */
};

static PyObject* PyBobIpOptflowHornSchunckFlow_new
(PyTypeObject* type, PyObject*, PyObject*) {

  /* Allocates the python object itself */
  PyBobIpOptflowHornSchunckFlowObject* self =
    (PyBobIpOptflowHornSchunckFlowObject*)type->tp_alloc(type, 0);

  self->cxx = 0;

  return reinterpret_cast<PyObject*>(self);

}

PyObject* PyBobIpOptflowHornSchunckFlow_NewFromSize
(Py_ssize_t input, Py_ssize_t output) {

  PyBobIpOptflowHornSchunckFlowObject* retval = (PyBobIpOptflowHornSchunckFlowObject*)PyBobIpOptflowHornSchunckFlow_new(&PyBobIpOptflowHornSchunckFlow_Type, 0, 0);

  retval->cxx = new bob::machine::LinearMachine(input, output);

  return reinterpret_cast<PyObject*>(retval);

}

PyTypeObject PyBobIpOptflowHornSchunckFlow_Type = {
    PyVarObject_HEAD_INIT(0, 0)
    s_linear_str,                                     /* tp_name */
    sizeof(PyBobIpOptflowHornSchunckFlowObject),            /* tp_basicsize */
    0,                                                /* tp_itemsize */
    (destructor)PyBobIpOptflowHornSchunckFlow_delete,       /* tp_dealloc */
    0,                                                /* tp_print */
    0,                                                /* tp_getattr */
    0,                                                /* tp_setattr */
    0,                                                /* tp_compare */
    (reprfunc)PyBobIpOptflowHornSchunckFlow_Repr,           /* tp_repr */
    0,                                                /* tp_as_number */
    0,                                                /* tp_as_sequence */
    0,                                                /* tp_as_mapping */
    0,                                                /* tp_hash */
    (ternaryfunc)PyBobIpOptflowHornSchunckFlow_forward,     /* tp_call */
    (reprfunc)PyBobIpOptflowHornSchunckFlow_Str,            /* tp_str */
    0,                                                /* tp_getattro */
    0,                                                /* tp_setattro */
    0,                                                /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,         /* tp_flags */
    s_linear_doc,                                     /* tp_doc */
    0,                                                /* tp_traverse */
    0,                                                /* tp_clear */
    (richcmpfunc)PyBobIpOptflowHornSchunckFlow_RichCompare, /* tp_richcompare */
    0,                                                /* tp_weaklistoffset */
    0,                                                /* tp_iter */
    0,                                                /* tp_iternext */
    PyBobIpOptflowHornSchunckFlow_methods,                  /* tp_methods */
    0,                                                /* tp_members */
    PyBobIpOptflowHornSchunckFlow_getseters,                /* tp_getset */
    0,                                                /* tp_base */
    0,                                                /* tp_dict */
    0,                                                /* tp_descr_get */
    0,                                                /* tp_descr_set */
    0,                                                /* tp_dictoffset */
    (initproc)PyBobIpOptflowHornSchunckFlow_init,           /* tp_init */
    0,                                                /* tp_alloc */
    PyBobIpOptflowHornSchunckFlow_new,                      /* tp_new */
};
