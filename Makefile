CXX = g++-14 -std=c++20 -fmodules-ts
CXXFLAGS = -Wall -Werror -g
HEADERFLAGS = -c -x c++-system-header

EXEC = exec

INTERFACE_OBJS = o/gameplay.o o/data.o o/graphic.o o/gui.o o/iobserver.o o/isubject.o o/link.o o/terminal.o o/virus.o o/coords.o 

IMPL_OBJS = o/data-impl.o o/graphic-impl.o o/virus-impl.o o/gameplay.o o/double-down-impl.o o/download-impl.o o/firewall-impl.o o/link-boost-impl.o o/polarize-impl.o  o/scan-impl.o o/small-swap-impl.o o/two-sum-impl.o

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

o/isubject.o: interface/isubject.cc o/iobserver.o
	$(CXX) $(CXXFLAGS) -c interface/isubject.cc

o/coords.o: interface/coords.cc
	$(CXX) $(CXXFLAGS) -c interface/coords.cc

o/link.o: interface/link.cc o/coords.o
	$(CXX) $(CXXFLAGS) -c interface/link.cc

o/virus.o: interface/virus.cc o/link.o o/coords.o
	$(CXX) $(CXXFLAGS) -c interface/virus.cc

o/gameplay.o: interface/gameplay.cc o/coords.o  o/link.o o/virus.o o/data.o o/coords.o 
	$(CXX) $(CXXFLAGS) -c interface/gameplay.cc

o/link-boost.o: interface/abilities/link-boost.cc o/gameplay.o o/link.o o/coords.o
	$(CXX) $(CXXFLAGS) -c interface/abilities/link-boost.cc

o/download.o: interface/abilities/download.cc o/gameplay.o o/link.o o/coords.o
	$(CXX) $(CXXFLAGS) -c interface/abilities/download.cc

o/firewall.o: interface/abilities/firewall.cc o/gameplay.o o/link.o o/coords.o
	$(CXX) $(CXXFLAGS) -c interface/abilities/firewall.cc

o/polarize.o: interface/abilities/polarize.cc o/gameplay.o o/link.o o/coords.o
	$(CXX) $(CXXFLAGS) -c interface/abilities/polarize.cc

o/scan.o: interface/abilities/scan.cc o/gameplay.o o/link.o o/coords.o
	$(CXX) $(CXXFLAGS) -c interface/abilities/scan.cc

o/two-sum.o: interface/abilities/two-sum.cc o/gameplay.o o/link.o o/coords.o
	$(CXX) $(CXXFLAGS) -c interface/abilities/two-sum.cc

o/double-down.o: interface/abilities/double-down.cc o/gameplay.o o/link.o o/coords.o
	$(CXX) $(CXXFLAGS) -c interface/abilities/double-down.cc

o/small-swap.o: interface/abilities/small-swap.cc o/gameplay.o o/link.o o/coords.o
	$(CXX) $(CXXFLAGS) -c interface/abilities/small-swap.cc

o/data.o: interface/data.cc o/link.o o/coords.o
	$(CXX) $(CXXFLAGS) -c interface/data.cc


o/gui.o: interface/gui.cc o/iobserver.o o/gameplay.o
o	$(CXX) $(CXXFLAGS) -c interface/gui.cc
	
o/terminal.o: interface/terminal.cc o/gui.o o/gameplay.o o/iobserver.o
	$(CXX) $(CXXFLAGS) -c interface/terminal.cc
	
o/graphic.o: interface/graphic.cc o/gui.o o/gameplay.o	
	$(CXX) $(CXXFLAGS) -c interface/graphic.cc

o/coords-impl.o: interface/coords-impl.cc o/gameplay.o	
	$(CXX) $(CXXFLAGS) -c interface/coords-impl.cc

o/gameplay-impl.o: impl/board-impl.cc o/isubject.o o/iobserver.o o/link.o o/player-header.o o/coords.o o/virus.o o/data.o
	$(CXX) $(CXXFLAGS) -c impl/gameplay-impl.cc

o/data-impl.o: impl/data-impl.cc o/coords.o o/gameplay.o
	$(CXX) $(CXXFLAGS) -c impl/data-impl.cc

.oo/graphic-impl.o: impl/graphic-impl.cc o/gameplay.o o/iobserver.o
	$(CXX) $(CXXFLAGS) -c impl/graphic-impl.cc

o/link-impl.o: impl/link-impl.cc o/coords	
	$(CXX) $(CXXFLAGS) -c impl/link-impl.cc	

o/virus-impl.o: impl/virus-impl.cc o/coords.o
	$(CXX) $(CXXFLAGS) -c impl/virus-impl.cc

o/terminal-impl.o: impl/terminal-impl.cc o/board.o o/gameplay.oplayer-header.o o/iobserver.o
	$(CXX) $(CXXFLAGS) -c impl/terminal-impl.cc

o/download-impl.o: impl/abilities/download-impl.cc o/coords.o o/player.o o/board.o o/link.o
	$(CXX) $(CXXFLAGS) -c impl/download-impl.cc

o/firewall-impl.o: impl/abilities/firewall-impl.cc o/coords.o o/gameplay.o o/link.o
	$(CXX) $(CXXFLAGS) -c impl/firewall-impl.cc

o/link-boost-impl.o: impl/abilities/link-boost-impl.cc o/coords.o o/gameplay.o o/link.o
	$(CXX) $(CXXFLAGS) -c impl/link-boost-impl.cc

o/polarize-impl.o: impl/abilities/polarize-impl.cc o/coords.o o/gameplay.o o/link.o
	$(CXX) $(CXXFLAGS) -c impl/polarize-impl.cc

o/scan-impl.o: impl/abilities/scan-impl.cc o/coords.o o/gameplay.o o/link.o
	$(CXX) $(CXXFLAGS) -c impl/scan-impl.cc

o/two-sum-impl.o: impl/abilities/two-sum-impl.cc o/coords.o o/gameplay.o o/link.o
	$(CXX) $(CXXFLAGS) -c impl/two-sum-impl.cc

o/double-down-impl.o: impl/abilities/double-down-impl.cc o/coords.o o/gameplay.o o/link.o
	$(CXX) $(CXXFLAGS) -c impl/double-down-impl.cc

o/small-swap-impl.o: impl/abilities/small-swap-impl.cc o/coords.o o/gameplay.o o/link.o
	$(CXX) $(CXXFLAGS) -c impl/small-swap-impl.cc
	
main.o: main.cc o/data.o o/virus.o o/display.o o/graphic.o o/gameplay.o o/coords.o
	$(CXX) $(CXXFLAGS) -c main.cc

clean:
	rm -f $(EXEC) *.o o/*.gcm
	rm -rf gcm.cache
	