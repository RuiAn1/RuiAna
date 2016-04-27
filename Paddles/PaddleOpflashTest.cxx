#ifndef LARLITE_PADDLEOPFLASHTEST_CXX
#define LARLITE_PADDLEOPFLASHTEST_CXX

#include "PaddleOpflashTest.h"
#include "FhiclLite/ConfigManager.h"
#include "DataFormat/track.h"
#include "DataFormat/ophit.h"
#include "DataFormat/opflash.h"
#include "DataFormat/mctrack.h"
#include "DataFormat/calorimetry.h"
#include "DataFormat/simphotons.h"

namespace larlite {

  PaddleOpflashTest::PaddleOpflashTest()
    :ana_base()
  {_name="PaddleOpflashTest";_fout=0;_configured = false; _tree = nullptr;}
  

  void PaddleOpflashTest::configure (const std::string config_file){
    
    ::fcllite::ConfigManager cfg_mgr(_name);

    cfg_mgr.AddCfgFile(config_file);
    
    auto const& main_cfg = cfg_mgr.Config().get_pset(_name);
    
    _producername_opflash   =  main_cfg.get<std::string>("ProducerNameOpflash","opflashSat");
    _producername_ophit     =  main_cfg.get<std::string>("ProducerNameOphit","opflashSat");
    //_producername_recotrack =  main_cfg.get<std::string>("ProducerNameRecotrack","trackkalmanhit");
    
    _configured = true;
    
  }
  
  bool PaddleOpflashTest::initialize() {

    if(!_configured){
      print(msg::kERROR,__FUNCTION__,"Must be configured before running");
      return false;
    }
    if(_tree)delete _tree;
    _tree = new TTree("PaddleTree","PaddleTree");
    _tree -> Branch("n_mct",&_n_mct,"n_mct/I");
    _tree -> Branch("n_flash",&_n_flash,"n_flash/I");
    _tree -> Branch("sumofg4",&_sum_simpho,"sum_simpho/D");
    _tree -> Branch("sumofophit",&_sum_ophit,"sum_ophit/D");
    _tree -> Branch("sumofopflash",&_sum_opflash,"sum_opflash/D");
    _tree -> Branch("ophit_amplitude","std::vector<double>",&_ophit_amplitude);
    _tree -> Branch("ophit_pe","std::vector<double>",&_ophit_pe);
    _tree -> Branch("opflash_pe","std::vector<double>",&_opflash_pe);
    _tree -> Branch("t_ophit","std::vector<double>",&_t_ophit);
    _tree -> Branch("t_opflash","std::vector<double>",&_t_opflash);
    _tree -> Branch("g4_t","std::vector<double>",&_g4_t);
    _tree -> Branch("g4_endx","std::vector<double>",&_g4_end_x);
    _tree -> Branch("g4_endy","std::vector<double>",&_g4_end_y);
    _tree -> Branch("g4_endz","std::vector<double>",&_g4_end_z);
      
    return true;
  }
  
  bool PaddleOpflashTest::analyze(storage_manager* storage) {
    
    _sum_simpho  = 0;
    _sum_ophit   = 0;
    _sum_opflash = 0;
    
    auto const geo = ::larutil::Geometry::GetME();
    
    /*auto ev_mct    = storage->get_data<event_mctrack>("mcreco");
    if (!ev_mct) {
      std::cout<<"........Couldn't find mctrack data product in this event...... "<<std::endl;
      }*/

    /*auto ev_reco = storage->get_data<event_track>(_producername_recotrack);
    if(!ev_reco) {
      print(msg::kERROR,__FUNCTION__,"No matching data product found for specified track producer name!");
      throw DataFormatException("No data found");
      }*/    

    
    auto ev_opflash = storage->get_data<event_opflash>(_producername_opflash);
    if(!ev_opflash) {
      print(msg::kERROR,__FUNCTION__,"No matching data product found for specified opflash producer name!");
      throw DataFormatException("No data found");
    }
    
    auto ev_ophit = storage->get_data<event_ophit>(_producername_ophit);
    if(!ev_ophit) {
      print(msg::kERROR,__FUNCTION__,"No matching data product found for specified ophit producer name!");
      throw DataFormatException("No data found");
    }

    /*auto ev_simpho = storage->get_data<event_simphotons>("largeant");
    if (!ev_simpho){
      std::cout<<"........Couldn't find sim photon data product in this event...... "<<std::endl;
      }*/
    
    // g4 photons
    /*_g4_t.clear();
    _g4_end_x.clear();
    _g4_end_y.clear();
    _g4_end_z.clear();
    for(size_t i = 0; i < ev_simpho->size(); ++i){
      auto const& g4_pho = ev_simpho->at(i);
      if(!g4_pho.size()) continue;
      for (size_t j=0; j<g4_pho.size(); ++j){
	auto g4t = g4_pho.at(j).Time;
	auto lastlocal = g4_pho.at(j).FinalLocalPosition;
	auto statposi  = g4_pho.at(j).InitialPosition;
	//std::cout<<statposi.x();
	//std::cout<<lastlocal.x();
	_g4_t.push_back(g4t);
	_g4_end_x.push_back(statposi.x());
	_g4_end_y.push_back(statposi.y());
	_g4_end_z.push_back(statposi.z());
      }
      _sum_simpho += g4_pho.size();
    }
    // truth start time
    double t = 0;
    
    _n_mct = ev_mct->size();
    if(ev_mct->size()) {
      double t0 = 1000;
      for (size_t i =0 ; i<ev_mct->size(); ++i){
	auto const& mctrk = ev_mct->at(i);
	if(mctrk.size() == 0) continue;
	t = mctrk.front().T()/1000.;//Convert MC start time into us
	if (t<t0) t0 = t;
      }
      t = t0;
    }
    */
  // ophit
    _t_ophit.clear();
    _ophit_amplitude.clear();
    _ophit_pe.clear();
    _pe_ophit.clear();
    _pe_ophit.resize(32,0.0);
    
    for(size_t i = 0; i < ev_ophit->size(); i++)
      {
	auto const& ophit = ev_ophit->at(i);
	if (ophit.PE()<0) {  // ophit.PE() returns negative values now??
	  //continue;
	}
	  _t_ophit.push_back(ophit.PeakTime());
	  _ophit_amplitude.push_back(ophit.Amplitude());
	  _ophit_pe.push_back(ophit.PE());

	  //if(ophit.PeakTime()>=t &&ophit.PeakTime()<=t+15)
	  if(ophit.PeakTime()>=-1 &&ophit.PeakTime()<=-0.85)
	  {
	    
	    auto const pmt_id = geo->OpDetFromOpChannel(ophit.OpChannel());
	    _pe_ophit[pmt_id] += ophit.PE();
	    //_pe_ophit[pmt_id] += ophit.Amplitude()/10.;
	    
	  }
      }

    _sum_ophit = std::accumulate(_pe_ophit.begin(),_pe_ophit.end(),0.0);
    
    // opflash
    _t_opflash.clear();
    _opflash_amplitude.clear();
    _opflash_pe.clear();
    _n_flash = ev_opflash->size();
    
    for(size_t i = 0; i < ev_opflash->size(); i++)
      {
	auto const& opflash = ev_opflash->at(i);

	_t_opflash.push_back(opflash.Time());

	_opflash_pe.push_back(opflash.TotalPE());
	
	//if(opflash.Time()>=t &&opflash.Time()<=t+5)
	if(opflash.Time()>=-1 &&opflash.Time()<=-0.85)
	  {
	    _sum_opflash += opflash.TotalPE();
	  }
      }

    //
    _tree->Fill();
    
    return true;
  }
  
  bool PaddleOpflashTest::finalize() {

    if (_fout){
      _fout->cd();
      if(_tree) _tree->Write();
    }
    
    return true;
  }

}
#endif
