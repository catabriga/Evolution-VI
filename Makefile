CC = gcc
CXX = g++ -std=c++0x
INCLUDES = -I./
CFLAGS = -c -Wall $(INCLUDES)
LDFLAGS = 
LIBS =
SOURCES =	$(wildcard src/*.cpp) \
			$(wildcard Box2D/*/*.cpp) $(wildcard Box2D/*/*/*.cpp)
HEADERS =	
#OBJECTS = $(patsubst %.cpp,$(BUILDDIR)/%.o,$(notdir $(SOURCES)))
OBJECTS = $(patsubst %.cpp,%.o,$(SOURCES))
EXECUTABLE = Evolution-VI
BUILDDIR = obj
TARGETDIR = bin

all: directories $(SOURCES) $(EXECUTABLE)
debug: CC += -g
debug: CXX += -g
debug: directories $(SOURCES) $(EXECUTABLE)
release: CC += -O3
release: CXX += -O3
release: directories $(SOURCES) $(EXECUTABLE)
prof: CC += -pg
prof: CXX += -pg
prof: directories $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CXX) $(LDFLAGS) $(patsubst %.o,$(BUILDDIR)/%.o,$(notdir $(OBJECTS))) -o $(TARGETDIR)/$@ $(LIBS)

%.o : %.cpp	
	$(CXX) $(CFLAGS) $< -o $(BUILDDIR)/$(notdir $@)
	
directories:
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(TARGETDIR)

clean:
	rm -f $(TARGETDIR)/$(EXECUTABLE)
	rm -f *.o
	rm -f $(BUILDDIR)/*.o