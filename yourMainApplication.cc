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
		if (argc == 1) {
		ui = new G4UIExecutive(argc, argv);
		}
		else{
		macroFileName = argv[1];
		}

	    auto * runManager = G4RunManagerFactory::CreateRunManager();
	    runManager->SetNumberOfThreads(1);
	    
	    YourDetectorConstruction* detector = new YourDetectorConstruction();
		runManager->SetUserInitialization(detector);

	    const G4String plName = "FTFP_BERT";
		G4PhysListFactory plFactory;
		plFactory.SetVerbose(0);
		G4VModularPhysicsList *pl = plFactory.GetReferencePhysList( plName );
	    runManager->SetUserInitialization(pl);

	    YourActionInitialization * actionInitialization = new YourActionInitialization(detector);
	    runManager->SetUserInitialization( actionInitialization );

	    // runManager->Initialize();
	    
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
