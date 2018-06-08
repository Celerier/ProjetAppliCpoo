QT += widgets
QT += sql # On rajoute SQL
QT += printsupport

LIBS += -LD:\Cours\IUT_info_Lyon_ASPE\Programmation\C++\AppliSynthese\DLL -llibmysql

SOURCES += \
    main.cpp \
    theacceuil.cpp \
    thegeneral.cpp \
    thechoose.cpp \
    thenewconv.cpp \
    convention.cpp \
    thenewentreprise.cpp \
    thegestionconvention.cpp \
    infoentreprise.cpp \
    infoetudiant.cpp \
    infoprojet.cpp \
    thepdf.cpp \
    pdffacture.cpp

FORMS += \
    thegeneral.ui \
    thechoose.ui \
    thenewconv.ui \
    thenewentreprise.ui \
    thegestionconvention.ui \
    infoentreprise.ui \
    infoetudiant.ui \
    infoprojet.ui

HEADERS += \
    theacceuil.h \
    thegeneral.h \
    thechoose.h \
    thenewconv.h \
    convention.h \
    thenewentreprise.h \
    thegestionconvention.h \
    infoentreprise.h \
    infoetudiant.h \
    infoprojet.h \
    thepdf.h \
    pdffacture.h
