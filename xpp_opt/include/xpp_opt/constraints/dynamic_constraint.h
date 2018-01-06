/**
 @file    dynamic_constraint.h
 @author  Alexander W. Winkler (winklera@ethz.ch)
 @date    Dec 5, 2016
 @brief   Brief description
 */

#ifndef XPP_XPP_OPT_SRC_DYNAMIC_CONSTRAINT_H_
#define XPP_XPP_OPT_SRC_DYNAMIC_CONSTRAINT_H_

#include <string>
#include <vector>

#include <ifopt/composite.h>

#include <xpp_states/cartesian_declarations.h>

#include <xpp_opt/models/dynamic_model.h>

#include <xpp_opt/variables/contact_schedule.h>
#include <xpp_opt/variables/node_values.h>
#include <xpp_opt/variables/spline.h>
#include <xpp_opt/variables/angular_state_converter.h>

#include "time_discretization_constraint.h"

namespace xpp {

class DynamicConstraint : public TimeDiscretizationConstraint {
public:
  using VecTimes = std::vector<double>;

  DynamicConstraint (const DynamicModel::Ptr& m,
                     const std::vector<double>& evaluation_times,
                     bool optimize_timings);
  virtual ~DynamicConstraint () = default;

  virtual void InitVariableDependedQuantities(const VariablesPtr& x) override;

private:
  Spline::Ptr base_linear_;
  Spline::Ptr base_angular_;
  std::vector<NodeValues::Ptr> ee_forces_;
  std::vector<NodeValues::Ptr> ee_motion_;
  std::vector<ContactSchedule::Ptr> ee_timings_;

  bool optimize_timings_;

  mutable DynamicModel::Ptr model_;
  double gravity_;
  AngularStateConverter converter_;

  int GetRow(int node, Coords6D dimension) const;

  virtual void UpdateConstraintAtInstance(double t, int k, VectorXd& g) const override;
  virtual void UpdateBoundsAtInstance(double t, int k, VecBound& bounds) const override;
  virtual void UpdateJacobianAtInstance(double t, int k, Jacobian&, std::string) const override;

  void UpdateModel(double t) const;
};

} /* namespace xpp */

#endif /* XPP_XPP_OPT_SRC_DYNAMIC_CONSTRAINT_H_ */
