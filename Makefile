CC = gcc
CFLAGS = -I$(LDIR) -Wall

.PHONY: all clean

SDIR = src
ODIR = $(SDIR)/obj
LDIR = lib

LIBS = -lm

FRACTAL_OBJ = main fractal draw pile

FOBJ = $(patsubst %,$(ODIR)/%.o,$(FRACTAL_OBJ))

EXE = main
NAMES = $(EXE)

run: all
	echo "Executing program...\n" && ./$(EXE) && echo "\nConverting image..." && convert fractal.pbm fractal.png && rm fractal.pbm

all: $(NAMES)

$(EXE) : $(FOBJ)
	$(CC) -o $@ $^ $(LIBS)

$(ODIR):
	mkdir -p $@

SRC = main
LIB = main fractal draw pile
$(ODIR)/$(SRC).o : $(SDIR)/$(SRC).c $(patsubst %,$(LDIR)/%.h, $(LIB)) | $(ODIR)
	$(CC) -c -o $@ $(patsubst $(ODIR)%.o,$(SDIR)%.c,$@) $(CFLAGS)

SRC = fractal
LIB = fractal main draw pile
$(ODIR)/$(SRC).o : $(SDIR)/$(SRC).c $(patsubst %,$(LDIR)/%.h, $(LIB)) | $(ODIR)
	$(CC) -c -o $@ $(patsubst $(ODIR)%.o,$(SDIR)%.c,$@) $(CFLAGS)

SRC = draw
LIB = draw main fractal pile
$(ODIR)/$(SRC).o : $(SDIR)/$(SRC).c $(patsubst %,$(LDIR)/%.h, $(LIB)) | $(ODIR)
	$(CC) -c -o $@ $(patsubst $(ODIR)%.o,$(SDIR)%.c,$@) $(CFLAGS)

SRC = pile
LIB = pile
$(ODIR)/$(SRC).o : $(SDIR)/$(SRC).c $(patsubst %,$(LDIR)/%.h, $(LIB)) | $(ODIR)
	$(CC) -c -o $@ $(patsubst $(ODIR)%.o,$(SDIR)%.c,$@) $(CFLAGS)

clean:
	rm -rf $(NAMES) $(ODIR)
