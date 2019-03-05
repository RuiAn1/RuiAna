/**
 * \file PaddleTrackOpflash.h
 *
 * \ingroup Paddles
 * 
 * \brief Class def header for a class PaddleTrackOpflash
 *
 * @author Rui
 */

/** \addtogroup Paddles

    @{*/

#ifndef LARLITE_PADDLETRACKOPFLASH_H
#define LARLITE_PADDLETRACKOPFLASH_H

#include "Analysis/ana_base.h"
#include "GeoAlgo/GeoAlgo.h"
#include "LArUtil/Geometry.h"
#include "TTree.h"
#include "PaddleTrackAna.h"
#include "iostream"
#include "fstream"
#include <functional>
#include <algorithm>
#include <math.h>
#include "OpT0Finder/Base/FlashMatchManager.h"
#include "OpT0Finder/Algorithms/LightPath.h"
#include "OpT0Finder/App/MCQCluster.h"
#include "OpT0Finder/PhotonLibrary/PhotonVisibilityService.h"
#include "OpT0Finder/Algorithms/PhotonLibHypothesis.h"
#include <numeric>
#include "TH2.h"
#include "TrackAnalysis/GetDeviation.h"
#include "TrackAnalysis/TrackDeviation.h"
#include "TrackAnalysis/GetLength.h"

namespace larlite {
  /**
     \class PaddleTrackOpflash
     User custom analysis class made by SHELL_USER_NAME
   */
  class PaddleTrackOpflash : public ana_base{
  
  public:

    /// Default constructor
    /*PaddleTrackOpflash()
      :_tree(nullptr)
      { _name="PaddleTrackOpflash";
	_v_pe_hist = 0;
	_fout=0;
	}*/

    PaddleTrackOpflash();

    /// Default destructor
    virtual ~PaddleTrackOpflash(){}

    /** IMPLEMENT in PaddleTrackOpflash.cc!
        Initialization method to be called before the analysis event loop.
    */ 
    virtual bool initialize();

    /** IMPLEMENT in PaddleTrackOpflash.cc! 
        Analyze a data event-by-event  
    */
    virtual bool analyze(storage_manager* storage);

    /** IMPLEMENT in PaddleTrackOpflash.cc! 
        Finalize method to be called after all events processed.
    */
    virtual bool finalize();

    void configure(const std::string config_file);
    
    // getter function
    std::vector<::geoalgo::Trajectory> Getretrj()       {return _retrj;       }
    std::vector<::geoalgo::Trajectory> Getmctrj()       {return _mctrj;       }
    double                             Getw8devi()      {return _w8devi;      }
    double                             Getdevi()        {return _devi;        }
    double                             GetSum_g4()      {return _pe_g4pho_sum;}
    double                             GetSum_PL()      {return _pe_mchit_sum;}

    // set the LP object to be used
    void setLP(::flashana::LightPath lp) { LP = lp; } 
    
  protected:
    
    TTree* _tree;
    TH1F* _hRatioPLOP;
    TH2F* _hRatioMap;
    
    std::ofstream _track_positions;
    
    std::string _mc_producer;
    std::string _g4_producer;
    std::string _track_producer;
    std::string _ophit_producer;
    std::string _opflash_producer;
    
    bool _save_histos;
    bool _ifusedata;
    bool _ifuselightpath;
    bool _configured;
    
    size_t _n_ev_reco;
    
    int _run;
    int _subrun;
    int _event;
    int _trk_id;
    
    int _test=0;
    int _n_evt;
    int _n_evt_paddle;
    int _n_evt_mc;
    int _n_tracks;
    int _opchannel_id;
    int _n_intersections_FV;
    int _n_intersections_mucs_top;
    int _n_intersections_mucs_bottom;
    int _n_mctrack;
    int _n_recotrack;
    size_t _n_mctrk_size , _n_mctrk_size_tot;
    size_t _n_retrk_size , _n_retrk_size_tot;
    size_t _n_QClusters_size;
    size_t _n_QClusters_size_size;

    bool _n_intsec_mcj;
    
    double _retrk_start_x;
    double _retrk_start_y;
    double _retrk_start_z;
    double _retrk_end_x;
    double _retrk_end_y;
    double _retrk_end_z;
    double _retrk_len;
    double _retrk_len_tot;
    
    double _mctrk_start_x;
    double _mctrk_start_y;
    double _mctrk_start_z;
    double _mctrk_end_x;
    double _mctrk_end_y;
    double _mctrk_end_z;
    double _mctrk_len;
    double _mctrk_len_tot;
    double _t_mcstart;

    double _dist_start;
    double _dist_start_corr;
    double _dist_end_corr;
    double _devi_start;
    
    double _mean;
    double _w8devi;
    double _devi;
    double _devi_x;
    double _devi_y;
    double _devi_z;
    double _dist_start_x;
    double _dist_start_y;
    double _dist_start_z;
    
    std::vector<double> _t_opflash;
    std::vector<double> _t_ophit;
    std::vector<double> _t_ophit_wrt;
    std::vector<double> _ophit_amplitude;
    std::vector<double> _ophit_pe;
    std::vector<double> _pe_ophit;//sum of PE on each PMT
    std::vector<double> _pe_mchit;//sum of PE on each PMT
        
    //muon intersection w/ MuCS
    double _MuCS_ints_x_top;
    double _MuCS_ints_z_top;
    double _MuCS_ints_x_bottom;
    double _MuCS_ints_z_bottom;
    
    double _length_xfiducial;
    double _length_yfiducial;
    double _length_zfiducial;
    double _length_trj_prj_fv;
    double _length_trj_prj_fv_neg;
    
    double _theta;
    double _pe_mchit_sum;
    double _pe_ophit_sum;
    double _pe_g4pho_sum;
    double _qratio_pl;
    double _qratio_re;

    std::vector<double> _g4_t;
    std::vector<double> _g4_end_x;
    std::vector<double> _g4_end_y;
    std::vector<double> _g4_end_z;
    
    double _mc_e;
    double _mc_e_dep;

    double _max_flash_pe;
    
    double _curvature;
    double _totalpe_opflash;
    int _count;
    ::geoalgo::GeoAlgo _geoAlgo;
    ::geoalgo::AABox _vfiducial;
    ::geoalgo::AABox _vphotonlib;
    ::geoalgo::AABox _vmucs_top;
    ::geoalgo::AABox _vmucs_bottom;
    std::vector<::geoalgo::Trajectory> _retrj;
    std::vector<::geoalgo::Trajectory> _mctrj;
    //tracks contained in TPC
    std::vector<::geoalgo::Trajectory> _trj_con;
    //tracks pass MuCS
    std::vector<::geoalgo::Trajectory> _trj_mucs;
    std::vector<::geoalgo::HalfLine> _trj_prj;
    std::vector<::geoalgo::LineSegment> _prj_lineseg;

    std::vector<TVector3> _trj_filt;
    
    ::flashana::QCluster_t tpc_obj;
    ::flashana::LightPath LP;

    ::flashana::Flash_t flash_obj;
    ::flashana::PhotonLibHypothesis PL;

    ::flashana::QCluster_t tpc_obj_mc;
    ::flashana::MCQCluster MCQ;
    
    
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
