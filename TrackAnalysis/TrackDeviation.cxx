#ifndef LARLITE_TRACKDEVIATION_CXX
#define LARLITE_TRACKDEVIATION_CXX

#include "TrackDeviation.h"

namespace larlite {
  
  void TrackDeviation::UseRealData (bool use)
  
  {
    if (use == true) _userealdata = true;
    else _usesimdata = true;
  }

  bool TrackDeviation::initialize() {
    
    if (_tree) delete _tree;
    _tree = new TTree("TrackAna","TrackAna");

    _tree->Branch("n_recotrack",&_n_recotrack,"_n_recotrack/I");
    _tree->Branch("n_mctrack",&_n_mctrack,"_n_mctrack/I");
    /*_tree->Branch("re_theta","std::vector<double>",&_re_theta);
    _tree->Branch("re_phi","std::vector<double>",&_re_phi);
    _tree->Branch("re_trk_start","std::vector<std::pair<int,std::vector<double>>>",&_retrk_start);
    */
    _tree->Branch("stdev",&_stdev,"_stdev/D");
    return true;
  }
  
  bool TrackDeviation::analyze(storage_manager* storage) {
    _retrj.clear();
    _mctrj.clear();
    _re_theta.clear();
    _re_phi.clear();
    _retrk_start.clear();
    _retrk_end.clear();
    //Use Real Data(to be done)
    if (_userealdata){}
    //Use Simulation Data
    if (_usesimdata) 
      {
	auto ev_ret = storage->get_data<event_track>("trackkalmanhit");
	if (!ev_ret) {
	  std::cout<<"........Couldn't find reco track data product in this event...... "<<std::endl;
	}
	auto ev_mct    = storage->get_data<event_mctrack>("mcreco");
	if (!ev_mct) {
	  std::cout<<"........Couldn't find mctrack data product in this event...... "<<std::endl;
	}
       
	_n_recotrack = ev_ret->size();
	_n_mctrack   = ev_mct->size();
	
	for (size_t i = 0; i < ev_ret->size(); ++i ){
	  
	  auto const& retrk = ev_ret->at(i);

	  if (retrk.NumberTrajectoryPoints()>1){
	    
	    ::geoalgo::Trajectory retrj;
	    std::pair<int,std::vector<double>> start,end;
	    start.second.resize(3,0.0);
	    end.second.resize(3,0.0);
	    start.first = i;
	    end.first   = i;

	    //std::cout<<"########"<<retrk.NumberTrajectoryPoints();
	    
	    for(size_t pt =0 ; pt < retrk.NumberTrajectoryPoints() ; ++pt){
	      
	      auto const& pos = retrk.LocationAtPoint(pt);

	      if(pt == 0){
		start.second[0] = pos[0];
		start.second[1] = pos[1];
		start.second[2] = pos[2];
	      }
	      if(pt == retrk.NumberTrajectoryPoints()-1){
		end.second[0] = pos[0];
		end.second[1] = pos[1];
		end.second[2] = pos[2];
	      }
	      
	      retrj.push_back(::geoalgo::Vector(pos[0],pos[1],pos[2]));
	      
	    }
	    _re_theta.push_back(std::make_pair(i,retrk.Theta()));
	    _re_phi.push_back(std::make_pair(i,retrk.Phi()));
	    _retrk_start.push_back(start);
	    _retrk_end.push_back(end);
	    _retrj.push_back(retrj);
	  }
	}

	for (size_t i = 0; i < ev_mct->size(); ++i ){

          auto const& mctrk = ev_mct->at(i);

	  if (mctrk.size()>1){

	    //std::cout<<"@@@@@@@@@"<<mctrk.size()<<std::endl;
	    ::geoalgo::Trajectory mctrj;
	    std::pair<int,std::vector<double>> start,end;
	    start.second.resize(3,0.0);
            end.second.resize(3,0.0);
            start.first = i;
            end.first   = i;
	    
	    for(size_t pt =0 ; pt < mctrk.size() ; ++pt){

              if(pt == 0){
                start.second[0] = mctrk.at(0).X();
		start.second[1] = mctrk.at(0).Y();
		start.second[2] = mctrk.at(0).Z();
		
	      }
              if(pt == mctrk.size()-1){
                end.second[0] = mctrk.at(mctrk.size()-1).X();
		end.second[1] = mctrk.at(mctrk.size()-1).Y();
		end.second[2] = mctrk.at(mctrk.size()-1).Z();
		}
	      
	      mctrj.push_back(::geoalgo::Vector(mctrk.at(pt).X(),
						mctrk.at(pt).Y(),
						mctrk.at(pt).Z()));
	    }
	    
	    _mc_px.push_back(std::make_pair(i,mctrk.at(0).Px()));
	    _mc_px.push_back(std::make_pair(i,mctrk.at(0).Py()));
	    _mc_px.push_back(std::make_pair(i,mctrk.at(0).Pz()));
	    _mctrk_start.push_back(start);
	    _mctrk_end.push_back(end);
            _mctrj.push_back(mctrj);
          }
	}
	
	if (_retrj.size()==1&&_mctrj.size()==1){
	  
	  GetDeviation GD;
	  GD.getdeviation(_retrj[0],_mctrj[0]);
	  //std::cout<<"lalalala\n"<<_stdev<<std::endl;
	}
	
	_tree->Fill();
      }
    
    return true;
  }

  bool TrackDeviation::finalize() {
    
    if(_tree) _tree->Write();
    
    return true;
  }

}
#endif
