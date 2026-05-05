        #ifndef YourSteppingAction_hh
        #define YourSteppingAction_hh

        #include "G4UserSteppingAction.hh"

        class YourDetectorConstruction;
        class YourEventAction;

        class YourSteppingAction : public G4UserSteppingAction
        {
            public:
                YourSteppingAction(YourDetectorConstruction * detector, YourEventAction * eventAction);
                ~YourSteppingAction() override;

                void UserSteppingAction(const G4Step * step) override;
            private:
                YourDetectorConstruction * fDetector;
                YourEventAction          * fEventAction;
        };

        #endif // YourSteppingAction_hh
