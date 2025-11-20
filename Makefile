CXX = g++-14 -std=c++20 -fmodules-ts
CXXFLAGS = -Wall -Werror -g
HEADERFLAGS = -c -x c++-system-header

EXEC = a4q2

INTERFACE_OBJS = asciiart.o blank.o blinking-box.o decorator.o filled-box.o mask-box.o moving-box.o studio.o

IMPL_OBJS = asciiart-impl.o blank-impl.o blinking-box-impl.o decorator-impl.o filled-box-impl.o mask-box-impl.o moving-box-impl.o studio-impl.o

HARNESS_OBJ = a4q2.o

HEADERS = iostream string

ALL_OBJS = $(INTERFACE_OBJS) $(IMPL_OBJS) $(HARNESS_OBJ)

$(EXEC): headers $(ALL_OBJS)
	$(CXX) $(CXXFLAGS) $(ALL_OBJS) -o $(EXEC)

.PHONY: headers clean

headers:
	$(CXX) $(HEADERFLAGS) $(HEADERS)

$(ALL_OBJS): headers

asciiart.o: asciiart.cc
	$(CXX) $(CXXFLAGS) -c asciiart.cc

studio.o: studio.cc asciiart.o
	$(CXX) $(CXXFLAGS) -c studio.cc

blank.o: blank.cc asciiart.o
	$(CXX) $(CXXFLAGS) -c blank.cc

decorator.o: decorator.cc asciiart.o
	$(CXX) $(CXXFLAGS) -c decorator.cc

blinking-box.o: blinking-box.cc decorator.o
	$(CXX) $(CXXFLAGS) -c blinking-box.cc

filled-box.o: filled-box.cc decorator.o
	$(CXX) $(CXXFLAGS) -c filled-box.cc

mask-box.o: mask-box.cc decorator.o
	$(CXX) $(CXXFLAGS) -c mask-box.cc

moving-box.o: moving-box.cc decorator.o
	$(CXX) $(CXXFLAGS) -c moving-box.cc

asciiart-impl.o: asciiart-impl.cc asciiart.o
	$(CXX) $(CXXFLAGS) -c asciiart-impl.cc

studio-impl.o: studio-impl.cc studio.o
	$(CXX) $(CXXFLAGS) -c studio-impl.cc

blank-impl.o: blank-impl.cc blank.o
	$(CXX) $(CXXFLAGS) -c blank-impl.cc

decorator-impl.o: decorator-impl.cc decorator.o
	$(CXX) $(CXXFLAGS) -c decorator-impl.cc

blinking-box-impl.o: blinking-box-impl.cc blinking-box.o
	$(CXX) $(CXXFLAGS) -c blinking-box-impl.cc

filled-box-impl.o: filled-box-impl.cc filled-box.o
	$(CXX) $(CXXFLAGS) -c filled-box-impl.cc

mask-box-impl.o: mask-box-impl.cc mask-box.o
	$(CXX) $(CXXFLAGS) -c mask-box-impl.cc

moving-box-impl.o: moving-box-impl.cc moving-box.o
	$(CXX) $(CXXFLAGS) -c moving-box-impl.cc

a4q2.o: a4q2.cc asciiart.o blank.o studio.o blinking-box.o filled-box.o mask-box.o moving-box.o 
	$(CXX) $(CXXFLAGS) -c a4q2.cc

clean:
	rm -f $(EXEC) *.o *.gcm
	rm -rf gcm.cache