#include "../../include/NaoFramework/Modules/DynamicModuleInterface.hpp"

#include <iostream>
#include <vector>

class Writer : public NaoFramework::Modules::DynamicModuleInterface {
    public:
        Writer(NaoFramework::Comm::LocalBlackboardAdapter & comm) : DynamicModuleInterface("Writer") {
            using namespace NaoFramework::Comm;
            RegistrationError e = RegistrationError::None;
            f_ = comm.registerProvide<int>("test", &e);
            if ( e != RegistrationError::None ) {
                log("Mistake..");
                throw e;
            }
            else {
                log("OK!");
            }
        }

        virtual ~Writer() { 
            log("Writer out!");
        }

        virtual void execute() { 
            int testData = 5;
            
            std::cout << "I'm Writer! I'm setting comm to: " << testData << '\n';
            f_(testData);

            log("I did something!");
        }
    private:
        NaoFramework::Comm::ProvideFunction<int> f_;
};

MODULE_EXPORT(Writer)
