CX = g++
CXXFLAGS = -std=c++14 -g -Werror=vla -Wall -MMD
EXEC = chess
OBJECTS = main.o bishop.o chesscontroller.o king.o observer.o piece.o queen.o subject.o board.o chessview.o knight.o pawn.o position.o rook.o textobserver.o graphicsobserver.o move.o window.o level1.o level2.o level3.o level4.o computerplayer.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -lX11 -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
