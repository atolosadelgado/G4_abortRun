    #include "YourDetectorConstruction.hh"
    #include "YourActionInitialization.hh"

    #include "G4PhysListFactory.hh" // to retrieve reference physics list
    #include "G4RunManagerFactory.hh" // to produce default G4RunManager
    #include "G4UImanager.hh" // to pass some built-in UI commands

	#include "G4UIExecutive.hh"
	#include "G4VisExecutive.hh"

	#include <thread>
	#include <chrono>
	#include <fstream>
	#include <cstdio>   // std::remove
	#include <iostream>

	int main(int argc, char** argv){

		//_______________________________________________________________________
		//-- non Geant4 section, to trigger run/event abort
		//--   by creating a dummy file
		//--   in stepping action, existence of this file is checked
		//--   if exists, it will call AbortRun + AbortEven methods
		//--   of the run manager
		std::thread abortThread([](){
			const char* filename = "abort_stepping";
			G4int waiting_time_seconds = 5;

			// remove file if already exist
			if (std::ifstream(filename).good()) {
				std::cout << "[Thread] File exists, removing it\n";
				std::remove(filename);
			}

			// wait 1 second
			std::this_thread::sleep_for(std::chrono::seconds(waiting_time_seconds));

			// create file
			std::ofstream outfile(filename);
			if (outfile) {
				std::cout << "[Thread] File created\n";
			}
		});
		//-- END non Geant4 section
		//_______________________________________________________________________

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
		G4int nThreads = 4;
		if("SerialOnly" == G4RunManagerTypeString) {
			runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::SerialOnly);
		}
		else if("MTOnly" == G4RunManagerTypeString) {
			runManager =  G4RunManagerFactory::CreateRunManager(G4RunManagerType::MTOnly);
			runManager->SetNumberOfThreads(nThreads);
		}
		else if("TaskingOnly" == G4RunManagerTypeString) {
			runManager =  G4RunManagerFactory::CreateRunManager(G4RunManagerType::TaskingOnly);
			runManager->SetNumberOfThreads(nThreads);
		}
		// else if("TBBOnly" == G4RunManagerTypeString) {
		// 	runManager =  G4RunManagerFactory::CreateRunManager(G4RunManagerType::TBBOnly);
		// 	runManager->SetNumberOfThreads(nThreads);
		// }
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

		// wait for the thread before returning
		abortThread.join();
	    return 0;
    }
