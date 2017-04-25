CC = gcc
CXX = g++ -std=c++0x
INCLUDES = -I./
CFLAGS = -c -Wall $(INCLUDES)
LDFLAGS =
LIBS = -lGL -lGLU -lglut -lX11
SOURCES =	$(wildcard src/*.cpp) $(wildcard src/*.c) \
			$(wildcard Box2D/*/*.cpp) $(wildcard Box2D/*/*/*.cpp)
HEADERS =
OBJECTS = $(patsubst %.cpp,$(BUILDDIR)/%.o,$(patsubst %.c,$(BUILDDIR)/%.o,$(SOURCES)))
EXECUTABLE = Evolution-VI
BUILDDIR = obj
TARGETDIR = bin

all: $(SOURCES) $(TARGETDIR)/$(EXECUTABLE)
debug: CC += -g
debug: CXX += -g
debug: $(SOURCES) $(TARGETDIR)/$(EXECUTABLE)
release: CC += -O3
release: CXX += -O3
release: $(SOURCES) $(TARGETDIR)/$(EXECUTABLE)
prof: CC += -pg
prof: CXX += -pg
prof: $(SOURCES) $(TARGETDIR)/$(EXECUTABLE)

$(TARGETDIR)/$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBS)

$(BUILDDIR)/%.o : %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CFLAGS) $< -o $@
	
$(BUILDDIR)/%.o : %.c
	@mkdir -p $(@D)
	$(CXX) $(CFLAGS) $< -o $@

clean:
	@rm -rf $(TARGETDIR)
	@rm -rf $(BUILDDIR)
