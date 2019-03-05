#ifndef GETLENGTH_CXX
#define GETLENGTH_CXX

#include "GetLength.h"

namespace larlite{

  double GetLength::CalculateLength (const std::vector<::geoalgo::Trajectory>& trjvec){

    _length_xfiducial = larutil::Geometry::GetME()->DetHalfWidth();
    _length_yfiducial = larutil::Geometry::GetME()->DetHalfHeight();
    _length_zfiducial = larutil::Geometry::GetME()->DetLength();

    _active_volume    = ::geoalgo::AABox(0, -_length_yfiducial, 0,
					 2 * _length_xfiducial, _length_yfiducial,_length_zfiducial);
    
    _length = 0;

    
    for (size_t i=0;i<trjvec.size();++i){
      
      for (size_t j=0;j<(trjvec[i].size()-1);++j){
	auto const& pt1 = trjvec[i][j];
	auto const& pt2 = trjvec[i][j+1];
	//std::cout<<pt2<<std::endl;
	//std::cout<<_active_volume.Contain(pt2);
	if(!_active_volume.Contain(pt2)) {
	  ::geoalgo::LineSegment cross_line(pt1,pt2);
	  auto const& pt_cross = _geoAlgo.Intersection(_active_volume,cross_line);
	  double dist_wal_2_last_pt_on_mc_track_in_tpc = pt1.Dist(pt_cross[0]);
	  _length+=dist_wal_2_last_pt_on_mc_track_in_tpc ;
	  continue;
	}
	double dist_tmp = pt1.Dist(pt2);
	_length+=dist_tmp;
      }
    }
    return _length;
  }
  
  ::geoalgo::Point_t GetLength::GetStartPoint (const std::vector<::geoalgo::Trajectory>& trjvec1 ,
					       const std::vector<::geoalgo::Trajectory>& trjvec2 ){
    
    if (trjvec1.size()!=trjvec2.size()) printf("Dimensions of two input vectors are not equal");
    double dist_start_start;
    double dist_start_end;
    dist_start_start = trjvec1[0][0].Dist(trjvec2[0][0]);
    dist_start_end   = trjvec1[0][0].Dist(trjvec2[0][trjvec2[0].size()-1]);
    if(dist_start_start<dist_start_end) _start_pt = trjvec1[0][0];
    if(dist_start_end<dist_start_start) _start_pt = trjvec1[0][trjvec1[0].size()-1];
    return _start_pt;
  }


  ::geoalgo::Point_t GetLength::GetEndPoint (const std::vector<::geoalgo::Trajectory>& trjvec1 ,
					     const std::vector<::geoalgo::Trajectory>& trjvec2 ){
    
    if (trjvec1.size()!=trjvec2.size()) printf("Dimensions of two input vectors are not equal");
    double dist_end_start;
    double dist_end_end;
    dist_end_start = trjvec1[0][trjvec1[0].size()-1].Dist(trjvec2[0][0]);
    dist_end_end   = trjvec1[0][trjvec1[0].size()-1].Dist(trjvec2[0][trjvec2[0].size()-1]);
    if(dist_end_end<dist_end_start) _end_pt = trjvec1[0][trjvec1[0].size()-1];
    if(dist_end_start<dist_end_end) _end_pt = trjvec1[0][0];
    
    return _end_pt;
  }
  
  
  
  std::vector<double> GetLength::CalculateLengthFraction (std::vector<::geoalgo::Trajectory>& trjvec){
    _length_frac.clear();
    //_length_frac.resize(trjvec.size(),0.0);
    //_length_frac[0] = 0.0;
    //_length_frac.push_back(0.0);
    _length = GetLength::CalculateLength(trjvec);
    double length_at_this_pt = 0;
    
    ::geoalgo::Trajectory tmp_trj;
    tmp_trj.clear();
    if (_if_flip){
      for(int i = trjvec[0].size()-1 ; i>-1 ; --i){
	tmp_trj.push_back(trjvec[0][i]);
      }
      trjvec.clear();
      trjvec.push_back(tmp_trj);
    }
        
    for (size_t i = 0 ; i < trjvec.size() ; ++i ){
      
      if(trjvec[i].size() == 1) continue;
      for (size_t pt = 1 ; pt<trjvec[i].size() ; ++pt){
	
	length_at_this_pt += trjvec[i][pt].Dist(trjvec[i][pt-1]);
	
	_length_frac.push_back(length_at_this_pt /_length); 
	
      }
    }
    return _length_frac;
  }
  
  
}
#endif
