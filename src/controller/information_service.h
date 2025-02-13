#ifndef INFORMATIONSERVICE_H
#define INFORMATIONSERVICE_H

class InformationService {
private:
    InformationService() = default;

public:
    static InformationService& getInstance() {
        static InformationService singleton;
        return singleton;
    }

    void load_EditInfo();
    void load_DepartmentInfo();
    void load_SubscribedDepartmentInfo();
};

#endif // INFORMATIONSERVICE_H
