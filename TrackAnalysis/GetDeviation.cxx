#ifndef GETDEVIATION_CXX
#define GETDEVIATION_CXX

#include "GetDeviation.h"

namespace larlite{
  double GetDeviation::getdist(const ::geoalgo::Vector& pt_1 ,
			     const ::geoalgo::Vector& pt_2 )
  {
    _dist = pt_1.Dist(pt_2);
    return _dist;
  }
  
  void GetDeviation::getdeviation ( const std::vector<::geoalgo::Trajectory>& trjvec1 , 
				    const std::vector<::geoalgo::Trajectory>& trjvec2 )
  {
    for (size_t n = 0 ; n<trjvec1.size() ; n++){

      auto const& pt1 = trjvec1[0][0];
      auto const& pt2 = trjvec2[0][0];
      GetDeviation::getdist(pt1,pt2);
      /*
	if the start points distance is larger than 10 cm, 
	possibly the track is reconstructed in the wrong direction
	one could try to flip the track then
      */
      /*
	if (_dist > 10){
      auto const& pt3 = trjvec1[trjvec1.size()-1][trjvec1[trjvec1.size()-1].size()-1];
      GetDeviation::getdist(pt3,pt2);
      }
      */
      _dist_start = _dist;
      _dist_start_xyz.clear();
      _dist_start_xyz.push_back(pt1[0]-pt2[0]);
      _dist_start_xyz.push_back(pt1[1]-pt2[1]);
      _dist_start_xyz.push_back(pt1[2]-pt2[2]);
      
      std::vector<double> devis;
      std::vector<double> devis_x;
      std::vector<double> devis_y;
      std::vector<double> devis_z;
      std::vector<double> weights;
      std::vector<double> weighted_devis;
      devis.clear();
      devis_x.clear();
      devis_y.clear();
      devis_z.clear();
      weights.clear();
      weighted_devis.clear();
      /*double shit2 = 0;
       for (size_t i=0; i<trj2.size()-1 ; ++i){
	auto const& pt1 = trj2[i];
	auto const& pt2 = trj2[i+1];
	GetDeviation::getdist(pt1,pt2);
	shit2 += _dist;
	}
      */

      // Compare devi from trj1 to trj2, so collect devis and weights from trj1
      for (size_t i=0; i<trjvec1[n].size()-1 ; ++i){
	auto const& pt1 = trjvec1[n][i];
	auto const& pt2 = trjvec1[n][i+1];
	GetDeviation::getdist(pt1,pt2);//calculate _dist btw pt1 and pt2
	_len_tot += _dist;
	weights.push_back(_dist);
	auto const& line1 = ::geoalgo::LineSegment(pt1, pt2);
	int track_id;
	::geoalgo::Point_t pt3 , pt4;
	auto const& devi = sqrt(_geoAlgo.SqDist(line1, trjvec2, pt3, pt4,track_id));
	/*
	std::cout<<"@@@@@@@@begin@@@@@@@\n"; 
	std::cout<<"pt3 is "<<i<<"th point on recotrk\n";
	std::cout<<"closest distance is "<<devi<<std::endl;
	std::cout<<"dist btw pt3&pt4 is "<<pt3.Dist(pt4)<<std::endl;
	std::cout<<"pt3 is              "<<pt3<<std::endl;
	std::cout<<"pt4 is              "<<pt4<<std::endl;
	std::cout<<"@@@@@@@@enddd@@@@@@@\n"; 
	*/	
	//auto const& pt = trj1[i];
	//auto const& devi = _geoAlgo.SqDist(pt,trj2);
	if (i == 0 ) _devi_start = devi;
	devis.push_back(devi);
	devis_x.push_back(_dist*(pt3[0]-pt4[0]));
	devis_y.push_back(_dist*(pt3[1]-pt4[1]));
	devis_z.push_back(_dist*(pt3[2]-pt4[2]));
	weighted_devis.push_back(_dist*devi);
      }
      /*std::cout<<"########################\n";
	std::cout<<devis.size()<<std::endl;
	std::cout<<weights.size()<<std::endl;
	std::cout<<weighted_devis.size()<<std::endl;
	
	double sq_sum = std::inner_product(devis.begin(), devis.end(), devis.begin(), 0.0);
	_mean = std::accumulate(std::begin(devis),std::end(devis),0.0)/devis.size();
	
	std::vector<double> diff(devis.size());
	std::transform(devis.begin(), devis.end(), diff.begin(),
	//std::bind2nd(std::minus<double>(), _mean));
	std::bind2nd(std::minus<double>(), 0.0));
	double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
      */
      
      double weighted_sum = 0;
      double devi_sum = 0;
      devi_sum = std::accumulate(std::begin(devis),std::end(devis),0.0);
      _devi =  devi_sum / devis.size();

      devi_sum = std::accumulate(std::begin(devis_x),std::end(devis_x),0.0);
      //_devi_x =  devi_sum / devis_x.size();
      _devi_x =  devi_sum / _len_tot;
      
      devi_sum = std::accumulate(std::begin(devis_y),std::end(devis_y),0.0);
      //_devi_y =  devi_sum / devis_y.size();
      _devi_y =  devi_sum / _len_tot;
      
      devi_sum = std::accumulate(std::begin(devis_z),std::end(devis_z),0.0);
      //_devi_z =  devi_sum / devis_z.size();
      _devi_z =  devi_sum / _len_tot;

      weighted_sum = std::accumulate(std::begin(weighted_devis),std::end(weighted_devis),0.0);
      _w8devi = weighted_sum / _len_tot;
      
      //std::cout<<stdev<<std::endl;
    }
  }
}


#endif
