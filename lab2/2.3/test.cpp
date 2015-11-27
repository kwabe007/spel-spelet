#include "calendar.hpp"
#include "kattistime.h"
#include "julian.hpp"
#include "gregorian.hpp"
#include <stdexcept>
#include <cassert>

using namespace std;
using namespace lab2;

int main() {

    time_t tp;
    time(&tp);
    set_k_time(tp);

    cout << "*******************TEST STARTED*******************\n";
    Calendar<Gregorian> default_calendar;
    cout << "Calendar successfully default-constucted\n";
    cout << "The date of created calendar is " << default_calendar.get_date_str() << endl;

    Calendar<Gregorian> greg_calendar(2004,5,3);
    cout << "greg_calendar created: " << greg_calendar.get_date_str() << endl;

    bool success;
    success = greg_calendar.set_date(2000,2,29);


    assert(success);

    cout << "greg_calendar's date successfully set: " << greg_calendar.get_date_str() << endl;

    try {
        greg_calendar.set_date(2100,2,29);
        success = true;
    }
    catch (invalid_argument) {
        success = false;
    }

    assert(!success);
    cout << "greg_calendar's date unsuccessfully set (according to plan): " << greg_calendar.get_date_str() << endl;

    Calendar<Julian> juli_calendar(greg_calendar);
    cout << "juli_calendar created: " << juli_calendar.get_date_str() << endl;

    greg_calendar.set_date(2014,12,16);
    cout << "greg_calendar's date set to: " << greg_calendar.get_date_str() << endl;

    success = greg_calendar.add_event("End of the world");
    assert(success);
    cout << "added 'End of the world' to greg_calendar (today)" << endl;

    success = greg_calendar.add_event("Upper body day", 2015);
    assert(success);
    cout << "added 'Upper body day' to greg_calendar (2000)" << endl;

    success = greg_calendar.add_event("Upper body day again", 2014,12);
    assert(success);
    cout << "added 'Upper body day again' to greg_calendar (2000,2)" << endl;

    success = greg_calendar.add_event("Upper body day with Jack3d", 2015,1);
    assert(success);
    cout << "added 'Upper body day with jack3d' to greg_calendar (2000,2)" << endl;

    success = greg_calendar.add_event("Upper body day yet again", 2015,12,2);
    assert(success);
    cout << "added 'Upper body day yet again (2000,12,2)" << endl;

    success = greg_calendar.add_event("Upper body day yet again", 2015,12,2);
    assert(!success);
    cout << "did not add 'Upper body day yet again (2000,12,2) (according to keikakku), TL Note: keikakku means plan" << endl;

    success = greg_calendar.add_event("ABS day!", 2015,12,2);
    assert(success);
    cout << "added 'ABS day!' (2015,12,2) (those six packs won't wait for anybody)" << endl;

    success = greg_calendar.add_event("Leg day", 2000,12,1);
    assert(!success);
    cout << "could not add 'Leg day'; every day is upper body day!" << endl;

    greg_calendar.set_date(2000,1,2);
    cout << "greg_calendar date set to 2000-01-02" << endl;

    cout << "greg_calendar now contains:\n" << greg_calendar << endl;

    success = greg_calendar.remove_event("Upper body day again", 2014,12);
    assert(success);
    cout << "removed 'Upper body day again' from greg_calendar (2014,12)" << endl;

    success = greg_calendar.remove_event("Upper body day yet again", 2015,12,2);
    assert(success);
    cout << "removed 'Upper body day yet again' from greg_calendar (2015,12,2)" << endl;

    cout << "greg_calendar now contains:\n" << greg_calendar << endl;

    greg_calendar.set_date(2015,3,31);
    cout << "greg_calendar date set to 2015-03-31" << endl;
    cout << "greg_calendar now contains:\n" << greg_calendar << endl;

    juli_calendar = greg_calendar;
    cout << "juli_calendar assigned to greg_calendar, it now contains:\n" << juli_calendar << endl;

    cout << "*******************TEST FINISHED*******************\n";
}
