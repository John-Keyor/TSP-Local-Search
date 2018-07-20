$(info **********************************  COMPILING **********************************)
CXX = g++ -I ~/lib/include
## add -pg to LDFLAGS and CFLAGS to generate gmon.out for gprof
LDFLAGS = -Wall # -ljpeg -lSDLmain -lSDL -lSDL_image -lSDL_ttf -pthread -lGLEW -lGLU \
	      # -lGL -lrt -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lboost_program_options \
          # -Wl,-rpath=~/lib -L ~/lib 
CFLAGS = -c -g -O3 -Wall -std=c++11
ODIR = build
TDIR = unitTests
SRCS = tsp_solver.cpp
OBJS_ = $(SRCS:.cpp=.o)
OBJS = $(addprefix $(ODIR)/, $(OBJS_)) 
default : local_search.out

## Dependancies go here
$(ODIR)/tsp_solver.o: src/tsp_solver.cpp

## Generate object files and executables
$(OBJS): $(ODIR)/%.o : src/%.cpp include/%.h
	$(CXX) $(CFLAGS) $< -o  $@

## Main Program
$(ODIR)/main.o : main.cpp $(foreach src, $(SRCS), src/$(src) include/$(src:.cpp=.h)) 
	$(CXX) $(CFLAGS) $< -o  $@

local_search.out : $(ODIR)/main.o $(OBJS)
	g++ $+ $(LDFLAGS) -o $@

## Delete objects and executables 
clean :
	rm -rf $(ODIR)/*.o project_blue_kangaroo.out 

######### UNIT TESTS ##########

## MST Test Program
#$(ODIR)/mst_test.o : mst_test.cpp src/tsp_solver.cpp
#	$(CXX) $(CFLAGS) $< -o  $@
