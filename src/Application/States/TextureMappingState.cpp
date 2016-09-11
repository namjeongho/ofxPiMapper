#include "TextureMappingState.h"

namespace ofx {
namespace piMapper {

TextureMappingState * TextureMappingState::_instance = 0;

TextureMappingState * TextureMappingState::instance(){
	if(_instance == 0){
		_instance = new ofx::piMapper::TextureMappingState();
	}
	return _instance;
}

TextureMappingState::TextureMappingState(){
	_bTranslateCanvas = false;
}

void TextureMappingState::draw(Application * app){
	ofPushMatrix();
	ofTranslate(_canvasTranslate.x, _canvasTranslate.y);
	app->getGui()->draw();
	ofPopMatrix();
	
	ofPushStyle();
	ofSetColor(255, 255, 255, 150);
	app->getSurfaceManager()->draw();
	ofPopStyle();
	
	ofPushMatrix();
	ofTranslate(_canvasTranslate.x, _canvasTranslate.y);
	
	Gui::instance()->getSurfaceHighlightWidget().setSurfaceManager(app->getSurfaceManager());
	Gui::instance()->getSurfaceHighlightWidget().draw();
	
	Gui::instance()->getTextureHighlightWidget().setSurfaceManager(app->getSurfaceManager());
	Gui::instance()->getTextureHighlightWidget().draw();
	
	ofPopMatrix();
}

void TextureMappingState::onKeyPressed(Application * app, ofKeyEventArgs & args){
	switch(args.key){
		 
	 case '>':
		 app->getCmdManager()->exec(
			 new SelNextTexCoordCmd(app->getGui()->getTextureEditor()));
		 break;
		 
	 case '<':
		 app->getCmdManager()->exec(
			 new SelPrevTexCoordCmd(app->getGui()->getTextureEditor()));
		 break;
	 
	 case ' ':
		 if(app->getSurfaceManager()->getSelectedSurface() == 0){
			return;
		 }
		 
         if(app->getSurfaceManager()->getSelectedSurface()->getSource()->getType() ==
            SourceType::SOURCE_TYPE_VIDEO){
            app->getCmdManager()->exec(
                new ToggleAnimatedSourceCmd(
                    app->getSurfaceManager()->getSelectedSurface()));
         }
		 break;
		 
	 case OF_KEY_TAB:
		 if(app->getSurfaceManager()->getSelectedSurface() != 0){
			app->getCmdManager()->exec(
				new SetNextSourceCmd(
					app->getSurfaceManager()->getSelectedSurface(),
					app->getGui()->getSourcesEditor()));
		 }else{
			app->getCmdManager()->exec(new SelNextSurfaceCmd(app->getSurfaceManager()));
		 }
		 break;
	}
}

void TextureMappingState::onBackgroundPressed(Application * app, GuiBackgroundEvent & e){
	cout << "TextureMappingState::onBackgroundPressed()" << endl;
	
	app->getCmdManager()->exec(
        new DeselectTexCoordCmd(app->getGui()->getTextureEditor()));
	
	_bTranslateCanvas = true;
	_clickPosition = ofPoint(e.args.x, e.args.y);
	_clickCanvasTranslate = _canvasTranslate;
}

void TextureMappingState::onMouseReleased(Application * app, ofMouseEventArgs & args){
	cout << "TextureMappingState::onMouseReleased()" << endl;
	
	_bTranslateCanvas = false;
}

void TextureMappingState::onMouseDragged(Application * app, ofMouseEventArgs & args){
	if(!_bTranslateCanvas){
		return;
	}
	
	ofPoint mousePosition = ofPoint(args.x, args.y);
	ofPoint distance =  mousePosition - _clickPosition;
	_canvasTranslate = _clickCanvasTranslate + distance;
}

} // namespace piMapper
} // namespace ofx