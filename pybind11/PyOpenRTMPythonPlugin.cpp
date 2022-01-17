#include <cnoid/Body>
#include <cnoid/Link>
#include <cnoid/Light>
#include <pybind11/pybind11.h>

#if defined(_WINDOWS) && defined(HAVE_UNISTD_H)
#undef HAVE_UNISTD_H
#endif



namespace py = pybind11;

namespace rtmiddleware {
  void set_dq_target(cnoid::Link* lb, double dq_target)
  {
    lb->dq_target() = dq_target;
  }
  double get_dq_target(cnoid::Link* lb)
  {
    return lb->dq_target();
  }
  void set_q_target(cnoid::Link* lb, double dq_target)
  {
    lb->q_target() = dq_target;
  }
  double get_q_target(cnoid::Link* lb)
  {
    return lb->q_target();
  }
  void light_on(cnoid::Body* body, const char* name, bool onoff)
  {
     cnoid::Light* light = body->findDevice<cnoid::Light>(name);
     light->on(onoff);
     light->notifyStateChange();
  }
  void setJointSurfaceVelocity(cnoid::Link* lb)
  {
    lb->setActuationMode(cnoid::Link::JOINT_SURFACE_VELOCITY);
  }
}

PYBIND11_MODULE(OpenRTMPythonPlugin, m) {
  m.doc() = "OpenRTM-aist Python plugin for choreonoid";

  m.def("set_dq_target", &rtmiddleware::set_dq_target, "set target speed.");
  m.def("get_dq_target", &rtmiddleware::get_dq_target, "get target speed.");
  m.def("set_q_target", &rtmiddleware::set_q_target, "set target position.");
  m.def("get_q_target", &rtmiddleware::get_q_target, "get target position.");
  m.def("light_on", &rtmiddleware::light_on, "on light switch.");
  m.def("setJointSurfaceVelocity", &rtmiddleware::setJointSurfaceVelocity, "set JOINT_SURFACE_VELOCITY for Link Object.");
}