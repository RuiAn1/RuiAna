/**
 * \file GetLength.h
 *
 * \ingroup TrackAnalysis
 * 
 * \brief Class def header for a class GetLength
 *
 * @author Rui
 */

/** \addtogroup TrackAnalysis

    @{*/
#ifndef GETLENGTH_H
#define GETLENGTH_H

#include <iostream>
#include "TrackDeviation.h"
#include "LArUtil/Geometry.h"

namespace larlite{
  /**
     \class GetLength
     User defined class GetLength ... these comments are used to generate
     doxygen documentation!
  */
  
  class GetLength{
    
  public:
  
    /// Default constructor
    GetLength(){}
    
    /// Default destructor
    ~GetLength(){}
    
    double CalculateLength (const std::vector<::geoalgo::Trajectory>& trjvec);
    
    ::geoalgo::Point_t GetStartPoint (const std::vector<::geoalgo::Trajectory>& trjvec1 ,
			   const std::vector<::geoalgo::Trajectory>& trjvec2 );

    ::geoalgo::Point_t GetEndPoint (const std::vector<::geoalgo::Trajectory>& trjvec1 ,
			 const std::vector<::geoalgo::Trajectory>& trjvec2 );
    
    
  protected:
    ::geoalgo::GeoAlgo _geoAlgo;
    
    double _length;
    ::geoalgo::Point_t _start_pt;
    ::geoalgo::Point_t _end_pt;
    ::geoalgo::AABox _active_volume;
    double _length_xfiducial;
    double _length_yfiducial;
    double _length_zfiducial; 

    
  };
}
#endif
/** @} */ // end of doxygen group 

