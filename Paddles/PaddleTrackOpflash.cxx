#ifndef LARLITE_PADDLETRACKOPFLASH_CXX
#define LARLITE_PADDLETRACKOPFLASH_CXX

#include "PaddleTrackOpflash.h"
#include "DataFormat/track.h"
#include "DataFormat/ophit.h"
#include "DataFormat/opflash.h"
#include "DataFormat/mctrack.h"
#include "DataFormat/calorimetry.h"
#include "DataFormat/simphotons.h"

double multi (double x) {return x*.23;}

namespace larlite {
  
  bool PaddleTrackOpflash::initialize() {
    
    if(!_v_pe_hist)
      _v_pe_hist =  new TH2F("PE","PE",100,-5,20,100,0,3000);
    
    if (_tree) {delete _tree;}
    _tree = new TTree("PaddleTree", "PaddleTree");
    
    _tree->Branch("run",&_run,"_run/I");
    _tree->Branch("subrun",&_subrun,"_subrun/I");
    _tree->Branch("event",&_event,"_event/I");
    _tree->Branch("trk_id",&_trk_id,"_trk_id/I");
    _tree->Branch("t_mcstart",&_t_mcstart,"_t_mcstart/D");
    _tree->Branch("n_mctrack",&_n_mctrack,"_n_mctrack/I");
    _tree->Branch("n_recotrack",&_n_recotrack,"_n_recotrack/I");
    _tree->Branch("mean",&_mean,"_mean/D");
    _tree->Branch("w8devi",&_w8devi,"_w8devi/D");
    _tree->Branch("devi",&_devi,"_devi/D");
    _tree->Branch("devi_x",&_devi_x,"_devi_x/D");
    _tree->Branch("devi_y",&_devi_y,"_devi_y/D");
    _tree->Branch("devi_z",&_devi_z,"_devi_z/D");
    _tree->Branch("dist_start",&_dist_start,"_dist_start/D");//w/o correction on reco track direction
    _tree->Branch("dist_start_corr",&_dist_start_corr,"_dist_start_corr/D");
    _tree->Branch("dist_end_corr",&_dist_end_corr,"_dist_end_corr/D");
    _tree->Branch("devi_start",&_devi_start,"_devi_start/D");
    _tree->Branch("dist_start_x",&_dist_start_x,"_dist_start_x/D");
    _tree->Branch("dist_start_y",&_dist_start_y,"_dist_start_y/D");
    _tree->Branch("dist_start_z",&_dist_start_z,"_dist_start_z/D");
    _tree->Branch("curvature",&_curvature,"_curvature/D");
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
    _tree->Branch("n_mctrk_size_tot",&_n_mctrk_size_tot,"_n_mctrk_size_tot/S");
    _tree->Branch("n_retrk_size_tot",&_n_retrk_size_tot,"_n_retrk_size_tot/S");
    /*_tree->Branch("n_QClusters_size",&_n_QClusters_size,"_n_QClusters_size/S");
    _tree->Branch("n_QClusters_size_size",&_n_QClusters_size_size,"_n_QClusters_size_size/S");
    */
    _tree->Branch("zenith",&_theta,"_theta/D");
    _tree->Branch("QRatio_pl",&_qratio_pl,"_qratio_pl/D"); 
    _tree->Branch("QRatio_re",&_qratio_re,"_qratio_re/D");
    _tree->Branch("pe_mchit_sum",&_pe_mchit_sum,"_pe_mchit_sum/D");
    _tree->Branch("pe_ophit_sum",&_pe_ophit_sum,"_pe_ophit_sum/D");
    _tree->Branch("mc_e",&_mc_e,"_mc_e/D");
    _tree->Branch("mc_e_dep",&_mc_e_dep,"_mc_e_dep/D");
    _tree->Branch("max_flash_pe",&_max_flash_pe,"_max_flash_pe/D");
    _tree->Branch("pe_g4pho_sum",&_pe_g4pho_sum,"_pe_g4pho_sum/D");
    
    _tree->Branch("t_opflash","std::vector<double>",&_t_opflash);
    _tree->Branch("t_ophit","std::vector<double>",&_t_ophit);
    _tree->Branch("t_ophit_wrt","std::vector<double>",&_t_ophit_wrt);//ophit time wrt mc start time
    _tree->Branch("ophit_pe","std::vector<double>",&_ophit_pe);
    _tree->Branch("ophit_amplitude","std::vector<double>",&_ophit_amplitude);
    _tree->Branch("pe_ophit","std::vector<double>",&_pe_ophit);
    _tree->Branch("pe_mchit","std::vector<double>",&_pe_mchit);

    _tree->Branch("n_intsec_mcj",&_n_intsec_mcj,"_n_intsec_mcj/B");

    _tree -> Branch("g4_t","std::vector<double>",&_g4_t);
    _tree -> Branch("g4_endx","std::vector<double>",&_g4_end_x);
    _tree -> Branch("g4_endy","std::vector<double>",&_g4_end_y);
    _tree -> Branch("g4_endz","std::vector<double>",&_g4_end_z);

    _tree -> Branch("_totalpe_opflash",&_totalpe_opflash,"totalpe_opflash/D");
    
    _length_xfiducial = larutil::Geometry::GetME()->DetHalfWidth();
    _length_yfiducial = larutil::Geometry::GetME()->DetHalfHeight();
    _length_zfiducial = larutil::Geometry::GetME()->DetLength();
    
    _vfiducial    = ::geoalgo::AABox(0, -_length_yfiducial, 0,
				  2 * _length_xfiducial, _length_yfiducial,_length_zfiducial);
    _vphotonlib   = ::geoalgo::AABox(-62.2517,-190.427,-125.628,318.602,190.427,1162.63);
    _vmucs_top    = ::geoalgo::AABox(-71.795, 393.941, 531.45, -23.795, 398.451, 579.45);
    //_vmucs_top = ::geoalgo::AABox(-271.795, 393.941, 331.45, 223.795, 398.451, 779.45);
    _vmucs_bottom = ::geoalgo::AABox(-19.6948, 316.041, 533.25, 28.3052, 320.551, 581.25);
    
    _track_positions.open ("TrackPositions.txt");
    
    _n_evt        = 0;
    _n_evt_paddle = 0;
    _n_evt_mc     = 0;
    _count        = 0;
    return true;
  }
  
  bool PaddleTrackOpflash::analyze(storage_manager* storage) {
    
    auto const geo = ::larutil::Geometry::GetME();
    _n_evt++;
    
    _pe_ophit.clear();
    _pe_mchit.clear();
    _pe_ophit.resize(32,0.0);
    _pe_mchit.resize(32,0.0);
    _t_opflash.clear();
    _t_ophit.clear();
    _t_ophit_wrt.clear();
    _ophit_pe.clear();
    _ophit_amplitude.clear();
    _retrj.clear();
    _mctrj.clear();
    _pe_mchit_sum  = 0;
    _pe_ophit_sum  = 0;
    _n_mctrk_size_tot = 0;
    _n_retrk_size_tot = 0;
    _mc_e_dep      = 0;
    _pe_g4pho_sum  = 0;
    _totalpe_opflash = 0;
    
    std::fill(_pe_ophit.begin(), _pe_ophit.end(), 0);

    /////////////////////////////////////////////////////
    ///////////////////Use Real Data/////////////////////
    /////////////////////////////////////////////////////
    
    if(_useData){
      auto ev_reco = storage->get_data<event_track>("trackkalmanhit");
      //auto ev_reco = storage->get_data<event_track>("stitchkalmanhit");
      if (!ev_reco) {
	std::cout<<"........Couldn't find reco track data product in this event...... "<<std::endl;
      }
      
      //auto ev_ophit = storage->get_data<event_ophit>("opFlash");
      auto ev_ophit = storage->get_data<event_ophit>("OpHitFinder");
      if (!ev_ophit) {
	std::cout<<"........Couldn't find ophit data product in this event...... "<<std::endl;
      }
      
      /*
	auto ev_opflash = storage->get_data<event_opflash>("opFlash");
	if (!ev_opflash) {
	std::cout<<"........Couldn't find opflash data product in this event...... "<<std::endl;
	}
      */

      _n_recotrack = ev_reco->size();
      /*
      for(size_t opf = 0; opf < ev_opflash->size(); opf++){
	auto const& opflash = ev_opflash->at(opf);
	_t_opflash.push_back(opflash.Time());

	}*/
      
      for(size_t oph = 0; oph < ev_ophit->size(); oph++){
	auto const& ophit = ev_ophit->at(oph);
	_t_ophit.push_back(ophit.PeakTime());
	_ophit_pe.push_back(ophit.PE());
	if(ophit.PeakTime()>-1 &&ophit.PeakTime()<-0.85){
	  auto const pmt_id = geo->OpDetFromOpChannel(ophit.OpChannel());
	  _pe_ophit[pmt_id] += ophit.PE();
	}
      }
      
      for(size_t i = 0; i <ev_reco->size(); i++ ){
	
	//0)Construct trajectory from track or mctrack
	auto const& trk = ev_reco->at(i);
	
	if(trk.NumberTrajectoryPoints() > 1){
	  
	  ::geoalgo::Trajectory trj;
	  
	  for (size_t pt = 0; pt < trk.NumberTrajectoryPoints(); pt++) {
	    
	    auto const& pos = trk.LocationAtPoint(pt);
	    
	    trj.push_back(::geoalgo::Vector(pos[0], pos[1], pos[2]));
	    
	  }
	  //1)Calculate intersections with MuCS to 0th select events
	  ::geoalgo::HalfLine trj_prj(trj[0], trj[0]-trj[trj.size()/2]);
	  ::geoalgo::HalfLine trj_prj_neg(trj[trj.size()-1], trj[trj.size()-1]-trj[trj.size()/2]);
	  
	  auto const&  intersection_trj_prj_top    = _geoAlgo.Intersection(_vmucs_top,trj_prj);
	  auto const&  intersection_trj_prj_bottom = _geoAlgo.Intersection(_vmucs_bottom,trj_prj);
	  
	  //auto const&  intersection_trj_prj_top_neg    = _geoAlgo.Intersection(_vmucs_top,trj_prj_neg);
	  //auto const&  intersection_trj_prj_bottom_neg = _geoAlgo.Intersection(_vmucs_bottom,trj_prj_neg);
	  
	  auto const&  intersection_trj_prj_fv        = _geoAlgo.Intersection(_vfiducial,trj_prj);
	  auto const&  intersection_trj_prj_fv_neg    = _geoAlgo.Intersection(_vfiducial,trj_prj_neg);
	  //auto const&  intersection_trj_fv            = _geoAlgo.Intersection(_vfiducial,trj);
	  
	  if(intersection_trj_prj_top.size()>0 && intersection_trj_prj_bottom.size()>0){//2)This strict requirement basically excludes all simulated data
	    
	    //_n_evt_paddle++;
	    
	    //3)Calculate zenith angle
	    std::vector<double> pt1,pt2,pt3,delta_p12,delta_p13,delta_p23;//1,2 for intersections on mucs_top/bottom, 3 for 1 project to mucs_bottom 
	    pt1.resize(3,0.0);
	    pt2.resize(3,0.0);
	    pt3.resize(3,0.0);
	    delta_p12.resize(3,0.0);
	    delta_p13.resize(3,0.0);
	    delta_p23.resize(3,0.0);
	    pt1 = intersection_trj_prj_top[0];
	    pt2 = intersection_trj_prj_bottom[0];
	    pt3 = {intersection_trj_prj_top[0].at(0),intersection_trj_prj_bottom[0].at(1),intersection_trj_prj_top[0].at(2)};
	    
	    for (size_t i = 0; i<3 ; i++){
	      delta_p12.push_back(pt1.at(i)-pt2.at(i));
	      delta_p13.push_back(pt1.at(i)-pt3.at(i));
	      delta_p23.push_back(pt2.at(i)-pt3.at(i));
	    }
	    double length_12 = sqrt(std::inner_product(begin(delta_p12), end(delta_p12), begin(delta_p12), 0.0));
	    double length_13 = sqrt(std::inner_product(begin(delta_p13), end(delta_p13), begin(delta_p13), 0.0));
	    double length_23 = sqrt(std::inner_product(begin(delta_p23), end(delta_p23), begin(delta_p23), 0.0));
	    
	    double cos_theta = (pow(length_12,2)+pow(length_13,2)-pow(length_23,2))/(2.*length_12*length_13); 
	    
	    if(length_12*length_13>0)_theta = acos (cos_theta) * 180.0 / M_PI;
	    
	    _MuCS_ints_x_top = intersection_trj_prj_top.at(0).at(0);
	    _MuCS_ints_z_top = intersection_trj_prj_top.at(0).at(2);
	    _MuCS_ints_x_bottom =  intersection_trj_prj_bottom.at(0).at(0);
	    _MuCS_ints_z_bottom =  intersection_trj_prj_bottom.at(0).at(2);
	    
	    _run    = storage->get_data<event_track>("trackkalmanhit")->run();
	    _subrun = storage->get_data<event_track>("trackkalmanhit")->subrun();
	    _event  = storage->get_data<event_track>("trackkalmanhit")->event_id();
	    _trk_id = trk.ID();
	  
	    //Save positions into txt file
	    _track_positions<<"Run: "<<_run<<" , Subrun: "<<_subrun<<" , Event: "<<_event<<" , Track_ID: "<<_trk_id<<std::endl; 
	    //_track_positions<<trj.front()<<std::endl;
	    //_track_positions<<trj.back()<<std::endl;
	    
	    //
	    //5)Implement PhotonVisibility from OpT0Finder now
	    //
	    
	    tpc_obj = LP.FlashHypothesis(trj);
	    
	    /* for(size_t i=0;i<tpc_obj.size();i++){
	      std::cout<<"wtf?"<<tpc_obj.at(i).q<<std::endl;
	      }*/
	    flash_obj.pe_v.resize(32,0.0);
	    PL.FillEstimate(tpc_obj,flash_obj);
	    _pe_mchit =  flash_obj.pe_v;
	    for(size_t i = 0; i<32;i++)std::cout<<flash_obj.pe_v.at(i);
	    
	    // Normalize
	    
	    std::transform(_pe_mchit.begin(), _pe_mchit.end(), _pe_mchit.begin(), multi);
	    	    
	    _pe_mchit_sum = std::accumulate(std::begin(_pe_mchit),std::end(_pe_mchit),0.0);
	    _pe_ophit_sum = std::accumulate(std::begin(_pe_ophit),std::end(_pe_ophit),0.0);
	    
	    //6)Get Q ratio
	    
	    std::vector<double> pe_ophit;
	    std::vector<double> pe_mchit;
	    pe_ophit.resize(32,0.0);
	    pe_mchit.resize(32,0.0);
	    pe_ophit = _pe_ophit;
	    pe_mchit = _pe_mchit;
	    std::sort(pe_ophit.begin(),pe_ophit.end());
	    std::sort(pe_mchit.begin(),pe_mchit.end());
	    double QRatio_pl = pe_mchit.at(31)/_pe_mchit_sum;//photon library
	    double QRatio_re = pe_ophit.at(31)/_pe_ophit_sum;//ophit
	    
	    _qratio_pl = QRatio_pl;
	    _qratio_re = QRatio_re;
	    
	    
	    //7)further select events
	    
	    
	    double length = trj.Length();
	    _length_trj_prj_fv = 0;
	    _length_trj_prj_fv_neg = 0;
	    
	    if(length>150){//1ST, track length larger than 50cm
	      std::vector<double> pt1,pt2,delta_p12;
	      pt1.resize(3,0.0);
	      pt2.resize(3,0.0);
	      delta_p12.resize(3,0.0);
	      if(intersection_trj_prj_fv.size()>0){//2ND, sum of gaps btw start/end of track and fv smaller than
		pt1 = intersection_trj_prj_fv[0];
		for(size_t i = 0; i<3 ; i++){
		  pt2[i] = trj.at(0).at(i);
		  delta_p12.push_back(pt1.at(i)-pt2.at(i));
		}
		_length_trj_prj_fv = sqrt(std::inner_product(begin(delta_p12), end(delta_p12), begin(delta_p12), 0.0));
	      }
	      pt1.resize(3,0.0);
	      pt2.resize(3,0.0);
	      delta_p12.resize(3,0.0);
	      if(intersection_trj_prj_fv_neg.size()>0){
		pt1 = intersection_trj_prj_fv_neg[0];
		for(size_t i = 0; i<3 ; i++){
		  pt2[i] = trj.at(trj.size()-1).at(i);
		  delta_p12.push_back(pt1.at(i)-pt2.at(i));
		}
		_length_trj_prj_fv_neg = sqrt(std::inner_product(begin(delta_p12), end(delta_p12), begin(delta_p12), 0.0));
	      }
	      if(_length_trj_prj_fv+_length_trj_prj_fv_neg<100){
		_n_evt_paddle++;
		//std::cout<<_run<<" "<<_subrun<<" "<<_event<<std::endl;
		_tree->Fill();
	      }
	    }
	  }
	    //_tree->Fill();
	}///Loop of Paddle Run data
      }
    }
  
    /////////////////////////////////////////////////////
    /////////////Use Simulation Data/////////////////////
    /////////////////////////////////////////////////////
    
    if(_useSimulation){

      auto ev_reco = storage->get_data<event_track>("trackkalmanhit");
      //auto ev_reco = storage->get_data<event_track>("trackkalmanhitcc");
      //auto ev_reco = storage->get_data<event_track>("stitchkalmanhit");
      //auto ev_reco = storage->get_data<event_track>("stitchkalmanhitcc");
      //auto ev_reco = storage->get_data<event_track>("pandoraCosmicKHit");
      //auto ev_reco = storage->get_data<event_track>("pandoraNuKHit");
      if (!ev_reco) {
	std::cout<<"........Couldn't find reco track data product in this event...... "<<std::endl;
      }
      
      auto ev_mct    = storage->get_data<event_mctrack>("mcreco");
      if (!ev_mct) {
	std::cout<<"........Couldn't find mctrack data product in this event...... "<<std::endl;
      }
      
      auto ev_mcs    = storage->get_data<event_mcshower>("mcreco");
      if (!ev_mcs) {
	std::cout<<"........Couldn't find mcshower data product in this event...... "<<std::endl;
      }
      
      auto ev_ophit = storage->get_data<event_ophit>("opflashSat");
      if (!ev_ophit) {
	std::cout<<"........Couldn't find ophit data product in this event...... "<<std::endl;
      }

      auto ev_opflash = storage->get_data<event_opflash>("opflashSat");
      if (!ev_ophit) {
	std::cout<<"........Couldn't find opflash data product in this event...... "<<std::endl;
      }      
      
      auto ev_simpho = storage->get_data<event_simphotons>("largeant");
      if (!ev_simpho){
	std::cout<<"........Couldn't find sim photon data product in this event...... "<<std::endl;
      }

      _n_mctrack   = ev_mct->size();
      _n_recotrack = ev_reco->size();

      //reco ophit
      double t = 0 ;
      if (ev_mct->size()){
	auto const& mctrk = ev_mct->at(0);
	t = mctrk.front().T()/1000.;//Convert MC start time into us
      }
      _t_mcstart = t;
      _max_flash_pe = 0.;

      //wocao
      
      for(size_t opf = 0; opf <ev_opflash->size();++opf){
	auto const& opflash = ev_opflash->at(opf);
	_totalpe_opflash += opflash.TotalPE();
	if (_max_flash_pe < opflash.TotalPE()) _max_flash_pe = opflash.TotalPE();
      }
      
      for(size_t oph = 0; oph < ev_ophit->size(); ++oph)
	{
	  auto const& ophit = ev_ophit->at(oph);

	  _t_ophit.push_back(ophit.PeakTime());
	  _t_ophit_wrt.push_back(ophit.PeakTime()-t);
	
	  _ophit_amplitude.push_back(ophit.Amplitude());
	  
	  _ophit_pe.push_back(ophit.PE());
	
	  if(ophit.PeakTime()>=t &&ophit.PeakTime()<=t+5)
	    {
	      _v_pe_hist->Fill(ophit.PeakTime()-t,ophit.PE());
	      
	      auto const pmt_id = geo->OpDetFromOpChannel(ophit.OpChannel());
	      
	      _pe_ophit[pmt_id] += ophit.PE();
	      
	    }
	}
      
      //g4 Photons

      _g4_t.clear();
      _g4_end_x.clear();
      _g4_end_y.clear();
      _g4_end_z.clear();
      
      for(size_t i = 0; i< ev_simpho->size(); i++)
	//ev_simpho is a vector of 32 doubles corrsponding to PE#s on 32 PMT
	{
	  auto const& g4_pho = ev_simpho->at(i);
	  _pe_g4pho_sum  = _pe_g4pho_sum +g4_pho.size();
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
	  
	}
      
      
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
	  _mc_e          = ev_mct->at(0).front().E()-105.7;
	  _mctrk_start_x = mctrk.front().X();//front() and begin() here have same values
	  _mctrk_start_y = mctrk.front().Y();
	  _mctrk_start_z = mctrk.front().Z();
	  _mctrk_end_x   = mctrk.back().X();
	  _mctrk_end_y   = mctrk.back().Y();
	  _mctrk_end_z   = mctrk.back().Z();//.back() returns the last element
	                                    //.end()  returns the iterator
	                                    //(not an element) past-the-end of the vector

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
	    
	    if(_vfiducial.Contain(pos)>0)retrj.push_back(::geoalgo::Vector(pos[0], pos[1], pos[2]));
	    
	  }
	  
	  _retrj.push_back(retrj);
	  
	  if (_retrj[i].size()>0){
	  
	  _n_retrk_size_tot = _n_retrk_size_tot + _retrj[i].size();

	  
	  }
	}
      }

      //Analysis on energy deposition
      
      //std::cout<<"trj size: "<<_retrj.size()<<std::endl;
      //std::cout<<"mcj  size: "<<_mctrj.size()<<std::endl;
      //auto const& intersec_trj_vfidu = _geoAlgo.Intersection(_vfiducial,_retrj[0]);
      _n_intsec_mcj = 0;

      for(int i = 0; i<_mctrj.size();++i){
	auto const& intersec_mcj_vfidu = _geoAlgo.Intersection(_vfiducial,_mctrj[i]);
	//std::cout<<"intsec trj size: "<<intersec_trj_vfidu.size()<<std::endl;
	//std::cout<<"intsec mc  size: "<<intersec_mcj_vfidu.size()<<std::endl;
	if(intersec_mcj_vfidu.size()==1) _n_intsec_mcj++;
      }

      //Get Deviation
      
      /*if (_retrj.size()==1&&_mctrj.size()==1&&_retrj[0].size()>1&&_mctrj[0].size()>1){

	::larlite::GetDeviation GD;
	GD.getdeviation(_retrj,_mctrj);
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
	
	::larlite::GetLength GL;
	_mctrk_len_tot = GL.CalculateLength(_mctrj);
	_retrk_len_tot = GL.CalculateLength(_retrj);
	_retrk_start_x = GL.GetStartPoint(_retrj,_mctrj)[0];
	_retrk_start_y = GL.GetStartPoint(_retrj,_mctrj)[1];
	_retrk_start_z = GL.GetStartPoint(_retrj,_mctrj)[2];
	_retrk_end_x   = GL.GetEndPoint(_retrj,_mctrj)[0];
	_retrk_end_y   = GL.GetEndPoint(_retrj,_mctrj)[1];
	_retrk_end_z   = GL.GetEndPoint(_retrj,_mctrj)[2];
	_dist_start_corr = _mctrj[0].front().Dist(GL.GetStartPoint(_retrj,_mctrj));
	_dist_end_corr   = _mctrj[0].back().Dist(GL.GetEndPoint(_retrj,_mctrj));
	
	//7 cm curvature
	if(_retrk_end_x != _retrj[0][0][0]){//right direction
	  double lenth_last_pt_trace_back = 0;
	  size_t ith = _retrj[0].size()-1;
	  while(lenth_last_pt_trace_back < 7&& ith > 1){
	    lenth_last_pt_trace_back += _retrj[0][ith].Dist(_retrj[0][ith-1]);
	    --ith;
	  }
	  double staright_length_r = _retrj[0][_retrj[0].size()-1].Dist(_retrj[0][ith+1]);
	  _curvature = staright_length_r / lenth_last_pt_trace_back;
	  bool in_tpc = _vfiducial.Contain(_retrj[0].back());
	  if (in_tpc){
	    ++_count;
	    _tree->Fill();}
	}

	if(_retrk_end_x == _retrj[0][0][0]){//wrong direction
	  double lenth_last_pt_trace_back = 0;
	  size_t ith = 0;
	  while(lenth_last_pt_trace_back < 7 && ith < _retrj[0].size()-1){
	    lenth_last_pt_trace_back += _retrj[0][ith].Dist(_retrj[0][ith+1]);
	    ++ith;
	  }
	  double staright_length_r = _retrj[0][0].Dist(_retrj[0][ith-1]);
	  _curvature = staright_length_r / lenth_last_pt_trace_back;
	  bool in_tpc = _vfiducial.Contain(_retrj[0].front());
	  if (in_tpc){
	    ++_count;
	    //_tree->Fill();
	  }
	}
      }*/

      //MCQCluster
      if(_useMCQCluster){
	
	MCQ.UseXshift(true);
	MCQ.Construct(*ev_mct,*ev_mcs);
	
	_n_QClusters_size = MCQ.QClusters().size();
	
	if ( MCQ.QClusters().size()>0){
	  
	  _n_QClusters_size_size = MCQ.QClusters().at(0).size();
	  
	  for(size_t i = 0; i<MCQ.QClusters().size();i++){
	    
	    ::geoalgo::Trajectory trji;
	    	    
	    for (size_t pt = 0; pt<MCQ.QCluster(i).size();pt++){

	      trji.push_back(::geoalgo::Vector(MCQ.QCluster(i).at(pt).x, MCQ.QCluster(i).at(pt).y, MCQ.QCluster(i).at(pt).z));
	      
	    }//x,y,z here are mid points on segment in mc track

	    if(_mc_e/2.3-_mctrk_len_tot>20){
	      //LP.TrackEnd(true);
	      //LP.PL_extension(true);
	    }

	    tpc_obj_mc = LP.FlashHypothesis(trji);
	    //tpc_obj_mc = MCQ.QCluster(i);
	    
	    flash_obj.pe_v.resize(32,0.0);
	    PL.FillEstimate(tpc_obj_mc,flash_obj);
	    std::transform(_pe_mchit.begin(), _pe_mchit.end(),flash_obj.pe_v.begin(), _pe_mchit.begin(),
			   std::plus<double>());
	  }
	}
      }
      //QCluster
      if(_useQCluster){
	
	for(size_t i = 0; i <_retrj.size(); ++i ){

	  if(_retrj[i].size()>1){
	    tpc_obj = LP.FlashHypothesis(_retrj[i]);
	    
	    flash_obj.pe_v.resize(32,0.0);
	    PL.FillEstimate(tpc_obj,flash_obj);
	    
	    std::transform(_pe_mchit.begin(), _pe_mchit.end(),flash_obj.pe_v.begin(), _pe_mchit.begin(),
			 std::plus<double>());
	  }
	}
      }
      
      /////Conclusion
      _pe_mchit_sum = std::accumulate(std::begin(_pe_mchit),std::end(_pe_mchit),0.0);
      _pe_ophit_sum = std::accumulate(std::begin(_pe_ophit),std::end(_pe_ophit),0.0);

      _tree->Fill();
    }
    return true;
  }
  
  bool PaddleTrackOpflash::finalize() {
    
    /*std::cout<<_pe_ophit.size()<<std::endl;
      for(size_t i=0; i< _pe_ophit.size(); i++){
      double bincontent = _pe_ophit.at(i);
      std::cout<<_pe_ophit.at(i)<<std::endl;
      _pe_dis_hist->SetBinContent(i+1,bincontent);
      }*/
    
    _track_positions.close();
    
    if(_useData){
      if(_fout){
	_fout->cd();
	if(_tree) _tree->Write();
	std::cout<<"\n"<<_n_evt_paddle<<" MuCS-through-going muons found in "<<_n_evt<<" events"<<std::endl;
      }
    }
    
    if(_useSimulation){
      if(_fout){
        _fout->cd();
        if(_tree) _tree->Write();
	std::cout<<"\n"<<_count<<" events found to be contained in Fiducial Volume of TPC of total evts "<<_n_evt<<std::endl;
	
	_v_pe_hist->Write();
	
      }
    }
    
    return true;
  }

}
#endif
