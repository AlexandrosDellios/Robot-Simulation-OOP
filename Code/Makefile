# Definitions de macros

CXX     = g++
CXXFLAGS = -g -Wall -std=c++11
CXXFILES = simulation.cc shape.cc robot.cc projet.cc particule.cc message.cc
OFILES = simulation.o shape.o robot.o projet.o particule.o message.o

# Definition de la premiere regle

prog: $(OFILES)
	$(CXX) $(OFILES) -o prog

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
	@/bin/rm -f *.o *.x *.cc~ *.h~ prog

#
# -- Regles de dependances generees automatiquement
#
# DO NOT DELETE THIS LINE
projet.o: projet.cc simulation.h
simulation.o: simulation.h simulation.cc robot.h  particule.h
robot.o: robot.cc robot.h message.h  particule.h shape.h
particule.o: particule.cc particule.h message.h shape.h
message.o: message.cc message.h
shape.o: shape.cc shape.h
