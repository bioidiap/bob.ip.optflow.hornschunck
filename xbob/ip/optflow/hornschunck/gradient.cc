/**
 * @file ip/python/SpatioTemporalGradient.cc
 * @date Tue Sep 6 17:29:53 2011 +0200
 * @author Andre Anjos <andre.anjos@idiap.ch>
 *
 * @brief Bindings to Spatio Temporal gradients
 *
 * Copyright (C) 2011-2013 Idiap Research Institute, Martigny, Switzerland
 */

#include <bob/ip/SpatioTemporalGradient.h>
#include <bob/core/cast.h>
#include <bob/python/ndarray.h>

using namespace boost::python;

static tuple forward_gradient_1(const bob::ip::ForwardGradient& g,
    bob::python::const_ndarray i) {

  blitz::Range all = blitz::Range::all();
  blitz::Array<double,2> i1;
  blitz::Array<double,2> i2;

  const bob::core::array::typeinfo& info = i.type();

  switch (info.dtype) {
    case bob::core::array::t_uint8:
      {
        blitz::Array<uint8_t,3> i_ = i.bz<uint8_t,3>();
        i1.reference(bob::core::array::cast<double,uint8_t>(i_(0,all,all)));
        i2.reference(bob::core::array::cast<double,uint8_t>(i_(1,all,all)));
      }
      break;
    case bob::core::array::t_float64:
      {
        blitz::Array<double,3> i_ = i.bz<double,3>();
        i1.reference(i_(0,all,all));
        i2.reference(i_(1,all,all));
      }
      break;
    default:
      PYTHON_ERROR(TypeError, "forward gradient call does not support array with type '%s'", info.str().c_str());
  }

  bob::python::ndarray Ex(bob::core::array::t_float64, info.shape[0], info.shape[1]);
  bob::python::ndarray Ey(bob::core::array::t_float64, info.shape[0], info.shape[1]);
  bob::python::ndarray Et(bob::core::array::t_float64, info.shape[0], info.shape[1]);
  blitz::Array<double,2> Ex_ = Ex.bz<double,2>();
  blitz::Array<double,2> Ey_ = Ey.bz<double,2>();
  blitz::Array<double,2> Et_ = Et.bz<double,2>();

  g(i1, i2, Ex_, Ey_, Et_);

  return make_tuple(Ex.self(), Ey.self(), Et.self());
}

static void forward_gradient_2(const bob::ip::ForwardGradient& g,
    bob::python::const_ndarray i1, bob::python::const_ndarray i2,
    bob::python::ndarray Ex, bob::python::ndarray Ey, bob::python::ndarray Et) {

  const bob::core::array::typeinfo& info = i1.type();

  blitz::Array<double,2> Ex_ = Ex.bz<double,2>();
  blitz::Array<double,2> Ey_ = Ey.bz<double,2>();
  blitz::Array<double,2> Et_ = Et.bz<double,2>();

  switch (info.dtype) {
    case bob::core::array::t_uint8:
      {
        g(bob::core::array::cast<double,uint8_t>(i1.bz<uint8_t,2>()),
            bob::core::array::cast<double,uint8_t>(i2.bz<uint8_t,2>()), Ex_, Ey_, Et_);
      }
      break;
    case bob::core::array::t_float64:
      {
        g(i1.bz<double,2>(), i2.bz<double,2>(), Ex_, Ey_, Et_);
      }
      break;
    default:
      PYTHON_ERROR(TypeError, "forward gradient call does not support array with type '%s'", info.str().c_str());
  }
}

static tuple forward_gradient_3(const bob::ip::ForwardGradient& g,
    bob::python::const_ndarray i1, bob::python::const_ndarray i2) {
  const bob::core::array::typeinfo& info = i1.type();

  bob::python::ndarray Ex(bob::core::array::t_float64, info.shape[0], info.shape[1]);
  bob::python::ndarray Ey(bob::core::array::t_float64, info.shape[0], info.shape[1]);
  bob::python::ndarray Et(bob::core::array::t_float64, info.shape[0], info.shape[1]);
  forward_gradient_2(g, i1, i2, Ex, Ey, Et);

  return make_tuple(Ex.self(), Ey.self(), Et.self());
}

static tuple central_gradient_1(const bob::ip::CentralGradient& g,
    bob::python::const_ndarray i) {

  blitz::Range all = blitz::Range::all();
  blitz::Array<double,2> i1;
  blitz::Array<double,2> i2;
  blitz::Array<double,2> i3;

  const bob::core::array::typeinfo& info = i.type();

  switch (info.dtype) {
    case bob::core::array::t_uint8:
      {
        blitz::Array<uint8_t,3> i_ = i.bz<uint8_t,3>();
        i1.reference(bob::core::array::cast<double,uint8_t>(i_(0,all,all)));
        i2.reference(bob::core::array::cast<double,uint8_t>(i_(1,all,all)));
        i3.reference(bob::core::array::cast<double,uint8_t>(i_(2,all,all)));
      }
      break;
    case bob::core::array::t_float64:
      {
        blitz::Array<double,3> i_ = i.bz<double,3>();
        i1.reference(i_(0,all,all));
        i2.reference(i_(1,all,all));
        i3.reference(i_(1,all,all));
      }
      break;
    default:
      PYTHON_ERROR(TypeError, "central gradient call does not support array with type '%s'", info.str().c_str());
  }

  bob::python::ndarray Ex(bob::core::array::t_float64, info.shape[0], info.shape[1]);
  bob::python::ndarray Ey(bob::core::array::t_float64, info.shape[0], info.shape[1]);
  bob::python::ndarray Et(bob::core::array::t_float64, info.shape[0], info.shape[1]);
  blitz::Array<double,2> Ex_ = Ex.bz<double,2>();
  blitz::Array<double,2> Ey_ = Ey.bz<double,2>();
  blitz::Array<double,2> Et_ = Et.bz<double,2>();

  g(i1, i2, i3, Ex_, Ey_, Et_);

  return make_tuple(Ex.self(), Ey.self(), Et.self());
}

static void central_gradient_2(const bob::ip::CentralGradient& g,
    bob::python::const_ndarray i1, bob::python::const_ndarray i2, bob::python::const_ndarray i3,
    bob::python::ndarray Ex, bob::python::ndarray Ey, bob::python::ndarray Et) {

  const bob::core::array::typeinfo& info = i1.type();

  blitz::Array<double,2> Ex_ = Ex.bz<double,2>();
  blitz::Array<double,2> Ey_ = Ey.bz<double,2>();
  blitz::Array<double,2> Et_ = Et.bz<double,2>();

  switch (info.dtype) {
    case bob::core::array::t_uint8:
      {
        g(bob::core::array::cast<double,uint8_t>(i1.bz<uint8_t,2>()),
            bob::core::array::cast<double,uint8_t>(i2.bz<uint8_t,2>()),
            bob::core::array::cast<double,uint8_t>(i3.bz<uint8_t,2>()), Ex_, Ey_, Et_);
      }
      break;
    case bob::core::array::t_float64:
      {
        g(i1.bz<double,2>(), i2.bz<double,2>(), i3.bz<double,2>(),
            Ex_, Ey_, Et_);
      }
      break;
    default:
      PYTHON_ERROR(TypeError, "central gradient call does not support array with type '%s'", info.str().c_str());
  }
}

static tuple central_gradient_3(const bob::ip::CentralGradient& g,
    bob::python::const_ndarray i1, bob::python::const_ndarray i2, bob::python::const_ndarray i3) {
  const bob::core::array::typeinfo& info = i1.type();

  bob::python::ndarray Ex(bob::core::array::t_float64, info.shape[0], info.shape[1]);
  bob::python::ndarray Ey(bob::core::array::t_float64, info.shape[0], info.shape[1]);
  bob::python::ndarray Et(bob::core::array::t_float64, info.shape[0], info.shape[1]);
  central_gradient_2(g, i1, i2, i3, Ex, Ey, Et);

  return make_tuple(Ex.self(), Ey.self(), Et.self());
}

void bind_ip_spatiotempgrad() {
  class_<bob::ip::PrewittGradient, bases<bob::ip::CentralGradient> >("PrewittGradient", "This class computes the spatio-temporal gradient using a 3-D sobel filter. The gradients are calculated along the x, y and t directions. It can be decomposed into 2 1D kernels that are applied in sequence. Considering h'(.) = [+1 0 -1] and h(.) = [1 1 1] one can represent the operations like this:\n\nEx = h'(x)h(y)h(t)\n\nEy = h(x)h'(y)h(t)\n\nEt = h(x)h(y)h'(t)", init<const blitz::TinyVector<int,2>&>((arg("self"), arg("shape")), "We initialize with the shape of the images we need to treat. The shape is used by the internal buffers.\n\nThe difference kernel for this operator is [+1; 0; -1]\n\nThe averaging kernel for this oeprator is [+1; +1; +1]."))
    ;

  class_<bob::ip::IsotropicGradient, bases<bob::ip::CentralGradient> >("IsotropicGradient", "This class computes the spatio-temporal gradient using a isotropic filter. The gradients are calculated along the x, y and t directions. The Sobel operator can be decomposed into 2 1D kernels that are applied in sequence. Considering h'(.) = [+1 0 -1] and h(.) = [1 sqrt(2) 1] one can represent the operations like this:\n\nEx = h'(x)h(y)h(t)\n\nEy = h(x)h'(y)h(t)\n\nEt = h(x)h(y)h'(t)", init<const blitz::TinyVector<int,2>&>((arg("self"), arg("shape")), "We initialize with the shape of the images we need to treat. The shape is used by the internal buffers.\n\nThe difference kernel for this operator is [+1; 0; -1]\n\nThe averaging kernel for this oeprator is [+1; +sqrt(2); +1]."))
    ;
}
