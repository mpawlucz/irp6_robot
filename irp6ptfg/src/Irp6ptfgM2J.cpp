#include <rtt/Component.hpp>

#include "Irp6ptfgM2J.h"
#include "Irp6ptfgTransmission.h"

Irp6ptfgM2J::Irp6ptfgM2J(const std::string& name)
    : RTT::TaskContext(name, PreOperational) {
  this->ports()->addPort("MotorPosition", port_motor_position_);
  this->ports()->addPort("JointPosition", port_joint_position_);

  dir_a_7 = -0.00000000283130;
  dir_b_7 = 0.00001451910074;
  dir_c_7 = 0.074;
}

Irp6ptfgM2J::~Irp6ptfgM2J() {
}

bool Irp6ptfgM2J::configureHook() {
  motor_position_.resize(1);
  joint_position_.resize(1);
  return true;
}

void Irp6ptfgM2J::updateHook() {
  port_motor_position_.read(motor_position_);
  mp2i(&motor_position_(0), &joint_position_(0));
  port_joint_position_.write(joint_position_);
}

void Irp6ptfgM2J::mp2i(const double* motors, double* joints) {
  joints[0] = dir_a_7 * (motors[0] * motors[0]) - dir_b_7 * motors[0] + dir_c_7;
}

ORO_CREATE_COMPONENT(Irp6ptfgM2J)

