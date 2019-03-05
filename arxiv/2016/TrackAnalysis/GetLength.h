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
    
    std::vector<double> CalculateLengthFraction (std::vector<::geoalgo::Trajectory>& trjvec);
    
    ::geoalgo::Point_t GetStartPoint (const std::vector<::geoalgo::Trajectory>& trjvec1 ,
				      const std::vector<::geoalgo::Trajectory>& trjvec2 );
    
    ::geoalgo::Point_t GetEndPoint (const std::vector<::geoalgo::Trajectory>& trjvec1 ,
				    const std::vector<::geoalgo::Trajectory>& trjvec2 );
    ///Setter function
    bool set_if_flip(bool if_){_if_flip = if_; return _if_flip;}

    
    
  protected:
    ::geoalgo::GeoAlgo _geoAlgo;

    bool _if_flip = false;
    
    double _length;
    ::geoalgo::Point_t _start_pt;
    ::geoalgo::Point_t _end_pt;
    ::geoalgo::AABox _active_volume;
    double _length_xfiducial;
    double _length_yfiducial;
    double _length_zfiducial; 
    std::vector<double> _length_frac;
    
  };
}
#endif
/** @} */ // end of doxygen group 

