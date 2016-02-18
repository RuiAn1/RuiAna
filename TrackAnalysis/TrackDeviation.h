/**
 * \file TrackDeviation.h
 *
 * \ingroup TrackAnalysis
 * 
 * \brief Class def header for a class TrackDeviation
 *
 * @author Rui
 */

/** \addtogroup TrackAnalysis

    @{*/

#ifndef LARLITE_TRACKDEVIATION_H
#define LARLITE_TRACKDEVIATION_H

#include "Analysis/ana_base.h"
#include "DataFormat/track.h"
#include "DataFormat/mctrack.h"
#include "GeoAlgo/GeoAlgo.h"
#include "LArUtil/Geometry.h"
#include "TTree.h"
#include "TH2.h"
#include "iostream"
#include "fstream"
#include <functional>
#include <algorithm>
#include <math.h>
#include <vector>
#include <numeric>
#include "GetDeviation.h"

namespace larlite {
  /**
     \class TrackDeviation
     User custom analysis class made by SHELL_USER_NAME
   */
  class TrackDeviation : public ana_base{
  
  public:

    /// Default constructor
    TrackDeviation()
      :_tree(nullptr)
      { _name="TrackDeviation";
	_fout=0;}

    /// Default destructor
    virtual ~TrackDeviation(){}

    /** IMPLEMENT in TrackDeviation.cc!
        Initialization method to be called before the analysis event loop.
    */ 
    virtual bool initialize();

    /** IMPLEMENT in TrackDeviation.cc! 
        Analyze a data event-by-event  
    */
    virtual bool analyze(storage_manager* storage);

    /** IMPLEMENT in TrackDeviation.cc! 
        Finalize method to be called after all events processed.
    */
    bool finalize();
    
    //setter function
    void UseRealData(bool use);
    
  protected:
    TTree* _tree;
    bool _usesimdata;
    bool _userealdata;
    
    int _n_recotrack;
    int _n_mctrack;
    
    double _mean;
    double _stdev;
    
    ::geoalgo::GeoAlgo _geoAlgo;
    
    std::vector<std::pair<int,std::vector<double>>> _retrk_start, _retrk_end;
    std::vector<std::pair<int,std::vector<double>>> _mctrk_start, _mctrk_end;
    
    std::vector<std::pair<int,double>> _retrk_len;
    std::vector<std::pair<int,double>> _mctrk_len;

    std::vector<std::pair<int,double>> _re_theta, _re_phi;
    std::vector<std::pair<int,double>> _mc_px,_mc_py,_mc_pz;

    std::vector<::geoalgo::Trajectory> _retrj;
    std::vector<::geoalgo::Trajectory> _mctrj;
    
  };
}
#endif

//**************************************************************************
// 
// For Analysis framework documentation, read Manual.pdf here:
//
// http://microboone-docdb.fnal.gov:8080/cgi-bin/ShowDocument?docid=3183
//
//**************************************************************************

/** @} */ // end of doxygen group 
