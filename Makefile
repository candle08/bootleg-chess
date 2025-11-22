CXX = g++-14 -std=c++20 -fmodules-ts
CXXFLAGS = -Wall -Werror -g
HEADERFLAGS = -c -x c++-system-header

EXEC = exec

INTERFACE_OBJS = o/ability.o o/o/board.o o/o/data.o o/o/graphic.o o/o/gui.o o/o/iobserver.o o/isubject.o o/link.o o/player.o o/player-header.o o/terminal.o o/virus.o

IMPL_OBJS = o/board-impl.o o/data-impl.o o/graphic-impl.o o/player-impl.o o/player-header-impl.o o/virus-impl.o 

HARNESS_OBJ = o/main.o

HEADERS = iostream vector algorithm string sstring

ALL_OBJS = $(INTERFACE_OBJS) $(IMPL_OBJS) $(HARNESS_OBJ)

$(EXEC): headers $(ALL_OBJS)
	$(CXX) $(CXXFLAGS) $(ALL_OBJS) -o $(EXEC)

.PHONY: headers clean

headers:
	$(CXX) $(HEADERFLAGS) $(HEADERS)

$(ALL_OBJS): headers

o/iobserver.o: interface/iobserver.cc
	$(CXX) $(CXXFLAGS) -c interface/iobserver.cc

o/isubject.o: interface/isubject.cc
	$(CXX) $(CXXFLAGS) -c interface/isubject.cc

o/ability.o: interface/ability.cc
	$(CXX) $(CXXFLAGS) -c interface/ability.cc

o/link-boost.o: interface/link-boost.cc o/ability.o
	$(CXX) $(CXXFLAGS) -c interface/link-boost.cc

o/download.o: interface/download.cc o/ability.o
	$(CXX) $(CXXFLAGS) -c interface/download.cc

o/firewall.o: interface/firewall.cc o/ability.o
	$(CXX) $(CXXFLAGS) -c interface/firewall.cc

o/polarize.o: interface/polarize.cc o/ability.o
	$(CXX) $(CXXFLAGS) -c interface/polarize.cc

o/scan.o: interface/scan.cc o/ability.o
	$(CXX) $(CXXFLAGS) -c interface/scan.cc

o/link.o: interface/link.cc 
	$(CXX) $(CXXFLAGS) -c interface/link.cc

o/data.o: interface/data.cc o/link.o
	$(CXX) $(CXXFLAGS) -c interface/data.cc

o/virus.o: interface/virus.cc o/link.o
	$(CXX) $(CXXFLAGS) -c interface/virus.cc

o/player.o: interface/player.cc o/ability.o o/virus.o o/data.o
	$(CXX) $(CXXFLAGS) -c interface/player.cc

o/player-header.o: interface/player-header.cc o/player.o
	$(CXX) $(CXXFLAGS) -c interface/player-header.cc

o/board.o: interface/board.cc o/player-header.o o/link.o o/isubject.o o/iobserver.o
	$(CXX) $(CXXFLAGS) -c interface/board.cc

o/gui.o: interface/gui.cc o/observer.o o/board.o
	$(CXX) $(CXXFLAGS) -c interface/gui.cc
	
o/terminal.o: interface/terminal.cc o/gui.o o/board.o
	$(CXX) $(CXXFLAGS) -c interface/terminal.cc
	
o/graphic.o: interface/graphic.cc o/gui.o o/board.o
	$(CXX) $(CXXFLAGS) -c interface/graphic.cc
	
o/coords.o: coords.cc
	$(CXX) $(CXXFLAGS) -c coords.cc

main.o: main.cc o/board.o o/ability.o o/data.o o/virus.o o/display.o o/graphic.o o/player.o o/coords.o
	$(CXX) $(CXXFLAGS) -c main.cc

clean:
	rm -f $(EXEC) *.o o/*.gcm
	rm -rf gcm.cache