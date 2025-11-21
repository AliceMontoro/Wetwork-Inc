# --- Compilador e Flags ---
CC = gcc
# Flags de aviso e debug
CFLAGS = -Wall -Wextra -g
# Flags para gerar dependências automáticas (.d)
# Isso garante que se você mudar um .h, o .c correspondente recompila
DEPFLAGS = -MMD -MP

# --- Nome do Executável ---
TARGET = meu_programa

# --- Arquivos ---
# Pega todos os .c da pasta
SRCS = $(wildcard *.c)
# Define os objetos (.o) baseados nos nomes dos .c
OBJS = $(SRCS:.c=.o)
# Define os arquivos de dependência (.d)
DEPS = $(SRCS:.c=.d)

# --- Regras ---

all: $(TARGET)

# Linkagem (Cria o executável)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compilação (Gera os .o e os .d)
%.o: %.c
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

# Inclui as regras de dependência geradas automaticamente
# O '-' no início impede erro se os arquivos .d ainda não existirem
-include $(DEPS)

# Limpeza (agora apaga os .d também)
clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)

run: all
	./$(TARGET)