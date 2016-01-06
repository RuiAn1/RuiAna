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
      /*if (_dist > 10){
	auto const& pt3 = trjvec1[trjvec1.size()-1][trjvec1[trjvec1.size()-1].size()-1];
	GetDeviation::getdist(pt3,pt2);
	}*/
      _dist_start = _dist;
      
      std::vector<double> devis;
      std::vector<double> weights;
      std::vector<double> weighted_devis;
      devis.clear();
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
	GetDeviation::getdist(pt1,pt2);
	_len_tot += _dist;
	weights.push_back(_dist);
	auto const& line1 = ::geoalgo::LineSegment(pt1, pt2);
	auto const& devi = _geoAlgo.SqDist(line1, trjvec2);
	//auto const& devi = _geoAlgo.SqDist(pt1, trjvec2);
	/*
	std::cout<<"@@@@@@@@@@@@@@@\n";
	std::cout<<"devi= "<< devi<<std::endl;
	std::cout<<"pt1 in linesegment is :"<<pt1<<"\n pt2 in linesegment is :"<<pt2<<std::endl;
	for(int p = 0; p < trjvec2[0].size();++p){
	  std::cout<<trjvec2[0][p]<<std::endl;
	}
	std::cout<<"@@@@@@@@@@@@@@@\n";
	*/	
	//auto const& pt = trj1[i];
	//auto const& devi = _geoAlgo.SqDist(pt,trj2);
	if (i == 0 ) _devi_start = devi;
	devis.push_back(devi);
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
      weighted_sum = std::accumulate(std::begin(weighted_devis),std::end(weighted_devis),0.0);
      _w8devi = weighted_sum / _len_tot;
      
      //std::cout<<stdev<<std::endl;
    }
  }
}


#endif
