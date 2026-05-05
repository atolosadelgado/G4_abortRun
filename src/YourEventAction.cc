    #include "YourEventAction.hh"
    #include "YourRunAction.hh"
    #include "G4SystemOfUnits.hh"

    YourEventAction::YourEventAction(YourRunAction * runAction):
            G4UserEventAction(),
            fRunAction(runAction){}

    YourEventAction::~YourEventAction(){}

    void YourEventAction::BeginOfEventAction(const G4Event*){
        fEdepPerEvent = 0;
    }

    void YourEventAction::EndOfEventAction(const G4Event*){
        G4cout << " Event Edep (in target) = "
               << fEdepPerEvent / CLHEP::MeV
               << " MeV"
               << G4endl;
        fRunAction->AddEventEdep(fEdepPerEvent);
    }
