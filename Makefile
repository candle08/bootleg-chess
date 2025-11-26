CXX = g++-14 -std=c++20 -fmodules-ts
CXXFLAGS = -Wall -Werror -g

HEADERFLAGS = -c -x c++-system-header 

EXEC = exec

INTERFACE_OBJS = gameplay.o data.o graphic.o gui.o observer.o link.o terminal.o virus.o coords.o xwindow.o

IMPL_OBJS = ability-impl.o board-impl.o data-impl.o graphic-impl.o player-impl.o player-header-impl.o virus-impl.o double-down-impl.o download-impl.o firewall-impl.o link-boost-impl.o polarize-impl.o scan-impl.o small-swap-impl.o two-sum-impl.o xwindow-impl.o link-impl.o terminal-impl.o

HARNESS_OBJ = main.o

HEADERS = iostream vector algorithm fstream map string cstdlib

%: %.o ;

ALL_OBJS = $(INTERFACE_OBJS) $(IMPL_OBJS) $(HARNESS_OBJ) 

$(EXEC): headers $(ALL_OBJS)
	$(CXX) $(CXXFLAGS) $(ALL_OBJS) -o $(EXEC) -lX11

.PHONY: headers clean

headers:
	$(CXX) $(HEADERFLAGS) $(HEADERS) 

$(ALL_OBJS): headers

observer.o: interface/observer.cc
	$(CXX) $(CXXFLAGS) -c interface/observer.cc

coords.o: interface/coords.cc
	$(CXX) $(CXXFLAGS) -c interface/coords.cc

link.o: interface/link.cc coords.o
	$(CXX) $(CXXFLAGS) -c interface/link.cc

virus.o: interface/virus.cc link.o coords.o
	$(CXX) $(CXXFLAGS) -c interface/virus.cc

gameplay.o: interface/gameplay.cc coords.o link.o virus.o data.o coords.o observer.o
	$(CXX) $(CXXFLAGS) -c interface/gameplay.cc

data.o: interface/data.cc link.o coords.o
	$(CXX) $(CXXFLAGS) -c interface/data.cc

gui.o: interface/gui.cc observer.o gameplay.o
	$(CXX) $(CXXFLAGS) -c interface/gui.cc
	
terminal.o: interface/terminal.cc gui.o gameplay.o observer.o
	$(CXX) $(CXXFLAGS) -c interface/terminal.cc
	
xwindow.o: interface/xwindow.cc 
	$(CXX) $(CXXFLAGS) -c interface/xwindow.cc

graphic.o: interface/graphic.cc gui.o gameplay.o xwindow.o
	$(CXX) $(CXXFLAGS) -c interface/graphic.cc

data-impl.o: impl/data-impl.cc coords.o gameplay.o link.o
	$(CXX) $(CXXFLAGS) -c impl/data-impl.cc

graphic-impl.o: impl/graphic-impl.cc gameplay.o observer.o xwindow.o
	$(CXX) $(CXXFLAGS) -c impl/graphic-impl.cc

link-impl.o: impl/link-impl.cc coords	
	$(CXX) $(CXXFLAGS) -c impl/link-impl.cc	

player-impl.o: impl/player-impl.cc virus.o data.o
	$(CXX) $(CXXFLAGS) -c impl/player-impl.cc
	
board-impl.o: impl/board-impl.cc observer.o link.o gameplay.o coords.o
	$(CXX) $(CXXFLAGS) -c impl/board-impl.cc

player-header-impl.o: impl/player-header-impl.cc gameplay.o coords.o
	$(CXX) $(CXXFLAGS) -c impl/player-header-impl.cc

virus-impl.o: impl/virus-impl.cc coords.o link.o
	$(CXX) $(CXXFLAGS) -c impl/virus-impl.cc

terminal-impl.o: impl/terminal-impl.cc gameplay.o observer.o
	$(CXX) $(CXXFLAGS) -c impl/terminal-impl.cc

ability-impl.o: impl/ability-impl.cc
	$(CXX) $(CXXFLAGS) -c impl/ability-impl.cc

download-impl.o: impl/abilities/download-impl.cc coords.o link.o gameplay.o
	$(CXX) $(CXXFLAGS) -c impl/abilities/download-impl.cc

firewall-impl.o: impl/abilities/firewall-impl.cc coords.o gameplay.o link.o gameplay.o
	$(CXX) $(CXXFLAGS) -c impl/abilities/firewall-impl.cc

link-boost-impl.o: impl/abilities/link-boost-impl.cc coords.o gameplay.o link.o gameplay.o
	$(CXX) $(CXXFLAGS) -c impl/abilities/link-boost-impl.cc

polarize-impl.o: impl/abilities/polarize-impl.cc coords.o gameplay.o link.o data.o virus.o gameplay.o
	$(CXX) $(CXXFLAGS) -c impl/abilities/polarize-impl.cc

scan-impl.o: impl/abilities/scan-impl.cc coords.o gameplay.o link.o gameplay.o
	$(CXX) $(CXXFLAGS) -c impl/abilities/scan-impl.cc

two-sum-impl.o: impl/abilities/two-sum-impl.cc coords.o gameplay.o link.o gameplay.o
	$(CXX) $(CXXFLAGS) -c impl/abilities/two-sum-impl.cc

double-down-impl.o: impl/abilities/double-down-impl.cc coords.o gameplay.o link.o gameplay.o
	$(CXX) $(CXXFLAGS) -c impl/abilities/double-down-impl.cc

small-swap-impl.o: impl/abilities/small-swap-impl.cc coords.o gameplay.o link.o gameplay.o
	$(CXX) $(CXXFLAGS) -c impl/abilities/small-swap-impl.cc
	
xwindow-impl.o: impl/xwindow-impl.cc xwindow.o
	$(CXX) $(CXXFLAGS) -c impl/xwindow-impl.cc

main.o: main.cc data.o virus.o graphic.o gameplay.o coords.o terminal.o
	$(CXX) $(CXXFLAGS) -c main.cc

clean:
	rm -f $(EXEC) *.o *.gcm
	rm -rf gcm.cache
