# Definitions de macros

#compilateur
CXX     = g++
#options de compilation
CXXFLAGS = -Wall -std=c++17
LINKING = `pkg-config --cflags gtkmm-4.0`
#options de liaisons
LDLIBS = `pkg-config --libs gtkmm-4.0`
#fichiers sources
CXXFILES = simulation.cc shape.cc robot.cc particule.cc message.cc
#fichiers objets générés
OFILES = simulation.o shape.o robot.o projet.o particule.o message.o gui.o \
 graphic.o

#Nom de l'executable
OUT = projet

# Definition de la premiere regle

all: $(OUT)

projet: $(OFILES)
	$(CXX) $(OFILES) -o projet

# Definitions de cibles particulieres

depend:
	@echo " *** MISE A JOUR DES DEPENDANCES ***"
	@(sed '/^# DO NOT DELETE THIS LINE/q' Makefile && \
	  $(CXX) -MM $(CXXFLAGS) $(CXXFILES) | \
	  egrep -v "/usr/include" \
	 ) >Makefile.new
	@mv Makefile.new Makefile

clean:
	@echo " *** EFFACE MODULES OBJET ET EXECUTABLE ***"
	@/bin/rm -f *.o *.x *.cc~ *.h~ projet
	

#dependances qui utilisent gtkmm
projet.o: projet.cc simulation.h robot.h shape.h particule.h gui.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)

gui.o: gui.cc gui.h graphic_gui.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)
	
graphic.o: graphic.cc graphic.h graphic_gui.h 
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)
	

$(OUT): $(OFILES)
	$(CXX) $(CXXFLAGS) $(LINKING) $(OFILES) -o $@ $(LDLIBS)
	

	
#
# -- Regles de dependances generees automatiquement
#
# DO NOT DELETE THIS LINE
simulation.o: simulation.cc simulation.h robot.h shape.h particule.h \
 constante.h message.h
shape.o: shape.cc shape.h
robot.o: robot.cc robot.h shape.h particule.h message.h constante.h
particule.o: particule.cc particule.h shape.h message.h constante.h
message.o: message.cc message.h
