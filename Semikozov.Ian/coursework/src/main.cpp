#include <boost/bind/bind.hpp>

#include "adc_worker.hpp"
#include "stand_manager.hpp"
#include "steppers_worker.hpp"

using namespace ByteStorm;
using namespace boost::placeholders;

int main()
{

    Test<int> test;
    auto *a = new ADCWorker;
    auto *s = new SteppersWorker;

    StandManager manager{ a, s };

    s->signal.connect(boost::bind(&StandManager::onAngleSet, boost::ref(manager), _1));
    a->signal.connect(boost::bind(&StandManager::onSingleShotCompleted, boost::ref(manager), _1));

    manager.bs.service.run();

    while (true) {}

    return 0;
}
