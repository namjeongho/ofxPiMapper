#include "PresentationState.h"

namespace ofx {
    namespace piMapper {
        
        PresentationState * PresentationState::_instance = 0;
    
        PresentationState * PresentationState::instance() {
            if (_instance == 0) {
                _instance = new ofx::piMapper::PresentationState();
            }
            return _instance;
        }
        
        void PresentationState::draw(Application * app) {
            ofSetColor(255, 255, 0);
            ofDrawBitmapString("Presentation State", 10, 20);
        }
    }
}