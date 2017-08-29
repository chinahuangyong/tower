/**
 @file    constraint_factory.h
 @author  Alexander W. Winkler (winklera@ethz.ch)
 @date    Jul 19, 2016
 @brief   Declares factory class to build constraints.
 */

#ifndef XPP_XPP_OPT_INCLUDE_XPP_OPT_COST_CONSTRAINT_FACTORY_H_
#define XPP_XPP_OPT_INCLUDE_XPP_OPT_COST_CONSTRAINT_FACTORY_H_

#include <memory>
#include <string>
#include <vector>

#include "cartesian_declarations.h"
#include "composite.h"
#include "dynamic_model.h"
#include "endeffectors.h"
#include "height_map.h"
#include "optimization_parameters.h"
#include "state.h"

namespace xpp {
namespace opt {


/** Builds all types of constraints/costs for the user.
  *
  * Implements the factory method, hiding object creation from the client.
  * The client specifies which object it wants, and this class is responsible
  * for the object creation. Factory method is like template method pattern
  * for object creation.
  */
class CostConstraintFactory {
public:
  using ComponentPtr     = std::shared_ptr<Component>;
  using OptVarsContainer = std::shared_ptr<Composite>;
  using MotionParamsPtr  = std::shared_ptr<OptimizationParameters>;
  using Derivatives      = std::vector<MotionDerivative>;

  CostConstraintFactory ();
  virtual ~CostConstraintFactory ();

  void Init(const OptVarsContainer&,
            const MotionParamsPtr&,
            const HeightMap::Ptr& terrain,
            const DynamicModel::Ptr& model,
            const EndeffectorsPos& ee_pos,
            const State3dEuler& initial_base,
            const State3dEuler& final_base);

  ComponentPtr GetCost(const CostName& id, double weight) const;
  ComponentPtr GetConstraint(ConstraintName name) const;

private:
  MotionParamsPtr params;
  OptVarsContainer opt_vars_;
  HeightMap::Ptr terrain_;
  DynamicModel::Ptr model_;


  EndeffectorsPos initial_ee_W_;
  State3dEuler initial_base_;
  State3dEuler final_base_;


  // constraints
  ComponentPtr MakeStateConstraint() const;
  ComponentPtr MakeDynamicConstraint() const;
  ComponentPtr MakeRangeOfMotionBoxConstraint() const;
  ComponentPtr MakeTotalTimeConstraint() const;
  ComponentPtr MakeTerrainConstraint() const;
  ComponentPtr MakeSwingConstraint() const;

  // costs
  ComponentPtr MakeForcesCost(double weight) const;
  ComponentPtr MakeMotionCost(double weight) const;
  ComponentPtr MakePolynomialCost(const std::string& poly_id,
                                   const Vector3d& weight_dimensions,
                                   double weight) const;

  ComponentPtr ToCost(const ComponentPtr& constraint, double weight) const;
};

} /* namespace opt */
} /* namespace xpp */

#endif /* XPP_XPP_OPT_INCLUDE_XPP_OPT_COST_CONSTRAINT_FACTORY_H_ */
