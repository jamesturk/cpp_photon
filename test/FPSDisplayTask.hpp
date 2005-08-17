#ifndef FPSDISPLAYTASK_HPP
#define FPSDISPLAYTASK_HPP

#include "photon.hpp"
#include <boost/lexical_cast.hpp>

// Used to measure FPS and display it in the title bar.  Pretty good example
//  of when to use a Task, logic is entirely separate from rest of application
//  and should be executed regularly.
//
// Note: Realistically framerate should not be displayed in the title bar 
//          because changing the title causes a stutter, and changing the title
//          bar every second makes applications with a lot of movement look 
//          terrible.
class FPSDisplayTask : public photon::util::Task
{
public:
    FPSDisplayTask() :
        Task("FPSDisplayTask"),
        app(Application::getInstance()),
        lastUpdate(0)
    { }

    void update(scalar timeDelta)
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
    Application& app;
    double lastUpdate;
};

#endif //FPSDISPLAYTASK_HPP
