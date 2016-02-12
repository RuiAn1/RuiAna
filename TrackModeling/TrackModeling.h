/**
 * \file TrackModeling.h
 *
 * \ingroup TrackModeling
 * 
 * \brief Class def header for a class TrackModeling
 *
 * @author Rui
 */

/** \addtogroup TrackModeling

    @{*/

#ifndef LARLITE_TRACKMODELING_H
#define LARLITE_TRACKMODELING_H

#include "Analysis/ana_base.h"
#include "GeoAlgo/GeoAlgo.h"
#include "LArUtil/Geometry.h"
#include "TTree.h"
#include "iostream"
#include "fstream"
#include <functional>
#include <algorithm>
#include <math.h>
#include <numeric>
#include "TH2.h"
#include "TrackAnalysis/GetDeviation.h"
#include "TrackAnalysis/TrackDeviation.h"
#include "TrackAnalysis/GetLength.h"

namespace larlite {
  /**
     \class TrackModeling
     User custom analysis class made by SHELL_USER_NAME
   */
  class TrackModeling : public ana_base{
  
  public:

    /// Default constructor
    TrackModeling();
      /*:_tree(nullptr)
    { _name="TrackModeling";
      _fout=0;
      }*/

    /// Default destructor
    virtual ~TrackModeling(){}

    /** IMPLEMENT in TrackModeling.cc!
        Initialization method to be called before the analysis event loop.
    */ 
    virtual bool initialize();
    
    /** IMPLEMENT in TrackModeling.cc! 
        Analyze a data event-by-event  
    */
    virtual bool analyze(storage_manager* storage);

    /** IMPLEMENT in TrackModeling.cc! 
        Finalize method to be called after all events processed.
    */
    virtual bool finalize();

    void configure(const std::string config_file);
    
    static TrackModeling* GetME() {
      if(!_me) _me = new TrackModeling;
      return _me;
    }
    
    
  protected:
    static TrackModeling* _me;
    
    ::geoalgo::GeoAlgo _geoAlgo;
    
    bool _configured;
    std::string _producer;

    TTree* _tree;
    int _n_evt;
    int _n_mctrack;
    int _n_recotrack;
    size_t _n_mctrk_size , _n_mctrk_size_tot;
    size_t _n_retrk_size , _n_retrk_size_tot;
    
    int _count;
    
    double _dist_start;
    double _dist_start_corr;
    double _dist_end_corr;
    double _devi_start;

    double _retrk_start_x;
    double _retrk_start_y;
    double _retrk_start_z;
    double _retrk_end_x;
    double _retrk_end_y;
    double _retrk_end_z;
    double _retrk_len_tot;

    double _mctrk_start_x;
    double _mctrk_start_y;
    double _mctrk_start_z;
    double _mctrk_end_x;
    double _mctrk_end_y;
    double _mctrk_end_z;
    double _mctrk_len_tot;
    double _t_mcstart;
    
    
    double _mean;
    double _w8devi;
    double _devi;
    double _devi_x;
    double _devi_y;
    double _devi_z;
    double _dist_start_x;
    double _dist_start_y;
    double _dist_start_z;
    
    double _mc_e;
    double _mc_e_dep;

    double _curvature;
    
    ::geoalgo::AABox _active_volume;
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
