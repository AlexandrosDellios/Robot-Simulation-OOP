# Definitions de macros

CXX     = g++
CXXFLAGS = -g -Wall -std=c++11
CXXFILES = simulation.cc shape.cc robot.cc projet.cc particule.cc message.cc
OFILES = simulation.o shape.o robot.o projet.o particule.o message.o

# Definition de la premiere regle

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
#
# -- Regles de dependances generees automatiquement
#
# DO NOT DELETE THIS LINE
simulation.o: simulation.cc simulation.h robot.h shape.h particule.h \
 constante.h
shape.o: shape.cc shape.h
robot.o: robot.cc robot.h shape.h particule.h message.h constante.h
projet.o: projet.cc simulation.h robot.h shape.h particule.h
particule.o: particule.cc particule.h shape.h message.h constante.h
message.o: message.cc message.h
