#ifndef FPSDISPLAYTASK_HPP
#define FPSDISPLAYTASK_HPP

#include "photon.hpp"
#include <boost/lexical_cast.hpp>

// used to measure FPS and display it in the title bar
class FPSDisplayTask : public photon::Task
{
public:
    FPSDisplayTask() :
        Task("FPSDisplayTask", 1000000),    // extremely low priority
        app(photon::AppCore::getInstance()),
        lastUpdate(0)
    { }

    void update()
    {
        // update (at most) once a second
        if(app.getTime() - lastUpdate > 1.0)
        {
            app.setTitle("FPS: " + 
                    boost::lexical_cast<std::string>(app.getFramerate()) );
            lastUpdate = app.getTime();
        }
    }

private:
    photon::AppCore& app;
    double lastUpdate;
};

#endif //FPSDISPLAYTASK_HPP
