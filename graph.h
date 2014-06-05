#ifndef GRAPH_H
#define GRAPH_H

/*This file defines the graph structure*/
#include <datavec.h>

//include data vector file


struct graph{
     std::vector<DVEC> v_data;
     std::string graphname;
     int num_plots;
     double _xmin;
     double _xmax;
     double _ymin;
     double _ymax;
     DPAIR _ylim;
     DPAIR _xlim;
     int fontwidth, fontheight;
     char* x_label;
     char* y_label;
     //plot type need to be defined here
     //grid type need to be defined here
     
};

typedef graph GRAPH;

class Graphdb{

public:
      Graphdb();
      virtual ~Graphdb();
      static GRAPH* CreateGraph(std::vector<DVEC> data_vector,int number_plots);
};

Graphdb::Graphdb(){

}

Graphdb::~Graphdb(){
}

GRAPH* Graphdb::CreateGraph(std::vector<DVEC> data_vector,int number_plots){
      
      GRAPH *graph_data=new GRAPH;
      graph_data->num_plots=number_plots;
      graph_data->_ymax=-BIGBIG;
      graph_data->_ymin=BIGBIG;
      for(int num_plot=0;num_plot<graph_data->num_plots;++num_plot){
          graph_data->v_data.push_back(data_vector[num_plot]);
          if(graph_data->v_data[num_plot]._vmax>graph_data->_ymax){
             graph_data->_ymax=graph_data->v_data[num_plot]._vmax;
          }
          if(graph_data->v_data[num_plot]._vmin<graph_data->_ymin){
             graph_data->_ymin=graph_data->v_data[num_plot]._vmin;
          }
      }
      graph_data->_xmin=floor(graph_data->v_data[0].probe_data[0].first);
      graph_data->_xmax=graph_data->v_data[0].probe_data[graph_data->v_data[0].v_length-1].first;
      return graph_data;

}

#endif GRAPH_H
