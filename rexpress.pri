
CONFIG(debug, debug|release){
    win32 {
    	versionAtLeast(QT_VERSION, 5.15.0) {
                LIBS += -lqtadvanceddocking -lanimations -ldi
    	}
    	else {
                LIBS += -lqtadvanceddockingd -lanimations -ldi
    	}
    }
    else:mac {
        LIBS += -lqtadvanceddocking_debug -lanimations -ldi
    }
    else {
        LIBS += -lqtadvanceddocking -lanimations -ldi
    }
}
else{
    LIBS += -lqtadvanceddocking -lanimations -ldi
}


unix:!macx {
    LIBS += -lxcb
}
