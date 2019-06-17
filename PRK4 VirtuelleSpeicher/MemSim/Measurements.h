#ifndef MEASUREMENTS_H
#define MEASUREMENTS_H

class Measurements {
public:
    static Measurements& getInstance() {
        static Measurements instance;
        return instance;
    }
    Measurements(const Measurements& orig) = delete;
    void operator=(Measurements const&) = delete;
    virtual ~Measurements();
    
    void tick();
    void pageError();
    void pageSuccess();
    void unhealthy();
    
    double getPageErrors() const;
    double getPageAccess() const;
    double getPageSuccess() const;
    int getTime() const;
    bool getHealth() const;
    
private:
    int mHealthy = true;
    int mTime = 0;
    double mPageErrors = 0;
    double mPageAccess = 0;
    double mPageSuccess = 0;
    Measurements(){}
};

#endif /* MEASUREMENTS_H */

