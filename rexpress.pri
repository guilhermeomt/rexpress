
CONFIG(debug, debug|release){
    win32 {
    	versionAtLeast(QT_VERSION, 5.15.0) {
                LIBS += -lqtadvanceddocking -lanimations
    	}
    	else {
                LIBS += -lqtadvanceddockingd -lanimations
    	}
    }
    else:mac {
        LIBS += -lqtadvanceddocking_debug -lanimations
    }
    else {
        LIBS += -lqtadvanceddocking -lanimations
    }
}
else{
    LIBS += -lqtadvanceddocking -lanimations
}


unix:!macx {
    LIBS += -lxcb
}
