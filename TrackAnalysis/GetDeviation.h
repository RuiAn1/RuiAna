/**
 * \file GetDeviation.h
 *
 * \ingroup TrackAnalysis
 * 
 * \brief Class def header for a class GetDeviation
 *
 * @author Rui
 */

/** \addtogroup TrackAnalysis

    @{*/
#ifndef GETDEVIATION_H
#define GETDEVIATION_H

#include <iostream>
#include "TrackDeviation.h"

namespace larlite{
  /**
     \class GetDeviation
     User defined class GetDeviation ... these comments are used to generate
     doxygen documentation!
  */
  class GetDeviation{
    
  public:
    
    /// Default constructor
    GetDeviation(){}
    
    /// Default destructor
    ~GetDeviation(){}
    
    void getdist      (const ::geoalgo::Vector& pt_1 ,
		       const ::geoalgo::Vector& pt_2 );
    void getdeviation (const ::geoalgo::Trajectory& trj1 ,
		       const ::geoalgo::Trajectory& trj2 );
    // Getter functions
    double getmean(){return _mean;}
    double getstdev(){return _stdev;}
    double getdist_start(){return _dist_start;}
    
  protected:
    ::geoalgo::GeoAlgo _geoAlgo;
    double _mean;
    double _stdev;
    double _dist;
    double _dist_start;
  };
}
#endif
/** @} */ // end of doxygen group 

