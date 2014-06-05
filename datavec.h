#ifndef DATAVEC_H
#define DATAVEC_H

/*This file includes the datastructure in which we retrive data stored in wave objects*/

#include <gnucap/globals.h>
#include <gnucap/constant.h>

using namespace std;
struct datavector{
       char* node_name;                   //Reterive from command given for plot
       std::vector<std::pair<double,double> > probe_data;  //Reterive data stored in this
       double _vmin;                        
       double _vmax;
       int v_length;
       int linestyle;
       int linecolor;
       int node_id;
       const char* v_legend;
};

typedef datavector DVEC;

class Vectordb{

public:
      Vectordb();
      virtual ~Vectordb();
      static DVEC CreatePvector(WAVE* _w,int node_num, 
                                                 const char* v_legend);
      double MetricToSci(double _value);
};

Vectordb::Vectordb(){
}

Vectordb::~Vectordb(){
}

DVEC Vectordb::CreatePvector(WAVE* _w,int node_num,
                                                 const char* v_legend){
     
     Vectordb b;
     DVEC data_vector;
     double _vmin=BIGBIG;
     double _vmax=-BIGBIG;
     data_vector.v_length=0;
     for (WAVE::const_iterator i=_w->begin();i!=_w->end();++i){
          data_vector.probe_data.push_back(DPAIR(b.MetricToSci(i->first),b.MetricToSci(i->second)));
          if(i->second>_vmax){
             _vmax=i->second;
          }
          if(i->second<_vmin){
             _vmin=i->second;
          } 
          data_vector.v_length++; 

     }
     data_vector.node_id=node_num;
     data_vector.v_legend=v_legend;
     data_vector._vmax=b.MetricToSci(_vmax);
     data_vector._vmin=b.MetricToSci(_vmin);
     return data_vector;
       
}

double Vectordb::MetricToSci(double _value){
 
     double _scivalue;         
     string point_value=static_cast<ostringstream*>(&(ostringstream()<<_value))->str();
     _scivalue=std::atof(point_value.c_str());
     return _scivalue;   
} 


#endif DATAVEC_H
