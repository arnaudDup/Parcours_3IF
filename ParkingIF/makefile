

EXE = Parking

# Compilateur et editeur de lien
COMP = @g++
LINK = @g++

# Options de compilation et editions de liens

# le chemin doit etre relatif en effet l'ÈnoncÈ le demande.
CHEMIN = /shares/public/tp/tp-multitache/
INC = -I$(CHEMIN)
LIB = -L$(CHEMIN)
CPPFLAGS = -Wall -ansi -ggdb -std=c++11 -g $(INC)
EDLFLAGS = $(LIB)


#Fichiers

SRC =
INT = GestionClavier.h Mere.h IPC.h BarriereEntree.h Sortie.h
REAL = $(INT:.h=.cpp)
OBJ = $(INT:.h=.o) Mere.o

#Autres commandes et message
ECHO = @echo
RM = @rm
MESSAGE = "Compilation terminÈe"


# règle permettant d’obtenir l’exécutable du programme.
$(EXE): $(OBJ) Config.h
	$(LINK)  -o $(EXE) $^ $(EDLFLAGS) -l tp -l ncurses -l tcl
	$(ECHO) $(MESSAGE)

# règle permettant d’obtenir l’ensemble des .o
src/%.o:%.cpp
	$(COMP) -c $(CPPFLAGS) $<

clean:
	$(RM) -fv *.o $(EXE)
