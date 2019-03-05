/**
 * \file PaddleOpflashTest.h
 *
 * \ingroup Paddles
 * 
 * \brief Class def header for a class PaddleOpflashTest
 *
 * @author Rui
 */

/** \addtogroup Paddles

    @{*/

#ifndef LARLITE_PADDLEOPFLASHTEST_H
#define LARLITE_PADDLEOPFLASHTEST_H

#include "Analysis/ana_base.h"
#include "TTree.h"
#include "OpT0Finder/Base/FlashMatchManager.h"
#include "OpT0Finder/Algorithms/LightPath.h"
#include "OpT0Finder/App/MCQCluster.h"
#include "OpT0Finder/PhotonLibrary/PhotonVisibilityService.h"
#include "OpT0Finder/Algorithms/PhotonLibHypothesis.h"
#include "LArUtil/Geometry.h"

namespace larlite {
  /**
     \class PaddleOpflashTest
     User custom analysis class made by SHELL_USER_NAME
   */
  class PaddleOpflashTest : public ana_base{
  
  public:

    /// Default constructor
    PaddleOpflashTest();

    /// Default destructor
    virtual ~PaddleOpflashTest(){}

    /** IMPLEMENT in PaddleOpflashTest.cc!
        Initialization method to be called before the analysis event loop.
    */ 

    void configure(const std::string config_file);
    
    virtual bool initialize();

    /** IMPLEMENT in PaddleOpflashTest.cc! 
        Analyze a data event-by-event  
    */
    virtual bool analyze(storage_manager* storage);

    /** IMPLEMENT in PaddleOpflashTest.cc! 
        Finalize method to be called after all events processed.
    */
    virtual bool finalize();

  protected:

    bool _configured;
    
    int _n_mct;
    int _n_flash;
    
    std::string _producername_opflash;
    std::string _producername_ophit;
    std::string _producername_recotrack;
    
    double _sum_simpho;
    double _sum_ophit;
    double _sum_opflash;

    std::vector<double> _t_ophit;
    std::vector<double> _ophit_amplitude;
    std::vector<double> _ophit_pe;
    std::vector<double> _t_opflash;
    std::vector<double> _opflash_amplitude;
    std::vector<double> _opflash_pe;
    std::vector<double> _pe_ophit;
    std::vector<double> _pe_mchit;
    
    std::vector<double> _g4_t;
    std::vector<double> _g4_end_x;
    std::vector<double> _g4_end_y;
    std::vector<double> _g4_end_z;
    
    TTree *_tree;
    
    ::flashana::FlashMatchManager _mgr;
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
