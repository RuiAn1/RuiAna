#ifndef LARLITE_TRACKMODELING_CXX
#define LARLITE_TRACKMODELING_CXX

#include "TrackModeling.h"
#include "FhiclLite/ConfigManager.h"

namespace larlite {

  TrackModeling* TrackModeling::_me = nullptr;
  
  //=====Constructor
  TrackModeling::TrackModeling()
    :ana_base()
    ,_active_volume(0,0,0,0,0,0)
  { _name="TrackModeling"; _fout=0; _configured=false; _tree = nullptr;}
  
  //=====Configure
  void TrackModeling::configure(const std::string config_file) {

    ::fcllite::ConfigManager cfg_mgr(_name);

    cfg_mgr.AddCfgFile(config_file);

    auto const& main_cfg = cfg_mgr.Config().get_pset(_name);

    std::vector<double> tpc_box = main_cfg.get<std::vector<double> >("TPC_Active_Volume");
    if(tpc_box.size()!=6) {
      print(msg::kERROR,__FUNCTION__,"TPC AV needs length 6 floating point...");
      throw std::exception();
    }

    _active_volume.Min(tpc_box[0],tpc_box[1],tpc_box[2]);
    _active_volume.Max(tpc_box[3],tpc_box[4],tpc_box[5]);

    _producer = main_cfg.get<std::string>("Producer","trackkalmanhit");

    _allow_flip = main_cfg.get<bool>("AllowFlip","false");
    
    _use_abs_devi = main_cfg.get<bool>("UseAbsDevi","false");
    
    _configured =true;
  }
  //=====Initialize
  bool TrackModeling::initialize() {

    //
    // This function is called in the beggining of event loop
    // Do all variable initialization you wish to do here.
    // If you have a histogram to fill in the event loop, for example,
    // here is a good place to create one on the heap (i.e. "new TH1D"). 
    //

    if(!_configured) {
      print(msg::kERROR,__FUNCTION__,"Must be configured before running!");
      return false;
    }

    if (_tree) {delete _tree;}
    _tree = new TTree("TrackTree", "TrackTree");

    _tree->Branch("mc_e",&_mc_e,"_mc_e/D");
    _tree->Branch("mc_e_dep",&_mc_e_dep,"_mc_e_dep/D");
    _tree->Branch("n_mctrack",&_n_mctrack,"_n_mctrack/I");
    _tree->Branch("n_recotrack",&_n_recotrack,"_n_recotrack/I");
    _tree->Branch("mean",&_mean,"_mean/D");
    _tree->Branch("w8devi",&_w8devi,"_w8devi/D");
    _tree->Branch("devi",&_devi,"_devi/D");
    _tree->Branch("devi_x",&_devi_x,"_devi_x/D");
    _tree->Branch("devi_y",&_devi_y,"_devi_y/D");
    _tree->Branch("devi_z",&_devi_z,"_devi_z/D");
    _tree->Branch("devi_start",&_devi_start,"_devi_start/D");
    
    _tree->Branch("dist_start",&_dist_start,"_dist_start/D");
    _tree->Branch("dist_start_corr",&_dist_start_corr,"_dist_start_corr/D");
    _tree->Branch("dist_end_corr",&_dist_end_corr,"_dist_end_corr/D");
    
    _tree->Branch("dist_start_x",&_dist_start_x,"_dist_start_x/D");
    _tree->Branch("dist_start_y",&_dist_start_y,"_dist_start_y/D");
    _tree->Branch("dist_start_z",&_dist_start_z,"_dist_start_z/D");

    _tree->Branch("curvature",&_curvature,"_curvature/D");

    _tree->Branch("n_mctrk_size_tot",&_n_mctrk_size_tot,"_n_mctrk_size_tot/S");
    _tree->Branch("n_retrk_size_tot",&_n_retrk_size_tot,"_n_retrk_size_tot/S");
    
    _tree->Branch("retrk_start_x",&_retrk_start_x,"_retrk_start_x/D");
    _tree->Branch("retrk_start_y",&_retrk_start_y,"_retrk_start_y/D");
    _tree->Branch("retrk_start_z",&_retrk_start_z,"_retrk_start_z/D");
    _tree->Branch("retrk_end_x",&_retrk_end_x,"_retrk_end_x/D");
    _tree->Branch("retrk_end_y",&_retrk_end_y,"_retrk_end_y/D");
    _tree->Branch("retrk_end_z",&_retrk_end_z,"_retrk_end_z/D");

    _tree->Branch("mctrk_start_x",&_mctrk_start_x,"_mctrk_start_x/D");
    _tree->Branch("mctrk_start_y",&_mctrk_start_y,"_mctrk_start_y/D");
    _tree->Branch("mctrk_start_z",&_mctrk_start_z,"_mctrk_start_z/D");
    _tree->Branch("mctrk_end_x",&_mctrk_end_x,"_mctrk_end_x/D");
    _tree->Branch("mctrk_end_y",&_mctrk_end_y,"_mctrk_end_y/D");
    _tree->Branch("mctrk_end_z",&_mctrk_end_z,"_mctrk_end_z/D");

    _tree->Branch("retrk_len_tot",&_retrk_len_tot,"_retrk_len_tot/D");
    _tree->Branch("mctrk_len_tot",&_mctrk_len_tot,"_mctrk_len_tot/D");

    _tree->Branch("length_frac","std::vector<double>",&_length_frac);
    _tree->Branch("devi_x_array","std::vector<double>",&_devi_x_array);
    _tree->Branch("devi_y_array","std::vector<double>",&_devi_y_array);
    _tree->Branch("devi_z_array","std::vector<double>",&_devi_z_array);
    
    _count = 0;
    _n_evt = 0;
    
    return true;
  }
  //=====Analyze
  bool TrackModeling::analyze(storage_manager* storage) {
  
    //
    // Do your event-by-event analysis here. This function is called for 
    // each event in the loop. You have "storage" pointer which contains 
    // event-wise data. To see what is available, check the "Manual.pdf":
    //
    // http://microboone-docdb.fnal.gov:8080/cgi-bin/ShowDocument?docid=3183
    // 
    // Or you can refer to Base/DataFormatConstants.hh for available data type
    // enum values. Here is one example of getting PMT waveform collection.
    //
    // event_fifo* my_pmtfifo_v = (event_fifo*)(storage->get_data(DATA::PMFIFO));
    //
    // if( event_fifo )
    //
    //   std::cout << "Event ID: " << my_pmtfifo_v->event_id() << std::endl;
    //
    ++_n_evt;
    _retrj.clear();
    _mctrj.clear();
    _length_frac.clear();
    _n_mctrk_size_tot = 0;
    _n_retrk_size_tot = 0;
    _mc_e_dep         = 0;
        
    auto ev_mct    = storage->get_data<event_mctrack>("mcreco");
    if (!ev_mct) {
      std::cout<<"........Couldn't find mctrack data product in this event...... "<<std::endl;
    }
    
    
    auto ev_reco = storage->get_data<event_track>(_producer);
    if(!ev_reco) {
      print(msg::kERROR,__FUNCTION__,"No matching data product found for specified track producer name!");
      throw DataFormatException("No data found");
    }

    _n_mctrack   = ev_mct->size();
    _n_recotrack = ev_reco->size();
    
    //Construt trajectory from MC track  
    for(size_t i = 0; i< ev_mct->size(); i++){

      auto const& mctrk = ev_mct->at(i);
      
      if (mctrk.size()>1){
	
	::geoalgo::Trajectory mctrj;
	
	for(size_t pt = 0; pt<mctrk.size() ; ++pt){

	  mctrj.push_back(::geoalgo::Vector(mctrk.at(pt).X(),
					    mctrk.at(pt).Y(),
					    mctrk.at(pt).Z()));
	  
	}

	_mctrj.push_back(mctrj);

	_mc_e_dep      = _mc_e_dep + mctrk.front().E()-mctrk.back().E();//Deposited energy
	_mc_e          = ev_mct->at(0).front().E()-105.7;               //MC Eng
	_mctrk_start_x = mctrk.front().X();                             //front() and begin() here have same values
	_mctrk_start_y = mctrk.front().Y();
	_mctrk_start_z = mctrk.front().Z();
	_mctrk_end_x   = mctrk.back().X();
	_mctrk_end_y   = mctrk.back().Y();
	_mctrk_end_z   = mctrk.back().Z();                              //front() and back() returns the first and last element
	                                                                //begin() and end()  returns the first and last iterator

	_n_mctrk_size_tot  = _n_mctrk_size_tot+mctrk.size();

      }
    }
    
    //Construct trajectory from reco track
    for(size_t i = 0; i <ev_reco->size(); i++ ){

      auto const& trk   = ev_reco->at(i);

      if(trk.NumberTrajectoryPoints() > 1){

	::geoalgo::Trajectory retrj;

	for (size_t pt = 0; pt < trk.NumberTrajectoryPoints(); pt++) {

	  auto const& pos = trk.LocationAtPoint(pt);

	  if(_active_volume.Contain(pos)>0)retrj.push_back(::geoalgo::Vector(pos[0], pos[1], pos[2]));

	}

	_retrj.push_back(retrj);

	if (_retrj[i].size()>0){

	  _n_retrk_size_tot = _n_retrk_size_tot + _retrj[i].size();

	}
      }
    }

    /////////////////////////
    ////Calculate_Deviation//
    /////////////////////////////////////////////////////////////////////
    ////Now only calculate events w/ only one reco track and one MC track
    ////Users should modifiy to work for other cases/////////////////////
    /////////////////////////////////////////////////////////////////////
    
    if (_retrj.size()==1&&_mctrj.size()==1 && _mctrj[0].size() > 0 && _retrj[0].size() > 0 ){
      ::larlite::GetDeviation GD;
      GD.getdeviation(_retrj,_mctrj);
      GD.setuse_abs_devi(_use_abs_devi);
      _if_flip    = GD.get_if_flip();
      _mean       = GD.getmean();
      _w8devi     = GD.getw8devi();
      _devi       = GD.getdevi();
      _dist_start = GD.getdist_start();//distance from MC start point to Reco start point, w/o direction correction
      _devi_start = GD.getdevi_start();
      _devi_x     = GD.getdevi_x();
      _devi_y     = GD.getdevi_y();
      _devi_z     = GD.getdevi_z();
      _dist_start_x = GD.getdist_start_xyz().at(0);
      _dist_start_y = GD.getdist_start_xyz().at(1);
      _dist_start_z = GD.getdist_start_xyz().at(2);
      _devi_x_array = GD.getdevi_x_array();
      _devi_y_array = GD.getdevi_y_array();
      _devi_z_array = GD.getdevi_z_array();
      
      ::larlite::GetLength GL;
      if (_allow_flip) GL.set_if_flip(_if_flip);
      _mctrk_len_tot   = GL.CalculateLength(_mctrj);
      _retrk_len_tot   = GL.CalculateLength(_retrj);
      _retrk_start_x   = GL.GetStartPoint(_retrj,_mctrj)[0];
      _retrk_start_y   = GL.GetStartPoint(_retrj,_mctrj)[1];
      _retrk_start_z   = GL.GetStartPoint(_retrj,_mctrj)[2];
      _retrk_end_x     = GL.GetEndPoint(_retrj,_mctrj)[0];
      _retrk_end_y     = GL.GetEndPoint(_retrj,_mctrj)[1];
      _retrk_end_z     = GL.GetEndPoint(_retrj,_mctrj)[2];
      _dist_start_corr = _mctrj[0].front().Dist(GL.GetStartPoint(_retrj,_mctrj));
      _dist_end_corr   = _mctrj[0].back().Dist(GL.GetEndPoint(_retrj,_mctrj));
      _length_frac     = GL.CalculateLengthFraction(_retrj);

      /*std::cout<<"============"
	       <<"size of _retrj[0] is    "<<_retrj[0].size()<<"\n"
	       <<"size of _length_frac is "<<_length_frac.size()<<"\n"
	       <<"size of devi_x_arrat is "<<_devi_x_array.size()<<"\n"
	       <<"size of devi_y_arrat is "<<_devi_y_array.size()<<"\n"
	       <<"size of devi_z_arrat is "<<_devi_z_array.size()<<"\n"<<std::endl;
      */
      //Curvature within 7cm near the track end
      if(_retrk_end_x != _retrj[0][0][0]&&_retrj[0].size()>2){//right direction
	double lenth_last_pt_trace_back = 0;
	size_t ith = _retrj[0].size()-1;
	while(lenth_last_pt_trace_back < 7&& ith > 1){
	  lenth_last_pt_trace_back += _retrj[0][ith].Dist(_retrj[0][ith-1]);
	  --ith;
	}
	double staright_length_r = _retrj[0][_retrj[0].size()-1].Dist(_retrj[0][ith+1]);
	_curvature = staright_length_r / lenth_last_pt_trace_back;
	bool in_tpc = _active_volume.Contain(_retrj[0].back());
	if (in_tpc){
	  ++_count;
	  _tree->Fill();
	}
      }

      if(_retrk_end_x == _retrj[0][0][0]&&_retrj[0].size()>1){//Flip the track if wrong direction
	double lenth_last_pt_trace_back = 0;
	size_t ith = 0;
	while(lenth_last_pt_trace_back < 7 && ith < _retrj[0].size()-1){
	  lenth_last_pt_trace_back += _retrj[0][ith].Dist(_retrj[0][ith+1]);
	  ++ith;
	}
	double staright_length_r = _retrj[0][0].Dist(_retrj[0][ith-1]);
	_curvature = staright_length_r / lenth_last_pt_trace_back;
	bool in_tpc = _active_volume.Contain(_retrj[0].front());
	if (in_tpc){
	  ++_count;
	  _tree->Fill();
	}
      }
    }
    
    return true;
  }
  //=====Finalize
  bool TrackModeling::finalize() {

    // This function is called at the end of event loop.
    // Do all variable finalization you wish to do here.
    // If you need, you can store your ROOT class instance in the output
    // file. You have an access to the output file through "_fout" pointer.
    //
    // Say you made a histogram pointer h1 to store. You can do this:
    //
    // if(_fout) { _fout->cd(); h1->Write(); }
    //
    // else 
    //   print(MSG::ERROR,__FUNCTION__,"Did not find an output file pointer!!! File not opened?");
    //

    if(_fout){
      _fout->cd();
      if(_tree) _tree->Write();
      printf("\n[%i]/[%i] events found to be contained in TPC Active Volume",_count,_n_evt);      
 
    }
    return true;   
  }
}
#endif
