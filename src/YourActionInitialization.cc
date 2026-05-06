    #include "YourActionInitialization.hh"
    #include "YourPrimaryGeneratorAction.hh"
    #include "YourSteppingAction.hh"
    #include "YourEventAction.hh"
    #include "YourRunAction.hh"

    YourActionInitialization::YourActionInitialization(YourDetectorConstruction * det):G4VUserActionInitialization(),fDetector(det){}

    YourActionInitialization::~YourActionInitialization(){}

    void YourActionInitialization::Build() const {
        YourPrimaryGeneratorAction* primaryAction = new YourPrimaryGeneratorAction(fDetector);
        SetUserAction(primaryAction);

        YourRunAction * runAction = new YourRunAction();
        SetUserAction(runAction);

        YourEventAction * eventAction = new YourEventAction();
        SetUserAction(eventAction);

        YourSteppingAction * stepAction = new YourSteppingAction();
        SetUserAction(stepAction);

    }
