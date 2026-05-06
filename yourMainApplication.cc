    #include "YourDetectorConstruction.hh"
    #include "YourActionInitialization.hh"

    #include "G4PhysListFactory.hh" // to retrieve reference physics list
    #include "G4RunManagerFactory.hh" // to produce default G4RunManager
    #include "G4UImanager.hh" // to pass some built-in UI commands

	#include "G4UIExecutive.hh"
	#include "G4VisExecutive.hh"

	int main(int argc, char** argv){
		// Detect interactive mode (if no arguments) and define UI session
		G4UIExecutive* ui = nullptr;
		G4String macroFileName;
		G4String G4RunManagerTypeString="";
		if (argc == 1) {
			ui = new G4UIExecutive(argc, argv);
		}
		else if (argc == 3) {
			macroFileName = argv[1];
			G4RunManagerTypeString = argv[2];
		}
		else{
			return -1;
		}

		G4RunManager * runManager = nullptr;
		if("SerialOnly" == G4RunManagerTypeString) {
			runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::SerialOnly);
		}
		else if("MTOnly" == G4RunManagerTypeString) {
			runManager =  G4RunManagerFactory::CreateRunManager(G4RunManagerType::MTOnly);
		}
		else if("TaskingOnly" == G4RunManagerTypeString) {
			runManager =  G4RunManagerFactory::CreateRunManager(G4RunManagerType::TaskingOnly);
		}
		else if("TBBOnly" == G4RunManagerTypeString) {
			runManager =  G4RunManagerFactory::CreateRunManager(G4RunManagerType::TBBOnly);
		}
		else{
			return -2;
		}

	    YourDetectorConstruction* detector = new YourDetectorConstruction();
		runManager->SetUserInitialization(detector);

	    const G4String plName = "FTFP_BERT";
		G4PhysListFactory plFactory;
		plFactory.SetVerbose(0);
		G4VModularPhysicsList *pl = plFactory.GetReferencePhysList( plName );
	    runManager->SetUserInitialization(pl);

	    YourActionInitialization * actionInitialization = new YourActionInitialization(detector);
	    runManager->SetUserInitialization( actionInitialization );
	    
	    G4UImanager * UImanager = G4UImanager::GetUIpointer();

		// Process macro in batch mode
		if (!ui) {
			G4String command = "/control/execute ";
			UImanager->ApplyCommand(command + macroFileName);
		}
		else {
			// interactive mode
			ui->SessionStart();
			delete ui;
		}
		delete runManager;

	    return 0;
    }
