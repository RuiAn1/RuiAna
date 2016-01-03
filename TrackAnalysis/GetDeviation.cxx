#ifndef GETDEVIATION_CXX
#define GETDEVIATION_CXX

#include "GetDeviation.h"

namespace larlite{
  void GetDeviation::getdist(const ::geoalgo::Vector& pt_1 ,
			     const ::geoalgo::Vector& pt_2 )
  {
    _dist = pt_1.Dist(pt_2);
  }
  
  void GetDeviation::getdeviation ( const ::geoalgo::Trajectory& trj1 , 
				    const ::geoalgo::Trajectory& trj2 )
  {
    /*std::cout<<"caonima\n";
    std::cout<<"retrj"<<trj1.size()<<std::endl;
    std::cout<<"mctrj"<<trj2.size()<<std::endl;
    */

    auto const& pt1 = trj1[0];
    auto const& pt2 = trj2[0];
    GetDeviation::getdist(pt1,pt2);
    if (_dist > 10){
      auto const& pt3 = trj1[trj1.size()-1];
      GetDeviation::getdist(pt3,pt2);
    }
    _dist_start = _dist;
    
    if (_dist >2&&_dist<10){
      std::cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
      std::cout<<_dist<<std::endl;
      std::cout<<trj1[0]<<std::endl;
      std::cout<<trj1[1]<<std::endl;
      std::cout<<trj2[trj2.size()-1]<<std::endl;
      std::cout<<trj2[trj2.size()-1]<<std::endl;
    }
    std::vector<double> lens;
    lens.clear();

    double shit1 = 0;
    double shit2 = 0;
    for (size_t i=0; i<trj2.size()-1 ; ++i){
      auto const& pt1 = trj2[i];
      auto const& pt2 = trj2[i+1];
      GetDeviation::getdist(pt1,pt2);
      shit2 += _dist;
    }
    for (size_t i=0; i<trj1.size()-1 ; ++i){
      auto const& pt1 = trj1[i];
      auto const& pt2 = trj1[i+1];
      GetDeviation::getdist(pt1,pt2);
      shit1 += _dist;
      
      auto const& line1 = ::geoalgo::LineSegment(trj1[i],trj1[i+1]);
      auto const& len = _geoAlgo.SqDist(line1, trj2);
      //if(_dist>10) std::cout<<len<<std::endl;
      //auto const& pt = trj1[i];
      //auto const& len = _geoAlgo.SqDist(pt,trj2);
      lens.push_back(len);
      //std::cout<<len<<std::endl;
      
    }

    double sq_sum = std::inner_product(lens.begin(), lens.end(), lens.begin(), 0.0);
    
    _mean = std::accumulate(std::begin(lens),std::end(lens),0.0)/lens.size();
    /*
    std::vector<double> diff(lens.size());
    std::transform(lens.begin(), lens.end(), diff.begin(),
		   //std::bind2nd(std::minus<double>(), _mean));
		   std::bind2nd(std::minus<double>(), 0.0));
    double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
    */

    _stdev = std::sqrt(sq_sum / lens.size());
    
    //std::cout<<stdev<<std::endl;
    
  }
}


#endif
