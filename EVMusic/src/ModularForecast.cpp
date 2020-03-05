#include "plugin.hpp"


struct ModularForecast : Module {
	enum ParamIds {
		NUM_PARAMS
	};
	enum InputIds {
        SUNNY_INPUT,
        RAINBOW_INPUT,
        THUNDER_INPUT,
        SNOW_INPUT,
        FALL_INPUT,
        NIGHT_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	ModularForecast() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
	}

	void process(const ProcessArgs& args) override {
	}
};

struct ModularForecastDisplay : OpenGlWidget {
    ModularForecast *module;
    ModularForecastDisplay(){}
    
    //Draw a custom widget in the module - the weather view
    //args.vg is the NVGContext
    void draw(const DrawArgs &args) override {
        
        //background
        nvgFillColor(args.vg, nvgRGB(20, 30, 33));
        nvgBeginPath(args.vg);
        nvgRect(args.vg, 0, 0, box.size.x, box.size.y);
        nvgFill(args.vg);
        glEnable(GL_DEPTH_TEST);
        
        //Testing OpenGL
        
        //Clear information from last draw
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        glBegin(GL_QUADS); //Begin quads
        
        //Trapezoid (f forces the compiler to treat these nums as floats)
        glVertex3f(-0.7f, -1.5f, -5.0f);
        glVertex3f(0.7f, -1.5f, -5.0f);
        glVertex3f(0.4f, -0.5f, -5.0f);
        glVertex3f(-0.4f, -0.5f, -5.0f);
        
        glEnd(); //Done!
        
        drawFramebuffer();
        
        
        if(module == NULL) return;
    }
};

struct ModularForecastWidget : ModuleWidget {
    ModularForecastWidget(ModularForecast *module);
};


ModularForecastWidget::ModularForecastWidget(ModularForecast *module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/ModularForecast.svg")));
    
        ModularForecastDisplay *display = new ModularForecastDisplay();
        display->module = module;
        display->box.pos = Vec(150, (RACK_GRID_HEIGHT / 8) - 10);
        display->box.size = Vec(box.size.x - 190, RACK_GRID_HEIGHT - 80);

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
        addInput(createInput<PJ301MPort>(Vec(18, 30), module, ModularForecast::SUNNY_INPUT));
        addInput(createInput<PJ301MPort>(Vec(18, 60), module, ModularForecast::RAINBOW_INPUT));
        addInput(createInput<PJ301MPort>(Vec(18, 90), module, ModularForecast::THUNDER_INPUT));
        addInput(createInput<PJ301MPort>(Vec(18, 120), module, ModularForecast::SNOW_INPUT));
        addInput(createInput<PJ301MPort>(Vec(18, 150), module, ModularForecast::FALL_INPUT));
        addInput(createInput<PJ301MPort>(Vec(18, 180), module, ModularForecast::NIGHT_INPUT));
    
        addChild(display);
};


Model* modelModularForecast = createModel<ModularForecast, ModularForecastWidget>("ModularForecast");
