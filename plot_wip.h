/*This is the main library used for plotting graph on cairo surface
*needs lot amount of modification and is under development*/

#ifndef PLOT_WIP_H
#define PLOT_WIP_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream> 
#include <math.h>
#include <cairomm/context.h>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm.h>
#include <graph.h>


#define DEFAULT_LINE_WIDTH 0.001
#define X_ORIGIN 0.10
#define Y_ORIGIN 0.90
#define GRID_STEP_X 0.08
#define GRID_STEP_Y 0.1
#define X_AXIS_MAX 0.9
#define Y_AXIS_MAX 0.1
#define X_AXIS_MIN 0.1
#define Y_AXIS_MIN 0.9
#define DELTA 0.02
#define EPS 1e-7
#define RGB_0 {0.0, 0.0, 0.0} /* Black         */
#define RGB_1 {0.0, 0.0, 0.8} /* Nigth blue    */
#define RGB_2 {0.0, 0.9, 0.0} /* Frog green    */
#define RGB_3 {0.0, 0.6, 0.6} /* Dark Cyan     */
#define RGB_4 {0.6, 0.0, 0.5} /* Dark Violet   */
#define RGB_5 {1.0, 0.4, 0.0} /* Vermilion     */
#define RGB_6 {1.0, 0.0, 1.0}   /* Violet       */
#define RGB_7 {0.4, 0.9, 0.9}    /* Light blue   */
#define RGB_8 {0.8, 0.4, 0.8}    /* Lilla        */
#define RGB_9 {0.0, 0.75, 0.5}  /* Grass green  */
#define RGB_10 {1.0, 0.5, 0.0}   /* Orange       */
#define RGB_11 {0.7, 0.1, 0.1} /* Dark Red      */
#define RGB_12 {0.88, 0.79, 0.44} /* Cream        */
#define RGB_13 {1.0,1.0,1.0}     /*White         */

struct color{
             double r,g,b;
      };

typedef color RGB_COLOR;

enum cairo_color_2d{
        Black = 0,
        Dark_Red,
        Nigth_Blue,
        Frog_Green, 
        Dark_Cyan,  
        Dark_Violet,
        Vermilion,     
        Cream,      
        Light_Blue, 
        Lilla,
        Grass_Green, 
        Dark_Gray,   
        Black_Smoke,
        Nr_Colors_2d
      };
static const RGB_COLOR color_palette[Nr_Colors_2d] = {
                 RGB_0,  
                 RGB_1,
                 RGB_2,
                 RGB_3,
                 RGB_4,
                 RGB_5,
                 RGB_6,
                 RGB_7,
                 RGB_8,
                 RGB_9,
                 RGB_10,
                 RGB_11,
                 RGB_12
              };

using namespace std;

class PlotLib: public Gtk::DrawingArea{
protected:
      double _xcurrent;
      double _ycurrent;
      double _xdest;
      double _ydest;
      double _xorigin;
      double _yorigin;
      int object_id[10];
      int object_color_id[10];
      RGB_COLOR rgb_color;
public:
      PlotLib();
      virtual ~PlotLib();
      static GRAPH* graph;
      virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
      void DrawAxis(const Cairo::RefPtr<Cairo::Context>& cr,double _xorigin,double _yorigin);
      void SetBackground(const Cairo::RefPtr<Cairo::Context>& cr);
      void DrawGrid(const Cairo::RefPtr<Cairo::Context>& cr,double _xlowerlim,double _xupperlim,double
                                        _ylowerlim,double _yupperlim,pair<double,double> _stepvalue,
                                                                     int num_Grid);
      void Grid(const Cairo::RefPtr<Cairo::Context>& cr,double _xmin,double _xmax,double
                                       _ymin,double _ymax,int num_Grid);
      pair<double,double> ScaleData(pair<double,double> value);
      void Plot(const Cairo::RefPtr<Cairo::Context>& cr);
      void SetColor(int object_id);
      void DrawLegends(const Cairo::RefPtr<Cairo::Context>& cr);
      void DrawLabel(const Cairo::RefPtr<Cairo::Context>& cr);
      
};

PlotLib::PlotLib()
{
}

PlotLib::~PlotLib()
{
  delete graph;
}

GRAPH* PlotLib::graph;
bool PlotLib::on_draw(const Cairo::RefPtr<Cairo::Context>& cr){             /*override function for drawing,all the stuffs should be inside this function*/
     Gtk::Allocation allocation = get_allocation();                         /*to display on window.*/   
     const int width = allocation.get_width();
     const int height = allocation.get_height();
     // scale to unit square (0 to 1 width and height)
   
     cr->scale(width, height);
     cr->set_line_width(DEFAULT_LINE_WIDTH);
     SetBackground(cr);
     cr->set_source_rgba(2,0,1,1);
     
     
     Grid(cr,graph->_xmin,graph->_xmax,graph->_ymin,graph->_ymax,4);
     DrawAxis(cr,_xorigin=X_ORIGIN,_yorigin);
     DrawLegends(cr);
     Plot(cr);
     return true;

}

void PlotLib::SetBackground(const Cairo::RefPtr<Cairo::Context>& cr)           /*Set the background of display window*/
{    rgb_color=RGB_13;
     cr->rectangle(0,0,1,1);
     cr->set_source_rgba(rgb_color.r,rgb_color.g,rgb_color.b,1);
     cr->fill();
     rgb_color=RGB_0;
     cr->rectangle(0.05,0.05,0.9,0.9);
     cr->set_source_rgba(rgb_color.r,rgb_color.g,rgb_color.b,1);
     cr->fill();
    
}

void PlotLib::DrawAxis(const Cairo::RefPtr<Cairo::Context>& cr, double _xorigin,double _yorigin)  /*for drawing axis mainly used when user defines his preference*/
{
     cr->set_line_width(4*DEFAULT_LINE_WIDTH);
     _xcurrent=_xorigin;
     _ycurrent=_yorigin;
     rgb_color=RGB_12;  
     cr->set_source_rgba(rgb_color.r,rgb_color.g,rgb_color.b,1);
     _xdest=_xcurrent;
     _ydest=_ycurrent;
     cr->move_to(_xdest,_ydest);
     _xdest=X_AXIS_MAX;
     cr->line_to(_xdest,_ydest);
     _xdest=_xorigin;
     _ydest=Y_ORIGIN;
     cr->move_to(_xdest,_ydest);
     _ydest=Y_AXIS_MAX;
     cr->line_to(_xdest,_ydest);
     cr->stroke();   
     cr->set_line_width(DEFAULT_LINE_WIDTH);
}

void PlotLib::DrawGrid(const Cairo::RefPtr<Cairo::Context>& cr,double _xlowerlim,double _xupperlim,double        /*for drawing grid*/
                                 _ylowerlim,double _yupperlim,pair<double,double> _stepvalue,int num_Grid){   

     if(num_Grid<2){
       std::cout<<"Error:not enough number of Grids";
       return;
     }
     _xcurrent=X_ORIGIN;
     _ycurrent=Y_ORIGIN;
     double x_stepsize=fabs(X_AXIS_MAX-X_AXIS_MIN)/10;
     double y_stepsize=fabs(Y_AXIS_MAX-Y_AXIS_MIN)/num_Grid;
     std::vector<double> dashes;
     dashes.push_back(DELTA/2);
     rgb_color=RGB_11;
     cr->set_source_rgba(rgb_color.r,rgb_color.g,rgb_color.b,1);
     cr->set_dash(dashes,0.0);
     cr->begin_new_path();
     cr->select_font_face("Pursia",Cairo::FONT_SLANT_NORMAL,Cairo::FONT_WEIGHT_NORMAL);
     cr->set_font_size(0.015);
     double i=_xlowerlim;
     double j=_ylowerlim;
     //plotting vertical Grid//
     while(_xcurrent<X_AXIS_MAX){
      cr->move_to(_xcurrent,_ycurrent);
      _xdest=_xcurrent;
      _ydest=Y_AXIS_MAX;
      cr->line_to(_xdest,_ydest);
      cr->stroke();
      string point_value=static_cast<ostringstream*>(&(ostringstream()<<i))->str();
      i+=_stepvalue.first;
      cr->move_to(_xcurrent,_ycurrent+DELTA);
      cr->show_text(point_value.c_str());
      _xcurrent=_xcurrent+ x_stepsize;

     }
     //plotting horizontal Grid//
     _xcurrent=X_ORIGIN;
     _ycurrent=Y_ORIGIN;
     while(_ycurrent>=Y_AXIS_MAX-DELTA){
      cr->move_to(_xcurrent,_ycurrent);
      _xdest=X_AXIS_MAX;
      _ydest=_ycurrent;
      cr->line_to(_xdest,_ydest);
      cr->stroke();
      if(fabs(j-0)<EPS){
        _yorigin=_ycurrent;
        j=0;
      }

      string point_value=static_cast<ostringstream*>(&(ostringstream()<<j))->str();
      j+=_stepvalue.second;
      cr->move_to(_xcurrent-DELTA*(double(strlen(point_value.c_str()))/2),_ycurrent);
      cr->show_text(point_value);
      _ycurrent=_ycurrent - y_stepsize;
      //_ycurrent=_ycurrent-GRID_STEP_Y;
     }
     cr->unset_dash();
     _xcurrent=X_ORIGIN;
     _ycurrent=Y_ORIGIN;
}

void PlotLib::Grid(const Cairo::RefPtr<Cairo::Context>& cr,double _xmin,double _xmax,double          /*for determining spacing between grid lines*/
                                                _ymin,double _ymax,int num_Grid){
     pair<double,double> tick_range;
     double range=fabs(_ymax-_ymin);
     double tick_range_y;
     double _ylowerlim;
     double _yupperlim;
     if(_ymin<0){
      tick_range_y=range/num_Grid;
      double power_num=ceil(log10(tick_range_y));
      double tenpower_num=pow(10,power_num);
      tick_range_y=(tick_range_y/tenpower_num);
      if(tick_range_y>0.2 && tick_range_y<=0.25){
       tick_range_y=0.25*tenpower_num;   
      }
      else if(tick_range_y>0.7 && tick_range_y<=0.75){
       tick_range_y=0.75*tenpower_num;
      }
      else{
       tick_range_y=(ceil(10*tick_range_y)/10)*tenpower_num;
      }
      _ylowerlim=tick_range_y*floor(_ymin/tick_range_y);
      _yupperlim=tick_range_y*ceil(_ymax/tick_range_y);
    }
    else{
      tick_range_y=range/(num_Grid);
      double power_num=ceil(log10(tick_range_y));
      double tenpower_num=pow(10,power_num);
      tick_range_y=(tick_range_y/tenpower_num);
      if(tick_range_y>0.2 && tick_range_y<=0.25){
       tick_range_y=0.25*tenpower_num;   
      }
      else if(tick_range_y>0.7 && tick_range_y<=0.75){
       tick_range_y=0.75*tenpower_num;
      }
      else{
       tick_range_y=(ceil(10*tick_range_y)/10)*tenpower_num;
      }
      _ylowerlim=0;
      _yupperlim=tick_range_y*ceil(_ymax/tick_range_y);
    }

    double range_x=fabs(_xmax-_xmin);
    double tick_range_x=range_x/10;
    tick_range=make_pair(tick_range_x,tick_range_y);
    
    graph->_xlim=make_pair(_xmin,_xmax);
    graph->_ylim=make_pair(_ylowerlim,_yupperlim);
    DrawGrid(cr,_xmin,_xmax,_ylowerlim,_yupperlim,tick_range,num_Grid);
    
} 

pair<double,double> PlotLib::ScaleData(pair<double,double> value){                                     /*scale the data to the required scale i.e.*/
       double _yupperlim=graph->_ylim.second;                                                          /*between 0.1 to 0.8 ->plotting area available*/
       double _ylowerlim=graph->_ylim.first;
       double range=_yupperlim-_ylowerlim;
       value.second=Y_ORIGIN- ((fabs(Y_AXIS_MAX-Y_AXIS_MIN)/range)*(value.second-_ylowerlim));
       double _xupperlim=graph->_xlim.second;
       double _xlowerlim=graph->_xlim.first;
       range=_xupperlim-_xlowerlim;
       value.first=X_ORIGIN+((X_AXIS_MAX-X_AXIS_MIN)/range)*(value.first-_xlowerlim);
       return value;

}

void PlotLib::DrawLegends(const Cairo::RefPtr<Cairo::Context>& cr){                              /*for drawing legends*/
     for(int num_plot=0;num_plot<graph->num_plots;++num_plot){
         
         const char* legend=graph->v_data[num_plot].v_legend;
         rgb_color=color_palette[num_plot+1];
         cr->set_source_rgba(rgb_color.r,rgb_color.g,rgb_color.b,1);
         cr->move_to(_xcurrent+DELTA/2,0.025);
         _xdest=_xcurrent+3*DELTA;
         cr->line_to(_xdest,0.025); 
         cr->move_to(_xdest+DELTA,0.025);
         cr->show_text(legend);
         cr->stroke();
         _xcurrent=_xdest+0.05;
     }
}    

void PlotLib::DrawLabel(const Cairo::RefPtr<Cairo::Context>& cr){                       /*for drawing labels*/
 
         
}

void PlotLib::Plot(const Cairo::RefPtr<Cairo::Context>& cr){                              /*plotting data*/
     for(int num_plot=0;num_plot<graph->num_plots;++num_plot){
         vector<pair<double,double> > data=graph->v_data[num_plot].probe_data;
         cr->set_source_rgba(color_palette[num_plot+1].r,color_palette[num_plot+1].g,color_palette 
                                                                             [num_plot+1].b,1);
         for(int i=1;i<data.size()-1;i+=3){

             /*if(i+3>=data.size()){
                i=data.size()-3;
                cr->move_to(ScaleData(data [i-1]).first,ScaleData(data[i-1]).second);
                cr->curve_to(ScaleData(data[i]).first,ScaleData(data[i]).second,
                                               ScaleData(data[i+1]).first,
                                              ScaleData(data[i+1]).second,
                                               ScaleData(data[i+2]).first,
                                               ScaleData(data[i+2]).second);
               cr->stroke();


              }*/

         //     else{
         
                  cr->move_to(ScaleData(data[i-1]).first,
                                        ScaleData(data[i-1]).second);
                  cr->curve_to(ScaleData(data[i]).first,
                                              ScaleData(data[i]).second,
                                              ScaleData(data[i+1]).first,
                                              ScaleData(data[i+1]).second,
                                              ScaleData(data[i+2]).first,
                                              ScaleData(data[i+2]).second);
                cr->stroke();
         //    } 
        }
     }

}

#endif PLOT_WIP_H
