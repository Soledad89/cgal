// Copyright (c) 2005, 2006 Fernando Luis Cacciola Carballal. All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL$
// $Id$
//
// Author(s)     : Fernando Cacciola <fernando_cacciola@ciudad.com.ar>
//
#ifndef CGAL_SURFACE_MESH_SIMPLIFICATION_POLICIES_EDGE_COLLAPSE_LINDSTROMTURK_SET_FULL_COLLAPSE_DATA_H
#define CGAL_SURFACE_MESH_SIMPLIFICATION_POLICIES_EDGE_COLLAPSE_LINDSTROMTURK_SET_FULL_COLLAPSE_DATA_H 1

#include <CGAL/Surface_mesh_simplification/Detail/ECMS_common.h>
#include <CGAL/Surface_mesh_simplification/Policies/Edge_collapse/Full_collapse_data.h>
#include <CGAL/Surface_mesh_simplification/Policies/Edge_collapse/LindstromTurk_params.h>
#include <CGAL/Surface_mesh_simplification/Policies/Edge_collapse/Detail/Lindstrom_Turk_core.h>


CGAL_BEGIN_NAMESPACE

namespace Surface_mesh_simplification
{

template<class ECM_>    
class LindstromTurk_set_cost_and_placement_cache
{
public:

  typedef ECM_ ECM ;

  typedef LindstromTurk_params Params ;
  
  typedef typename boost::graph_traits<ECM>::vertex_descriptor vertex_descriptor ;
  typedef typename boost::graph_traits<ECM>::edge_descriptor   edge_descriptor ;
  
  typedef typename halfedge_graph_traits<ECM>::Point Point_3 ;
  typedef typename Kernel_traits<Point_3>::Kernel     Kernel ;
  typedef typename Kernel::FT                         FT ;
  
  typedef Cost_and_placement_cache<ECM> Cache ;
  
  typedef optional<FT>      Optional_cost_type ;
  typedef optional<Point_3> Optional_placement_type ;
  
  typedef LindstromTurk_params CostParams      ;
  typedef LindstromTurk_params PlacementParams ;

public :

  LindstromTurk_set_cost_and_placement_cache() {}
  
  void operator() ( Cache&                 rCache
                  , edge_descriptor const& aEdge
                  , ECM&                   aSurface
                  , CostParams const*      aCostParams 
                  , PlacementParams const* aPlacementParams 
                  ) const 
  {
    CGAL_assertion(aCostParams);
    CGAL_assertion(aPlacementParams);
    CGAL_assertion(aCostParams == aPlacementParams);
    CGAL_assertion( handle_assigned(aEdge) );
    
    LindstromTurkCore<ECM> core(*aCostParams,aEdge,aSurface,true);

    Optional_cost_type lCost ;
    Optional_placement_type lPlacement ;
    tie(lCost,lPlacement) = core.compute();
    rCache = Cache(lCost,lPlacement);
  }                         
  
};    

} // namespace Surface_mesh_simplification

CGAL_END_NAMESPACE

#endif // CGAL_SURFACE_MESH_SIMPLIFICATION_POLICIES_EDGE_COLLAPSE_LINDSTROMTURK_SET_FULL_COLLAPSE_DATA_H //
// EOF //
 
