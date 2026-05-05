    #include "YourRunAction.hh"
    #include "YourPrimaryGeneratorAction.hh"

    #include "G4Run.hh"
    #include "G4SystemOfUnits.hh"
    #include "globals.hh"

    YourRunAction::YourRunAction(YourPrimaryGeneratorAction * pgenerator):
            G4UserRunAction(),
            fPrimaryGeneratorAction(pgenerator){}

    YourRunAction::~YourRunAction(){}

    void YourRunAction::BeginOfRunAction(const G4Run *){
        // reset accumulator before each run
        fEdepInTarget = 0.0;
        fPrimaryGeneratorAction->UpdatePosition();
    }

    void YourRunAction::EndOfRunAction(const G4Run * run){

        G4int numberOfEvent = run->GetNumberOfEvent();
        G4double edepAverage = fEdepInTarget  / numberOfEvent;
        G4cout << " Mean energy deposited in the target per event : "
               << edepAverage / CLHEP::MeV
               << " MeV"
               << G4endl;
    }
