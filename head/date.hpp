// Class representing a date
class Date
{
private:
    int day;
    int month;
    int year;

public:
    // Constructors

    Date() : day(0), month(0), year(0) {}

    Date(int dd, int mm, int yyyy)
        : day(dd), month(mm), year(yyyy) {}

    // Function to set due date (increment by 3 days)

    void setDueDate()
    {
        day += 3;
        if (day > 31)
        {
            day -= 31;
            month += 1;
        }
        if (month > 12)
        {
            month -= 12;
            year += 1;
        }
    }

    // Getter for the year

    int getYear() const
    {
        return year;
    }
};
