CXX = g++-14 -std=c++20 -fmodules-ts
CXXFLAGS = -Wall -Werror -g
HEADERFLAGS = -c -x c++-system-header

EXEC = exec

INTERFACE_OBJS = o/ability.o o/o/board.o o/o/data.o o/o/graphic.o o/o/gui.o o/o/iobserver.o o/isubject.o o/link.o o/player.o o/player-header.o o/terminal.o o/virus.o o/coords.o 

IMPL_OBJS = o/board-impl.o o/data-impl.o o/graphic-impl.o o/player-impl.o o/player-header-impl.o o/virus-impl.o 

HARNESS_OBJ = o/main.o

HEADERS = iostream vector algorithm fstream map string

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

o/coords.o: interface/coords.cc
	$(CXX) $(CXXFLAGS) -c interface/coords.cc

o/ability.o: interface/ability.cc o/coords.o
	$(CXX) $(CXXFLAGS) -c interface/ability.cc

o/link-boost.o: interface/abilities/link-boost.cc o/ability.o
	$(CXX) $(CXXFLAGS) -c interface/abilities/link-boost.cc

o/download.o: interface/abilities/download.cc o/ability.o o/coords.o
	$(CXX) $(CXXFLAGS) -c interface/abilities/download.cc

o/firewall.o: interface/abilities/firewall.cc o/ability.o o/coords.o
	$(CXX) $(CXXFLAGS) -c interface/abilities/firewall.cc

o/polarize.o: interface/abilities/polarize.cc o/ability.o o/coords.o
	$(CXX) $(CXXFLAGS) -c interface/abilities/polarize.cc

o/scan.o: interface/abilities/scan.cc o/ability.o o/coords.o
	$(CXX) $(CXXFLAGS) -c interface/abilities/scan.cc

o/two-sum.o: interface/abilities/two-sum.cc o/ability.o o/coords.o
	$(CXX) $(CXXFLAGS) -c interface/abilities/two-sum.cc

o/double-down.o: interface/abilities/double-down.cc o/ability.o o/coords.o
	$(CXX) $(CXXFLAGS) -c interface/abilities/double-down.cc

o/small-swap.o: interface/abilities/small-swap.cc o/ability.o o/coords.o
	$(CXX) $(CXXFLAGS) -c interface/abilities/small-swap.cc

o/link.o: interface/abilities/link.cc o/coords.o
	$(CXX) $(CXXFLAGS) -c interface/abilities/link.cc

o/data.o: interface/data.cc o/link.o o/coords.o
	$(CXX) $(CXXFLAGS) -c interface/data.cc

o/virus.o: interface/virus.cc o/link.o o/coords.o
	$(CXX) $(CXXFLAGS) -c interface/virus.cc

o/player.o: interface/player.cc o/ability.o o/virus.o o/data.o
	$(CXX) $(CXXFLAGS) -c interface/player.cc

o/player-header.o: interface/player-header.cc o/player.o
	$(CXX) $(CXXFLAGS) -c interface/player-header.cc

o/board.o: interface/board.cc o/player-header.o o/link.o o/isubject.o o/iobserver.o o/coords.o
	$(CXX) $(CXXFLAGS) -c interface/board.cc

o/gui.o: interface/gui.cc o/observer.o o/board.o
	$(CXX) $(CXXFLAGS) -c interface/gui.cc
	
o/terminal.o: interface/terminal.cc o/gui.o o/board.o o/player-header.o
	$(CXX) $(CXXFLAGS) -c interface/terminal.cc
	
o/graphic.o: interface/graphic.cc o/gui.o o/board.o
	$(CXX) $(CXXFLAGS) -c interface/graphic.cc

o/display.o: interface/display.cc o/board.o o/gui.o
	$(CXX) $(CXXFLAGS) -c interface/display.cc

o/coords-impl.o: interface/coords-impl.cc
	$(CXX) $(CXXFLAGS) -c interface/coords-impl.cc

o/board-impl.o: impl/board-impl.cc o/isubject.o o/iobserver.o o/link.o o/player-header.o o/coords.o
	$(CXX) $(CXXFLAGS) -c impl/board-impl.cc

o/data-impl.o: impl/data-impl.cc o/coords.o
	$(CXX) $(CXXFLAGS) -c impl/data-impl.cc

o/graphic-impl.o: impl/graphic-impl.cc o/board.o
	$(CXX) $(CXXFLAGS) -c impl/graphic-impl.cc

o/link-impl.o: impl/link-impl.cc o/coords.o
	$(CXX) $(CXXFLAGS) -c impl/link-impl.cc

o/player-header-impl.o: impl/player-header-impl.cc o/player.o o/coords.o
	$(CXX) $(CXXFLAGS) -c impl/player-header-impl.cc

o/player-impl.o: impl/player-impl.cc o/link-boost.o o/firewall.o o/polarize.o o/scan.o o/small-swap.o o/two-sum.o o/double-down.o o/download.o o/virus.o o/data.o
	$(CXX) $(CXXFLAGS) -c impl/board-impl.cc

o/virus-impl.o: impl/virus-impl.cc o/coords.o
	$(CXX) $(CXXFLAGS) -c impl/virus-impl.cc

o/terminal-impl.o: impl/terminal-impl.cc o/board.o o/gui.o o/player-header.o
	$(CXX) $(CXXFLAGS) -c impl/terminal-impl.cc

o/display-impl.o: impl/display-impl.cc o/board.o o/gui.o
	$(CXX) $(CXXFLAGS) -c impl/display-impl.cc

o/download-impl.o: impl/abilities/download-impl.cc o/coords.o o/player.o p/board.o
	$(CXX) $(CXXFLAGS) -c impl/download-impl.cc

o/firewall-impl.o: impl/abilities/firewall-impl.cc o/coords.o o/player.o p/board.o
	$(CXX) $(CXXFLAGS) -c impl/firewall-impl.cc

o/link-boost-impl.o: impl/abilities/link-boost-impl.cc o/coords.o o/player.o p/board.o
	$(CXX) $(CXXFLAGS) -c impl/link-boost-impl.cc

o/polarize-impl.o: impl/abilities/polarize-impl.cc o/coords.o o/player.o p/board.o
	$(CXX) $(CXXFLAGS) -c impl/polarize-impl.cc

o/scan-impl.o: impl/abilities/scan-impl.cc o/coords.o o/player.o p/board.o
	$(CXX) $(CXXFLAGS) -c impl/scan-impl.cc

o/two-sum-impl.o: impl/abilities/two-sum-impl.cc o/coords.o o/player.o p/board.o
	$(CXX) $(CXXFLAGS) -c impl/two-sum-impl.cc

o/double-down-impl.o: impl/abilities/double-down-impl.cc o/coords.o o/player.o p/board.o
	$(CXX) $(CXXFLAGS) -c impl/double-down-impl.cc

o/small-swap-impl.o: impl/abilities/small-swap-impl.cc o/coords.o o/player.o p/board.o
	$(CXX) $(CXXFLAGS) -c impl/small-swap-impl.cc
	
main.o: main.cc o/board.o o/ability.o o/data.o o/virus.o o/display.o o/graphic.o o/player.o o/coords.o
	$(CXX) $(CXXFLAGS) -c main.cc

clean:
	rm -f $(EXEC) *.o o/*.gcm
	rm -rf gcm.cache
	