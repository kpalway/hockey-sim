
INCLUDES = -I/usr/include/GL -I. -I/u3/kpalway/bin/fltk-1.3.4-2/ -I/u3/kpalway/cs779/project/mpfr/include -IXext -I/u3/kpalway/cs779/project/eigen

CC = g++

CFLAGS = -Wall -g -std=c++11 -funroll-loops -ffast-math -O3
#LIBS = -L/u3/kpalway/bin/fltk-1.3.4-2/lib/ -lfltk -lGL -lpng -lm -g -lfltk_gl -lXext -lXfixes -lX11 -ldl -lXrender -lXcursor -lXinerama

%.o: %.cpp Makefile
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@
	#$(CC) -c -MMD -MT $*.d $(CFLAGS) $(INCLUDES) $< -o $@

TARGET = hockey-sim
OFILES = main.o Player.o PlayerDatabase.o Team.o TeamDatabase.o IndividualStats.o OnIceStats.o BioStats.o CSV.o Game.o Event.o ShotAttempt.o Shot.o Goal.o PeriodEnd.o LineChange.o Penalty.o

CPPFILES = $(OFILES:.o=.cpp)
DFILES = $(OFILES:.o=.d)

$(TARGET): $(OFILES)
	$(CC) -o $(TARGET) -g $(OFILES)
#	$(CC) -o $(TARGET) -g $(OFILES) $(LIBS)

clean:
	rm -f *.o $(TARGET) *.d ../$(TARGET)

-include $(DFILES)
