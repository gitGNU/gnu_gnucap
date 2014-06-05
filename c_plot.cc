//g++ -fPIC -shared -o plotting.so c_plot.cc -I /home/abhi/gtk `pkg-config --cflags --libs gtkmm-3.0` -w

#include <gnucap/u_sim_data.h>
#include <gnucap/c_comand.h>
#include <gnucap/globals.h>
#include <gnucap/m_wave.h>
#include <gnucap/u_prblst.h>
#include <gnucap/declare.h>	
#include <gnucap/s__.h>
#include <plot_wip.h>
/*plot out the data stored in wave object in separate window
*TO DO: Make it more customized and under the control of user i.e 
*what to display and how to display,for now it display all the node stored in wave */
namespace {

class CMD_TABLE : public CMD{
    
public:
    void do_it(CS&, CARD_LIST*)
    {
    std::string probe_name;
    PROBELIST& storelist=_probe_lists->store[_sim->_mode];
    if(storelist.size()){     /*check the whether storelist is empty or not*/
    int num_waves=0;
    std::vector<DVEC> data_vector;
    for (PROBELIST::const_iterator
	   p=storelist.begin();  p!=storelist.end();  ++p) {
           WAVE* w=SIM::find_wave(p->label().c_str());
           if(w){
             DVEC pdata;
             pdata=Vectordb::CreatePvector(w,num_waves+1,"v");
             num_waves++;
             data_vector.push_back(pdata);
           }
    }
    int argc=1;                         //a hack which i have to do here//
    char* p[]={"asd",NULL};
    char **argv=p;
   
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv);
    Gtk::Main kit(argc,argv);
    Gtk::Window win;
    win.set_title("Gnucap");
    win.set_default_size(800,600);
    DVEC pdata;
    PlotLib area;
    area.graph=Graphdb::CreateGraph(data_vector,num_waves);
    win.add(area);
    area.show();
    Gtk::Main::run(win);       //This is the loop which is creating problem
   
    }
    else{
       throw Exception_No_Match("No probe stored");
    }
    }
}p;
DISPATCHER<CMD>::INSTALL d1(&command_dispatcher,"plot_wip",&p);
}
