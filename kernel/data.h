#ifndef DATA_H
#define DATA_H


class Data
{
public:
    /**
     * @brief Data Class constructor.
     */
    Data();

    double getFrequency() const;
    void setFrequency(double value);

    double getPosition() const;
    void setPosition(double value);

    double getAzimuth() const;
    void setAzimuth(double value);

    double getPolar() const;
    void setPolar(double value);

    double getDistance() const;
    void setDistance(double value);

    double getDate() const;
    void setDate(double value);

private:
    double frequency;
    double position;
    double azimuth;
    double polar;
    double distance;
    double date;
};

#endif // DATA_H
