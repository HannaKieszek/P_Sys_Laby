OUTDIR=build9
SRCDIR=laboratorium9
CC=gcc
TARGET=$(OUTDIR)/plik
SRC=$(wildcard $(SRCDIR)/*.c)
OBJ=$(patsubst $(SRCDIR)/%.c, $(OUTDIR)/%.o, $(SRC))

all: $(TARGET)

clean:
	rm -rf $(OUTTDIR)

$(TARGET): $(OBJ)
	$(CC) $^ -o $@

$(OUTDIR)/%.o: $(SRCDIR)/%.c | $(OUTDIR)
	$(CC) -c $< -o $@

$(OUTDIR):
	mkdir $@
