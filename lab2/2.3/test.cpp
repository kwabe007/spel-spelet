#include "calendar.hpp"
#include "kattistime.h"
#include "julian.hpp"
#include "gregorian.hpp"

#include <stdexcept>
#include <cassert>


using namespace std;
using namespace lab2;
unsigned int GLOBAL_DEBUG_BITS = 3;
std::ofstream ERR_FS("err");
std::ofstream TESTCAL("mycal.ics");


int main() {

    time_t tp;
    time(&tp);
    set_k_time(tp);

    cout << "*******************TEST STARTED*******************\n";
    Calendar<Gregorian> default_calendar;
    cout << "Calendar successfully default-constucted\n";
    cout << "The date of created calendar is " << default_calendar << endl;

    Calendar<Gregorian> greg_calendar(2004,5,3);
    cout << "greg_calendar created: " << greg_calendar << endl;

    bool success;
    success = greg_calendar.set_date(2000,2,29);


    assert(success);

    cout << "greg_calendar's date successfully set: " << greg_calendar << endl;

    try {
        greg_calendar.set_date(2100,2,29);
        success = true;
    }
    catch (invalid_argument) {
        success = false;
    }
    assert(!success);
    cout << "greg_calendar's date unsuccessfully set (according to plan): " << greg_calendar << endl;

    Calendar<Julian> juli_calendar(greg_calendar);
    cout << "juli_calendar created from greg_calendar: " << juli_calendar << endl;

    greg_calendar.set_date(2014,11,16);
    cout << "greg_calendar's date set to: " << greg_calendar << endl;

    success = greg_calendar.add_event("End of the world");
    assert(success);
    cout << "added 'End of the world' to greg_calendar (today)" << endl;

    success = greg_calendar.add_event("Upper body day", 2015);
    assert(success);
    cout << "added 'Upper body day' to greg_calendar (2015)" << endl;

    success = greg_calendar.add_event("Upper body day again", 2014,12);
    assert(success);
    cout << "added 'Upper body day again' to greg_calendar (2014,12)" << endl;

    success = greg_calendar.add_event("Look in the mirror and admire gains", 2013,12);
    assert(success);
    cout << "added 'Look in the mirror and admire gains' to greg_calendar (2013,12)" << endl;

    success = greg_calendar.add_event("Buy more Jack3d", 2015,1);
    assert(success);
    cout << "added 'Buy more Jack3d' to greg_calendar (2015,1)" << endl;

    success = greg_calendar.add_event("Upper body day yet again", 2015,12,2);
    assert(success);
    cout << "added 'Upper body day yet again (2015,12,2)" << endl;

    success = greg_calendar.add_event("Upper body day yet again", 2015,12,2);
    assert(!success);
    cout << "did not add 'Upper body day yet again (2015,12,2) (according to keikakku), TL Note: keikakku means plan" << endl;

    success = greg_calendar.add_event("ABS day!", 2015,12,2);
    assert(success);
    cout << "added 'ABS day!' (2015,12,2) (those six packs won't wait for anybody)" << endl;

    try {
        greg_calendar.add_event("Leg day", 2000,122,1);
        success = true;
    }
    catch (invalid_argument) {
        success = false;
    }
    assert(!success);
    cout << "could not add 'Leg day' (2000,122,1); every day is upper body day!" << endl;

    greg_calendar.set_date(2000,1,2);
    cout << "greg_calendar date set to 2000-01-02" << endl;

    cout << "greg_calendar now shows:\n" << greg_calendar << endl;

    success = greg_calendar.remove_event("Upper body day again", 2012,12,1);
    assert(!success);
    cout << "could not remove 'Upper body day again' from greg_calendar (2012,12,1)" << endl;

    success = greg_calendar.remove_event("Upper body day again", 2014,12);
    assert(success);
    cout << "removed 'Upper body day again' from greg_calendar (2014,12)" << endl;

    success = greg_calendar.remove_event("Upper body day yet again", 2015,12,2);
    assert(success);
    cout << "removed 'Upper body day yet again' from greg_calendar (2015,12,2)" << endl;

    success = greg_calendar.remove_event("Upper body day yet again", 2015,12,2);
    assert(!success);
    cout << "could not remove 'Upper body day yet again' from greg_calendar (2015,12,2)" << endl;

    cout << "greg_calendar now shows:\n" << greg_calendar << endl;

    greg_calendar.set_date(2015,3,31);
    cout << "greg_calendar date set to 2015-03-31" << endl;
    cout << "greg_calendar now shows:\n" << greg_calendar << endl;


    juli_calendar = greg_calendar;
    cout << "juli_calendar assigned to greg_calendar, it now shows:\n" << juli_calendar << endl;

    success = greg_calendar.add_event("Bicep day", 2014,12,2);
    assert(success);
    cout << "added 'Bicep day' (2014,12,2) (curl for your life!)" << endl;

    TESTCAL << greg_calendar;


    cout << "*******************TEST FINISHED*******************\n";
}
