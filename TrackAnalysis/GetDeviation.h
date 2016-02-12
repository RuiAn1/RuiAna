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
    
    double getdist      (const ::geoalgo::Vector& pt_1 ,
			 const ::geoalgo::Vector& pt_2 );
    void getdeviation (const std::vector<::geoalgo::Trajectory>& trjvec1 ,
		       const std::vector<::geoalgo::Trajectory>& trjvec2 );
    // Getter functions
    double getmean()      {return _mean;}
    double getdevi()      {return _devi;}
    double getw8devi()    {return _w8devi;}
    double getdevi_x()    {return _devi_x;}
    double getdevi_y()    {return _devi_y;}
    double getdevi_z()    {return _devi_z;}
    double getdist_start(){return _dist_start;}
    double getdevi_start(){return _devi_start;}
    double getlen_tot()   {return _len_tot;}
    std::vector<double> getdist_start_xyz(){return _dist_start_xyz;}
    
  protected:
    ::geoalgo::GeoAlgo _geoAlgo;
    double _mean;
    double _devi;
    double _w8devi;
    double _dist;
    double _dist_start;
    double _devi_start;
    double _len_tot = 0;
    double _devi_x;
    double _devi_y;
    double _devi_z;
    std::vector<double> _dist_start_xyz;
    
  };
}
#endif
/** @} */ // end of doxygen group 

