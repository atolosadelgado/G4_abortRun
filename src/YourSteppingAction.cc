    #include "YourSteppingAction.hh"
    #include "YourEventAction.hh"
    #include "YourDetectorConstruction.hh"
    #include "G4Step.hh"
    #include "G4Track.hh"
    #include "G4ParticleDefinition.hh"
    #include "G4RunManager.hh"

    YourSteppingAction::YourSteppingAction(YourDetectorConstruction * detector, YourEventAction * eventAction):
                G4UserSteppingAction(),
                fDetector(detector),
                fEventAction(eventAction){}

    YourSteppingAction::~YourSteppingAction(){}

    void YourSteppingAction::UserSteppingAction(const G4Step * step){
	if( std::ifstream("abort_stepping").good() )
	{
		G4cout << "abort_stepping has been created, aborting" << G4endl;
		G4RunManager::GetRunManager()->AbortEvent();
		G4RunManager::GetRunManager()->AbortRun(true);
	}
    
	    // return if volume is not target
        if(fDetector->GetTargetPhysicalVolume() != step->GetPreStepPoint()->GetPhysicalVolume()){
            return;
        }

        G4double edep = step->GetTotalEnergyDeposit();

//        G4cout << "-- edep = " << edep / CLHEP::MeV << " MeV" << G4endl;
//        G4cout << "-- particle = " << step->GetTrack()->GetParticleDefinition()->GetParticleName() << G4endl;
        fEventAction->AddEdep(edep);
    }
