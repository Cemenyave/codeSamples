#include "string.h"

struct Date
{
  int day   = 0;
  int month = 0;
  int year  = 0;

  Date() {}

  Date(const String &str)
  {
    enum {
      day_reading,
      month_reading,
      year_reading,
      finish_state
    };

    if (!str.size())
      return;

    int num = 0;
    int state = day_reading;
    for (size_t i = 0, s = str.size(); i < s; ++i) {
      if (str[i] == '.') {
        switch (state) {
          case day_reading:
            this->day = num;
            break;
          case month_reading:
            this->month = num;
            break;
          case finish_state:
          default:
            assert(0);
            return;
        }
        num = 0;
        ++state;
        continue;
      }
      if ('0' <= str[i] && str[i] <= '9') {
        num = num * 10 + (str[i] - '0');
      }
    }
    this->year = num;
  }

  ///
  /// @return amount of full monthes in date
  ///
  int getMonthCount()
  {
    return (this->month - 1) + this->year * 12;
  }
};
